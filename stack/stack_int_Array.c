/**
 * 用数组的形式实现栈
 */

#include <stdio.h>

#define MAX_SIZE_ARRAY 10   //数组的最大值,capacity=10
int array[MAX_SIZE_ARRAY];  //用数组存储信息，用栈记录索引
int top = -1;   //栈顶的位置

void Push(int x){
    if(top>=(MAX_SIZE_ARRAY-1)){
        printf("Overflow");
        return;
    }
    top++;
    array[top] = x;
}

void Pop(void){
    if(-1 == top){
        printf("栈为空,无法出栈");
        return;
    }
    top--;
}

int top_peek(){
    return array[top];
}

void print(){
    if(-1 == top){
        printf("栈为空,无法出栈");
        return;
    }
    printf("栈内容:");
    for (int i = 0; i <= top; i++)
    {
        printf("%d ",array[i]);
    }
    printf("\n");
}

int main(){
    Push(5); print();
    Push(3); print();
    Pop(); print();
    printf("%d ",top_peek());

    return 0;
}