#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node
{
    int data;  //数据域
    struct Node* pNext; //指针域
}NODE,*PNODE;  //NODE等价于 struct Node, PNODE等价于 struct Node*

typedef struct Stack
{
    PNODE pTop;     //指向顶部指针
    PNODE pBottom;  //指向底部指针
}STACK,*PSTACK;

//函数声明
void init_Stack(PSTACK);     //初始化栈
void push_Stack(PSTACK,int); //数据压入栈
void traverse_Stack(PSTACK); //遍历栈中元素
bool is_empty(PSTACK);       //判断栈是否为空
bool pop_Stack(PSTACK,int*); //出栈
void clear_Stack(PSTACK);    //清空栈

int main(void)
{
    STACK S;
    int val;
    init_Stack(&S);
    push_Stack(&S,1);
    push_Stack(&S,3);
    push_Stack(&S,4);
    push_Stack(&S,6);
    traverse_Stack(&S);
    pop_Stack(&S,&val);
    // printf("%d\n",val);
    traverse_Stack(&S);
    clear_Stack(&S);
    traverse_Stack(&S);

    
    return 0;
}

void init_Stack(PSTACK pS)
{
    pS->pBottom=(PNODE)malloc(sizeof(NODE));
    if(pS->pBottom==NULL)
    {
        printf("分配内存失败，栈的初始化失败！\n");
        exit(-1);
    }else
    {
        pS->pTop=pS->pBottom;
        pS->pBottom->pNext=NULL; //等价于pS->pTop->pNext=NULL
    }
}

void push_Stack(PSTACK pS,int val)
{
    PNODE pNew=(PNODE)malloc(sizeof(NODE));
    pNew->data=val;
    pNew->pNext=pS->pTop;
    pS->pTop=pNew;
}

void traverse_Stack(PSTACK pS)
{
    if(is_empty(pS)){
        printf("该栈为空！\n");
        return;
    }
    PNODE pTemp=pS->pTop;
    while(pTemp!=pS->pBottom)
    {
        printf("%d ",pTemp->data);
        pTemp=pTemp->pNext;
    }
    printf("\n");
    return;
}

bool is_empty(PSTACK pS)
{
    if(pS->pBottom==pS->pTop){
        return true;
    }else{
        return false;
    }
}

bool pop_Stack(PSTACK pS,int *pVal)
{
    if(is_empty(pS))
    {
        printf("该栈为空，出栈失败！\n");
        return false;
    }else{
        PNODE pTmep=pS->pTop;
        *pVal=pTmep->data;
        pS->pTop=pTmep->pNext;
        free(pTmep);
        pTmep=NULL;
        return true;
    }
}

void clear_Stack(PSTACK pS)
{
    if(is_empty(pS)){
        return;
    }else{
        while(pS->pTop!=pS->pBottom){
            PNODE pTemp=pS->pTop;               
            pS->pTop=pS->pTop->pNext;
            free(pTemp);                     
        }
        // PNODE p=pS->pTop;
        // PNODE q=NULL;
        // while (p!=pS->pBottom)
        // {
        //     q=p->pNext;
        //     free(p);
        //     p=q;
        // }
        // pS->pTop=pS->pBottom;
    }
    return;
}
