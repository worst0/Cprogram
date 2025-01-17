/*************************************************************************
> File Name: test.c
> Author: weier 
> Mail: 1931248856@qq.com 
> Created Time: Wed 12 Aug 2020 04:43:41 PM CST
************************************************************************/

#include "head.h"
#include "thread_pool.h"

int epollfd;

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage : %s port!\n", argv[0]);
        exit(1);
    }
    int server_listen, sockfd, port;
    ssize_t nrecv;
    
    //创建线程
    pthread_t tid[THREADNUM];
    struct task_queue taskQueue = *task_queue_init(&taskQueue, MAX);
    
    for (int i = 0; i < THREADNUM; ++i) {
        pthread_create(&tid[i], NULL, thread_run, (void *)&taskQueue);
    }

    // 0 有问题,fd自动分配是尽可能小的
    int fd[MAXUSER] = {0};
    port = atoi(argv[1]);
    if ((server_listen = socket_create(port)) < 0) {
        perror("socket_create()");
        exit(1);
    }

    //epoll实例， ->反应堆
    if ((epollfd = epoll_create(1)) < 0) {
        perror("epoll_create()");
        exit(1);
    }

    taskQueue.epollfd = epollfd;
    struct epoll_event ev, events[MAX];

    ev.data.fd = server_listen;
    ev.events = EPOLLIN;

    if (epoll_ctl(epollfd, EPOLL_CTL_ADD, server_listen, &ev) < 0) {
        perror("epoll_ctl(): server_listen");
        exit(1);
    }

    while (1) {
        int nfds = epoll_wait(epollfd, events, MAX, -1);
        if (nfds < 0) {
            perror("epoll_wait");
            exit(1);
        }
        sleep(1);
        for (int i = 0; i < nfds; ++i) {
            if (events[i].data.fd == server_listen  && (events[i].events & EPOLLIN)) {
                if ((sockfd = accept(server_listen, NULL, NULL)) < 0) {
                    perror("accept()");
                    exit(1);

                }
                fd[sockfd] = sockfd;
                ev.events = EPOLLIN | EPOLLET;
                ev.data.fd = sockfd;
                if (epoll_ctl(epollfd, EPOLL_CTL_ADD, sockfd, &ev) < 0) {
                    perror("epoll_ctl(): add");
                    exit(1);
                }
            } else {
                if (events[i].events & EPOLLIN) {
                    DBG(YELLOW"<main>"NONE " : push %d\n", events[i].data.fd);
                    task_queue_push(&taskQueue, events[i].data.fd);
                } 
            }
        }
    }

    close(server_listen);
    return 0;
}
