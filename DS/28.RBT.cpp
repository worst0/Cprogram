/*************************************************************************
	> File Name: 28.RBT.cpp
	> Author: wei 
	> Mail: 1931248856@qq.com
	> Created Time: 2020年10月24日 星期六 16时34分45秒
 ************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define RED 0
#define BLACK 1
#define DOUBLE_BLACK 2

typedef struct Node {
    int key, color; // 0 red, 1 black, 2 double black;
    struct Node *lchild, *rchild;
} Node;

Node _NIL, * const NIL = &_NIL;

// 属性        构造
__attribute__((constructor))
void init_NIL() {
    NIL->key = 0;
    NIL->lchild = NIL->rchild = NIL;
    NIL->color = BLACK;
    return ;
}

Node *getNewNode(int key) {
    Node *p = (Node *)malloc(sizeof(Node));
    p->key = key;
    p->lchild = p->rchild = NIL;
    p->color = RED;
    return p;
}

int hasRedChild(Node *root) {
    return root->lchild->color == RED || root->rchild->color == RED;
}

Node *left_rotate(Node *root) {
    Node *temp = root->rchild;
    root->rchild = temp->lchild;
    temp->lchild = root;
    return temp;
}

Node *right_rotate(Node *root) {
    Node *temp = root->lchild;
    root->lchild = temp->rchild;
    temp->rchild = root;
    return temp;
}

Node *insert_maintain(Node *root) {
    if (!hasRedChild(root)) return root;  
    if (root->lchild->color == RED && root->rchild->color == RED) {
        if (!hasRedChild(root->lchild) && !hasRedChild(root->rchild)) return root;
        goto insert_end;
        /*
        root->color = RED;
        root->lchild->color = root->rchild->color = BLACK;
        return root;
        */
    }
    if (root->lchild->color == RED) {
        if (!hasRedChild(root->lchild)) return root;
        if (root->lchild->rchild->color == RED) {
            root->lchild = left_rotate(root->lchild);
        }
        root = right_rotate(root);
    } else {
        if (!hasRedChild(root->rchild)) return root;
        if (root->rchild->lchild->color == RED) {
            root->rchild = right_rotate(root->rchild);
        }
        root = left_rotate(root);
    }
insert_end:
    root->color = RED;
    root->lchild->color = root->rchild->color = BLACK;
    return root;
}


Node *__insert(Node *root, int key) {
    if (root == NIL) return getNewNode(key);
    if (root->key == key) return root;
    if (root->key > key) root->lchild = __insert(root->lchild, key);
    else root->rchild = __insert(root->rchild, key);
    return insert_maintain(root);
}

Node *insert(Node *root, int key) {
    root = __insert(root, key);
    root->color = BLACK;
    return root;
}

Node *perdecessor(Node *root) {
    Node *temp = root->lchild;
    while (temp->rchild != NIL) temp = temp->rchild;
    return temp;
}

Node *erase_maintain(Node *root) {
    if (root->lchild->color != DOUBLE_BLACK && root->rchild->color != DOUBLE_BLACK) return root; 
    if (root->lchild->color == DOUBLE_BLACK) {
        if (root->rchild->color == RED) {
            root->color = RED;
            //lchild?
            root->rchild->color = BLACK;
            root = left_rotate(root);
            root->lchild = erase_maintain(root->lchild);
            return root;
        }
        if (!hasRedChild(root->rchild)) {
            root->color += 1;
            root->lchild->color -= 1;
            root->rchild->color -= 1;
            return root;
        }
        if (root->rchild->rchild->color != RED) {
            //小右旋
            root->rchild->lchild->color = BLACK;
            root->rchild->color = RED;
            root->rchild = right_rotate(root->rchild);
        }
        //大左旋
        root->rchild->color = root->color;
        root->lchild->color -= 1;
        root = left_rotate(root);
        root->lchild->color = root->rchild->color = BLACK;
    } else {
        if (root->lchild->color == RED) {
            root->color = RED;
            //lchild?
            root->lchild->color = BLACK;
            root = right_rotate(root);
            root->rchild = erase_maintain(root->rchild);
            return root;
        }    
        if (!hasRedChild(root->lchild)) {
            root->color += 1;
            root->lchild->color -= 1;
            root->rchild->color -= 1;
            return root;
        }
        //l?
        //不等价 if (root->lchild->rchild->color == RED);
        //lr
        if (root->lchild->lchild->color != RED) {
            //小左旋
            root->lchild->rchild->color = BLACK;
            root->lchild->color = RED;
            root->lchild = left_rotate(root->lchild);
        }
        //大右旋
        root->lchild->color = root->color;
        root->rchild->color -= 1;
        root = right_rotate(root);
        root->lchild->color = root->rchild->color = BLACK;
    }   
    return root;
}

Node *__erase(Node *root,int key) {
    if (root == NIL) return root;
    if (root->key > key) {
        root->lchild = __erase(root->lchild, key);
    } else if (root->key < key) {
        root->rchild = __erase(root->rchild, key);
    } else {
        //度为1 或 0
        if (root->lchild == NIL || root->rchild == NIL) {
            Node *temp = root->lchild == NIL ? root->rchild : root->lchild;
            // 如何处理 NIL变双重黑
            temp->color += root->color;
            free(root);
            return temp;
        } else {
            Node *temp = perdecessor(root);
            root->key = temp->key;
            root->lchild = __erase(root->lchild, temp->key);
        }
    }
    return erase_maintain(root);
}

Node *erase(Node *root, int key) {
    root = __erase(root, key);
    root->color = BLACK;
    return root;
}

void clear(Node *root) {
    if (root == NIL) return ;
    clear(root->lchild);
    clear(root->rchild);
    free(root);
    return ;
}

void output(Node *root) {
    if (root == NIL) return ;
    printf("%d [%d, %d] %s\n", 
        root->key, 
        root->lchild->key, 
        root->rchild->key,
        root->color ? "BLACK" : "RED"
    );
    output(root->lchild);
    output(root->rchild);
    return ;
}

int main() {
    int op, val;
    Node *root = NIL;
    while (~scanf("%d%d", &op, &val)) {
        switch (op) {
            case 1 : root = insert(root, val); break;
            case 2 : root = erase(root, val); break;
        }
        output(root);
    }

    return 0;
}
