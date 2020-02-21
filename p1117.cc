#include "common.h"
#include <mutex>
// https://newdee.gitbook.io/leetcode/leetcode-index/1117.building_h2o
class H2O {
private:
    mutex mH;
    mutex mO;
	int nH;
public:
    H2O() {
		mO.lock();
		nH = 0;
	}

    void hydrogen(function<void()> releaseHydrogen) {

        // releaseHydrogen() outputs "H". Do not change or remove this line.
		mH.lock();
        releaseHydrogen();
        nH++;
        if (nH == 1) {
            mH.unlock(); // continue this hydrogen thread execution
        } else { // nH == 2;
			mO.unlock();
		}
    }

    void oxygen(function<void()> releaseOxygen) {

        // releaseOxygen() outputs "O". Do not change or remove this line.
		mO.lock();
        nH = 0;
        releaseOxygen();
		mH.unlock();
    }
};

int main() {

//	Solution s;

	return 0;
}
