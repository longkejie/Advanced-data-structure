/*************************************************************************
	> File Name: 1.双数组字典树.cpp
	> Author: longkejie
	> Mail:1721248012@qq.com 
	> Created Time: Sat 23 Jan 2021 07:18:23 PM CST
 ************************************************************************/

#include<iostream>
#include<cstring>
#include<map>
#include<queue>
#include<stack>
#include<algorithm>
#include<set>
#include<vector>
#include<cmath>
using namespace std;
#define BASE 26

typedef struct Node {
    int flag;
    struct Node *next[BASE];
} Node;

typedef struct DANode{
    int base, check;
}DANode;


Node *getNewNode() {
    Node *p = (Node *)malloc(sizeof(Node));
    p->flag = 0;
    memset(p->next, 0, sizeof(p->next));
    return p;
}

inline int code(char c) {
    return c - 'a';
}

int insert(Node *root, const char *str) {
    int cnt  = 0;
    Node *p = root;
    for (int i = 0; str[i]; ++i) {
        int ind = code(str[i]);
        if (p->next[ind] == NULL) {
            p->next[ind] = getNewNode();
            cnt++;
        }
        p = p->next[ind];
    }
    p->flag = 1;
    return cnt;
}

void clear_tree(Node *root) {
    if (root == NULL) return;
    for (int i = 0; i < BASE; ++i) {
        clear_tree(root->next[i]);
    }
    free(root);
    return ;
}

int get_base_value(Node *root, DANode *tree, int ind) {
    int base = 1, flag;
    do {
        base += 1;
        flag = 1;
        for (int i = 0; i < BASE & flag; ++i) {
            if (root -> next[i] == NULL) continue;
            if (tree[base + i].check) flag = 0;

        }
    }while (flag == 0);
    return base;
}

int transform_double_array_tire(Node *root, DANode *tree, int ind) {
    if (root == NULL) return 0;
    if (root -> flag) tree[ind].check = -tree[ind].check;
    int base = get_base_value(root, tree, ind);
    tree[ind].base = base;
    for (int i = 0; i < BASE; ++i) {
        if (root -> next[i] == NULL) continue;
        tree[base + i].check = ind;
    }
    int max_ind = ind;
    for (int i = 0; i < BASE; ++i) {
        int a = transform_double_array_tire(root->next[i],tree,base + i);
        max_ind = max(max_ind, a);
    }

    return max_ind;
}

int main () {

    int n, cnt = 1;
    char str[1000];
    scanf("%d",&n);
    Node *root = getNewNode();
    for (int i = 0; i < n; ++i) {
        scanf("%s",str);
        cnt += insert(root, str);
    }
    size_t tree_size = sizeof(DANode) * (cnt * BASE);
    DANode *tree = (DANode *)malloc(tree_size);
    memset(tree, 0 ,sizeof(DANode));
    int max_ind = transform_double_array_tire(root, tree, 1);
    for (int i = 0 ; i <= max_ind; ++i) {
        printf("(%d | %d, %d)\t",i, tree[i].base, tree[i].check);
        if ((i + 1) % 5 == 0) printf("\n");
    }
    printf("\n");
    free(tree);
    clear_tree(root);

    return 0;
}
