// multi-thread
// to be done
#include "common.h"
#include <mutex>
#include <condition_variable>

class FooBar_ref {
private:
    int n;
    mutex mtx;
    condition_variable cv;
    bool done[2] = {false, false};
public:
    FooBar_ref(int n) {
        this->n = n;
    }

    void foo(function<void()> printFoo) {
        
        for (int i = 0; i < n; i++) {
         
            unique_lock<mutex> lck(mtx);
            while (done[0]) {
                cv.wait(lck);
            }
            printFoo();
            done[0] = true;
            cv.notify_one();
            lck.unlock();
        }
    }

    void bar(function<void()> printBar) {
        
        for (int i = 0; i < n; i++) {
            unique_lock<mutex> lck(mtx);
            while (!done[0]) {
                cv.wait(lck);
            }
            printBar();
            
            done[0] = false;
                   
            cv.notify_one();
            lck.unlock();
        }
    }
};



class Foo {
    
private:
    mutex mtx;
    condition_variable cv;
    bool done[3] = {false, false, false};
public:
    void first(function<void()> printFirst) {
        
        unique_lock<mutex> lck(mtx);

        done[0] = true;
        printFirst();
        
        cv.notify_all();
        lck.unlock();
    }

    void second(function<void()> printSecond) {
        
        unique_lock<mutex> lck(mtx);
        while (!done[0]) cv.wait(lck);

        done[1] = true;
        printSecond();
        
        cv.notify_all();
        lck.unlock();
    }

    void third(function<void()> printThird) {
        
        unique_lock<mutex> lck(mtx);
        while (!done[1]) cv.wait(lck);
        
        printThird();
        
        cv.notify_all();
        lck.unlock();
    }
};


class FooBar {
private:
    int n;
    mutex mFoo;
    mutex mBar;
public:
    FooBar(int n) {
        this->n = n;
        mBar.lock();
    }

    void foo(function<void()> printFoo) {
        
        for (int i = 0; i < n; ++i) {
            
        	// printFoo() outputs "foo". Do not change or remove this line.
            mFoo.lock();
            printFoo();    
            mBar.unlock();
        }
    }

    void bar(function<void()> printBar) {
        
        for (int i = 0; i < n; ++i) {
            
        	// printBar() outputs "bar". Do not change or remove this line.
            mBar.lock();                       
            printBar();    
            mFoo.unlock();
        }
    }
};
