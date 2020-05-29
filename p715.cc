#include "common.h"
class RangeModule {
public:
	RangeModule() {
	}

	void addRange(int left, int right) {
		auto it = intervals.lower_bound({ left, left });
		if (it == intervals.end()) {
			intervals.insert({ left, right });
		}
		else {
			auto lower = it;
			auto upper = intervals.upper_bound({ right, right });
			MyInterval interval(left, right);
			for (; it != upper; ++it) {
				interval.start = min(interval.start, it->start);
				interval.end = max(interval.end, it->end);
			}
			intervals.erase(lower, upper);
			intervals.insert(interval);
		}
	}

	bool queryRange(int left, int right) {
		auto lower = intervals.lower_bound({ left, left });
		if (lower == intervals.end()) {
			return false;
		}
		else {
			return (lower->start <= left && lower->end >= right);
		}

	}

	void removeRange(int left, int right) {
		auto lower = intervals.lower_bound({ left, left });
		if (lower == intervals.end()) {
			return;
		}
		else {
			auto upper = intervals.upper_bound({ right, right });
			vector<MyInterval> ToInsert;
			for(auto it = lower; it != upper; ++it){
				if (it->start < left) {
					ToInsert.push_back({ it->start, left });
				}
				// not else if
				if (it->end > right) {
					ToInsert.push_back({right, it->end});
				}
			}
			intervals.erase(lower, upper);
			for (auto&interval : ToInsert) {
				intervals.insert(interval);
			}
		}
	}
private:
	struct MyInterval {
		int start;
		int end;
		MyInterval(int s, int e) :start(s), end(e) {}
		bool operator<(const MyInterval& b) const {
			return end < b.start;
		}
	};
	set<MyInterval> intervals;
};

int main() {

	Solution s;

	return 0;
}
