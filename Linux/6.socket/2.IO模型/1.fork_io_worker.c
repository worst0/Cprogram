/*************************************************************************
	> File Name: 1.fork_io_worker.c
	> Author: weier 
	> Mail: 1931248856@qq.com 
	> Created Time: Wed 12 Aug 2020 02:36:14 PM CST
 ************************************************************************/

#include "head.h"

void worker(int fd, struct User *user) {
    while (1) {
        char buff[512] = {0};
        if ((recv(fd, buff, sizeof(buff), 0)) <= 0) {
            break;
        }
        printf(GREEN"<%s>"NONE" : %s!\n", user->name, buff);
    }
    close(fd);
    DBG(GREEN"<%s>"NONE" : logout!\n", user->name);
    return ;
}

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usgae : %s port!\n", argv[0]);
        exit(1);
    }
    int server_listen, sockfd, port;
    port = atoi(argv[1]);
    
    if ((server_listen = socket_create(port)) < 0) {
        perror("server_listen()");
        exit(1);
    }

    pid_t pid;

    while (1) {
        struct sockaddr_in client;
        struct User user;

        bzero(&user, sizeof(user));
        
        //sizeof是操作符，类似于+-×/
        socklen_t len = sizeof(client);
        if ((sockfd = accept(server_listen, (struct sockaddr *)&client, &len)) < 0)  {
            perror("accept()");
            exit(1);
        }
        get_info("../../common/names", &user, inet_ntoa(client.sin_addr)); 
        if ((pid = fork()) < 0) {
            perror("fork()");
            exit(1);
        }

        if (pid == 0) {
            worker(sockfd, &user);
            exit(0);
        }
    }

    return 0;
}
