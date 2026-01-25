#include<stdio.h>
#include<stdlib.h>


// ==========================================
// 1. LeetCode 定义的数据结构 (不要改)
// ==========================================
struct ListNode{
    int val;
    struct ListNode *next;
};

// ==========================================
// 2. LeetCode 的核心解题函数 (在这里写题)
// ==========================================
struct ListNode* reverseList(struct ListNode* head) {
    if(head == NULL || head->next == NULL){
        return head;
    }
    struct ListNode *ret = reverseList(head->next);
    head->next->next = head;
    head->next = NULL;
    return ret;
}
// ==========================================
// 3. 本地调试辅助函数 (帮你手动造链表)
// ==========================================

/**
 * @brief 创建一个新节点
 */
struct ListNode *CreateNode(int val){
    struct ListNode *newNode = (struct ListNode*)malloc(sizeof(struct ListNode));
    newNode->val = val;
    newNode->next = NULL;
    return newNode;
}

/**
 * @brief  根据数组创建链表 (模拟 LeetCode 输入: head = [1,2,3,4,5])
 * @param  arr: 整数数组
 * @param  size: 数组大小
 * @return 链表头指针
 */
struct ListNode* createListFromArray(int* arr, int size){
    if(size == 0){return NULL;}
    struct ListNode *head = CreateNode(arr[0]);
    struct ListNode *curr = head;
    for (int i = 1; i < size; i++)
    {
        struct ListNode *temp = CreateNode(arr[i]);
        curr->next = temp;
        curr = temp;   
    }
    return head;   
}

/**
 * @brief  打印链表方便观察
 */
void printList(struct ListNode* head){
    struct ListNode *curr = head;
    while (curr != NULL)
    {
        printf("%d->",curr->val);
        curr = curr->next;
    }
    printf("NULL\n");
}

/**
 * @brief  释放内存 
 */
void freeList(struct ListNode* head){
    struct ListNode *curr = head;
    while (curr!=NULL)
    {
        struct ListNode *temp = curr;
        curr = curr->next;
        free(temp);
    }
}


// ==========================================
// 4. Main 函数入口
// ==========================================
int main() {
    // 模拟输入数据
    int arr[] = {1, 2, 3, 4, 5};
    int n = sizeof(arr) / sizeof(arr[0]);

    // 1. 手动创建链表
    printf("创建链表...\n");
    struct ListNode* head = createListFromArray(arr, n);
    
    // 打印原始链表
    printf("原始链表: ");
    printList(head);

    // 2. 调用算法函数
    printf("正在反转...\n");
    struct ListNode* newHead = reverseList(head);

    // 3. 验证结果
    printf("反转结果: ");
    printList(newHead);

    // 4. 清理内存
    freeList(newHead);

    // 为了防止窗口一闪而过 (Windows)
    system("pause"); 
    return 0;
}