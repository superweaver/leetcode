#include "common.h"
class Solution {
public:
    int maxNumberOfFamilies(int n, vector<vector<int>>& reservedSeats) {
		unordered_map<int, int> cache; // row, bitmap of row
		for (auto &v : reservedSeats) {
            cache[v[0]] |= (1 << (v[1]));
        }
        const int mask = (0xFF);
        const int lower = 0x0F;
		const int mid = (0x0F << 2);
		const int mid_hat = 0xFF - mid;
		const int upper = 0xF0;
		int counter = 0;
		vector<int> value(256, 0);
        for (int bitmap = 1; bitmap < 256; ++bitmap) {
            if ((bitmap & lower) && !(bitmap & upper)) {
				value[bitmap] = 1;
            } else if ((bitmap & upper) && !(bitmap & lower)) {
				value[bitmap] = 1;
            } else if ((bitmap & mid_hat) && !(bitmap & mid)) {
				value[bitmap] = 1;
            } else {
				value[bitmap] = 2;
            }
        }
        for (auto & p : cache) {
			// p.second is the bitmap
            int bitmap = ((p.second >> 2) & mask);
			// pay attention to why >> 2
			/*
            if (bitmap) { // at least delete 1 part
                if ((bitmap & lower) && !(bitmap & upper)) {
                    ++counter;
                } else if ((bitmap & upper) && !(bitmap & lower)) {
                    ++counter;
                } else if ((bitmap & mid_hat) && !(bitmap & mid)) {
                    ++counter;
                } else {
                    counter += 2;
                }
            }  // else { continue;}
			*/
			counter += value[bitmap];
        }
        return 2 * n - counter;
    }
};

class Solution2 {
public:
    int maxNumberOfFamilies(int n, vector<vector<int>>& reservedSeats) {
        const int mask = (0xFF);
        const int lower = 0x0F;
		const int mid = (0x0F << 2);
		const int mid_hat = 0xFF - mid;
		const int upper = 0xF0;
        vector<int> value(256, 0);
        for (int bit = 1; bit < 256; ++bit) {  // start from 1
            if ((bit & lower) && !(bit & upper)) {
                value[bit] = 1;
            } else if ((bit & upper) && !(bit & lower)) {
                value[bit] = 1;
            } else if ((bit & mid_hat) && !(bit & mid)) {
                value[bit] = 1;
            } else {
                value[bit] = 2;
            }
        }
        int counter = 0;
        sort(reservedSeats.begin(), reservedSeats.end());
        for (size_t i = 0; i < reservedSeats.size();) {
            int r = reservedSeats[i][0];
            int tmp = 0;
            size_t j = i; // not i + 1
            while (j < reservedSeats.size() && reservedSeats[j][0] == r) {
                tmp |= (1 << reservedSeats[j++][1]);
            }
            counter += value[((tmp >> 2) & mask)];
            // pay attention to why >> 2
            i = j;
        }
        return 2 * n - counter;
    }
};

int main() {
    int n = 3;
    vector<vector<int>> reservedSeats = { { 1, 2 }, { 1, 3 }, { 1, 8 },
                                          { 2, 6 }, { 3, 1 }, { 3, 10 } }; // 4
	/*
    n = 2, reservedSeats = { { 2, 1 }, { 1, 8 }, { 2, 6 } };               // 2
    n = 4, reservedSeats = { { 4, 3 }, { 1, 4 }, { 4, 6 }, { 1, 7 } }; // 4
	*/

    Solution s;
    cout << s.maxNumberOfFamilies(n, reservedSeats) << endl;

    return 0;
}
