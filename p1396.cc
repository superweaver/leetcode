#include "common.h"
class UndergroundSystem {
public:
    UndergroundSystem() {

    }

    void checkIn(int id, string stationName, int t) {
		d_checkin[id] =  make_pair(move(stationName), t);
        // d_checkin.insert({id, {move(stationName), t}}); // this does not work
		// insertion may fail if id is in unordered_map;
    }

    void checkOut(int id, string stationName, int t)
    {
        const auto& v = d_checkin[id];  // (station, start_time)
                                        // what to do if v.first == stationName ???
        const string key = v.first + stationName;
        t -= v.second;  // time spent
        auto& p = d_cache[key];
        p.first += t;
        ++p.second;
    }

    double getAverageTime(string startStation, string endStation) {
		string key = startStation + endStation;
		// assume key is in d_cache
		if (d_cache.count(key)) {
			auto& p = d_cache[key];
            return double(p.first) / p.second;
        } else {
			return 0;
		}
    }
private:
    unordered_map<string, pair<int, int>> d_cache; // {startstation_endstation, {previous_sum, previous_count}}
	unordered_map<int, pair<string, int>> d_checkin; // id, {station, checkin_time}
};


int main() {

	Solution s;

	return 0;
}
