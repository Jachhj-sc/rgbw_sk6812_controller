#ifndef QUEUE_H
#define QUEUE_H
#include "Arduino.h"

bool queue_isEmpty();
bool queue_isFull();
byte dequeue();
bool enqueue(byte);
void queue_clear();

#endif
