#include <iostream>
#include <string>
#include <vector>

using namespace std;

/*
   The Visitor Interface delcares a set of visiting methods
   that corrspond to component classes. The signature of a visiting method allows
   the visitor to identify the exact class of the component that it's dealing with.
   */

class ConcreteComponentA;
class ConcreteComponentB;

// Interface
class Visitor {
    public:
        // here Concrete Component must be provided instead of base interface
        virtual void VisitConcreteComponentA(const ConcreteComponentA* element) const = 0;
        virtual void VisitConcreteComponentB(const ConcreteComponentB* element) const = 0;
};
// Component is the class we'r going to visit
// The Component Interface declares an 'accept' method that should take base Visitor interface as argument
class Component {
    public:
        virtual ~Component() {}
        virtual void Accept(Visitor* visitor) const = 0;
};

/*
   Each Concrete Component must implement the 'Accept' method in such a way that 
   it calls the visitor's method corrsponding to current Concrete component class.
   */
class ConcreteComponentA : public Component {
    public:
        /**
         * Note that we're calling `visitConcreteComponentA`, which matches the
         * current class name. This way we let the visitor know the class of the
         * component it works with.
         */
        void Accept(Visitor* visitor) const override {
            // must match to current class
            visitor->VisitConcreteComponentA(this);
        }
        /**
         * Concrete Components may have special methods that don't exist in their base
         * class or interface. The Visitor is still able to use these methods since
         * it's aware of the component's concrete class.
         */
        std::string ExclusiveMethodOfConcreteComponentA() const {
            return "A";
        }
};

class ConcreteComponentB : public Component {
    public:
        /**
         * Note that we're calling `visitConcreteComponentB`, which matches the
         * current class name. This way we let the visitor know the class of the
         * component it works with.
         */
        void Accept(Visitor* visitor) const override {
            // must match to current class
            visitor->VisitConcreteComponentB(this);
        }
        /**
         * Concrete Components may have special methods that don't exist in their base
         * class or interface. The Visitor is still able to use these methods since
         * it's aware of the component's concrete class.
         */
        std::string SpecialMethodOfConcreteComponentB() const {
            return "B";
        }
};

/*
   Concrete Visitor implements several versions of the same algorithm,
   which can work with all concrete component classes.
   You can experience the biggest benefit of the Visitor pattern when using it
 * with a complex object structure, such as a Composite tree. In this case, it
 * might be helpful to store some intermediate state of the algorithm while
 * executing visitor's methods over various objects of the structure.
 */

class ConcreteVisitor1: public Visitor {
    public:
        void VisitConcreteComponentA(const ConcreteComponentA* element) const override {
            cout << element->ExclusiveMethodOfConcreteComponentA() << " + ConcreteVisitor1\n";
        }
        void VisitConcreteComponentB(const ConcreteComponentB* element) const override {
            cout << element->SpecialMethodOfConcreteComponentB() << " + ConcreteVisitor1\n";
        }
};

class ConcreteVisitor2 : public Visitor {
    public:
        void VisitConcreteComponentA(const ConcreteComponentA *element) const override {
            std::cout << element->ExclusiveMethodOfConcreteComponentA() << " + ConcreteVisitor2\n";
        }
        void VisitConcreteComponentB(const ConcreteComponentB *element) const override {
            std::cout << element->SpecialMethodOfConcreteComponentB() << " + ConcreteVisitor2\n";
        }
};

/*
   the client code can run visitor operations over any set of elements without
   figuring out their concrete classes.
   */
void ClientCode (const vector<const Component*>& components, Visitor* visitor) {
    for(const auto& p : components) {
        // The accept operation directs a call to the appropriate operation in the visitor object
        p->Accept(visitor);
    }
}

int main () {
    vector<const Component*> components{new ConcreteComponentA, new ConcreteComponentB};
    cout << "The client code works with all visitors via the base Visitor interface:\n";
    ConcreteVisitor1* visitor1 = new ConcreteVisitor1;
    ClientCode(components, visitor1);
    cout << endl;

    cout << "It also allows the same client code to work withdifferent types of visitors:\n";
    ConcreteVisitor2* visitor2 = new ConcreteVisitor2;
    ClientCode(components, visitor2);
    cout << endl;

    for (const auto& p:components) {
        delete p;
    }
    delete visitor1;
    delete visitor2;

    return 0;
}


