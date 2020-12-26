/*************************************************************************
        > File Name: 1.red_black_tree_lkj.cpp
        > Author: longkejie
        > Mail:1721248012@qq.com
        > Created Time: Sat 26 Dec 2020 10:26:09 AM CST
 ************************************************************************/
#include<stdio.h>
#include<iostream>
#include<stdlib.h>

typedef struct Node {
    int data;
    struct Node *lchild, *rchild;
    int color; //0 - red 1 - black 2 - double-black
}Node;

Node __NIL; // 虚拟尾结点
#define NIL (&__NIL)

__attribute__((constructor))
void init() {
    NIL -> data = 0;
    NIL->lchild = NIL->rchild = NULL;
    NIL->color = 1;
}

//初始化结点，插入结点的颜色应该为红色，所以color为0
Node *getNewNode(int val) {
    Node *p = (Node *)malloc(sizeof(Node));
    p -> data = val;
    p->lchild = p->rchild = NIL;
    p->color = 0;
    return p;
}
//申请内存就要记得清空内存
void clear(Node *root) {
    if (root == NIL) return;
    clear(root->lchild);
    clear(root->rchild);
    free(root);
    return;
}

//判断某个结点是否有红色的子节点。
int has_red_child(Node *root) {
    return (root->lchild->color == 0 || root->rchild->color == 0);
}
//左旋
Node *leftroate(Node *root) {
    Node *temp = root->rchild;
    root->rchild = temp -> lchild;
    temp->lchild = root;
    return temp;
}

//右旋
Node *rightroate(Node *root) {
    Node *temp = root->lchild;
    root->lchild = temp->rchild;
    temp->rchild = root;
    return temp;
}

//插入调整函数，站在祖父结点上看，红黑树插入的重点。
Node *insert_maintain(Node *root) {
    if (!has_red_child(root)) return root; // 如果该结点没有红孩子，则不会发生冲突，不需要调整。返回即可
    //情况1，发生冲突，并且叔父结点为红色，这里直接红色上浮即可。
    int flag = 0;
    if (root->lchild->color == 0 && root->rchild->color == 0) {
        if (has_red_child(root->lchild) ||has_red_child(root->rchild)) {
            root->color = 0;
            root->lchild->color = root->rchild->color = 1;
            return root;
        }
    }
    //利用flag判断是左子树发生冲突还是右子树发生冲突
    if (root->lchild->color == 0 && has_red_child(root->lchild)) flag = 1;
    if (root->rchild->color == 0 && has_red_child(root->rchild)) flag = 2;
    if (flag == 0) return root;
    //情况2以及情况三，情况2为LL或者LR,情况3位LR或者RL，情况3根据小右旋或者小左旋可以转换为情况2
    if (flag == 1) {//左子树冲突
        if (root->lchild->lchild->color != 0) {//LR类型，先小左旋
            root->lchild = leftroate(root->lchild);
        }
        root = rightroate(root);//大右旋
    }else {//右子树冲突
           if (root->rchild->rchild->color != 0) {//RL类型，先小右旋
               root->rchild = rightroate(root->rchild);
           }
           root = leftroate(root);//大左旋
    }
    //选择完毕后无论哪种情况，都是红色上浮即可
    root->color = 0;
    root->rchild->color = root->lchild->color = 1;
    return root;
}



//真正的插入函数，根据结点的值以及插入进来的值，判断插入到结点的左子树还是右子树。
Node *__insert(Node *root, int val) {
    if (root == NIL) return getNewNode(val);
    if (root->data == val) return root;//如果等于插入进来的值，直接返回该结点即可
    if (root->data > val) root->lchild = __insert(root->lchild, val);//如果大于插入进来的值，将该值插入到左子树
    if (root->data < val) root->rchild = __insert(root->rchild, val);//否则插入到右子树
    return insert_maintain(root); // 插入调整函数，回溯时被调用，从祖父结点看是否需要调整。
}


//封装一层，便于插入结束后，将根结点颜色改为黑色
Node *insert(Node *root, int val) {
    root = __insert(root, val);
    root->color = 1;
    return root;
}

