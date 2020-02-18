#include "common.h"
class SnapshotArray {
public:
    SnapshotArray(int length)
    {
        snap_id = 0;
        n = length;
        lastModified.resize(n);
    }

    void set(int index, int val)
    {
        diff[index] = val;
    }
    int snap()
    {
        if (!snap_id) {
            for (auto& p : diff) {
                if (p.second != 0) {
                    lastModified[p.first].push_back({ snap_id, p.second });
                }
            }
        } else {
            for (auto& p : diff) {
                auto& last = lastModified[p.first];
                if (last.empty()) {
                    last.push_back({ snap_id, p.second });
                } else {
                    if (last.back().second == p.second) {
                        continue;
                    } else {
                        last.push_back({ snap_id, p.second });
                    }
                }
            }
        }
        return snap_id++;
    }

    int get(int index, int snap_id)
    {
        auto& v = lastModified[index];
        if (v.empty()) {
            return 0;
        }
        // find the last index <= snap_id

		int l  = 0;
		int r = v.size() - 1;

        if (snap_id < v[l].first) {
            return 0;
        }
        if (snap_id >= v[r].first) {
            return v.back().second;
        }
        while (l + 1 < r) {
            int mid = l + (r - l) / 2;
            if (v[mid].first == snap_id) {
                return v[mid].second;
            } else if (v[mid].first < snap_id) {
                l = mid;
            } else {
                r = mid - 1;
            }
        }
		if (v[r].first <= snap_id) {
			return v[r].second;
		} else {
			return v[l].second;
		}
    }

private:
    unordered_map<int, int> diff;
    int n;
    int snap_id;
    vector<vector<pair<int, int>>> lastModified;  // the snap_id of last modification for index i
};

int main()
{

    /*
Input: ["SnapshotArray","set","snap","set","get"]
[[3],[0,5],[],[0,6],[0,0]]
Output: [null,null,0,null,5]
*/
	/*
	int length = 3;
    SnapshotArray s(length);
	s.set(0, 5); // 0
	s.snap();
	s.set(0, 6); // 1
	s.snap();
	s.set(0, 8); // 2
	s.snap();
	s.set(0, 9); // 3
	s.snap();
	s.set(0, 10); // 4
	s.snap();
	cout << s.get(0, 0) << endl;
	cout << s.get(0, 1) << endl;
	cout << s.get(0, 3) << endl;
	*/

    vector<string> commands = { "SnapshotArray", "snap", "get", "set",  "snap", "get",  "set",
                                "set",           "snap", "get", "snap", "snap", "snap", "get",
                                "get",           "get",  "set", "get",  "set" };
    vector<vector<int>> inputs = { { 2 },    {},        { 0, 0 }, { 1, 7 }, {},
                                   { 0, 1 }, { 0, 17 }, { 1, 6 }, {},       { 1, 1 },
                                   {},       {},        {},       { 1, 5 }, { 0, 1 },
                                   { 0, 0 }, { 0, 4 },  { 1, 4 }, { 1, 11 } };

    SnapshotArray s(inputs[0][0]);
	for (size_t i = 1; i < commands.size(); ++i) {
		auto&command = commands[i];
		if (command == "snap") {
			s.snap();
		} else if (command == "get") {
			cout << s.get(inputs[i][0], inputs[i][1]) << endl;
        } else if (command == "set") {
            s.set(inputs[i][0], inputs[i][1]);
        }
    }
    return 0;
}
