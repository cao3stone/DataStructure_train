//离散存储的数组--链表

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node
{
    int data;  //数据域
    struct Node* pNext; //指针域
}NODE,*PNODE;  //NODE等价于 struct Node, PNODE等价于 struct Node*


//函数声明
PNODE create_list(void);     //创建链表
void traverse_list(PNODE);   //遍历链表
bool is_empty_list(PNODE);   //判断链表是否为空
int length_list(PNODE);      //获取链表长度
bool insert_list(PNODE,int,int);  //在指定位置插入数据
bool delete_list(PNODE,int,int*); //删除指定位置的数据
void sort_list(PNODE);           //链表元素排序

int main(void)
{
    PNODE pHead=create_list();
    traverse_list(pHead);

    if(insert_list(pHead,5,84)){
        printf("插入成功，新的链表为：");
        traverse_list(pHead);
    }else{
        printf("插入失败\n");
    }

    int delete_val;
    if(delete_list(pHead,8,&delete_val)){
        printf("删除成功，删除的值是:%d\n",delete_val);
    }else{
        printf("删除失败\n");
    }

    sort_list(pHead);
    traverse_list(pHead);

    // int len=length_list(pHead);

    // if(is_empty_list(pHead)){
    //     printf("链表为空");
    // }else{
    //     printf("链表不为空,长度为：%d",len);
    // }


    return 0;
}

//创建链表
PNODE create_list(void)
{
    int len; //链表长度
    printf("请确定链表的节点个数：");
    scanf("%d",&len);

    PNODE pHead=(PNODE)malloc(sizeof(NODE));  //创建头节点
    if(pHead==NULL) //判断链表是否创建成功
    {
        printf("创建链表失败，程序终止！\n");
        exit(-1);
    }

    PNODE pTail=pHead;  //定义一个尾指针，永远指向最后一个节点
    pTail->pNext=NULL;

    for(int i=0;i<len;i++)
    {
        int val; //临时接收数据
        printf("请输入第%d个元素的值：",i+1);
        scanf("%d",&val);

        PNODE pNew=(PNODE)malloc(sizeof(NODE));  //创建新的节点
        if(pNew==NULL) //判断链表是否创建成功
        {
            printf("创建链表失败，程序终止！\n");
            exit(-1);
        }
        pNew->data=val;        
        pNew->pNext=NULL;
        pTail->pNext=pNew;
        pTail=pNew;
    }
    return pHead;
} 

//遍历链表并显示所有元素
void traverse_list(PNODE pHead)
{
    PNODE p=pHead->pNext;  //定义一个临时指针p，永远指向下一个节点的下一个指针
    while(p!=NULL)
    {
        printf("%d",p->data);
        printf(" ");
        p=p->pNext;  //临时指针后移一个
    }
    printf("\n");
}

//判断链表是否为空
bool is_empty_list(PNODE pHead)
{
    if(pHead->pNext==NULL){
        return true;
    }else{
        return false;
    }
}

//获取链表长度
int length_list(PNODE pHead)
{
    int len=0;
    PNODE p=pHead->pNext;  //定义一个临时指针p，永远指向下一个节点的下一个指针
    while(p!=NULL)
    {
        len++;
        p=p->pNext;  //临时指针后移一个
    }
    return len;
}  

//链表元素排序（冒泡排序）
void sort_list(PNODE pHead)
{
    int len=length_list(pHead); //获取链表长度
    int i,j,temp;
    PNODE p,q;
    for(i=0,p=pHead->pNext;i<len-1;i++,p=p->pNext){
        for(j=i+1,q=p->pNext;j<len;j++,q=q->pNext){
            if(p->data<q->data){  //a[i]<a[j]
                temp=p->data;   //temp=a[i];
                p->data=q->data;//a[i]=a[j];
                q->data=temp;//a[j]=temp;
            }
        }
    }
}

//在指定位置插入数据,在pos处，插入val
bool insert_list(PNODE pHead,int pos,int val)
{
    int i=0;
    PNODE p=pHead;
    while(p!=NULL && i<pos-1){
        i++;
        p=p->pNext;
    }
    if(p==NULL || i>pos-1){
        return false;
    }  //从 while 到 if 是为了判断插入位置 pos 是否符合要求，是否在已有节点之中，并将p指向pos位置前一个节点

    PNODE pNew=(PNODE)malloc(sizeof(NODE)); //创建新的节点
    if(pNew==NULL) //判断链表是否创建成功
    {
        printf("创建新节点失败，程序终止！\n");
        exit(-1);
    }
    pNew->data=val;    //新节点赋值
    PNODE q=p->pNext;  //创建一个临时节点，指向p的下一个节点（原先pos位置上的节点）
    p->pNext=pNew;     //p的下一个节点指向pNew（pNew添加到pos位置上）
    pNew->pNext=q;     //pNew指向原先pos位置上的节点（连上）

    return true;
}

//删除指定位置的数据，删除pos位置上的值，并用pVal接收它
bool delete_list(PNODE pHead,int pos,int* pVal)
{
    int i=0;
    PNODE p=pHead;
    while(p!=NULL && i<pos-1){
        i++;
        p=p->pNext;
    }
    if(p==NULL || i>pos-1){
        return false;
    }  //从 while 到 if 是为了判断插入位置 pos 是否符合要求，是否在已有节点之中，并将p指向pos位置前一个节点

   PNODE q=p->pNext;  //临时节点q指向pos位置上的节点
   *pVal=q->data;    

   p->pNext=p->pNext->pNext;  //跳过pos位置上的节点
   free(q);  //释放临时指针
   q=NULL;   //避免成为野指针

   return true;
}