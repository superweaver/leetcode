#include <iostream>
#include <string>

using namespace std;
/**
  The Implementation defines the interface for all implementation
  classes. It doesn't have to match the Abstraction's interface.
  In fact, the two interfaces can be entirely different. Typically the
  Implementation interface provides only primitive operations, while the
  Abstraction defines higher-level operations based on those primitives.
  */

class Implementation {
  public:
    virtual ~Implementation() {}
    virtual string OperationImplementation() const = 0;
};

/**
  Each concrete Implementation corresponds to a specific platform and
  implements the Implementation interface using that platform's API.
  */
class concreteImplementationA : public Implementation {
  public:
    string OperationImplementation() const override {
        return "concreteImplementationA: Here's the result on the platform "
               "A.\n";
    }
};

class concreteImplementationB : public Implementation {
  public:
    string OperationImplementation() const override {
        return "concreteImplementationB: Here's the result on the platform "
               "B.\n";
    }
};

/**
  The Abstraction defines the interface for the "control" part of the two class
  hierarchies. It maintains a reference to the Implementation hierarchy and
  delegate all of real work to this object.
   */
class Abstraction {
  protected:
    Implementation *implementation_;

  public:
    Abstraction(Implementation *implementation)
        : implementation_(implementation) {}
    ~Abstraction() {}

    virtual string Operation() const {
        return "Abstraction: base operation with:\n" +
               this->implementation_->OperationImplementation();
    }
};

/**
  You can extend the Abstraction without changing the Implementation classes.
  */

class ExtendedAbstraction : public Abstraction {
  public:
    ExtendedAbstraction(Implementation *implementation)
        : Abstraction(implementation) {}
    string Operation() const override {
        return "ExtendedAbstraction: extended operation with:\n" +
               this->implementation_->OperationImplementation();
    }
};

/**
Except for the initialization phase, where an Abstraction object gets linked
with a specific Implementation object, the client code should only depdend on
the Abstraction class. This way, the client code can support andy
abstraction-implementation combination.
   */

void ClientCode(Abstraction &abstraction) {
    cout << abstraction.Operation() << endl;
}

/**
 * The client code should be able to work with any pre-configured abstraction-
 * implementation combination.
 */

int main() {
    Implementation *implementation = new concreteImplementationA;
    Abstraction *abstraction =
        new Abstraction(implementation); // a pre-configured combination
    ClientCode(*abstraction);
    delete implementation;
    delete abstraction;

    implementation = new concreteImplementationB;
    abstraction =
        new ExtendedAbstraction(implementation); // a pre-configured combination
    ClientCode(*abstraction);
    delete implementation;
    delete abstraction;
    return 0;
}
