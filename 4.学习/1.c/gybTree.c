/*************************************************************************
	> File Name:    gybTree.c
	> Author:       candy7 
	> Mail:         bc970321@163.com
	> Created Time: 2019年04月08日 星期一 19时20分12秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    char data;
    struct node *lchild, *rchild;
} BinTreeNode;

BinTreeNode * createBinTreeByGLists(char *gLists, int nodeQuantity);
void preOrderTraverse(BinTreeNode *node);
void inOrderTraverse(BinTreeNode *node);
void postOrderTraverse(BinTreeNode *node);

int main(int argc, const char * argv[]) {

    char *gLists = "(A (B (C, D), E ( , F)) )";

    BinTreeNode *rootNode = createBinTreeByGLists(gLists, 6);

    printf("pre order: ");
    preOrderTraverse(rootNode);
    printf("\nin order: ");
    inOrderTraverse(rootNode);
    printf("\npost order: ");
    postOrderTraverse(rootNode);

    return 0;
}

//根据广义表创建二叉树
BinTreeNode * createBinTreeByGLists(char *gLists, int nodeQuantity) {
    BinTreeNode *rootNode = NULL;
    BinTreeNode *currNode = NULL;

    //创建指针数组作为栈结构
    BinTreeNode **stack = (BinTreeNode **) malloc(sizeof(BinTreeNode *) * nodeQuantity);
    int top = -1;

    int flag = 0;
    const int START_LEFT_CHILD = 1, START_RIGHT_CHILD = 2;

    int index = 0;

    char c = gLists[index];

    while (c != '\0') {

        switch (c) {
            case '(':
                stack[++top] = currNode;
                flag = START_LEFT_CHILD;
                break;
            case ',':
                flag = START_RIGHT_CHILD;
                break;
            case ')':
                top--;
                break;
            case ' ':
                break;
            default:
                currNode = (BinTreeNode *) malloc(sizeof(BinTreeNode));
                currNode->data = c;
                currNode->lchild = currNode->rchild = NULL;

                if (rootNode == NULL) {
                    rootNode = currNode;
                } else {
                    int x1 = START_LEFT_CHILD;
                    int x2 = START_RIGHT_CHILD;
                    switch (flag) {
                        case x1:
                            stack[top]->lchild = currNode;
                            break;
                        case x2:
                            stack[top]->rchild = currNode;
                            break;
                    }
                }
        }

        c = gLists[++index];
    }

    //释放
    free(stack);

    return rootNode;
}

//前序遍历
void preOrderTraverse(BinTreeNode *node) {
    if (node != NULL) {
        printf("%c", node->data);

        preOrderTraverse(node->lchild);

        preOrderTraverse(node->rchild);
    }
}

//中序遍历
void inOrderTraverse(BinTreeNode *node) {
    if (node != NULL) {
        inOrderTraverse(node->lchild);

        printf("%c", node->data);

        inOrderTraverse(node->rchild);
    }
}

//后序遍历
void postOrderTraverse(BinTreeNode *node) {
    if (node != NULL) {
        postOrderTraverse(node->lchild);

        postOrderTraverse(node->rchild);

        printf("%c", node->data);
    }
}

//--------------------- 

//作者：liuhe688 

//来源：CSDN 

//原文：https://blog.csdn.net/liuhe688/article/details/51837898 

//版权声明：本文为博主原创文章，转载请附上博文链接！
