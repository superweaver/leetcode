#include "common.h"
class DinnerPlates {
public:
    DinnerPlates(int capacity) {
		cap = capacity;
		right = 0;
		cache.push_back({});
    }

    void push(int val) {
        if (!notfull.empty()) {
			int i = *notfull.begin();
			auto& s = cache[i];
			s.push(val);
			if (s.size() == cap) {
				notfull.erase(i);
			}
			right = max(right, i);
        } else {
            while (right >= 0 && cache[right].empty()) {
                right--;
            }
			if (right < 0) {
				right++;
			}
            if (cache[right].size() == cap) {
                cache.push_back({});
				right++;
            }
            cache[right].push(val);
        }
    }

    int pop() {
        while (right >= 0 && cache[right].empty()) {
            right--;
        }
        if (right < 0) {
            return -1;
        }
		int r = cache[right].top();
		cache[right].pop();
		while(right>= 0 && cache[right].empty()) {
			right--;
		}
		if (right < 0) {
			right = 0;
		}
		return r;
    }

    int popAtStack(int index) {
		if (index >= (int)cache.size()) {
			return -1;
		}else {
			auto &s = cache[index];
			if (s.empty()) {
				return -1;
			} else {
				int r = s.top();
				s.pop();
				notfull.insert(index);
				return r;
			}
		}
    }
private:
	size_t cap;
	int right;
	vector<stack<int>> cache;
	set<int> notfull;
};

int main() {
	vector<string>	commands ={"push","push","push","push","push","popAtStack","push","push","popAtStack","popAtStack","pop","pop","pop","pop","pop"};
	vector<vector<int>> parameters = {{1},{2},{3},{4},{5},{0},{20},{21},{0},{2},{},{},{},{},{}};
	int capacity = 2;
	DinnerPlates s(capacity);
	for(size_t i = 0; i < commands.size(); ++i) {
		auto&c = commands[i];
		if (c == "push") {
			s.push(parameters[i][0]);
			cout << c << ":" << parameters[i][0] << endl;
		} else if (c == "popAtStack") {
			cout << c << " " << parameters[i][0] <<  ":" << s.popAtStack(parameters[i][0]) << endl;
		} else if (c == "pop") {
			cout << c << ":" << s.pop() << endl;
		}
	}

	return 0;
}
