#include <iostream>
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
  protected:
    Singleton(const std::string &value) : value_(value) {}
    static Singleton *singleton_;
    string value_;

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

Singleton *Singleton::singleton_ = nullptr;
/**
  Static method should be defined outside the class
  */
Singleton *Singleton::GetInstance(const string &value) {
    // not thread safe
    if (singleton_ == nullptr) {
        // you need input value for the construction of singleton_
        singleton_ = new Singleton(value);
    }
    return singleton_;
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
