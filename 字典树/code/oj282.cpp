/*************************************************************************
	> File Name: oj282.cpp
	> Author: longkejie
	> Mail:1721248012@qq.com 
	> Created Time: Wed 13 Jan 2021 09:57:03 PM CST
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

#define MAX_N 100000
#define BASE 31
struct node{
    struct node *next[2];
} tree[BASE * MAX_N];

int cnt = 0;
node *getNode() {
    return &tree[cnt++];
}

void insert(node *root, int x) {
    for (int i = 30; i >= 0; --i) {
        int ind = !!(x & (1 << i));
        if (root->next[ind] == NULL) root -> next[ind] = getNode();
        root = root -> next[ind];
    }
    return ;
}

int query(node *root, int x ) {
    int ans = 0;
    for (int i = 30; i >= 0; --i) {
        int ind = !(x & (1 << i));
        if (root -> next[ind]) {
            ans |= (1 << i);
            root = root->next[ind];
        }else {

            root = root->next[!ind];
        }
    }
    return ans;
}

int n;
int val[MAX_N + 5];
int main () {
    cin >> n;
    int ans = 0, a;
    node *root = getNode();
    cin >> a, n--;
    insert(root, a);
    while (n--) {
        cin >> a;
        ans = max(ans, query(root, a));
        insert(root,a);
    }
    cout << ans << endl;
    return 0;
}
