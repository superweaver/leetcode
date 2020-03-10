#include "common.h"
class CombinationIterator {
public:
    CombinationIterator(string characters, int combinationLength) {
		s = characters;	
		len = combinationLength;
        if (len <= s.size()) {
            candidate = s.substr(0, len);
			for (size_t i = 0; i < len; ++i) {
				index.push_back(i);
			}
        }
    }

    string next() {
		string ret = candidate;
		bool find = false;
        for (int j = len - 1; j >= 0; --j) {
            // check if you can find a larger character
			auto it = index[j] + 1;	
			//auto it = upper_bound(s.begin(), s.end(), ret[j]);
            if (it < s.size() && (j + s.size() - it) >= len ) {
				candidate.resize(j);
				for (size_t k = j; k < len ; ++k) {
                    index[k] = it;
					candidate.push_back(s[it++]);
                }
				find = true;
				break;
            }
        }
		if (!find) {
			candidate.clear();
		}
		return ret;
    }

    bool hasNext() {
		return !candidate.empty();
    }
private:
	string s;
	string candidate;
	vector<size_t> index;
	size_t len;
};


int main() {
    string str = "abcdef";
    int len = 3;
    CombinationIterator cit(str, len);
	while(cit.hasNext()) {
		cout << cit.next() << endl;
	}
    return 0;
}
