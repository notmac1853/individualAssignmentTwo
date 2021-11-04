// (c) 2013-2020 David Gerstl, all rights reserved
// For the use of my C++ students to use as a base to implement
// dynamic arrays, exceptions and operator overloading, and templates


// Class farmingdale::queue: General std::string queue implementation based on circular array. 
// We will add dynamic arrays (for unlimited size), templates (to allow multiple types) etc.

// note: This is not thread safe--there are no mutexes or locks on the indexes.

// like #pragma once but more portable
//#ifndef H_FARMINGDALECONTIGUOUSMEMORYQUEUE
#define H_FARMINGDALECONTIGUOUSMEMORYQUEUE


// Note to students. It's OK to #include in a library header (inside the guards). 
// but DO NOT add a "using" directive inside a library header
#include <string>
#include "farmingdaleStatus.h"

// See https://docs.microsoft.com/en-us/visualstudio/debugger/finding-memory-leaks-using-the-crt-library?view=vs-2019
// for some notes on what we're doing here.
#define _CRTDBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>

// Two consts for student messages. These will give the line number and file of the 
const std::string TEMPLATED_HEADER_FILE = (std::string(__FILE__).substr(std::string(__FILE__).find_last_of("\\/") + 1));
const int TEMPLATED_HEADER_LINE = (__LINE__ + 3); // must not add more comments or space...

namespace farmingdale {
	// Note: namespaces are additive, so you can add new elements to this namespace in other files or later
	template <class CL> class queue;
}
template <class CL> class farmingdale::queue {
private:
	static const int INITIAL_QUEUE_SIZE = 16; // This should remain the initial size of the dynamic array
	CL* data; //  [INITIAL_QUEUE_SIZE] ;     // This should become a dynamic array in M5

	int oldestIndex;		// index of the oldest element in the queue
	int nextInsertIndex;	// index of the first empty spot
	int currentCapacity;

	// we use capacity. Note that since we want to distinguish between full and empty, we leave
	// a single empty space always in the circular array (see the slides and videos). Because of this, 
	// the array size used for the circular calculations is always one more than the available slots
	// given and index, returns the address of the next index in a circular array
	inline int nextIndexOf(int index) const { return((index + 1) % (currentQueueCapacity() + 1)); }
public:
	queue();
	// rule of threes
	queue(const queue<CL>& copyMe);
	~queue();
	queue<CL>& operator=(queue<CL>); // using the copy/swap idiom

	// returns the initial size without a reallocation of memory
	inline int initialQueueCapacity() const { return INITIAL_QUEUE_SIZE - 1; }
	// returns the current queue capacity: same as initial except will change in dynamic
	inline int currentQueueCapacity() const { return currentCapacity - 1; }

	inline bool isEmpty() const { return (oldestIndex == nextInsertIndex); }
	inline bool isFull() { return (nextIndexOf(nextInsertIndex) == oldestIndex); }
	statusCode enqueue(CL addMe);
	statusCode dequeue(CL& returnedElement);
	statusCode peek(CL& returnedElement) const;
	// compare two queues
	bool operator==(const queue<CL>&) const;
	// print a stack to a stream (e.g., std::cout)
	void printToStream(std::ostream& outputStream);
};
template <class CL> inline std::ostream& operator<<(std::ostream& theStream, farmingdale::queue<CL> theQueue) {
	theQueue.printToStream(theStream);
	return theStream;
}
template <class CL> inline bool operator!=(const farmingdale::queue<CL>& lhs, const farmingdale::queue<CL>& rhs) {
	return (!(lhs == rhs));
}

//student written code begins here

// print a stack to a stream (e.g., std::cout)
template <class CL> void farmingdale::queue<CL>::printToStream(std::ostream& theStream) {
	theStream << "(oldest)";
	for (int i = oldestIndex; i != nextInsertIndex; i = nextIndexOf(i)) {
		theStream << data[i];
		if (nextIndexOf(i) != nextInsertIndex) {
			theStream << " ; ";
		}
	}
	theStream << "(newest)";
}


