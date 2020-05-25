#include "common.h"
class Solution {
    // https://programming.guide/random-point-within-circle.html
    // https://www.cnblogs.com/tenosdoit/p/4025221.html
    // https://blogs.sas.com/content/iml/2016/03/30/generate-uniform-2d-ball.html
    // theta is U(0, 2PI);
    // r is not uniformly distributed
    // CDF(r) = P(R:R < r) = PI*r^2/Pi = r^2
    // then pdf(r) = 2r;
    // or
    // r1 = 1, r2 = 2; then we expect to see twice as many points on the circle of r2 i
    // as that on the circle of r1, assume points are uniformly distributed;
    // similarly, pdf(r) = 2r;
    // then do inverse tansform
    // CDF : y = x^2
    // get the inverse function x = sqrt(y)
    // then swap y and x
    // y = sqrt(x); x is uniformly distributed;
  public:
    Solution(double radius, double x_center, double y_center) {
        r = radius;
        c_x = x_center;
        c_y = y_center;
    }

    vector<double> randPoint() {
        double result_radius = r * sqrt(double(rand()) / RAND_MAX);
        double result_theta = 2 * PI * double(rand()) / RAND_MAX;
        return {c_x + result_radius * cos(result_theta), c_y + result_radius * sin(result_theta)};
    }

  private:
    double r;
    double c_x;
    double c_y;
    const double PI = 3.141592653589793;
};

int main() {

	Solution s;

	return 0;
}
