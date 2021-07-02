#include "queue.h"

#define SIZE 100

byte inp_arr[SIZE];
int Rear = - 1;
int Front = - 1;

bool enqueue(byte insert_item) {
  if (Rear == SIZE - 1)
    return 0;
  else {
    if (Front == - 1) {
      Front = 0;
    }
    Rear = Rear + 1;
    inp_arr[Rear] = insert_item;
    return 1;
  }
}

byte dequeue() {
  if (Front == - 1 || Front > Rear) {
    return -1;
  }
  else {
    return inp_arr[Front++];
  }
}

bool queue_isEmpty() {
  if (Front == - 1) {
    return 1;
  } else {
    return 0;
  }
}


bool queue_isFull() {
  if (Rear >= SIZE - 1) {
    return 1;
  } else {
    return 0;
  }
}

void queue_clear() {
  int Rear = - 1;
  int Front = - 1;
}
