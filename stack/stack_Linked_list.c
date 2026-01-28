/*
    用链表的形式实现栈
*/
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct Node{
    int data;
    struct Node* next;
}Node;

typedef struct Stack{
    Node* head;
}Stack;

void InitializeStack(Stack* Stack){
    Stack->head = NULL;
}

Node* CreateNode(int data){
    Node* newNode = (Node*)malloc(sizeof(Node));
    if(newNode == NULL){
        printf("Node create failed.");
        exit(1);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

int isEmpty(Stack* Stack){
    return Stack->head == NULL;
}

int peak(Stack* Stack){
    if(isEmpty(Stack)){
        printf("\nStack is Empty.");
        return INT_MIN;
    }
    else{
        return Stack->head->data;
    }
}

void Push(Stack* Stack,int data){
    Node* newNode = CreateNode(data);
    newNode->next = Stack->head;
    Stack->head = newNode;
}

void Pop(Stack* Stack){
    if(isEmpty(Stack)){
        printf("stack underflow.");
        return;
    }
    Node* temp = Stack->head;
    Stack->head = Stack->head->next;
    free(temp); 
}

int main(){
    Stack Stack;
    InitializeStack(&Stack);

    Push(&Stack,12);
    printf("第一次入栈的栈顶：%d\n",peak(&Stack));
    Push(&Stack,66);
    printf("第二次入栈的栈顶%d\n",peak(&Stack));
    Pop(&Stack);
    printf("出栈后的栈顶%d\n",peak(&Stack));
    return 0;
}