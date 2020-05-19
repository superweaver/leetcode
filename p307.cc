#include "common.h"
class NumArray_segment {
  public:
    NumArray_segment(vector<int> &nums) {
        // root is in i = 1
        // leftchild = 2*i, rightchild = 2*i + 1
        d_size = nums.size();
        sgtree.assign(2 * d_size, 0);
        for (int i = 0; i < d_size; ++i) {
            update(i, nums[i]);
        }
    }

    void update(int i, int val) {
        i += d_size;
        int delta = val - sgtree[i];
        sgtree[i] = val;
        while (i > 1) {
            i >>= 1; // parent;
            sgtree[i] = sgtree[i << 1] + sgtree[(i << 1) + 1];
        }
    }

    int sumRange(int i, int j) {
        // inclusive
        if (i > j) {
            swap(i, j);
        }
        i += d_size;
        j += d_size;
        int sum = 0;
        while(i <= j) {
            if (i & 1) { // i points to right child
                sum += sgtree[i++];
            }
            if (!(j & 1)) { // j points to left child
                sum += sgtree[j--];
            }
            i /= 2;
            j /= 2;
        }
        return sum;
    }
  private:
    vector<int> sgtree;
    int d_size;
};

class NumArray {
  public:
    NumArray(vector<int> &nums) {
        original = nums;
        n = nums.size() + 1;
        BIT.assign(n, 0);
        for (int i = 0; i < n - 1; ++i) {
            // not update
            add(i, nums[i]);
        }
    }

    void update(int i, int val) {
        add(i, val - original[i]);
        original[i] = val;
    }

    int sumRange(int i, int j) {
        if (i > j) {
            swap(i, j);
        }
        return getsum(j) - getsum(i - 1);
    }

  private:
    // root index is 1
    int n; // 1 + original n
    vector<int> original;
    vector<int> BIT;
    void add(int i, int delta) {
        if (delta == 0) {
            return;
        }
        for (i++; i < n; i += (i & -i)) {
            BIT[i] += delta;
        }
    }

    int getsum(int i) {
        // 0 to i
        int sum = 0;
        for (i++; i > 0; i -= (i & -i)) {
            sum += BIT[i];
        }
        return sum;
    }
};

int main() {

    vector<int> nums = {1, 3, 5};
    NumArray s(nums);
    cout << s.sumRange(1, 2) << endl;
    s.update(1, -3);
    cout << s.sumRange(1, 2) << endl;
    NumArray_segment sg(nums);
    cout << sg.sumRange(1, 2) << endl;
    sg.update(1, -3);
    cout << sg.sumRange(1, 2) << endl;

    cout << sg.sumRange(1, 1) << endl;

    return 0;
}
