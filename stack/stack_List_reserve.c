/**
 *  通过栈的方式实现链表反转
 */
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_VALUE 20

typedef struct Node{
    int data;
    struct Node* next;
}Node;

typedef struct Stack{
    Node* data[MAX_VALUE];
    int top;
}Stack;

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

void InitializeStack(Stack* Stack){
    Stack->top = -1;
}

int isEmpty(Stack* Stack){
    return Stack->top == -1;
}

int isFull(Stack* Stack){
    return Stack->top == MAX_VALUE-1;
}

void Push(Stack* Stack,Node* node){
    if(!isFull(Stack)){
        Stack->top++;
        Stack->data[Stack->top] = node; 
    }
}

Node* Pop(Stack* Stack){
    if(!isEmpty(Stack)){
        Node* node = Stack->data[Stack->top];
        Stack->top--;
        return node;
    }
    return NULL;
}

int peak(Stack* Stack){
    if(isEmpty(Stack)){
        printf("\nStack is Empty.");
        return INT_MIN;
    }
    else{
        return Stack->data[Stack->top]->data;
    }
}

void Linked_list_reserve(Node** head){
    if(*head == NULL || (*head)->next == NULL){return;}

    Stack Stack;
    InitializeStack(&Stack);
    Node* temp = *head;

    while (temp!= NULL)
    {
        Push(&Stack,temp);
        temp = temp->next;
    }

    *head = Pop(&Stack);
    temp = *head;
    while (!isEmpty(&Stack))
    {
        temp->next=Pop(&Stack);
        temp = temp->next;
    }
    temp->next = NULL;
}

void Print(Node* head){
    Node* temp = head;
    while (temp != NULL)
    {
        printf("%d->",temp->data);
        temp = temp->next;
    }
    printf("\n");
}

int main(){
    Node* head = CreateNode(2);
    head->next = CreateNode(8);
    head->next->next = CreateNode(9);
    Print(head);
    Linked_list_reserve(&head);
    Print(head);
    return 0;
}