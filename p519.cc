#include "common.h"
// random shuffle
class Solution {
    // https://www.acwing.com/solution/LeetCode/content/519/
    // https://www.cnblogs.com/grandyang/p/9781289.html
    // https://leetcode.com/problems/random-flip-matrix/discuss/154156/Shuffle
  public:
    Solution(int n_rows, int n_cols) {
        R = n_rows;
        C = n_cols;
        Indices.clear();
        currentZeros = R * C;
    }
    // when the number of flip is much less than N = R * C;
    // then it is a waste of space.
    // because in the Indices array, most of value at index i is i;

    // Use a unordered_map cache to store a index to value map;
    // index is the index of whole array,
    // value is the current stored value in the array;
    // if cache[index] presents, that means previously index has been randomly picked and at that
    // time, we have swap its value with value at v[currentZeros](the back of active array at that time)
    vector<int> flip() {
        if (currentZeros) {
            int i = rand() % currentZeros;
            int valueAtI = i; // assume i has not been picke before;
            if (Indices.find(i) != Indices.end()) {
                valueAtI = Indices[i];
            }
            int rowid = valueAtI / C;
            int colid = valueAtI - rowid * C;
            // swap the value at i and value at currentZeros - 1(the last zero)
            int indexLastZero = currentZeros - 1;
            int valueAtLastZero = indexLastZero;
            if (Indices.find(indexLastZero) != Indices.end()) {
                valueAtLastZero = Indices[indexLastZero];
            }
            Indices[i] = valueAtLastZero;
            // Indices[indexLastZero] = valueAtI; // this is not needed, because in the following
            // flip
            // the rolled i will never be larger than indexLastZero - 1;
            // indexLastZero has been marked as flipped :)

            currentZeros--;
            return {rowid, colid};
            // i = row.id * C + col.id
        } else {
            return {};
        }
    }

    void reset() {
        currentZeros = R * C;
        Indices.clear();
    }

  private:
    int R;
    int C;
    unordered_map<int, int> Indices;
    int currentZeros;
};

int main() {

	Solution s;

	return 0;
}
