#ifndef QUEUE_H
#define QUEUE_H
#include <exception>

template <class T>
struct Title
{
	T name;
	Title *next, *prev;
};

template <class T>
class Queue {
  public:
    Queue();
    
    ~Queue();

    void enqueue (const T & item);
      /* adds the item to the end of the queue.
         The same item may be added many times. */

    void dequeue (); 
      /* removes the front element of the queue. 
         Throws an EmptyQueueException when called on an empty queue.
         EmptyQueueException should inherit from std::exception. */

    const T & peekFront ();
      /* returns the front element of the queue. 
         Throws an EmptyQueueException when called on an empty queue.
         EmptyQueueException should inherit from std::exception. */

    bool isEmpty ();
      /* returns whether the queue is empty. */
  private:
    Title<T> *head, *tail;
};

class EmptyQueueException : public exception
{
	
};
#include "QueueImp.h"
#endif
