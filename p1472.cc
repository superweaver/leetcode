#include "common.h"
class BrowserHistory {
public:
    BrowserHistory(string homepage) {
        current = 1;// to be filled
        urls.push_back(homepage);
        h = homepage;
    }

    void visit(string url) {
        urls.resize(current);
        urls.push_back(url);
        current++;
    }

    string back(int steps) {
        int n = urls.size();
        current -= steps;
        if (current < 0) {
            current = 0;
        }
        return urls[current];
    }

    string forward(int steps) {
        int n = urls.size();
        current += steps;
        if (current >= n - 1) {
            current = n - 1;
        }
        return urls[current];
    }
private:
    vector<string> urls;
    string h;
    int current;
};

int main() {

	Solution s;

	return 0;
}
