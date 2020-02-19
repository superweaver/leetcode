#include "common.h"
#include <mutex>
//https://zxi.mytechroad.com/blog/concurrent/leetcode-1116-print-zero-even-odd/
class ZeroEvenOdd {
private:
    int n;
    mutex m_odd;
    mutex m_zero;
    mutex m_even;

public:
    ZeroEvenOdd(int n)
    {
        this->n = n;
        m_odd.lock();
        m_even.lock();
    }

    // printNumber(x) outputs "x", where x is an integer.
    void zero(function<void(int)> printNumber)
    {
        for (int i = 0; i < n; ++i){
            m_zero.lock();
            printNumber(0);
            if (i&1) {
                m_even.unlock();
            } else {
                m_odd.unlock();
            }
        }
        
    }

    void even(function<void(int)> printNumber)
    {
		for (int i = 2; i <= n; i +=2) {
            m_even.lock();
            printNumber(i);
            m_zero.unlock();
        }
    }

    void odd(function<void(int)> printNumber)
    {
    
        for (int i = 1; i <= n; i +=2) {
            m_odd.lock();
            printNumber(i);
            m_zero.unlock();
        }
    }
};


int main()
{

    return 0;
}
