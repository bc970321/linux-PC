/*************************************************************************
	> File Name:    5.binary_tree.cpp
	> Author:       candy7 
	> Mail:         bc970321@163.com
	> Created Time: 2019年04月23日 星期二 16时57分38秒
 ************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

typedef struct Node {
    int key;
    struct Node *lchild, *rchild;
} Node;

Node *getNewNode(int key) {
    Node *p = (Node *)malloc(sizeof(Node));
    p->key = key;
    p->lchild = p->rchild = NULL;
    return p;
}

Node *insert(Node *tree, int val, int pwd) {
    int temp = pwd % 2;
    if (pwd == 1) {
        printf("111\n");
        return getNewNode(val);
    }
    else if (pwd == 2) {
        tree->lchild = insert(tree->lchild, val, pwd / 2 + temp);
    }
    else if (pwd == 3) {
        tree->rchild = insert(tree->rchild, val, pwd / 2 + temp);
    }
    else if (pwd / 2 % 2 == 0) {
        tree->lchild = insert(tree->lchild, val, pwd / 2 + temp);
        printf("222\n");
    }
    else {
        tree->rchild = insert(tree->rchild, val, pwd / 2 + temp);
        printf("333\n");
    }
    return tree;
}


void in_order(Node *tree) {
    if (tree == NULL) return ;
    in_order(tree->lchild);
    printf("%d\n", tree->key);
    in_order(tree->rchild);
    return ;
}


void clear(Node *tree) {
    if (tree == NULL) return ;
    clear(tree->lchild);
    clear(tree->rchild);
    free(tree);
    return ;
}

int main() {
    int n;
    scanf("%d", &n);
    Node *root = NULL;
    int ll = (int)pow(2, n);
    for (int i = 1; i <= ll - 1; i++) {
        int val;
        scanf("%d", &val);
        printf("%d %d\n", val, i);
        root = insert(root, val, i);
    }
    in_order(root);
    clear(root);
    return 0;
}
