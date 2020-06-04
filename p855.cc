#include "common.h"
class ExamRoom {
  public:
    ExamRoom(int N) {
        capacity = N;
        count = 0;
        distances.insert(Interval(-1, capacity, capacity));
        seats.insert(-1);
        seats.insert(capacity);
    }

    int seat() {
        if (count == capacity) {
            return -1;
        }
        auto current = *distances.begin();
        int seat = -1;
        if (current.start == -1) {
            seat = 0;
        } else if (current.end == capacity) {
            seat = capacity - 1;
        } else {
            seat = (current.start + current.end) / 2;
        }
        seats.insert(seat);
        count++;
        distances.erase(distances.begin());
        distances.insert(Interval(current.start, seat, capacity));
        distances.insert(Interval(seat, current.end, capacity));
        return seat;
    }

    void leave(int p) {
        auto it = seats.find(p);
        if (it != seats.end()) {
            int Prev = *prev(it);
            int Next = *next(it);
            seats.erase(it);
            distances.erase({Prev, p, capacity});
            distances.erase({p, Next, capacity});
            count--;
            distances.insert({Prev, Next, capacity});
        }
    }

  private:
    int count;    // number of students in ExamRoom
    int capacity; // capacity of ExamRoom
    struct Interval {
        int start;
        int end;
        int upper;
        Interval(int s, int e, int u) : start(s), end(e), upper(u) {}
        // they must sit in the seat that maximizes the distance to the closest person
        // [0, 4] and [4, 9] is same
        //  because put it at 2 and 6 will have same closest distance
        //  but [-1, 4] and [4, capacity] :(
        bool operator<(const Interval &rhs) const {
            int closest_left = getclostdistance();
            int closest_right = rhs.getclostdistance();
            if (closest_left != closest_right) {
                return closest_left > closest_right;
            } else {
                return start < rhs.start;
            }
        }
        int getclostdistance() const {
            if (start == -1) {
                return end;
            } else if (end == upper) {
                return upper - start - 1;
            } else {
                return (end - start) / 2;
            }
        }
    };
    set<int> seats;
    set<Interval> distances;
};

int main() {


    return 0;
}
