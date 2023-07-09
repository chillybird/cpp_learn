#include <stdio.h>
#include "CircularQueue.h"

int main()
{
    CircularQueue queue;
    int size = 5;

    // 初始化循环队列
    initCircularQueue(&queue, size);

    // 入队操作
    enqueue(&queue, 1);
    enqueue(&queue, 2);
    enqueue(&queue, 3);

    // 出队操作
    int value1 = dequeue(&queue);
    printf("Dequeued value: %d\n", value1);

    // 打印循环队列中的元素
    printCircularQueue(&queue);

    // 入队操作
    enqueue(&queue, 4);
    enqueue(&queue, 5);

    // 打印循环队列中的元素
    printCircularQueue(&queue);

    // 继续入队，此时循环队列已满
    enqueue(&queue, 6);

    // 销毁循环队列
    destroyCircularQueue(&queue);

    return 0;
}