#include <stdio.h>

//移动，打印移动步骤，方便理解
void move(char from,char to)
{
    printf("%c--->%c\n",from,to);
}

//汉诺塔主程序
//n--汉诺塔层数
//from--原始柱子
//temp--中间柱子
//to--目标柱子
void hanoi(int n,char from,char temp,char to)
{
    if(n==1){                    //从from到to只有一层，就直接移动
        move(from,to);           //递归截止条件
    }else{
        hanoi(n-1,from,to,temp); //把上面的n-1层，借助to，从from移动到temp
        move(from,to);           //最底层，从from到to
        hanoi(n-1,temp,from,to); //把tmep上的n-1层，借助from，移动到to上
    }
}

int main(void)
{
    int n;
    printf("请设置汉诺塔的层数：");
    scanf("%d",&n);
    hanoi(n,'A','B','C');

    return 0;
}

