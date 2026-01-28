/**
 * 通过栈的方式实现字符串反转
 */

#include <stdio.h>
#include <string.h>

#define MAX_SIZE_ARRAY 10   //数组的最大值,capacity=10

typedef struct Stack{
    char array[MAX_SIZE_ARRAY];
    int top;
} Stack;

void InintializeStack(Stack* Stack){
    Stack->top = -1;   //栈顶的位置
}

int isEmpty(Stack* Stack){
    return -1 ==Stack->top;
}

int isFull(Stack* Stack){
    if(Stack->top == MAX_SIZE_ARRAY-1){
        return 1;
    }
    else return 0;
}

void Push(Stack* Stack,char x){
    if(Stack->top>=(MAX_SIZE_ARRAY-1)){
        printf("Overflow");
        return;
    }
    Stack->top++;
    Stack->array[Stack->top] = x;
}

char Pop(Stack* Stack){
    if (!isEmpty(Stack))
    {
        char c = Stack->array[Stack->top];
        Stack->top--;
        return c;
    }
    return '\0';
}

char top_peek(Stack* Stack){
    return Stack->array[Stack->top];
}

void print(Stack* Stack){
    if(-1 == Stack->top){
        printf("栈为空,无法出栈");
        return;
    }
    printf("栈内容:");
    for (int i = 0; i <= Stack->top; i++)
    {
        printf("%c ",Stack->array[i]);
    }
    printf("\n");
}

//通过栈的形式实现对数组的反转
void Stack_resrvse(char* str){
    Stack S;
    InintializeStack(&S);
    int len = strlen(str);
    for (int i = 0; i < len; i++)
    {
        Push(&S,str[i]);
    }
    for (int i = 0; i < len; i++)
    {
        str[i] = Pop(&S);
    }
}

int main(){
    int flag_test1=0;
    int flag_test2=0;
    if(flag_test1){
        char str[MAX_SIZE_ARRAY];
        printf("请输入字符串");
        scanf("%s",str);
        printf("Normal:%s\n",str);
        Stack_resrvse(str);
        printf("reserve:%s\n",str);    
    }
    if(flag_test2){}
    return 0;
}