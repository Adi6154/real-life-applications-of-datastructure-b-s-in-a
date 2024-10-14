#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100


typedef struct {
    char name[100];
    int priority;
} Road;


typedef struct {
    Road roads[MAX];
    int size;
} PriorityQueue;


void insert(PriorityQueue *pq, char name[], int priority);
Road extractMin(PriorityQueue *pq);
void heapify(PriorityQueue *pq, int i);
void swap(Road *a, Road *b);
void displaySchedule(PriorityQueue pq);

int main() {
    PriorityQueue pq;
    pq.size = 0;

    int choice;
    char name[100];
    int priority;

    while (1) {
        printf("\n--- Road Repair Scheduling ---\n");
        printf("1. Add a Road\n");
        printf("2. Schedule Next Repair\n");
        printf("3. Display Repair Schedule\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter Road Name: ");
                scanf("%s", name);
                printf("Enter Priority (1 is highest): ");
                scanf("%d", &priority);
                insert(&pq, name, priority);
                break;
            case 2:
                if (pq.size > 0) {
                    Road next = extractMin(&pq);
                    printf("Next road to be repaired: %s (Priority: %d)\n", next.name, next.priority);
                } else {
                    printf("No roads to repair.\n");
                }
                break;
            case 3:
                if (pq.size > 0) {
                    displaySchedule(pq);
                } else {
                    printf("No roads in the schedule.\n");
                }
                break;
            case 4:
                exit(0);
            default:
                printf("Invalid choice!\n");
        }
    }

    return 0;
}


void insert(PriorityQueue *pq, char name[], int priority) {
    if (pq->size == MAX) {
        printf("Queue is full!\n");
        return;
    }

    pq->size++;
    int i = pq->size - 1;
    strcpy(pq->roads[i].name, name);
    pq->roads[i].priority = priority;

    // Fix the min-heap property
    while (i != 0 && pq->roads[(i - 1) / 2].priority > pq->roads[i].priority) {
        swap(&pq->roads[i], &pq->roads[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}


Road extractMin(PriorityQueue *pq) {
    if (pq->size <= 0) {
        printf("Queue is empty!\n");
        exit(1);
    }

    Road root = pq->roads[0];
    if (pq->size == 1) {
        pq->size--;
        return root;
    }

    pq->roads[0] = pq->roads[pq->size - 1];
    pq->size--;

    heapify(pq, 0);

    return root;
}


void heapify(PriorityQueue *pq, int i) {
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < pq->size && pq->roads[left].priority < pq->roads[smallest].priority) {
        smallest = left;
    }

    if (right < pq->size && pq->roads[right].priority < pq->roads[smallest].priority) {
        smallest = right;
    }

    if (smallest != i) {
        swap(&pq->roads[i], &pq->roads[smallest]);
        heapify(pq, smallest);
    }
}


void swap(Road *a, Road *b) {
    Road temp = *a;
    *a = *b;
    *b = temp;
}


void displaySchedule(PriorityQueue pq) {
    printf("\nCurrent Repair Schedule (by Priority):\n");
    for (int i = 0; i < pq.size; i++) {
        printf("Road: %s (Priority: %d)\n", pq.roads[i].name, pq.roads[i].priority);
    }
}
