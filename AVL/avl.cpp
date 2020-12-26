/*************************************************************************
        > File Name: 2.avl_lkj.cpp
        > Author: longkejie
        > Mail:1721248012@qq.com
        > Created Time: Tue 22 Dec 2020 10:16:46 PM CST
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>
#define DATA(n) (n != NIL? n -> data : 0)
#define SIZE(n) (n->size)

typedef struct Node {
    int data, size;
    struct Node *lchild, *rchild;
}Node;

Node __NIL;
#define NIL (&__NIL)

__attribute__((constructor))
void init() {
    NIL->data = 0;
    NIL->lchild = NIL->rchild = NULL;
    NIL->size = 0;
}
void updatesize(Node *);

Node *leftroate(Node *root) {
    Node *temp = root->rchild;
    root->rchild = temp -> lchild;
    temp->lchild = root;
    updatesize(root);
    updatesize(temp);
    return temp;
}

Node *rightroate(Node *root) {
    Node *temp = root->lchild;
    root->lchild = temp->rchild;
    temp->rchild = root;
    updatesize(root);
    updatesize(temp);
    return temp;
}


Node *maintain(Node *root) {
    if (abs(SIZE(root -> lchild) - SIZE(root->rchild)) <= 1) return root;
    if (SIZE(root->lchild) > SIZE(root->rchild)) {
        if (SIZE(root->lchild->rchild) > SIZE(root->lchild->lchild)) {
            root->lchild = leftroate(root->lchild);
        }
        root = rightroate(root);
    }else {
        if (SIZE(root->rchild->lchild) > SIZE(root->rchild->rchild)) {
            root->rchild = rightroate(root->rchild);
        }
        root = leftroate(root);
    }
    return root;
}

Node *getNewNode(int val) {
    Node *node = (Node *)malloc(sizeof(Node));
    node->data = val;
    node->lchild = node->rchild = NIL;
    node->size = 1;
    return node;
}

void updatesize(Node *root) {
    root->size = ( SIZE(root->lchild) > SIZE(root->rchild) ? SIZE(root->lchild) : SIZE(root->rchild) ) + 1;
}

Node *insert(Node *root, int val) {
    if (root == NIL) return getNewNode(val);
    if (root->data == val) return root;
    if (root->data > val) root->lchild=insert(root->lchild, val);
    if (root->data < val) root->rchild=insert(root->rchild, val);
    updatesize(root);
    return maintain(root);
}

Node *precessor(Node *root) {
    Node *temp = root -> lchild;
    while (temp -> rchild != NIL) temp = temp->rchild;
    return temp;
}

Node *erase(Node *root, int val) {
    if (root == NIL) return NIL;
    if (root->data > val) root->lchild = erase(root->lchild, val);
    if (root->data < val) root->rchild = erase(root->rchild, val);
    if (root->data == val) {
        if (root->lchild == NIL || root->rchild == NIL ) {
            Node *temp = root->lchild ? root->lchild : root->rchild;
            free(root);
            root=NULL;
            return temp;
        }else {
            Node *temp = precessor(root);
            root->data = temp->data;
            root->lchild = erase(root->lchild, temp->data);
        }
    }
    updatesize(root);
    return maintain(root);
}


void output(Node *root) {
    if (root == NIL) return;
    output(root->lchild);
    printf("%d(%d)=[%d,%d]\n",DATA(root), SIZE(root), DATA(root->lchild),DATA(root->rchild));
    output(root->rchild);
    return;
}

int main () {
    int op, val;
    Node *root = NIL;
    while (~scanf("%d %d",&op,&val)) {
        switch(op) {
            case 1:
                root=insert(root, val);break;
            case 2:
                root=erase(root,val);break;
        }
        output(root);
    }

    return 0;
}
