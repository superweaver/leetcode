#include "common.h"
class MyCircularQueue {
public:
	/** Initialize your data structure here. Set the size of the queue to be k. */
	MyCircularQueue(int k) {
		capacity = k;
		q.resize(k);
		head = 0;
		//tail = -1;
        tail = -1 + k;
		full = false;
	}

	/** Insert an element into the circular queue. Return true if the operation is successful. */
	bool enQueue(int value) {
        if (isFull()) {
            return false;
        }
        tail++;
		if (tail == capacity) {
			tail = 0;
		}
		q[tail] = value;
		if ((tail + 1) % capacity == head) {
			full = true;
		}
		return true;
	}

	/** Delete an element from the circular queue. Return true if the operation is successful. */
	bool deQueue() {
        if (isEmpty()) {
            return false;
        }
        head++;
        if (head == capacity) {
            head = 0;
        }
        full = false;
		return true;
	}

	/** Get the front item from the queue. */
	int Front() {
        if (isEmpty()) {
            return -1;
        }
        return q[head];
	}

	/** Get the last item from the queue. */
	int Rear() {
        if (isEmpty()) {
            return -1;
        }
        return q[tail];
	}

	/** Checks whether the circular queue is empty or not. */
    bool isEmpty() { return !full && (tail + 1) % capacity == head; }

    /** Checks whether the circular queue is full or not. */
	bool isFull() {
		//return (tail + 1) % capacity == head;
		return full;
	}
private:
	vector<int> q;
	int capacity;
	int head;
	int tail;
	bool full;
};
/**
 * Your MyCircularQueue object will be instantiated and called as such:
 * MyCircularQueue* obj = new MyCircularQueue(k);
 * bool param_1 = obj->enQueue(value);
 * bool param_2 = obj->deQueue();
 * int param_3 = obj->Front();
 * int param_4 = obj->Rear();
 * bool param_5 = obj->isEmpty();
 * bool param_6 = obj->isFull();
 */

int main() {

	Solution s;

	return 0;
}
