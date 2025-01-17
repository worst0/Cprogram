/*************************************************************************
	> File Name: 22.ac.cpp
	> Author: wei 
	> Mail: 1931248856@qq.com
	> Created Time: 2020年10月17日 星期六 19时37分37秒
 ************************************************************************/

#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <ctime>
using namespace std;
#define BASE 26
#define BEGIN_LETTER 'a'
typedef struct Node{
    int flag;
    struct Node *next[BASE], *fail;
} Node;

typedef struct Queue {
    Node **data;
    int head, tail, size;
} Queue;

Queue *init_queue(int n) {
    Queue *q = (Queue *)calloc(sizeof(Queue), 1);
    q->data = (Node **)malloc(sizeof(Node *) * n);
    q->head = q->tail = 0;
    q->size = n;
    return q;
}

Node *front(Queue *q) {
    return q->data[q->head];
}

int empty(Queue *q) {
    return q->head == q->tail;
}

int push(Queue *q, Node *node) {
    q->data[q->tail++] = node;
    return 1;
}

int pop(Queue *q) {
    if (empty(q)) return 0;
    q->head++;
    return 1;
}

void clear_queue(Queue *q) {
    if (q == NULL) return ;
    free(q->data);
    free(q);
    return ;
}

Node *getNewNode() {
    Node *p = (Node *)calloc(sizeof(Node), 1);
    return p;
}

int insert(Node *root, const char *str) {
    int cnt = 0;
    Node *p = root;
    for (int i = 0; str[i]; ++i) {
        int ind = str[i] - BEGIN_LETTER;
        if (p->next[ind] == NULL) p->next[ind] = getNewNode(), cnt += 1;
        p = p->next[ind];
    }
    p->flag = 1;
    return cnt;
}

void clear(Node *root) {
    if (root == NULL) return ; 
    for (int i = 0; i < BASE; ++i) {
        clear(root->next[i]);
    }
    free(root);
    return ;
}

void build_ac(Node *root, int n) {
    Queue *q = init_queue(n + 10);
    root->fail = NULL;
    push(q, root);
    while (!empty(q)) {
        Node *now_node = front(q);
        pop(q);
        for (int i = 0; i < BASE; ++i) {
            if (now_node->next[i] == NULL) continue;
            Node *p = now_node->fail;
            while (p && p->next[i] == NULL) p = p->fail;
            if (p == NULL) now_node->next[i]->fail = root;
            else now_node->next[i]->fail = p->next[i];
            push(q, now_node->next[i]);
        }
    }
    return ;
}

int match(Node *root, const char *str) {
    int cnt = 0;
    Node *p = root;
    for (int i = 0; str[i]; ++i) {
        int ind = str[i] - BEGIN_LETTER;
        while (p && p->next[ind] == NULL) p = p->fail;
        if (p == NULL) p = root;
        else p = p->next[ind];
        Node *q = p;
        while (q) cnt += q->flag, q = q->fail;
    }
    return cnt;
}

int main() {
    Node *root = getNewNode();
    int n, cnt = 0;
    char str[1000];
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        scanf("%s", str);
        cnt += insert(root, str);
    } 
    // build ac
    build_ac(root, cnt);
    scanf("%s", str);
    //match ac
    printf("match word cnt : %d\n", match(root, str));
    return 0;
}
