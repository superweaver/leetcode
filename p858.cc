#include "common.h"
//https://www.cnblogs.com/grandyang/p/10646040.html
class Solution {
public:
    int mirrorReflection(int p, int q) {
        return 1 - p / gcd(p, q) % 2 + q / gcd(p, q) % 2;
    }
    int gcd(int p, int q) {
        return q ? gcd(q, p % q) : p;
    }
};

class Solution_my {
public:
    int mirrorReflection(int p, int q) {
        int cx = 0;
        int cy = 0;
        int speedx = p;
        int speedy = q;
        int r = -1;
        while((r = check(cx, cy, p, q)) > 2) {
            if (speedx >= 0 && speedy >= 0) {
                if (speedx * (p - cy) <= speedy * (p - cx)) {
                    // meet top
                    int newcy = p;
                    cx += speedx * (newcy - cy) / speedy;
                    cy = newcy;
                    speedy = -speedy;
                } else {
                    // meet right
                    int newcx = p;
                    cy += speedy * (newcx - cx) / speedx;
                    cx = newcx;
                    speedx = -speedx;
                }
            } else if (speedx >= 0 && speedy < 0) {
                // right or bottom
                if (speedx * cy <= (-speedy) * (p - cx)) {
                    // bottom
                    int newcy = 0;
                    cx += speedx * (newcy - cy) / speedy;
                    cy = newcy;
                    speedy = -speedy;
                }
                else {
                    int newcx = p;
                    cy += speedy * (newcx - cx) / speedx;
                    cx = newcx;
                    speedx = -speedx;
                }
            } else if (speedx < 0 && speedy >= 0) {
                // top, left
                if (speedy * cx <= (-speedx) * (p - cy)) {
                    int newcx = 0;
                    cy += speedy * (newcx - cx) / speedx;
                    cx = newcx;
                    speedx = -speedx;

                } else {
                    int newcy = p;
                    cx += speedx * (newcy - cy) / speedy;
                    cy = newcy;
                    speedy = -speedy;
                }
            } else {
                // bottom, left
                if ((-speedy) * cx <= (-speedx) * cy) {
                    int newcx = 0;
                    cy += speedy * (newcx - cx) / speedx;
                    cx = newcx;
                    speedx = -speedx;

                } else {
                    int newcy = 0;
                    cx += speedx * (newcy - cy) / speedy;
                    cy = newcy;
                    speedy = -speedy;
                }
            }
        }
        return r;
    }
private:
    int check(int cx, int cy, int p, int q) {

        cout << cx << " " << cy << endl;
        if (cx == 0 && cy == p) {
            return 2;
        }
        if (cx == p) {
            if (cy == 0) {
                return 0;
            }
            if (cy == p) {
                return 1;
            }
        }
        return 3;
    }
};

int main() {

	Solution s;

	return 0;
}
