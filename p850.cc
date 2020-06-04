#include "common.h"
//https://zhuanlan.zhihu.com/p/82997538
//http://www.voidcn.com/article/p-uudouwfb-byr.html
//http://hehejun.blogspot.com/2018/09/leetcoderectangle-area-ii.html
//https://www.cnblogs.com/grandyang/p/11371256.html
//http://hehejun.blogspot.com/2018/09/leetcoderectangle-area-ii.html
//
class Solution {
public:
	int rectangleArea(vector<vector<int>>& rectangles) {
		vector<Edge> vec;
		for (size_t i = 0; i < rectangles.size(); ++i) {
			auto&rect = rectangles[i];
			vec.push_back({ rect[0], {rect[1], rect[3]}, LEFT, i });
			vec.push_back({ rect[2], {rect[1], rect[3]}, RIGHT, i });
		}
		sort(vec.begin(), vec.end(), [](const Edge&a, const Edge&b) {
			if (a.x != b.x) {
				return a.x < b.x;
			}
			else {
				if (a.i < b.i) {
					return true;
				}
				else if (b.i < a.i) {
					return false;
				}
				else {
					return a.type > b.type; // LEFT =1
				}
			}
		});
		set<pair<Interval, int>> active_set;
		active_set.insert({vec[0].i, vec[0].id});
		int pre_x = vec[0].x;
		int result = 0;
		for (size_t i = 1; i < vec.size(); ++i) {
			int delta_x = vec[i].x - pre_x;
			// merge interval
            if (delta_x) {
                int total_y = getY(active_set);
			    result = (result + ((long long)(delta_x)*total_y)) % 1000000007;
            }
			if (vec[i].type == LEFT) {
				active_set.insert({vec[i].i, vec[i].id});
			}
			else {
				active_set.erase({vec[i].i, vec[i].id});
			}
			pre_x = vec[i].x;
		}
		return result;
	}
private:
	enum { LEFT = 1, RIGHT = -1 };
	struct Interval {
		int start;
		int end;
		Interval(int s, int e) :start(s), end(e) {}
		bool operator < (const Interval& other) const {
			if (start != other.start) {
				return start < other.start;
			}
			else {
				return end < other.end;
			}
		}
	};
	struct Edge {
		int x;
		Interval i;
		int type; // LEFT or RIGHT
		size_t id;
	};
	int getY(set<pair<Interval, int>>&active_set) {
		int s = -1;
		int e = -1;
		int total_y = 0;
        // s and e is previous merged interval
        // merge other interval to get total y
		for (auto&m : active_set) {
			auto& i_m = m.first;
			//int id = m.second;
            // s == -1 is not needed I think
            // because all i_m.start >= 0
			//if (s == -1 || i_m.start > e) {
            if (i_m.start > e) {
                total_y += e - s;
				s = i_m.start;
				e = i_m.end;
            } else {
                e = max(e, i_m.end);
            }
        }
		total_y += e - s;
		return total_y;
	}
};

int main() {
    vector<vector<int>> rectangles = {{0,0,2,2},{1,0,2,3},{1,0,3,1}};
	Solution s;
    cout <<s.rectangleArea(rectangles) << endl;

	return 0;
}
