#include <stdio.h>
#include <stdbool.h>

#define MAX_PEOPLE 50

typedef struct {
    int id;
} People;

typedef struct {
    People data[MAX_PEOPLE];
    int head;
    int tail;
    int count;
} Queue;

int main() {
    Queue q;
    int total_people=50;
    int report_interval=5;

    // 初始化队列
    q.head = 0;
    q.tail = 0;
    q.count = 0;

    // 1~50 号人入队
    for (int i = 1; i <= total_people; i++) {
        q.data[q.tail].id = i;
        q.tail = (q.tail + 1) % MAX_PEOPLE;
        q.count++;
    }

    // 模拟报数淘汰
    while (q.count > 1) {
        // 前 report_interval-1 个人：出队再入队
        for (int i = 0; i < report_interval - 1; i++) {
            q.data[q.tail] = q.data[q.head];
            q.head = (q.head + 1) % MAX_PEOPLE;
            q.tail = (q.tail + 1) % MAX_PEOPLE;
        }
        // 第 report_interval 个人：淘汰
        printf("淘汰: %d\n", q.data[q.head].id);
        q.head = (q.head + 1) % MAX_PEOPLE;
        q.count--;
    }

    printf("最后剩下的人是: %d\n", q.data[q.head].id);

    return 0;
}