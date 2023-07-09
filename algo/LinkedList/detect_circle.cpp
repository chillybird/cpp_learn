#include <iostream>
#include "utils.h"

using namespace std;

// https://www.programmercarl.com/0142.%E7%8E%AF%E5%BD%A2%E9%93%BE%E8%A1%A8II.html#%E6%80%9D%E8%B7%AF
LinkedNode* detectCircle(LinkedNode* head)
{
    LinkedNode* slow = head;
    LinkedNode* fast = head;
    while(fast != nullptr && fast->next != nullptr)
    {
        slow = slow -> next;
        fast = fast -> next -> next;
        if(slow == fast) // 环内相遇
        {
            // x = (n - 1) (y + z) + z，x表示头节点到入环节点的个数，(y+z)表示环的大小，z表示慢指针在环中前进的距离
            fast = head;
            while(slow != fast)
            {
                slow = slow->next;
                fast = fast->next;
            }
            return fast;
        }
    }
    return nullptr;
}

int main()
{
    LinkedNode* linkedlist = new LinkedNode(0);
    for (int i = 1; i <= 10; i++)
    {
        linkedList_add(linkedlist, i);
    }
    LinkedNode* tmp = linkedlist->next->next;
    LinkedNode* curr = linkedlist;
    while(curr->next != nullptr)
    {
        curr = curr->next;
    }
    curr->next = tmp;
    cout << detectCircle(linkedlist)->val << endl;
    return 0;
}