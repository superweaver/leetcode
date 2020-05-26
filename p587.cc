#include "common.h"

class Solution {
public:
	typedef pair<int, int> CP;
	vector<vector<int>> outerTrees(vector<vector<int>>& points) {
		// assume no duplicated tree in same coordinate
		vector<CP> coordinates;
		vector<vector<int> > result;
		if (points.empty()) {
			return result;
		}
		for (auto& v : points) {
			coordinates.push_back({ v[0], v[1] });
		}
		sort(coordinates.begin(), coordinates.end());
		CP origin = coordinates.front();
		// sort again acoording to k and r
		//unordered_map<double, vector<int> > skew;
		int n = coordinates.size();
		vector<Node> ks_r(n-1);
		for (int i = 1; i < n; ++i) {
			double k = 0.;
			if (coordinates[i].first != origin.first) {
				k = (coordinates[i].second - origin.second) / double(coordinates[i].first - origin.first);
			}
			else {
				k = numeric_limits<double>::max();
			}
			double r = pow(coordinates[i].second - origin.second,2) + pow(coordinates[i].first - origin.first,2);
			ks_r[i-1].kr.first = k;
			ks_r[i-1].kr.second = r;
			ks_r[i - 1].i = i;
		}
		sort(ks_r.begin(), ks_r.end());
		// !!!! when k is same, the longer CP should be in front
		vector<CP> sorted;
		sorted.push_back(origin);
		for (auto k : ks_r) {
			sorted.push_back(coordinates[k.i]);
		}
		// loop in sorted CP
		result.clear();
		result.push_back({ origin.first, origin.second });
		n = sorted.size();
		/*
		for (auto& sp : sorted) {
			cout << sp.first << " " << sp.second << endl;
		}
		cout << endl;
		*/
		CP PreV(0, -1);
		for (int i = 1; i < n; ++i) {
			if (result.size() == 1) {
				result.push_back({ sorted[i].first, sorted[i].second });
			}
			else {
				do {
					int rn = result.size();
					auto& p = result[rn - 2];
					auto& c = result[rn - 1];
					PreV.first = c[0] - p[0];
					PreV.second = c[1] - p[1];
					CP CurrentV(sorted[i].first - c[0], sorted[i].second - c[1]);
					int outer = PreV.first * CurrentV.second - CurrentV.first* PreV.second;
					// positive area or negative
					if (outer >= 0) {
						// OK, next one
						break;
					}
					else {
						result.pop_back();
					}
				} while (result.size() > 1);
				// size == 1 or break;
					result.push_back({ sorted[i].first, sorted[i].second });
			}
		}
		return  result;
	}
private:
	struct Node {
		pair<double, double> kr;
		int i;
		Node(){}
		bool operator < (const Node& b) {
			if (kr.first == b.kr.first) {
				// key , here !!!
				if (kr.first > 0)
					return kr.second > b.kr.second;
				else
					return kr.second < b.kr.second;
			}
			else {
				return kr.first < b.kr.first;
			}
		}
	};
};

int main() {

	Solution s;

	return 0;
}
