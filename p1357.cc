#include "common.h"
class Cashier {
public:
    Cashier(int n, int discount, vector<int>& products, vector<int>& prices) {
		index = 0;
		this->n = n;
		this->discount = discount;
		// 1 <= products.length <= 200
		// 1 <= products[i] <= 200
		id2price = vector<int>(201, 0);
		for (size_t i = 0; i < products.size(); ++i) {
			id2price[products[i]] = prices[i];
		}
    }
    double getBill(vector<int> product, vector<int> amount) {
        index++;
        double ratio = (index % n == 0) ? (1.0 - discount / 100.0) : 1.0;
		int p = 0;
		for (size_t i = 0; i < product.size(); ++i) {
			p += amount[i] * id2price[product[i]];
		}
		return ratio * p;
    }
private:
	int index;
	vector<int> id2price;
	int n;
	int discount;
};

int main() {

	Solution s;

	return 0;
}
