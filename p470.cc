#include "common.h"

int rand7() { return (rand() % 7) + 1; }

class Solution {
public:
  //https://massivealgorithms.blogspot.com/2019/02/leetcode-470-implement-rand10-using.html
  //https://www.cnblogs.com/grandyang/p/9727206.html
  //https://www.geeksforgeeks.org/implement-rand3-using-rand2/
  int rand10() {
     while (true) {
         int num  = (7 * (rand7() - 1) + rand7() - 1) + 1 ;  // [0...48] + 1 =>[1..49]
         if (num <= 40) {
             return num % 10 + 1;
         }
     }
  }
};
class Solution2 {
public:
  //https://massivealgorithms.blogspot.com/2019/02/leetcode-470-implement-rand10-using.html
  //https://www.cnblogs.com/grandyang/p/9727206.html
  //https://www.geeksforgeeks.org/implement-rand3-using-rand2/
  int rand10() {
        while (true) {
            int a = rand7(), b = rand7();
            int num = (a - 1) * 7 + b;  // U(1, 49)

            if (num <= 40) {
                return num % 10 + 1;
            } else {
                a = num - 40; // here a = rand9() !!!
                b = rand7();  // b is rand7()
                num = (a - 1) * 7 + b;     // num = ((a - 1) * 7 + b - 1) + 1 = rand63()
                if (num <= 60) {
                    return num % 10 + 1;
                } else {
                    a = num - 60; // a = rand3();
                    b = rand7();
                    num = (a - 1) * 7 + b; // num = rand21();
                    if (num <= 20) {
                        return num % 10 + 1;
                    }
                }
            }
        }
    }
};

int main() {

	Solution s;

	return 0;
}
