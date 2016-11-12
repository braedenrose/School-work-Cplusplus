// File name: DblQueue.cpp
// Author: braeden rose

// Email: braeden.rose@vanderbilt.edu
// Class: CS2201 @ Vanderbilt U.
// Assignment Number: 6
// Description: 
// A linked-list implementation of the queue class. The queues hold items of type double, and
// allow the user to construct, add to, subtract from, and investigate the size of the queue using 
// the methods in the class. Every method has a worst case constant time runtime. 
// Honor statement: this is my originial work.
// Last Changed: 3-28-16

#include <cstddef> // for NULL
#include <stdexcept>
#include "DblQueue.h"
using namespace std;

//Class Constructor
//Creates an empty queue, initializes front and back are same
DblQueue::DblQueue() :
	myFront(nullptr),
	myBack(nullptr),
	mySize(0)
{
}

//Copy constructor
// pre:  Class object, aQueue, exists
// post: Object is initialized to be a copy of the parameter
DblQueue::DblQueue(const DblQueue& aQueue) :
	mySize(0),
	myFront(nullptr),
	myBack(nullptr)
{
	if (!aQueue.isEmpty())
	{
		queuePtr temp = aQueue.myFront;
		for (size_t i = 0; i < aQueue.size(); i++)
		{
			enqueue(temp->val);
			temp = temp->next;
		}
	}
}

// Class Destructor
// Destroys a queue
// pre:  Class object exists
// post: Class object does not exist
DblQueue::~DblQueue() {
	while (!isEmpty())
	{
		dequeue();
	}
}


// Assignment operator
// Assigns a queue to another
// pre: both class objects exist
// post: this class object gets assigned a copy of the parameter class object
const DblQueue& DblQueue::operator= (const DblQueue& rhs) {
	if (this != &rhs)
	{
		DblQueue temp(rhs);
		std::swap(myFront, temp.myFront);
		std::swap(myBack, temp.myBack);
		std::swap(mySize, temp.mySize);
	} 
	return *this;
}

// isEmpty
// Checks if the queue is empty
// pre:  A queue exists.
// post: Returns true if it IS empty, false if NOT empty.
bool DblQueue::isEmpty() const {
	if (myFront == nullptr)
		return true;
	else
		return false;
}

// enqueue
// enqueues an item to back of the queue.
// pre:  DblQueue exists and item is passed.
// post: adds the given item to the end of the queue.
void DblQueue::enqueue(const ItemType& item) {
	queuePtr temp = new queueNode;
	temp->val = item;
	if (myFront == nullptr)
	{
		myFront = temp;
	}
	else {
		myBack->next = temp;
	}
	myBack = temp;
	mySize++;
	
}

// dequeue
// dequeues the front item off the queue 
// pre:  DblQueue exists.
// post: Removes item on front of the queue. If the queue
//       was already empty, throws an std::underflow_error exception.
void DblQueue::dequeue() {
	if (isEmpty())
		throw std::underflow_error("The queue is empty");
	else {
		queuePtr curr = myFront->next;
		delete myFront;
		myFront = curr;
		mySize--;

		if (mySize == 0)
			myBack = nullptr;
	}
}

// front
// Returns the front item of the queue without dequeueing it.
// pre:  DblQueue exists.
// post: Returns item at front of queue.  If the queue is empty,
//       throws an std::underflow_error exception.
ItemType DblQueue::front() const {
	if (isEmpty())
		throw std::underflow_error("The queue is empty");
	else
		return myFront->val;
}

// size
// Returns the number of items on the queue.
size_t DblQueue::size() const {
	return mySize;
}

