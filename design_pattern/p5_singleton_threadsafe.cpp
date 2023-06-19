#include <iostream>
#include <mutex>
#include <string>
#include <thread>
#include <utility>

using std::cout;
using std::endl;
using std::string;

/**
  The Singleton class defines the GetInstance method that servers as
  an alternative to constructor and lets clients access the same instance
  of this calss over and over.
  */

class Singleton {
    /**
      The Singleton's constructor should always be private to prevent direct
      construction calls with the 'new' operator.
      */
  private:
    static Singleton *pInstance_;
    static std::mutex mutex_;

  protected:
    string value_;
    Singleton(const std::string &value) : value_(value) {}
    ~Singleton() {}

  public:
    /**
      Singleton should not be cloneable.
      */
    Singleton(Singleton &other) = delete;

    /**
      Singleton should not be assignable.
      */
    void operator=(const Singleton &) = delete;

    /**
        static method to control the access to the singleton instance.
       */
    static Singleton *GetInstance(const string &value);

    /**
      Finally, any singleton should define some business logic, which can be
      executed on its instance.
      */
    void SomeBusinessLogic() {
        cout << "Business logic inside singlton instance" << endl;
    }
    string value() const { return value_; }
};

Singleton *Singleton::pInstance_(nullptr);
std::mutex Singleton::mutex_;
/**
  Static method should be defined outside the class
  */

/*
   the first time we call GetInstance we'll lock the storage location
   and then we makesure again that the variable is null and then we set the value
   */
Singleton *Singleton::GetInstance(const string &value) {
    // thread safe
    std::lock_guard<std::mutex> lock(mutex_);
    if (pInstance_ == nullptr) {
        // you need input value for the construction of pInstance_
        pInstance_ = new Singleton(value);
    }
    return pInstance_;
}

void ThreadFoo() {
    // Following code emulates slow innitialization
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    // static method
    Singleton *singleton = Singleton::GetInstance("FOO");
    // not thread safe
    std::cout << singleton->value() << "\n";
}

void ThreadBar() {
    // Following code emulates slow innitialization
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    // static method
    Singleton *singleton = Singleton::GetInstance("BAR");
    // not thread safe
    std::cout << singleton->value() << "\n";
}

int main() {
    cout << "If you see the same value, then singlton was reused(yay!)\n"
         << "If you see different values, then 2 singltons were "
            "created(boo!!)\n\n";
    std::thread t1(ThreadFoo);
    std::thread t2(ThreadBar);
    t1.join();
    t2.join();

    return 0;
}
