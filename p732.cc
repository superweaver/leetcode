#include "common.h"

class MyCalendarThree {
public:
	MyCalendarThree() {
		maxbooking = 0;
	}
	int book(int start, int end) {
		auto itstart = startevents.lower_bound(start);
		int earlierstarts = distance(startevents.begin(), itstart);
		auto itend = endevents.lower_bound(start);
		int earlierends = distance(endevents.begin(), itend);
		int count = earlierstarts - earlierends;
		int books = count;
		startevents.insert(start);
		endevents.insert(end);
		itstart = startevents.lower_bound(start);
		itend = endevents.lower_bound(start);
		while ((itend != endevents.end() && *itend < end) || (itstart != startevents.end() && *itstart < end)) {
			if (*itend <= *itstart) {
				count--;
				++itend;
			}
			else {
				count++;
				books = max(books, count);
				++itstart;
			}
			if (itstart == startevents.end()) { // key
				break;
			}
		}
		return maxbooking = max(maxbooking, books);
	}

private:
	multiset<int> startevents;
	multiset<int> endevents;
	int maxbooking;
};

int main() {

	Solution s;

	return 0;
}
