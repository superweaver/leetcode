#include "common.h"
class MyCalendar {
public:
	MyCalendar() {

	}

	bool book(int start, int end) {
		MyInterval nextbook(start, end);
		auto it = books.lower_bound(nextbook);
		if (it == books.end()) {
			books.insert(nextbook);
			return true;
		}
		else {
			if (nextbook < *it) {
				books.insert(nextbook);
				return true;
			}
			else {
				return false;
			}
		}
	}
private:
	struct MyInterval {
		int start;
		int end;
		MyInterval(int s, int e):start(s), end(e) {}
		bool operator< (const MyInterval&b) const { // const is important
			return	end <= b.start;
		}
	};
	set<MyInterval> books;
};
/**
 * Your MyCalendar object will be instantiated and called as such:
 * MyCalendar* obj = new MyCalendar();
 * bool param_1 = obj->book(start,end);
 */

int main() {

	Solution s;

	return 0;
}