Node *precessor(Node *root) {
    Node *temp = root -> lchild;
    while (temp->rchild != NIL) temp = temp->rchild;
    return temp;
}
//删除调整函数，主要是站在父亲结点上看，去除双黑结点。
Node *erase_maintain(Node *root) {
    if (root->lchild->color != 2 && root->rchild->color != 2) return root;//没有双黑结点返回即可。
    int flag = 0;
    //如果双黑结点的兄弟结点为红色，应该通过旋转使其变为黑色。
    if (has_red_child(root)) {
        if (root->lchild->color == 0) {
            root->lchild->color = 1;
            root->color = 0;
            root = rightroate(root);
            root ->rchild = erase_maintain(root->rchild);
            return root;
        }else if (root->rchild->color == 0) {
            root->rchild->color = 1;
            root->color = 0;
            root = leftroate(root);
            root->lchild = erase_maintain(root->lchild);
            return root;
        }
    }
    //情况1:双黑结点的兄弟为黑色，并且它兄弟的孩子都为黑色，将根结点黑色加一层，双黑结点以及兄弟结点黑色减一层即可。
    if (root -> lchild -> color == 2) {
        if (!has_red_child(root->rchild)) {//情况1
            root->color += 1;
            root->lchild->color -= 1;
            root->rchild->color -= 1;
            return root;
        }else {
            root->lchild->color -= 1;
            if (root->rchild->rchild->color != 0) {//情况2，进行一个小右旋，转换为情况三
                root->rchild->lchild->color = 1;
                root->rchild->color = 0;
                root->rchild = rightroate(root->rchild);
            }
            //情况三，大左旋即可
            root = leftroate(root);
            root -> color = root->lchild->color;
        }

    }else {
        if (!has_red_child(root->lchild)) {
            root->color += 1;
            root->lchild->color -= 1;
            root->rchild->color -= 1;
            return root;
        }else {
            root->rchild->color -= 1;
            if (root->lchild->lchild->color != 0) {//情况二，与上述情况类似
                root->lchild->rchild->color = 1;
                root->lchild->color = 0;
                root->lchild = leftroate(root->lchild);
            }
            //情况三；
            root->color = root->rchild->color;
            root = rightroate(root);
        }
    }
    root->lchild->color = root->rchild->color = 1;
    return root;
}

//删除结点函数
Node *__erase(Node *root, int val) {
    if (root == NIL) return NIL;
    if (root->data > val) root -> lchild = __erase(root->lchild, val);//如果大于插入进来的值，往左子树去查找需要删除的结点。
    if (root->data < val) root->rchild = __erase(root->rchild, val);//如果小于插入进来的值，往右子树去查找需要删除的结点。
    if (root->data == val) {
        if (root->lchild == NIL || root->rchild == NIL) {
            Node *temp = root->lchild != NIL ? root->lchild : root->rchild;
            temp->color += root->color;//将root的颜色加到temp颜色上。
            free(root);//释放root。
            return temp;
        }else {
            Node *temp = precessor(root);//删除的结点度为2，找到前驱结点，改为删除度为1的操作。
            root->data = temp->data;
            root->lchild = __erase(root->lchild, temp->data);
        }
    }

    return erase_maintain(root);//递归回溯调用删除调整函数。
}


//封住一层删除节点函数，便于删除调整结束后，将根结点改为黑色
Node *erase(Node *root, int val) {
    root = __erase(root, val);
    root->color = 1;
    return root;
}

//中序遍历
void output(Node *root) {
    if (root == NIL) return;
    output(root->lchild);
    printf("%d %d %d %d\n",root->data, root->color, root->lchild->data, root->rchild->data);
    output(root->rchild);
    return;
}


int main () {
    int op, val;
    Node *root = NIL;
    while (~scanf("%d %d",&op,&val)) {
        switch(op) {
            case 1: root = insert(root,val);break;
            case 2: root = erase(root,val); break;
            case 3: output(root);break;
        }
    }
    clear(root);
    return 0;
}
