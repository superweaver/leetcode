#include "common.h"
class Solution {
public:
  string reformatDate(string date) {
      vector<string> month = {"Jan", "Feb", "Mar", "Apr", "May", "Jun",
                              "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
      unordered_map<string, int>  map_month;
      for (int i = 0; i < 12; ++i) {
           map_month[month[i]] = i;
      }
      //Day Month Year
      int offset = 0; // one digit in
      if (isdigit(date[1])) {
          offset = 1;
      }

      int p = 3 + offset;
      int d = stoi(date.substr(0, p));
      p++;
      int m = map_month[date.substr(p, 3)] + 1;
      p += 3;
      p ++;
      int y = stoi(date.substr(p));
      string result = to_string(y) + (m < 10 ? "-0" : "-") + to_string(m) + (d < 10 ? "-0" : "-") + to_string(d);
      return result;
  }
};


int main() {

    string date = "20th Oct 2052";
    date = "6th Jun 1933";
    date = "26th May 1960";
	Solution s;
    cout << s.reformatDate(date) << endl;
    return 0;
}
