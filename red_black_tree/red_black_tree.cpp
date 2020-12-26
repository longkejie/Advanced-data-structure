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

Node __NIL; // ����β���
#define NIL (&__NIL)

__attribute__((constructor))
void init() {
    NIL -> data = 0;
    NIL->lchild = NIL->rchild = NULL;
    NIL->color = 1;
}

//��ʼ����㣬���������ɫӦ��Ϊ��ɫ������colorΪ0
Node *getNewNode(int val) {
    Node *p = (Node *)malloc(sizeof(Node));
    p -> data = val;
    p->lchild = p->rchild = NIL;
    p->color = 0;
    return p;
}
//�����ڴ��Ҫ�ǵ�����ڴ�
void clear(Node *root) {
    if (root == NIL) return;
    clear(root->lchild);
    clear(root->rchild);
    free(root);
    return;
}

//�ж�ĳ������Ƿ��к�ɫ���ӽڵ㡣
int has_red_child(Node *root) {
    return (root->lchild->color == 0 || root->rchild->color == 0);
}
//����
Node *leftroate(Node *root) {
    Node *temp = root->rchild;
    root->rchild = temp -> lchild;
    temp->lchild = root;
    return temp;
}

//����
Node *rightroate(Node *root) {
    Node *temp = root->lchild;
    root->lchild = temp->rchild;
    temp->rchild = root;
    return temp;
}

//�������������վ���游����Ͽ��������������ص㡣
Node *insert_maintain(Node *root) {
    if (!has_red_child(root)) return root; // ����ý��û�к캢�ӣ��򲻻ᷢ����ͻ������Ҫ���������ؼ���
    //���1��������ͻ�������常���Ϊ��ɫ������ֱ�Ӻ�ɫ�ϸ����ɡ�
    int flag = 0;
    if (root->lchild->color == 0 && root->rchild->color == 0) {
        if (has_red_child(root->lchild) ||has_red_child(root->rchild)) {
            root->color = 0;
            root->lchild->color = root->rchild->color = 1;
            return root;
        }
    }
    //����flag�ж���������������ͻ����������������ͻ
    if (root->lchild->color == 0 && has_red_child(root->lchild)) flag = 1;
    if (root->rchild->color == 0 && has_red_child(root->rchild)) flag = 2;
    if (flag == 0) return root;
    //���2�Լ�����������2ΪLL����LR,���3λLR����RL�����3����С��������С��������ת��Ϊ���2
    if (flag == 1) {//��������ͻ
        if (root->lchild->lchild->color != 0) {//LR���ͣ���С����
            root->lchild = leftroate(root->lchild);
        }
        root = rightroate(root);//������
    }else {//��������ͻ
           if (root->rchild->rchild->color != 0) {//RL���ͣ���С����
               root->rchild = rightroate(root->rchild);
           }
           root = leftroate(root);//������
    }
    //ѡ����Ϻ�����������������Ǻ�ɫ�ϸ�����
    root->color = 0;
    root->rchild->color = root->lchild->color = 1;
    return root;
}



//�����Ĳ��뺯�������ݽ���ֵ�Լ����������ֵ���жϲ��뵽����������������������
Node *__insert(Node *root, int val) {
    if (root == NIL) return getNewNode(val);
    if (root->data == val) return root;//������ڲ��������ֵ��ֱ�ӷ��ظý�㼴��
    if (root->data > val) root->lchild = __insert(root->lchild, val);//������ڲ��������ֵ������ֵ���뵽������
    if (root->data < val) root->rchild = __insert(root->rchild, val);//������뵽������
    return insert_maintain(root); // �����������������ʱ�����ã����游��㿴�Ƿ���Ҫ������
}


//��װһ�㣬���ڲ�������󣬽��������ɫ��Ϊ��ɫ
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
//ɾ��������������Ҫ��վ�ڸ��׽���Ͽ���ȥ��˫�ڽ�㡣
Node *erase_maintain(Node *root) {
    if (root->lchild->color != 2 && root->rchild->color != 2) return root;//û��˫�ڽ�㷵�ؼ��ɡ�
    int flag = 0;
    //���˫�ڽ����ֵܽ��Ϊ��ɫ��Ӧ��ͨ����תʹ���Ϊ��ɫ��
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
    //���1:˫�ڽ����ֵ�Ϊ��ɫ���������ֵܵĺ��Ӷ�Ϊ��ɫ����������ɫ��һ�㣬˫�ڽ���Լ��ֵܽ���ɫ��һ�㼴�ɡ�
    if (root -> lchild -> color == 2) {
        if (!has_red_child(root->rchild)) {//���1
            root->color += 1;
            root->lchild->color -= 1;
            root->rchild->color -= 1;
            return root;
        }else {
            root->lchild->color -= 1;
            if (root->rchild->rchild->color != 0) {//���2������һ��С������ת��Ϊ�����
                root->rchild->lchild->color = 1;
                root->rchild->color = 0;
                root->rchild = rightroate(root->rchild);
            }
            //�����������������
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
            if (root->lchild->lchild->color != 0) {//��������������������
                root->lchild->rchild->color = 1;
                root->lchild->color = 0;
                root->lchild = leftroate(root->lchild);
            }
            //�������
            root->color = root->rchild->color;
            root = rightroate(root);
        }
    }
    root->lchild->color = root->rchild->color = 1;
    return root;
}

//ɾ����㺯��
Node *__erase(Node *root, int val) {
    if (root == NIL) return NIL;
    if (root->data > val) root -> lchild = __erase(root->lchild, val);//������ڲ��������ֵ����������ȥ������Ҫɾ���Ľ�㡣
    if (root->data < val) root->rchild = __erase(root->rchild, val);//���С�ڲ��������ֵ����������ȥ������Ҫɾ���Ľ�㡣
    if (root->data == val) {
        if (root->lchild == NIL || root->rchild == NIL) {
            Node *temp = root->lchild != NIL ? root->lchild : root->rchild;
            temp->color += root->color;//��root����ɫ�ӵ�temp��ɫ�ϡ�
            free(root);//�ͷ�root��
            return temp;
        }else {
            Node *temp = precessor(root);//ɾ���Ľ���Ϊ2���ҵ�ǰ����㣬��Ϊɾ����Ϊ1�Ĳ�����
            root->data = temp->data;
            root->lchild = __erase(root->lchild, temp->data);
        }
    }

    return erase_maintain(root);//�ݹ���ݵ���ɾ������������
}


//��סһ��ɾ���ڵ㺯��������ɾ�����������󣬽�������Ϊ��ɫ
Node *erase(Node *root, int val) {
    root = __erase(root, val);
    root->color = 1;
    return root;
}

//�������
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
