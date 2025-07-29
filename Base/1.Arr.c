//连续存储的数组

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

struct Arr
{
    int* pBase;//指向第一个元素的指针
    int len;   //数组长度
    int cnt;   //有效元素个数
};

void init_arr(struct Arr *pArr,int length);      //初始化数组
bool append_arr(struct Arr *pArr,int val);    //追加（在末尾插入）
bool insert_arr(struct Arr *pArr,int pos,int val);    //插入（在任意位置插入）
bool delete_arr(struct Arr *pArr,int pos,int *pVal);    //删除
int get_arr(struct Arr *pArr,int pos);        //取得某个元素
bool is_empty(struct Arr *pArr);      //判断数组是否为空
bool is_full(struct Arr *pArr);       //判断数组是否为满
void sort_arr(struct Arr *pArr);      //排序
void show_arr(struct Arr *pArr);      //显示数组所有元素
void inversion_arr(struct Arr *pArr); //翻转数组元素

int main(void)
{
    struct Arr arr;

    init_arr(&arr,6); 
    append_arr(&arr,1);
    append_arr(&arr,3);
    append_arr(&arr,4);
    append_arr(&arr,6);
    insert_arr(&arr,2,15);
    show_arr(&arr);

    inversion_arr(&arr);
    show_arr(&arr);

    int val;  //接收被删除的数据
    if(delete_arr(&arr,2,&val)){
        printf("删除成功，您删除的元素是：%d\n",val);
    }
    show_arr(&arr);

    int val2=get_arr(&arr,1);
    printf("第%d个位置的元素是：%d\n",1,val2);

    append_arr(&arr,85);
    show_arr(&arr);

    sort_arr(&arr);
    show_arr(&arr);

    return 0;
}

//初始化数组
void init_arr(struct Arr *pArr,int length)
{
    pArr->pBase=(int*)malloc(sizeof(int)*length);
    if(pArr->pBase==NULL)
    {
        printf("动态分配内存失败！\n");
        exit(-1);  
    }
    else{
        pArr->len=length;
        pArr->cnt=0;
    }
    return;
}

//判断数组是否为空
bool is_empty(struct Arr *pArr)
{
    if(pArr->cnt==0){
        return true;
    }else{
        return false;
    }
}

//判断数组是否为满
bool is_full(struct Arr *pArr)
{
    if(pArr->cnt==pArr->len){
        return true;
    }else{
        return false;
    }
}

//显示数组所有已有元素
void show_arr(struct Arr *pArr)
{
    if(is_empty(pArr))
    {
        printf("该数组为空！\n");

    }else{
        for(int i=0;i<pArr->cnt;i++){
            printf("%d ",pArr->pBase[i]);
        }
        printf("\n");
    }
    return;
}

//追加数组元素（在末尾插入）
bool append_arr(struct Arr *pArr,int val)
{
    if(is_full(pArr)){
        printf("该数组已满，追加失败！\n");
        return false;
    }else{  //不满时追加
        pArr->pBase[pArr->cnt]=val;
        (pArr->cnt)++;
        return true;
    }
}

//在指定位置插入元素
bool insert_arr(struct Arr *pArr,int pos,int val)
{
    if(is_full(pArr)){
        printf("该数组已满，插入失败！\n");
        return false;
    }
    if(pos<1 || pos > pArr->cnt+1)
    {
        printf("插入位置错误，插入失败！\n");
        return false;
    }
    {  //不满时插入
        for(int i=pArr->cnt-1;i>=pos-1;i--){
            pArr->pBase[i+1]=pArr->pBase[i];//插入位置之后的元素后移
        }
        pArr->pBase[pos-1]=val;
        (pArr->cnt)++;
        return true;
    }
}

//翻转数组元素
void inversion_arr(struct Arr *pArr)
{
    int temp;
    for(int i=0, j=pArr->cnt-1;i<j;i++,j--){
        temp=pArr->pBase[i];
        pArr->pBase[i]=pArr->pBase[j];
        pArr->pBase[j]=temp;
    }    
}

//删除指定位置的元素
bool delete_arr(struct Arr *pArr,int pos,int *pVal)
{
     if(pos<1 || pos > pArr->cnt)
    {
        printf("删除位置错误，删除失败！\n");
        return false;
    }
    if(is_empty(pArr)){
        printf("该数组为空，删除失败！\n");
        return false;
    }
    {
        *pVal=pArr->pBase[pos-1];
        for(int i=pos;i<pArr->cnt;i++)
        {
            pArr->pBase[i-1]=pArr->pBase[i];
        }
        (pArr->cnt)--;
        return true;
    }
} 

//获取指定位置的元素
int get_arr(struct Arr *pArr,int pos)
{
    return pArr->pBase[pos-1];
}

//数组排序--冒泡
void sort_arr(struct Arr *pArr)
{
    int temp;
    for(int i=0;i<pArr->cnt;i++){
        for(int j=i+1;j<pArr->cnt;j++){
            if(pArr->pBase[i]<pArr->pBase[j]){
                temp=pArr->pBase[i];
                pArr->pBase[i]=pArr->pBase[j];
                pArr->pBase[j]=temp;
            }
        }
    }
}