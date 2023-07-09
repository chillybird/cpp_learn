#include <iostream>
#include "utils.h"

using namespace std;

LinkedNode* reverseLinkedList(LinkedNode* head)
{
    LinkedNode* tmp;
    LinkedNode* pre = nullptr, *curr = head;
    while(curr != nullptr)
    {
        tmp = curr->next;
        curr->next = pre;
        pre = curr;
        curr = tmp;
    }
    return pre;
}

int main()
{
    LinkedNode* linkedlist = new LinkedNode(0);
    for (int i = 1; i <= 10; i++)
    {
        linkedList_add(linkedlist, i);
    }
    cout << "before:" << endl;
    linkedlist_print(linkedlist);
    LinkedNode* reversed_linkedlist = reverseLinkedList(linkedlist);
    cout << "after:" << endl;
    linkedlist_print(reversed_linkedlist);
    return 0;
}