#include <iostream>
#include <string>

using namespace std;


/*
   The Abstract Class defines a template method that contains
   a skeleton of some algorithm, composed of calls to (usually)
   abstract primitive operations.

   Concrete subclasses should implement these operations, but
   leave the template method itself intact.
   */

class AbstractClass {
// template method defines the skeleton of an algorithm// template method defines the skeleton of an algorithm// template method defines the skeleton of an algorithm// template method defines the skeleton of an algorithm// template method defines the skeleton of an algorithm// template method defines the skeleton of an algorithm// template method defines the skeleton of an algorithm// template method defines the skeleton of an algorithm// template method defines the skeleton of an algorithm
    public:
        // don't override it
        void TemplateMethod() const {
            this->BaseOperations1();
            this->RequiredOperations1();
            this->BaseOperations2();
            this->Hook1(); // optional
            this->RequiredOperations2();
            this->BaseOperations3();
            this->Hook2(); // optional
        }
    protected:
        // these operations have already gotten default implementation
        void BaseOperations1() const {
            cout << "AbstractClass says: I am doing the bulk of the work\n";
        }
        void BaseOperations2() const {
            cout << "AbstractClass says: But I let subclasses overrid some operations\n";
        }
        void BaseOperations3() const {
            cout << "AbstractClass says: But I am doing the bulk of the work anyway\n";
        }

        // while others are pure abstract, they need to be implemented in subclasses.
        virtual void RequiredOperations1() const = 0;
        virtual void RequiredOperations2() const = 0;

        // hooks are optional
        // subclasses may override them, but not mandatory.
        // hooks provide additional extensiton points in some crucial
        // places of the algorithm
        virtual void Hook1() const {}
        virtual void Hook2() const {}
};

/*
   Concrete classes have to implement all abstract method
   They can also overrid some operations with a default implementation
   */

class ConcreteClass1 : public AbstractClass {
    protected:
        void RequiredOperations1() const override {
            cout << "ConcreteClass1 says : implemented Operation1\n";
        }

        void RequiredOperations2() const override {
            cout << "ConcreteClass1 says : implemented Operation2\n";
        }
};
/**
 * Usually, concrete classes override only a fraction of base class' operations.
 */
class ConcreteClass2 : public AbstractClass {
    protected:
        void RequiredOperations1() const override {
            std::cout << "ConcreteClass2 says: Implemented Operation1\n";
        }
        void RequiredOperations2() const override {
            std::cout << "ConcreteClass2 says: Implemented Operation2\n";
        }
        void Hook1() const override {
            std::cout << "ConcreteClass2 says: Overridden Hook1\n";
        }
};

// note: each ConcreteClass is an independent template method, defined all 
// details of the algorithms.

// so client code should work with abstract interface of base class of 
// AbstractClass
void ClientCode(AbstractClass* class_) {
    class_->TemplateMethod();
}

int main() {
    cout << "Same Client code can work with different subclasses:\n";
    // because each subclasses is complete and independent
    ConcreteClass1* concreteClass1 = new ConcreteClass1;
    ClientCode(concreteClass1);
    cout << endl;

    cout << "Same client code can work with different subclasses:\n";
    ConcreteClass2* concreteClass2 = new ConcreteClass2;
    ClientCode(concreteClass2);

    delete concreteClass1;
    delete concreteClass2;
    return 0;
}
