//多项式加法和乘法
//用链表表示多项式，每一个节点为每一项
#include <stdio.h>
#include <stdlib.h>

#include <time.h>  //查看计算时间，比较时间复杂度
clock_t start,stop;
double duration;
//多项式结构体
typedef struct PolyNode
{
    int coef;
    int expon;
    struct PolyNode* Next;
}POLYNODE,*PPOLYNODE;

//函数声明
PPOLYNODE ReadPoly();  //读取多项式
void Attach(int,int,PPOLYNODE*);  //连接多项式的每一项
void PrintPoly(PPOLYNODE);       //打印多项式
PPOLYNODE Add(PPOLYNODE,PPOLYNODE);  //多项式加法
PPOLYNODE Mult_f1(PPOLYNODE,PPOLYNODE); //多项式乘法:多个加法
PPOLYNODE Mult_f2(PPOLYNODE,PPOLYNODE); //多项式乘法:逐项加入放

int main(void)
{
    PPOLYNODE p1=ReadPoly();
    PrintPoly(p1);
    PPOLYNODE p2=ReadPoly();
    PrintPoly(p2);

    PPOLYNODE pAdd=Add(p1,p2);
    PrintPoly(pAdd);

    // PPOLYNODE pMult_f1=Mult_f1(p1,p2);
    // PrintPoly(pMult_f1);

    // PPOLYNODE pMult_f2=Mult_f1(p1,p2);
    // PrintPoly(pMult_f2);

    // int max_time=1000000;

    // start=clock();
    // for(int i=0;i<max_time;i++){
    //     PPOLYNODE pMult=Mult_f1(p1,p2);
    //     free(pMult);
    //     pMult=NULL;
    // }
    // stop=clock();
    // duration=((double)(stop-start))/CLK_TCK;
    // printf("ticks of f1=%f\n",(double)(stop-start));
    // printf("duration of f1=%6.2f\n",duration);

    // start=clock();
    // for(int i=0;i<max_time;i++){
    //     PPOLYNODE pMult=Mult_f2(p1,p2);
    //     free(pMult);
    //     pMult=NULL;
    // }
    // stop=clock();
    // duration=((double)(stop-start))/CLK_TCK;
    // printf("ticks of f2=%f\n",(double)(stop-start));
    // printf("duration of f2=%6.2f\n",duration);   

    return 0;
}

//函数定义

//读取多项式/多项式初始化
PPOLYNODE ReadPoly()
{
    int N; //多项式个数
    printf("请输入多项式的数量：");
    scanf("%d",&N);
    PPOLYNODE pHead=(PPOLYNODE)malloc(sizeof(POLYNODE));
    pHead->Next=NULL;
    PPOLYNODE pRear=pHead;
    for(int i=0;i<N;i++){
        int c,e;
        printf("请输入第%d项的系数和次数：",i+1);
        scanf("%d %d",&c,&e);
        Attach(c,e,&pRear);
    }
    // PPOLYNODE t=(PPOLYNODE)malloc(sizeof(POLYNODE));
    // t=pHead;
    // pHead=pHead->Next;
    // free(t);
    return pHead;
}

//连接多项式的每一项
void Attach(int c,int e,PPOLYNODE* pRear)
{
    PPOLYNODE pNew=(PPOLYNODE)malloc(sizeof(POLYNODE));
    pNew->coef=c;     //新节点赋值
    pNew->expon=e;
    pNew->Next=NULL;
    (*pRear)->Next=pNew; //连接新节点
    (*pRear)=pNew;       //尾指针后移
}
//打印多项式
void PrintPoly(PPOLYNODE pHead)
{
    PPOLYNODE t=pHead->Next;
    printf("y=");
    while(t!=NULL){
        printf("%dx^%d",t->coef,t->expon);
        t=t->Next;
        if(t!=NULL){printf("+");}
    }
    printf("\n");
}    

