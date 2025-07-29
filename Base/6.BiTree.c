#include <stdio.h>
#include <stdlib.h>

typedef struct TBNode
{
    char data;
    struct TBNode* pLchild;
    struct TBNode* pRchild;
}TBNODE,*PTBNODE;

PTBNODE Create_BiTree();
void PreTraverseBitree(PTBNODE);
void MiTraverseBitree(PTBNODE);
void PostTraverseBitree(PTBNODE);

int main(){
    PTBNODE root =Create_BiTree();
    PreTraverseBitree(root);
    //MiTraverseBitree(root);
    //PostTraverseBitree(root);

    return 0;
}

PTBNODE Create_BiTree()
{
    PTBNODE pA= (PTBNODE)malloc(sizeof(TBNODE));
    PTBNODE pB= (PTBNODE)malloc(sizeof(TBNODE));
    PTBNODE pC= (PTBNODE)malloc(sizeof(TBNODE));
    PTBNODE pD= (PTBNODE)malloc(sizeof(TBNODE));

    pA->data='A';
    pA->pLchild=pB;
    pA->pRchild=pC;

    pB->data='B';
    pB->pLchild=NULL;
    pB->pRchild=NULL;

    pC->data='C';
    pC->pLchild=pD;
    pC->pRchild=NULL;

    pD->data='D';
    pD->pLchild=NULL;
    pD->pRchild=NULL;

    return pA;
}

//前序遍历
void PreTraverseBitree(PTBNODE root)
{
    if(root!=NULL)
    {
        printf("%c\n",root->data);

        if(root->pLchild!=NULL){
            PreTraverseBitree(root->pLchild);
        }

        if(root->pRchild!=NULL){
            PreTraverseBitree(root->pRchild);
        }
    }
}

//中序遍历
void MiTraverseBitree(PTBNODE root)
{
    if(root!=NULL)
    {
        
        if(root->pLchild!=NULL){
            MiTraverseBitree(root->pLchild);
        }

        printf("%c\n",root->data);

        if(root->pRchild!=NULL){
            MiTraverseBitree(root->pRchild);
        }
    }
}

//后序遍历
void PostTraverseBitree(PTBNODE root)
{
    if(root!=NULL)
    {
        
        if(root->pLchild!=NULL){
            PostTraverseBitree(root->pLchild);
        }
        
        if(root->pRchild!=NULL){
            PostTraverseBitree(root->pRchild);
        }

         printf("%c\n",root->data);
    }
}