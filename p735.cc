#include "common.h"

class Solution {
public:
	vector<int> asteroidCollision(vector<int>& asteroids) {
		vector<int> result;
		for (auto i : asteroids) {
			if (result.empty()) {
				result.push_back(i);
			}
			else {
				int pre = result.back();
				if (pre < 0) {
					result.push_back(i);
				}
				else {
					if (i > 0) {
						result.push_back(i);
					}
					else {
						// pre > 0, i < 0
						while (!result.empty() && result.back() > 0 && result.back() + i < 0) {
							result.pop_back();
						}
						if (result.empty()) {
							result.push_back(i);
						}
						else if (result.back() < 0) {
							result.push_back(i);
						}
						else if (result.back() + i == 0) {
							result.pop_back();
						}
						else {
							// do nothing
							// result.back() + i > 0;
						}
					}
				}
			}
		}
		return result;
	}
};

int main() {

	Solution s;

	return 0;
}
