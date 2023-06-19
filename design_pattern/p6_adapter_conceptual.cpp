#include <algorithm>
#include <iostream>
#include <string>

using namespace std;

/**
  The Target class defines the domain-specific interface used by the client code
  This is the relatively new code, it provides a common interface needed by
  client code which may not be compatible with legacy code or 3rd party
  libraries then adapter pattern is needed
  */

class Target {
  public:
    virtual ~Target() = default;

    virtual string Request() const {
        return "Target: the default target's behavior.";
    }
};

/**
  The Adaptee contains some useful behavior, but its interface is incompatible
  with the client code. The Adaptee needs some adaptation before the client
  code can use it.
  */
class Adaptee {
  public:
    string SpecificRequest() const {
        return ".eetpadA eht fo roivaheb laicepS";
    }
};

/**
  The Adapter makes the Adaptee's interface compatible with the Target's
  interface.
  */
class Adapter : public Target {
  private:
    Adaptee *adaptee_;

  public:
    Adapter(Adaptee *adaptee) : adaptee_(adaptee) {}
    /*
       override base class's Request to act as a Target
       */
    string Request() const override {
        string to_reverse = this->adaptee_->SpecificRequest();
        reverse(to_reverse.begin(), to_reverse.end());
        return "Adapter: (TRANSLATED) " + to_reverse;
    }
};

/*
   The client code suppots all classes that follow the Target interface
   includes the base Target class, Adapter (the derived class)
   */
void ClientCode(const Target *target) {
    // only call Request via target
    cout << target->Request();
}

int main() {
    cout << "Client: I can work just fine with the Target objects:\n";
    Target *target = new Target;
    ClientCode(target);
    cout << endl;

    Adaptee *adaptee = new Adaptee;
    cout << "Client: The Adapee has a weird interface.  See, I don't "
            "understand it:\n";
    cout << "Adaptee: " << adaptee->SpecificRequest();
    cout << endl;
    cout << "Client: But I can work with it via The Adapter:" << endl;

    Adapter *adapter = new Adapter(adaptee);
    ClientCode(adapter);
    cout << endl;

    delete target;
    delete adaptee;
    delete adapter;

    return 0;
}
