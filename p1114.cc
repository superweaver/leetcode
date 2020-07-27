#include "common.h"
#include <mutex>

class Foo {
public:
    Foo() {
        flag2.lock();
        flag3.lock();
    }

    void first(function<void()> printFirst) {

        // printFirst() outputs "first". Do not change or remove this line.
        printFirst();
        flag2.unlock();
    }

    void second(function<void()> printSecond) {
        flag2.lock();
        // printSecond() outputs "second". Do not change or remove this line.
        printSecond();
        flag3.unlock();
    }

    void third(function<void()> printThird) {
        flag3.lock();
        // printThird() outputs "third". Do not change or remove this line.
        printThird();
    }
private:
    mutex flag2;
    mutex flag3;
};

int main() {


	return 0;
}
