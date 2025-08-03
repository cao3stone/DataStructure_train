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
#include <stdlib.h>

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
void LevelOrderTraberse(PBTNODE);

//栈的相关函数
PSTACK create_stack(PBTNODE);
void push(PSTACK,PBTNODE);
PBTNODE pop(PSTACK);
bool is_empty(PSTACK);

//显示叶子节点
void PreOrderLeaf(PBTNODE);
void InOrderLeaf(PBTNODE);
void PostOrderLeaf(PBTNODE);

//求树高
int PreOrderHeight(PBTNODE);
int InOrderHeight(PBTNODE);
int PostOrderHeight(PBTNODE);

int main(void)
{
    PBTNODE BT=create_BiTree();
    // PreOrderTraverse(BT);    printf("\n");
    // InOrderTraverse(BT);    printf("\n");
    // PostOrederTraverse(BT);    printf("\n");
    // PreOrderLeaf(BT);    printf("\n");
    // InOrderLeaf(BT);    printf("\n");
    // PostOrderLeaf(BT);    printf("\n");
    int Height=PreOrderHeight(BT);
    printf("%d",Height);

    return 0;
}

PBTNODE create_BiTree()
{
/*      A
       / \
      B   C
     / \   \
    D   E   F
    \
     G    */
    PBTNODE pA=(PBTNODE)malloc(sizeof(BTNODE));
    PBTNODE pB=(PBTNODE)malloc(sizeof(BTNODE));
    PBTNODE pC=(PBTNODE)malloc(sizeof(BTNODE));
    PBTNODE pD=(PBTNODE)malloc(sizeof(BTNODE));
    PBTNODE pE=(PBTNODE)malloc(sizeof(BTNODE));
    PBTNODE pF=(PBTNODE)malloc(sizeof(BTNODE));
    PBTNODE pG=(PBTNODE)malloc(sizeof(BTNODE));

    pA->val='A';    pA->LChild=pB;    pA->Rchild=pC;
    pB->val='B';    pB->LChild=pD;    pB->Rchild=pE;
    pC->val='C';    pC->LChild=NULL;  pC->Rchild=pF;
    pD->val='D';    pD->LChild=NULL;  pD->Rchild=pG;
    pE->val='E';    pE->LChild=NULL;  pE->Rchild=NULL;
    pF->val='F';    pF->LChild=NULL;  pF->Rchild=NULL;
    pG->val='G';    pG->LChild=NULL;  pG->Rchild=NULL;

    return pA;
}

void PreOrderTraverse(PBTNODE root)
{
    if(root!=NULL){
        printf("%c ",root->val);
        if(root->LChild!=NULL){
            PreOrderTraverse(root->LChild);
        }
        if(root->Rchild!=NULL){
            PreOrderTraverse(root->Rchild);
        }
    }
}

void InOrderTraverse(PBTNODE root)
{
    if(root!=NULL){
        if(root->LChild!=NULL){
            InOrderTraverse(root->LChild);
        }
        printf("%c ",root->val);
        if(root->Rchild!=NULL){
            InOrderTraverse(root->Rchild);
        }
    }
}

void PostOrederTraverse(PBTNODE root)
{
    if(root!=NULL){
        if(root->LChild!=NULL){
            PostOrederTraverse(root->LChild);
        }
        if(root->Rchild!=NULL){
            PostOrederTraverse(root->Rchild);
        }
        printf("%c ",root->val);
    }
}

void InOrderTraverse_Stack(PBTNODE);
void PostOrederTraverse_Stack(PBTNODE);
void LevelOrderTraberse(PBTNODE);


PSTACK create_stack(PBTNODE root)
{
    PSTACK pS=(PBTNODE)malloc(sizeof(BTNODE));
    if(pS==NULL){
        printf("内存已满，栈创建失败！\n");
        exit(-1);
    }
    pS->pBottem=root;
    pS->pTop=pS->pBottem;
    pS->pTop->LChild=NULL;  //以左节点作为下一个指针；
    
}

void push(PSTACK pS,PBTNODE BT)
{
    PBTNODE pNew=(PBTNODE)malloc(sizeof(BTNODE));
    if(pNew==NULL){
        printf("内存分配失败！\n");
        exit(-1);
    }else{
        pNew->val=BT->val;
        pNew->LChild=pS->pTop;
        pS->pTop=pNew;
    }
}

PBTNODE pop(PSTACK pS)
{
    PBTNODE BT=pS->pTop;
    pS->pTop=pS;
}

bool is_empty(PSTACK pS)
{
    if(pS->pTop==pS->pBottem){
        return true;
    }else{
        return false;
    }
}


//显示叶子节点
void PreOrderLeaf(PBTNODE root)
{
    if(root!=NULL)
    {
        if(root->LChild==NULL && root->Rchild==NULL){
            printf("%c ",root->val);
        }
        PreOrderLeaf(root->LChild);
        PreOrderLeaf(root->Rchild);
    }
}

void InOrderLeaf(PBTNODE root)
{
    if(root!=NULL){
        InOrderLeaf(root->LChild);
        if(root->LChild==NULL && root->Rchild==NULL){
            printf("%c ",root->val);
        }
        InOrderLeaf(root->Rchild);
    }
}

void PostOrderLeaf(PBTNODE root)
{
    if(root!=NULL){
        PostOrderLeaf(root->LChild);
        PostOrderLeaf(root->Rchild);
        if(root->LChild==NULL && root->Rchild==NULL){
            printf("%c ",root->val);
        }
    }
}

//求树高
int PreOrderHeight(PBTNODE root)
{
    int ML,MR,MaxH;
    if(root!=NULL){
        ML=PreOrderHeight(root->LChild);  //求左子树高度
        MR=PreOrderHeight(root->Rchild);  //求右子树高度
        MaxH=(ML>MR) ? ML : MR;           //求最高子树高度
        return MaxH+1;                    //返回树高
    }else{
        return 0;  //空树的高度为0
    }
}

int InOrderHeight(PBTNODE);
int PostOrderHeight(PBTNODE);