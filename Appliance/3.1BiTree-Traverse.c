/*
二叉树的各种遍历算法：
1.递归先序遍历，中序遍历，后序遍历
2.非递归中序遍历，后序遍历，利用栈实现
3.层序遍历
4.遍历的应用：4.1输出所有的叶子节点；4.2计算树高
基于链表实现二叉树
    A
   / \
  B   C
 / \   \
D   E   F
 \
  G
*/

#include <stdio.h>
#include <stdbool.h>
typedef char ElementType; //数据类型
typedef struct BTNode     //二叉树
{
    ElementType val;
    struct BTNode* LChild;
    struct BTNode* Rchild;
}BTNODE,* PBTNODE;

typedef struct Stack     //栈
{
    PBTNODE pTop;
    PBTNODE pBottem;
}STACK,* PSTACK;

//二叉树相关函数声明
PBTNODE create_BiTree();
void PreOrderTraverse(PBTNODE);
void InOrderTraverse(PBTNODE);
void PostOrederTraverse(PBTNODE);
void InOrderTraverse_Stack(PBTNODE);
void PostOrederTraverse_Stack(PBTNODE);

//栈的相关函数
PSTACK create_stack(PBTNODE);
bool  

int main(void)
{
    return 0;
}