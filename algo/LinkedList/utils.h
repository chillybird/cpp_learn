#ifndef __UTILS_H__
#define __UTILS_H__

#include <iostream>

/* 链表 */
struct LinkedNode
{
    int val;
    LinkedNode *next;
    LinkedNode(int val) : val(val), next(nullptr){};
};

void linkedList_add(LinkedNode* head, int val)
{
    LinkedNode* node = new LinkedNode(val);

    LinkedNode* curr = head;
    while (curr->next != nullptr)
    {
        curr = curr->next;
    }
    curr->next = node;
}

void linkedlist_print(LinkedNode* head)
{
    LinkedNode* curr = head;
    while(curr != nullptr)
    {
        std::cout << curr->val << " ";
        curr = curr -> next;
    }
    std::cout << std::endl;
}

#endif // UTILS_H__