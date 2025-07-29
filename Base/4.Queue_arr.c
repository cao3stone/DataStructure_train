//利用数组实现循环队列

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Queue
{
    int* pBase; //数组指针
    int front;  //头部指针位置
    int rear;   //尾部指针位置
    int len;    //队列长度
}QUEUE;

void init_Queue(QUEUE*,int);
bool en_Queue(QUEUE*,int);
bool out_Queue(QUEUE*,int*);
bool is_empty(QUEUE*);
bool is_full(QUEUE*);
void traverse_Queue(QUEUE*);


int main(void)
{
    QUEUE Q;
    int val;

    init_Queue(&Q,5);
    en_Queue(&Q,1);
    en_Queue(&Q,2);
    en_Queue(&Q,3);
    en_Queue(&Q,4);
    en_Queue(&Q,5);
    en_Queue(&Q,6);
    if(out_Queue(&Q,&val))
    {
        printf("出队成功，出队元素为：%d。\n",val);
    }
    out_Queue(&Q,&val);
    traverse_Queue(&Q);
    en_Queue(&Q,3);

    traverse_Queue(&Q);



    return 0;
}

//初始化队列
void init_Queue(QUEUE* pQ,int len)
{
    pQ->pBase=(int*)malloc(sizeof(int)*len);
    pQ->front=0;
    pQ->rear=0;
    pQ->len=len;
}

//元素入队
bool en_Queue(QUEUE* pQ,int val)
{
    if(is_full(pQ)){
        printf("该队列已满，入队失败！\n");
        return false;
    }else{
        pQ->pBase[pQ->rear]=val;
        pQ->rear=(pQ->rear+1)%pQ->len;
        return true;
    }    
}

//元素出队
bool out_Queue(QUEUE* pQ,int* pVal)
{
    if(is_empty(pQ)){
        printf("该队列已空，出队失败！\n");
        return false;
    }else{
        *pVal=pQ->pBase[pQ->front];
        pQ->front=(pQ->front+1)%pQ->len;
        return true;
    }
}

//判断队列是否为空
bool is_empty(QUEUE* pQ)
{
    if(pQ->front==pQ->rear)
    {
        return true;
    }else{
        return false;
    }
}

//判断队列是否为满
bool is_full(QUEUE* pQ)
{
    if((pQ->rear+1)%pQ->len==pQ->front){
        return true;
    }else{
        return false;
    }
}

//遍历队列
void traverse_Queue(QUEUE* pQ)
{
    if(is_empty(pQ)){
        printf("该队列为空！\n");
    }else{
        printf("队列中的元素为：");
        for(int index=pQ->front;index!=pQ->rear;index=(index+1)%pQ->len){
            printf("%d ",pQ->pBase[index]);
        }
        printf("\n");
    }
}
