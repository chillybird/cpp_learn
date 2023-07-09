#ifndef __CIRCULARQUEUE_H__
#define __CIRCULARQUEUE_H__

#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int* data;
    int front;
    int rear;
    int _size;
    int _count;
} CircularQueue;

// 初始化循环队列
void initCircularQueue(CircularQueue* queue, int size)
{
    queue->data = (int*)malloc(sizeof(int)*size);
    queue->front = 0;
    queue->rear = 0;
    queue->_size = size;
    queue->_count = 0;
}

// 判断循环队列是否为空
int isCircularQueueEmpty(CircularQueue* queue) {
    return queue->_count == 0;
}

// 判断循环队列是否已满
int isCircularQueueFull(CircularQueue* queue) {
    return queue->_count == queue->_size;
}

void enqueue(CircularQueue* queue, int value)
{
    if (isCircularQueueFull(queue)) {
        printf("Circular Queue is full. Cannot enqueue.\n");
        return;
    }

    queue->data[queue->rear] = value;
    queue->rear = (queue->rear + 1) % queue->_size;
    queue->_count++;
}

// 出队操作
int dequeue(CircularQueue* queue) {
    if (isCircularQueueEmpty(queue)) {
        printf("Circular Queue is empty. Cannot dequeue.\n");
        return -1;
    }

    int value = queue->data[queue->front];
    queue->front = (queue->front + 1) % queue->_size;
    queue->_count--;

    return value;
}

// 打印循环队列中的元素
void printCircularQueue(CircularQueue* queue) {
    if (isCircularQueueEmpty(queue)) {
        printf("Circular Queue is empty.\n");
        return;
    }

    printf("Circular Queue: ");
    int i = queue->front;
    for (int count = 0; count < queue->_count; count++) {
        printf("%d ", queue->data[i]);
        i = (i + 1) % queue->_size;
    }
    printf("\n");
}

// 销毁循环队列，释放内存
void destroyCircularQueue(CircularQueue* queue) {
    free(queue->data);
    queue->data = NULL;
    queue->front = 0;
    queue->rear = 0;
    queue->_size = 0;
    queue->_count = 0;
}

#endif // CIRCULARQUEUE_H__