template <class CL> farmingdale::queue<CL>::queue()
	:
	oldestIndex(0),
	nextInsertIndex(0),
	currentCapacity(INITIAL_QUEUE_SIZE)
{
	data = new CL[currentCapacity]; //FINISHED
}

template <class CL> farmingdale::queue<CL>::~queue() {
	delete[] data;
}


template <class CL> farmingdale::queue<CL>::queue(const queue<CL>& copyMe) {
	//Step 1: Copy the oldestIndex from copyMe
	oldestIndex = copyMe.oldestIndex;
	//Step 2: Copy the nextInsertIndex from copyMe
	nextInsertIndex = copyMe.nextInsertIndex;
	//***Step 3: Copy the currentCapacity
	currentCapacity = copyMe.currentCapacity;
	//***Step 4: Allocate the buffer using new, the size of it will be current capacity
	data = new CL[currentCapacity]; //FINISHED
	//Step 5: Copy all of the items in the array from oldestIndex until nextInsert...into data[] (Look at printToStream, it does exactly that)
	for (int i = oldestIndex; i != nextInsertIndex; i = nextIndexOf(i)) {
		data[i] = copyMe.data[i];

	}
}


template <class CL> farmingdale::statusCode farmingdale::queue<CL>::peek(CL& returnedElement) const {
	//Step 1: check if empty, if so return failure
	if (isEmpty()) {
		return farmingdale::FAILURE;
	}
	//Step 2: Put item [oldestIndex] into returnedElement
	returnedElement = data[oldestIndex];
	//Step 3: Return success 
	return farmingdale::statusCode::SUCCESS;
}

template <class CL> farmingdale::statusCode farmingdale::queue<CL>::dequeue(CL& returnedElement) {
	//Step 1: check if empty, if so return failure
	if (isEmpty()) {
		return farmingdale::FAILURE;
	}
	//Step 2: Put item [oldestIndex] into returnedElement
	returnedElement = data[oldestIndex];
	//Step 3: Move oldestIndexUp
	oldestIndex = nextIndexOf(oldestIndex);
	//Step 3: Return success
	return farmingdale::SUCCESS;

}

template <class CL> farmingdale::statusCode farmingdale::queue<CL>::enqueue(CL addMe) {
	//Step 1: Check if the queue is full, grow the queue as follows
	if (isFull()) {
		//***Step1a: Allocate new memory, size ~= 2x currentCapacity
		int newCapacity = currentCapacity * 2;
		CL* MemoryNew = new CL[newCapacity];
		//***Step1b: Copy the data
		int destination = 0;
		for (int i = oldestIndex; i != nextInsertIndex; i = nextIndexOf(i))
		{
			MemoryNew[destination] = data[i];
			++destination;
		}
		//***Step1c: Fix the indexes. 
		oldestIndex = 0;
		nextInsertIndex = destination;
		//***Step1d: Call delete[] on the old memory
		delete[] data;
		//***Step1e: Set data to the new memory
		data = MemoryNew;
		//***Step 1f: Set the new capacity
		currentCapacity = newCapacity;
	}
	//Step 2: If not, we'll add the item in slot [nextInsert]
	data[nextInsertIndex] = addMe;
	//Step 3: Advance nextInsert to the next slot (Do it modulo the size, not just ++)
	nextInsertIndex = nextIndexOf(nextInsertIndex);
	//Step 4: return SUCESS
	return farmingdale::SUCCESS;
}

template <class CL> bool farmingdale::queue<CL>::operator==(const queue<CL>& rhs) const {
	int myIterator = oldestIndex;
	int otherIterator = rhs.oldestIndex;
	while (myIterator != nextInsertIndex && otherIterator != rhs.nextInsertIndex) {
		//compare
		if (data[myIterator] != rhs.data[otherIterator]) {
			return false;
		}
		//advance
		myIterator = nextIndexOf(myIterator);
		otherIterator = rhs.nextIndexOf(otherIterator);
	}
	if (myIterator != nextInsertIndex || otherIterator != rhs.nextInsertIndex) {
		return false;
	}

	return true;
}

