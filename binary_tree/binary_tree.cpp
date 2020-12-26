/*************************************************************************
        > File Name: 1.binary_search_tree_lkj.cpp
        > Author: longkejie
        > Mail:1721248012@qq.com
        > Created Time: Tue 22 Dec 2020 04:03:29 PM CST
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE(n)  (n ? n->size : 0)

typedef struct Node {
    int data, size;
    struct Node *lchild, *rchild;
}Node;

Node *getNewNode(int val) {
    Node *node = (Node *)malloc(sizeof(Node));
    node -> data = val;
    node -> size = 1;
    node -> lchild = node -> rchild = NULL;
    return node;
}

void clear(Node *root) {
    if (root == NULL) return;
    if (root -> lchild) clear(root->lchild);
    if (root -> rchild) clear(root->rchild);
    free(root);
    root=NULL;
    return ;
}

void updatesize(Node *root) {
    root -> size = SIZE(root -> lchild) + SIZE(root -> rchild) + 1;
}

Node *insert(Node *root, int val) {
    if (root == NULL) return getNewNode(val);
    if (root -> data == val) return root;
    if (root -> data > val) root->lchild = insert(root -> lchild,val);
    if (root -> data < val) root->rchild = insert(root -> rchild,val);
    updatesize(root);
    return root;
}


Node *precessor(Node *root) {
    while (root -> rchild) root = root->rchild;
    return root;
}


Node *erase(Node *root, int val) {
    if (root == NULL) return NULL;
    if (root -> data > val) {
        root -> lchild = erase(root -> lchild, val);
    }else if (root -> data < val) {
        root -> rchild = erase(root -> rchild, val);
    }else {
        if (root -> lchild == NULL || root -> rchild == NULL) {
            Node *temp = root -> lchild ? root -> lchild : root -> rchild;
            free(root);
            root = NULL;
            return temp;
        }else {
            Node *temp = precessor(root -> lchild);
            root->data = temp->data;
            root -> lchild = erase(root -> lchild, temp -> data);
        }
    }
    updatesize(root);
    return root;
}
void output(Node *);
void topk(Node *root, int k) {
    if (root == NULL) return;
    if (k <= SIZE(root -> lchild)) {
        topk(root -> lchild, k);
    }else {
        output(root -> lchild);
        printf("%d(%d)=(%d,%d)\n",root->data, root->size, root -> lchild ? root->lchild->data : 0, root -> rchild ?root->rchild->data : 0);
        topk(root->rchild,k - SIZE(root -> lchild) - 1);
    }
    return ;
}

void output(Node *root) {
    if (root == NULL) return;
    output(root->lchild);
    printf("%d(%d)=(%d,%d)\n",root->data, root->size, root -> lchild ? root->lchild->data : 0, root -> rchild ?root->rchild->data : 0);
    output(root->rchild);
    return;
}

void output_k(Node *root, int k) {
    if (k <= 0 || k > root -> size) {
        printf("please input the right k\n");
        return ;
    }
    if (SIZE(root -> lchild) == k - 1) {
        printf("the %d iteram is %d\n", k, root -> data);
    }else if (SIZE(root -> lchild) + 1 > k) {
        output_k(root -> lchild, k);
    }else {
        output_k(root -> rchild, k - SIZE(root -> lchild) - 1);
    }
    return;
}

int main () {

    int val, op;
    Node *root = NULL;
    while(~scanf("%d %d",&op,&val)) {
        switch(op) {
            case 1:
                root = insert(root, val);break;
            case 2:
                root = erase(root, val);break;
            case 3:
                output_k(root,val);break;
            case 4:
                topk(root, val);printf("----------------\n");break;
        }
        output(root);
    }
    clear(root);
    return 0;
}
