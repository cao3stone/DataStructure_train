//利用数组实现队列

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node
{
    int data;
    struct Node* pNext;
}NODE,* PNODE;

typedef struct Queue
{
    PNODE pFront;
    PNODE pRear;
}QUEUE,* PQUEUE;

void init_Queue(PQUEUE);
bool is_empty(PQUEUE);
void en_Queue(PQUEUE,int);
bool out_Queue(PQUEUE,int*);
void traverse_Queue(PQUEUE);


int main(void)
{
    QUEUE Q;
    init_Queue(&Q);
    en_Queue(&Q,1);
    en_Queue(&Q,3);
    en_Queue(&Q,4);
    en_Queue(&Q,6);
    en_Queue(&Q,7);
    traverse_Queue(&Q);

    int val;
    if(out_Queue(&Q,&val)){
        printf("出队成功，出队元素为：%d。\n",val);
    }
    if(out_Queue(&Q,&val)){
        printf("出队成功，出队元素为：%d。\n",val);
    }
    if(out_Queue(&Q,&val)){
        printf("出队成功，出队元素为：%d。\n",val);
    }
    if(out_Queue(&Q,&val)){
        printf("出队成功，出队元素为：%d。\n",val);
    }
    en_Queue(&Q,3);
    traverse_Queue(&Q);
    if(out_Queue(&Q,&val)){
        printf("出队成功，出队元素为：%d。\n",val);
    }
    if(out_Queue(&Q,&val)){
        printf("出队成功，出队元素为：%d。\n",val);
    }
    if(out_Queue(&Q,&val)){
        printf("出队成功，出队元素为：%d。\n",val);
    }

    traverse_Queue(&Q);

    return 0;
}

//初始化队列
void init_Queue(PQUEUE pQ)
{
    pQ->pFront=(PNODE)malloc(sizeof(NODE));
    if(pQ->pFront==NULL){
        printf("分配内存失败，队列初始化失败！\n");
        exit(-1);
    }else{
        pQ->pRear=pQ->pFront;
        pQ->pFront->pNext=NULL;
    }
}

//判断队列是否为空
bool is_empty(PQUEUE pQ)
{
    if(pQ->pFront==pQ->pRear){
        return true;
    }else{
        return false;
    }
}

//元素入队
void en_Queue(PQUEUE pQ,int val)
{
    PNODE pNew=(PNODE)malloc(sizeof(NODE));
    if(pNew==NULL){
        printf("内存不足，入队失败！\n");
    }else{
        pQ->pRear->pNext=pNew; //链接节点   
        pQ->pRear=pNew;        //尾指针指向最后一个节点
        pNew->data=val;
        pNew->pNext=NULL;
    }
}

//元素出队
bool out_Queue(PQUEUE pQ,int* pVal)
{
    if(is_empty(pQ)){
        printf("出队失败，该队列已空！\n");
        return false;
    }else{
        PNODE p=pQ->pFront->pNext;
        *pVal=p->data;
        pQ->pFront->pNext=p->pNext;
        if(p->pNext==NULL){pQ->pFront=pQ->pRear;} //避免下溢
        free(p);
        p=NULL;
        return true;
    }
}

//遍历队列元素
void traverse_Queue(PQUEUE pQ)
{
    if(is_empty(pQ))
    {
        printf("该队列为空！\n");
    }else{
        PNODE p=pQ->pFront->pNext;
        while(p!=NULL){
            printf("%d ",p->data);
            p=p->pNext;
        }
        printf("\n");
    }
}