#include "common.h"
// https://zxi.mytechroad.com/blog/desgin/leetcode-895-maximum-frequency-stack/
//
class FreqStack {
public:
    FreqStack() {
        index = 0;
    }
    void push(int x) {
        int key = ((++x2f[x]) << 16) | (index++);
        q.push({key, x});
    }
    int pop() {
        int x = q.top().second; // only pop this, previous count for x should be kept
        q.pop();
        if(--x2f[x] == 0) {
            // maybe there is no need to erase it
            x2f.erase(x);
        }
        return x;
    }
private:
    int index;
    unordered_map<int, int> x2f; // value -> frequence
    priority_queue<pair<int, int>> q; // key = frequence << 16 + index, value is x
};

// https://zxi.mytechroad.com/blog/desgin/leetcode-895-maximum-frequency-stack/
//
class FreqStack_ref {
public:
    FreqStack_ref() {
    }
    void push(int x) {
        int current = ++x2f[x];
        if (current > stacks.size()) {
            stacks.push_back({});
        }
        stacks[current - 1].push(x);
    }

    int pop() {
        auto &s = stacks.back();
        int x = s.top();
        s.pop(); // if there are more x , they are in other frequency slot
        if(s.empty()) {
            stacks.pop_back();
        }
        if (--x2f[x] == 0) {
            x2f.erase(x);
        }
        return x;
    }
private:
    unordered_map<int, int> x2f; // value -> freuqence
    vector<stack<int>> stacks;
};



int main() {

	Solution s;

	return 0;
}
