#include <iostream>
#include <string>
#include <algorithm>
using namespace std;
/* the base Component interface defines operations that can be altered by decorators
*/
class Component {
    public:
        ~Component(){}
        virtual string Operation() const = 0;
};

/* Concrete Component provides default implemention of operations.
   There might be several variations of these classes.
   */
class ConcreteComponent: public Component {
    public:
        string Operation() const override {
            return "ConcreteComponent" ;
        }
};

/*
   The base Decorator follows the same interface as the other Components.
   The primary purpose of this class is to define the wrapping interface for 
   all concrete decorators.
   The default implemention of the wrapping code might include a field
   for storing the wrapped Component and the means to initialize it.
   */
class Decorator : public Component {
    protected:
        Component* component_; // the wrapped component
    public:
        Decorator(Component* component) : component_(component){}
        /*
           The Decorator delegates all work to the wrapped component.
           */
        string Operation() const override {
            return this->component_->Operation();
        }
};

/* 
   Concrete Decorators call the wrapped object (may via parent class method) and alter its result in some way.
   */

class ConcreteDecoratorA : public Decorator {
    /*
       Decorators may call parent implementation of the Operation, instead of calling the wrapped object directly.
       This apporoach simplifies extension of Decorator class
       */
    public:
        ConcreteDecoratorA(Component* component):Decorator(component) {}
        string Operation() const override {
            // call Operation in base class to simplify extension of Decorator
            return "ConcreteDecoratorA(" + Decorator::Operation() + ")";
        }
};

/**
 * Decorators can execute their behavior either before or after the call to a
 * wrapped object.
 */
class ConcreteDecoratorB : public Decorator {
    public:
        ConcreteDecoratorB(Component* component) : Decorator(component) {
        }

        string Operation() const override {
            return "ConcreteDecoratorB(" + Decorator::Operation() + ")";
        }
};

/* 
   The client code works with all objects using the Component interface.
   In this way, it can stay independent of the concrete classed of components
   it works with.
   */

void ClientCode(Component* component) {
    cout  << "Result: " << component->Operation() << endl;
}

int main() {
    /* Client code can support both simple component and decorated component */
    Component* simple = new ConcreteComponent();
    cout << "Client: I have gotten a simple Component" << endl;
    ClientCode(simple);

    /* decorating it */
    Component* decorator1 = new ConcreteDecoratorA(simple);
    Component* decorator2 = new ConcreteDecoratorB(decorator1);
    cout << "Client: now we have gotten a decorated compoenent" << endl;
    ClientCode(decorator2);
    cout << endl;

    delete simple;
    delete decorator1;
    delete decorator2;
    return 0;
}