//多项式加法
PPOLYNODE Add(PPOLYNODE pHead1,PPOLYNODE pHead2)
{
    PPOLYNODE t1=pHead1->Next,t2=pHead2->Next;
    PPOLYNODE pRes=(PPOLYNODE)malloc(sizeof(POLYNODE));  //结果多项式
    pRes->Next=NULL;
    PPOLYNODE pRear=pRes;
    while(t1!=NULL && t2!=NULL){
        if(t1->expon==t2->expon) //指数相同
        {
            int sum=t1->coef+t2->coef;
            if(sum){
                Attach(sum,t1->expon,&pRear);
            }            
            t1=t1->Next;
            t2=t2->Next;
        }else if(t1->expon<t2->expon){  //指数不同，先放大的
            Attach(t1->coef,t1->expon,&pRear);
            t1=t1->Next;
        }else{
            Attach(t2->coef,t2->expon,&pRear);
            t2=t2->Next;
        }
    }
    while(t1!=NULL){
        Attach(t1->coef,t1->expon,&pRear);
        t1=t1->Next;
    }
    while(t2!=NULL){
        Attach(t2->coef,t2->expon,&pRear);
        t2=t2->Next;
    }
    return pRes;
}

//多项式乘法:多个加法
PPOLYNODE Mult_f1(PPOLYNODE pHead1,PPOLYNODE pHead2)
{
    PPOLYNODE t1=pHead1->Next,t2=pHead2->Next;
    PPOLYNODE pRes=(PPOLYNODE)malloc(sizeof(POLYNODE));
    pRes->Next=NULL;
    while(t1!=NULL){
        PPOLYNODE pTemp_head=(PPOLYNODE)malloc(sizeof(POLYNODE));//单个元素乘第二个式子
        pTemp_head->Next=NULL;
        PPOLYNODE pTemp_rear=pTemp_head;
        while(t2!=NULL){
            Attach(t1->coef*t2->coef,t1->expon+t2->expon,&pTemp_rear);
            t2=t2->Next;
        }
        pRes=Add(pRes,pTemp_head);  //结果累加
        free(pTemp_head); pTemp_head=NULL;   //内存释放
        free(pTemp_rear); pTemp_rear=NULL;        
        t2=pHead2->Next;
        t1=t1->Next;
    }
    return pRes;
}

//多项式乘法:逐项加入放
PPOLYNODE Mult_f2(PPOLYNODE pHead1,PPOLYNODE pHead2)
{
    PPOLYNODE t1=pHead1->Next,t2=pHead2->Next;
    PPOLYNODE pRes=(PPOLYNODE)malloc(sizeof(POLYNODE));
    pRes->Next=NULL;
    PPOLYNODE pRear=pRes;

    while(t2!=NULL){  //第一个元素和第二个式子相乘，构建初始式子
        Attach(t1->coef*t2->coef,t1->expon+t2->expon,&pRear);
        t2=t2->Next;
    }
    t1=t1->Next;
    //逐项相乘
    while(t1!=NULL){
        t2=pHead2->Next;
        pRear=pRes;
        while(t2!=NULL){
            int c=t1->coef*t2->coef;
            int e=t1->expon+t2->expon;
            //比较指数大小，找到插入结果的位置
            while(pRear->Next!=NULL && pRear->Next->expon<e){
                pRear=pRear->Next;
            }
            if(pRear->Next!=NULL && pRear->Next->expon==e){
                if(pRear->Next->expon+c){  //系数不为零
                    pRear->Next->expon+=c;
                }else{                     //系数为零
                    PPOLYNODE temp=pRear->Next;
                    pRear->Next=temp->Next;
                    free(temp);
                    temp=NULL;
                }
            }else{
                PPOLYNODE temp=(PPOLYNODE)malloc(sizeof(POLYNODE));
                temp->coef=c;
                temp->expon=e;
                temp->Next=NULL;
                pRear->Next=temp;
                pRear=temp;
            }
            t2=t2->Next;
        }        
        t1=t1->Next;
    }    
    return pRes;
}
