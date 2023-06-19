#include <iostream>
#include <string>

using namespace std;

/*
   The Mediator interface declares a method used by components
   to notify the mediator about various events. The Mediator may
   react to these events and pass the execution to other components.
   */
class BaseComponent;

class Mediator {
    public:
        virtual void Notify(BaseComponent* sender, string event) const = 0;
};

/*
   The Base Component provides the basic functionality of
   storing a mediator's instance inside component objects.
   */

class BaseComponent {
    protected:
        Mediator* mediator_;

    public:
        BaseComponent(Mediator* mediator = nullptr): mediator_(mediator) {

        }
        void set_mediator(Mediator* mediator) {
            this->mediator_ = mediator;
        }
};

/*
   Concrete Components implement various functionality. They
   don't depend on other components.
   They also don't depend on any concrete mediator classes.
   */

class Component1 : public BaseComponent {
    public:
        void DoA() {
            cout << "Component 1 does A.\n";
            this->mediator_->Notify(this, "A");
        }

        void DoB() {
            cout << "Component 1 does B.\n";
            this->mediator_->Notify(this, "B");
        }
};

class Component2 : public BaseComponent {
    public:
        void DoC() {
            cout << "Component 2 does C.\n";
            this->mediator_->Notify(this, "C");
        }

        void DoD() {
            cout << "Component 2 does D.\n";
            this->mediator_->Notify(this, "D");
        }
};

/*
   Concrete Mediators implemnt cooperative behavior by coordinating
   several components.
   */
class ConcreteMediator : public Mediator {
    private:
        Component1* component1_;
        Component2* component2_;

    public:
        ConcreteMediator(Component1* c1, Component2* c2): component1_(c1), component2_(c2) {
            this->component1_->set_mediator(this);
            this->component2_->set_mediator(this);
        }

        void Notify(BaseComponent* sender, string event) const override {
            // must implement this Notify interface
            // this is for business logic
            if (event == "A") {
                cout << "Mediator reacts on A and triggers following operations:\n";
                this->component2_->DoC();
            }
            if (event == "D") {
                cout << "Mediator reacts on D and triggers following operations:\n";
                this->component1_->DoB();
                this->component2_->DoC();
            }
        }
};

void ClientCode () {
    Component1* c1 = new Component1;
    Component2* c2 = new Component2;
    ConcreteMediator* mediator = new ConcreteMediator(c1, c2);
    cout << "Client triggers operation A.\n";
    c1->DoA(); // to mediator and trigger Notify()
    cout << endl;
    cout << "Client trigggers operation D.\n";
    c2->DoD();

    delete c1;
    delete c2;
    delete mediator;
}

int main () {
    ClientCode();
    return 0;
}
