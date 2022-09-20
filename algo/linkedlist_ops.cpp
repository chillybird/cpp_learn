#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>

using namespace std;

class MyLinkedList {
public:
    struct LinkedNode {
        int val;
        LinkedNode* next;
        LinkedNode(int val) : val(val), next(NULL) {}
    };

    MyLinkedList()
    {
        _size = 0;
        _dummyHead = new LinkedNode(0);
    }

    int get(int index)
    {
        if (index > _size - 1 || index < 0)
        {
            return -1;
        }
        LinkedNode* cur = _dummyHead -> next;
        while(index--)
        {
            cur = cur -> next;
        }
        return cur->val;
    }

    void addAtHead(int val)
    {
        LinkedNode* newNode  = new LinkedNode(val);
        newNode->next = _dummyHead->next;
        _dummyHead->next = newNode;
        _size++;
    }

    void addAtTail(int val)
    {
        LinkedNode *newNode = new LinkedNode(val);
        LinkedNode *cur = _dummyHead;
        while (cur->next != nullptr)
        {
            cur = cur->next;
        }
        cur->next = newNode;
        _size++;
    }

    void addAtIndex(int index, int val)
    {
        if (index > _size - 1 || index < 0)
        {
            return;
        }

        LinkedNode* newNode = new LinkedNode(val);
        LinkedNode* cur = _dummyHead;

        while(index--)
        {
            cur = cur->next;
        }
        newNode->next = cur->next;
        cur->next = newNode;
        _size++;
    }

    void deleteAtIndex(int index)
    {
        if (index > _size - 1 || index < 0)
        {
            return;
        }
        LinkedNode* cur = _dummyHead;
        while(index--)
        {
            cur = cur->next;
        }
        LinkedNode* tmp = cur->next;
        cur->next = cur->next->next;
        delete tmp;
        _size--;
    }
    void printLinkedList()
    {
        LinkedNode* cur = _dummyHead;
        int index = _size;
        while(index--)
        {
            cur = cur->next;
            cout << cur->val << " ";
        }
        cout << endl;
    }

private:
    int _size;
    LinkedNode* _dummyHead;
};

int main(){
    MyLinkedList linkedlist = MyLinkedList();
    linkedlist.addAtHead(1);
    linkedlist.addAtTail(3);
    linkedlist.addAtIndex(1,2);   //链表变为1-> 2-> 3
    cout << linkedlist.get(1) << endl;            //返回2
    linkedlist.deleteAtIndex(1);  //现在链表是1-> 3
    cout << linkedlist.get(1) << endl;           //返回3

    linkedlist.printLinkedList();

    return 0;
}