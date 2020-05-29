#include "common.h"

class Solution {
public:
	///////
	//A/**/
	// aaa /*
	// bb*/cc/*
	// */dd
	// aaaccdd
	vector<string> removeComments(vector<string>& source) {
		vector<string> result;
		queue<char> q;
		for (auto& s : source) {
			for (auto c : s) {
				q.push(c);
			}
			q.push('\n');
		}
		string temp;
		bool removedblock = false;
		processing(q, temp, result, removedblock);
		return result;
	}
private:
	void processing(queue<char>&q, string& temp, vector<string>& result, bool removedblock) {
		while (!q.empty()) {
			while (!q.empty() && q.front() != '/'&&q.front() != '\n') {
				temp.push_back(q.front());
				//removedblock = false;
				q.pop();
			}
			if (q.empty()) {
				break;
			}
			else if (q.front() == '\n') {
				q.pop();
				if (temp.empty() && removedblock) {
					// ignore this removed block
				}
				else {
					result.push_back(temp);
				}
				removedblock = false; // handled a \n
				temp.clear();
				continue;
			}
			else {
				// q.front() == '/'
				q.pop();
				if (q.front() != '/'&&q.front() != '*') {
                    temp.push_back('/'); // previously poped '/'
					processing(q, temp, result, false);
				}
				else if (q.front() == '/') {
					while (q.front() != '\n') {
						q.pop();
					}
					q.pop();
					if (!temp.empty()) {
						result.push_back(temp);
					}
					temp.clear();
					processing(q, temp, result, false);
				}
				else {
					// q.front() == '*'
					q.pop();
					char a = -1;
					char b = q.front();
					while (!(a == '*'&&b == '/')) {
						a = b;
						b = q.front();
						q.pop();
					}
					processing(q, temp, result, true);
				}
			}
		}
	}
};

int main() {

	Solution s;

	return 0;
}
