#include "common.h"

class MyCircularDeque {
public:
	/** Initialize your data structure here. Set the size of the deque to be k. */
	MyCircularDeque(int k) {
        if (k > 0) {
            capacity = k;
            q.resize(k);
        }
        head = 0;
        tail = k - 1;
        full = false;
    }

    /** Adds an item at the front of Deque. Return true if the operation is successful. */
	bool insertFront(int value) {
        if (isFull()) {
            return false;
        }
        head = (head - 1 + capacity) % capacity;
        q[head] = value;
        if ((tail + 1) % capacity == head) {
            full = true;
        }
        return true;
	}

	/** Adds an item at the rear of Deque. Return true if the operation is successful. */
	bool insertLast(int value) {
        if (isFull()) {
            return false;
        }
        tail = (tail + 1 + capacity) % capacity;
        q[tail] = value;
        if ((tail + 1) % capacity == head) {
            full = true;
        }
        return true;

	}

	/** Deletes an item from the front of Deque. Return true if the operation is successful. */
	bool deleteFront() {
        if (isEmpty()) {
            return false;
        }
        head = (head + 1 + capacity) % capacity;
		full = false;
		return true;
	}

	/** Deletes an item from the rear of Deque. Return true if the operation is successful. */
    bool deleteLast() {
        if (isEmpty()) {
            return false;
        }
        tail = (tail - 1 + capacity) % capacity;
        full = false;
		return true;
    }

    /** Get the front item from the deque. */
	int getFront() {
        if (isEmpty()) {
            return -1;
        }
        return q[head];
	}

	/** Get the last item from the deque. */
	int getRear() {
        if (isEmpty()) {
            return -1;
        }
        return q[tail];
	}

	/** Checks whether the circular deque is empty or not. */
	bool isEmpty() {
		return !full && (tail + 1) % capacity == head;
	}

	/** Checks whether the circular deque is full or not. */
	bool isFull() {
		return full;
	}
private:
	vector<int> q;
	int capacity;

	int head;
	int tail;
	bool full;
};

int main() {

	Solution s;

	return 0;
}
