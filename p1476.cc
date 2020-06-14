#include "common.h"
class SubrectangleQueries {
public:
  SubrectangleQueries(vector<vector<int>> &rectangle) { d_r = rectangle; }

  void updateSubrectangle(int row1, int col1, int row2, int col2, int newValue) {
      for (int i = row1; i <= row2; ++i) {
          auto &v = d_r[i];
          for (int j = col1; j <= col2; ++j) {
              v[j] = newValue;
          }
      }
  }

  int getValue(int row, int col) {
      return d_r[row][col];
  }
private:
    vector<vector<int>> d_r;
};

int main() {

	Solution s;

	return 0;
}
