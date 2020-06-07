#include "common.h"
class RLEIterator {
public:
    RLEIterator(vector<int>& A) {
        _A = A;
        iA = iSub = 0;
    }
    int next(int n) {
        size_t _iA = iA;
        size_t _iSub = iSub;
        while (true) {
            if (_iA >= _A.size()) {
                iA = _iA;
                iSub = _iSub + n;
                break;
            }
            if (_A[_iA] - _iSub >= n) {
                iA = _iA;
                iSub = _iSub + n;
                return _A[iA + 1];
            } else {
                n -= _A[_iA] - _iSub;
                _iA += 2;
                _iSub = 0;
            }
        }
        // question is not clear
        return -1;
    }
private:
    vector<int> _A;
    size_t iA;
    size_t iSub;
};


int main() {

	Solution s;

	return 0;
}
