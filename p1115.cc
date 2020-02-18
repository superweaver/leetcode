// multi-thread
// to be done
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
