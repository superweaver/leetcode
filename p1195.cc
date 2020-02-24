#include "common.h"
#include <mutex>
#include <semaphore.h>

//https://www.showsql.com/2019/11/26/leetcode1195-fizz-buzz-multithreaded/
class FizzBuzz {
private:
    int n;
    int i;
    sem_t sem_fizz;
    sem_t sem_buzz;
    sem_t sem_fb;
    sem_t sem_number;

public:
    FizzBuzz(int n)
    {
        this->n = n;
        i = 1;
        sem_init(&sem_fizz, 0, 0);
        sem_init(&sem_buzz, 0, 0);
        sem_init(&sem_fb, 0, 0);
        sem_init(&sem_number, 0, 1);
    }

    void deliver()
    {
        int r3 = i % 3;
        int r5 = i % 5;
        if (r3 == 0 && r5) {
            sem_post(&sem_fizz);
        } else if (r3 && r5 == 0) {
            sem_post(&sem_buzz);
        } else if (r3 == 0 && r5 == 0) {
            sem_post(&sem_fb);
        } else {
            sem_post(&sem_number);
        }
    }

    void notify_end()
    {
        sem_post(&sem_fizz);
        sem_post(&sem_buzz);
        sem_post(&sem_fb);
        sem_post(&sem_number);
    }

    // printFizz() outputs "fizz".
    void fizz(function<void()> printFizz)
    {
        while (1) {
            sem_wait(&sem_fizz);

            if (i > n) {

                notify_end();
                break;
            }
            printFizz();
            ++i;
            deliver();
        }
    }

    // printBuzz() outputs "buzz".
    void buzz(function<void()> printBuzz)
    {
        while (1) {
            sem_wait(&sem_buzz);

            if (i > n) {

                notify_end();
                break;
            }
            // printf("b ");
            printBuzz();
            ++i;

            deliver();
        }
    }

    // printFizzBuzz() outputs "fizzbuzz".
    void fizzbuzz(function<void()> printFizzBuzz)
    {
        while (1) {
            sem_wait(&sem_fb);

            if (i > n) {

                notify_end();
                break;
            }
            printFizzBuzz();
            ++i;

            deliver();
        }
    }

    // printNumber(x) outputs "x", where x is an integer.
    void number(function<void(int)> printNumber)
    {
        while (1) {
            sem_wait(&sem_number);

            if (i > n) {

                notify_end();
                break;
            }
            printNumber(i);
            ++i;
            deliver();
        }
    }
};

int main()
{

    Solution s;

    return 0;
}
