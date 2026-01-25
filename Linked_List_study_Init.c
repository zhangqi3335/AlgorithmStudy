#include <stdio.h>
#include <stdlib.h>

typedef struct List_Node{
    int data;
    struct List_Node *next;
} Node;

Node* Create_New_Node(int data){
    Node* newNode = (Node*)malloc(sizeof(Node));
    if(newNode == NULL){
        printf("memory allocation failed.\n");
        exit(1);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void insert_to_head(Node** head,int data){
    Node* new_node = Create_New_Node(data);
    new_node->next = *head;
    *head = new_node;
}

void insert_to_end(Node** head,int data){
    Node* new_node = Create_New_Node(data);
    if(NULL == *head){
        *head = new_node;
        return;
    }
    Node* temp = *head;
    while(NULL != temp->next){
        temp = temp->next;
    }
    temp->next = new_node;
}

void insert_at_position(Node** head,int data,int position){
    if(position <= 0){
        printf("Invalid Position\n");
        return;
    }
    if(position == 1){
        insert_to_head(head,data);
        return;
    }

    Node* new_node = Create_New_Node(data);
    Node* temp = *head;

    for(int i=0;(temp!=NULL)&&(i<(position-2));i++){
        temp = temp->next;
    }

    if(temp == NULL){
        printf("Position out of bound\n");
        free(new_node);
        return;
    }

    new_node->next = temp->next;
    temp->next = new_node;
}

void delete_from_head(Node** head){
    if(*head == NULL){
        return;
    }
    Node* temp = *head;
    *head = temp->next;
    free(temp);
}

void delete_from_last(Node** head){
    if(*head == NULL){
        return;
    }
    if((*head)->next == NULL){
        free(*head);
        *head = NULL;
        return;
    }
    Node* temp = *head;
    while(temp->next->next != NULL){
        temp = temp->next;
    }
    free(temp->next);
    temp->next = NULL;
}

void delete_at_position(Node** head,int position){
    if(*head == NULL || position <= 0){
        return;
    }
    if(position == 1){
        delete_from_head(head);
        return;
    }

    Node* temp = *head;
    for(int i=0;(temp!=NULL)&&(i<(position-2));i++){
        temp = temp->next;
    }

    if(temp == NULL || temp->next == NULL){
        return;
    }

    Node* next = temp->next->next;
    free(temp->next);
    temp->next = next;
}

//Function to reserve theLinked_list
void reserve_iterative(Node** head){
    Node* current = *head;
    Node* prev = NULL;
    while(current != NULL){
        Node* next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    *head = prev;
}

void print(Node* head){
    while(head){
        printf("%d ", head->data);
        head = head->next;
    }
    printf("\n");
}

void reverse_print(Node* head){
    if(NULL == head){
        return;
    }
    reverse_print(head->next);
    printf("%d ",head->data);
}

int main(){
    int test_flag = 1; // 0 停止测试，其他值开启测试
    int test_reverse_print = 1; // 控制 reverse_print 测试
    int test_insert_at_position = 0; // 控制 insert_at_position 测试
    int test_delete_from_head = 0; // 控制 delete_from_head 测试
    int test_delete_from_last = 0; // 控制 delete_from_last 测试
    int test_delete_at_position = 0; // 控制 delete_at_position 测试
    int test_reserve_iterative = 0; // 控制 reserve_iterative 测试
    if (test_flag != 0) {
        Node* head = NULL;
        // 初始化链表
        insert_to_head(&head, 3);
        insert_to_head(&head, 2);
        insert_to_head(&head, 1);
        printf("Original List: ");
        print(head);
        printf("\n");
        // 测试 reverse_print
        if (test_reverse_print != 0) {
            printf("Reversed List: ");
            reverse_print(head);
            printf("\n");
        }
        // 测试 insert_at_position
        if (test_insert_at_position != 0) {
            insert_at_position(&head, 4, 2);
            printf("List after inserting 4 at position 2: ");
            print(head);
            printf("\n");
        }
        // 测试 delete_from_head
        if (test_delete_from_head != 0) {
            delete_from_head(&head);
            printf("List after deleting from head: ");
            print(head);
            printf("\n");
        }
        // 测试 delete_from_last
        if (test_delete_from_last != 0) {
            delete_from_last(&head);
            printf("List after deleting from last: ");
            print(head);
            printf("\n");
        }
        // 测试 delete_at_position
        if (test_delete_at_position != 0) {
            delete_at_position(&head, 2);
            printf("List after deleting at position 2: ");
            print(head);
            printf("\n");
        }
        // 测试 reserve_iterative
        if (test_reserve_iterative != 0) {
            insert_to_head(&head, 5);
            insert_to_head(&head, 4);
            insert_to_head(&head, 3);
            insert_to_head(&head, 2);
            insert_to_head(&head, 1);
            printf("List before reversing iteratively: ");
            print(head);
            printf("\n");
            reserve_iterative(&head);
            printf("List after reversing iteratively: ");
            print(head);
            printf("\n");
        }
        // 释放链表内存
        while (head != NULL) {
            Node* temp = head;
            head = head->next;
            free(temp);
        }
    }
    return 0;
}