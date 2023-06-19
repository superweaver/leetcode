#include <iostream>
#include <string>
#include <vector>
#include <ctime>

using namespace std;

/*
   The Memento interface provides a way to retrieve
   the memento's metadata, such as creation date or name.
   However, it doesn't expose the Originator's state.
*/

class Memento{
    public:
        virtual ~Memento() {}
        // get metadata but not state of Originator
        virtual string GetName() const = 0;
        virtual string date() const = 0;

        virtual string state() const = 0;
};

/**
  The Concrete Memento contains the infrastructure for
  storing the Originator's state
  */
class ConcreteMemento: public Memento {
    private:
        string state_;
        string date_;
    public:
        // when created, need to get state to take a snapshot
        ConcreteMemento(string state) : state_(state){
            time_t now = time(0);
            this->date_ = ctime(&now);
        }

        // The Originator uses this method when restoring its state.
        string state() const override {
            return this->state_;
        }
        string GetName() const override {
            return this->date_ + " / (" + this->state_.substr(0, 9) + "...)";
        }
        string date() const override {
            return this->date_;
        }
};

/*
   The Originator holds some important state that may change
   over time. It also defines a method for saving the sate
   inside a memento and another method for restoring the state from it.
   */
class Originator {
    private:
        string state_;
        std::string GenerateRandomString(int length = 10) {
            const char alphanum[] =
                "0123456789"
                "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                "abcdefghijklmnopqrstuvwxyz";
            int stringLength = sizeof(alphanum) - 1;

            std::string random_string;
            for (int i = 0; i < length; i++) {
                random_string += alphanum[std::rand() % stringLength];
            }
            return random_string;
        }
    public:
        Originator(string state) : state_(state) {
            cout << "Originator: my initial state is:" << state_ << endl;
        }
        /*
           Originator's business logic may affect its internal state.
           Therefore, the client should backup the state before
           launching methods of the business via the save() method
           */
        void DoSomthing() {
            cout << "Originator: I'm doing something important.\n" << endl;
            this->state_ = GenerateRandomString(30);
            cout << "Originator: and my state has changed to " << this->state_ << endl;
        }

        /*
           saves the current state inside a memento
           */
        Memento* Save() {
            return new ConcreteMemento(this->state_);
        }
        /*
           restores the Originator's state from a memento object.j
           */
        void Restore(Memento* memento) {
            this->state_ = memento->state();
            cout << "Originator: my state has changed to: " << this->state_ << "\n";
        }
};

/*
   The Caretaker doesn't depend on the ConcreteMemento class.
   Therefore, it doesn't have access to the Originator's state,
   stored inside the memento.
   It works with all mementos via the base Memento interface.
   */
class Caretaker {
    private:
        vector<Memento* > mementos_;
        Originator* originator_;
    public:
        Caretaker(Originator* originator) : originator_(originator) {
        }
        ~Caretaker() {
            for (auto& m: mementos_) {
                delete m;
            }
        }

        void Backup() {
            cout << "\nCaretaker: saving Originator's state...\n";
            mementos_.push_back(this->originator_->Save());
        }

        void Undo() {
            if(mementos_.empty()) {
                return;
            }
            Memento* memento = mementos_.back();
            mementos_.pop_back();
            cout << "Caretaker: restoring state to" << memento->GetName() << endl;
            try {
                this->originator_->Restore(memento);
            } catch(...) {
                this->Undo();
            }
        }

        void ShowHistory() const {
            cout << "Caretaker: Here's the list of mementos:\n";
            for (Memento* const & memento : mementos_) {
                cout << memento->GetName() << "\n";
            }
        }
};

void ClientCode() {
    Originator* originator = new Originator("Super-duper-super-puper-super");
    Caretaker* caretaker = new Caretaker(originator);
    // backup before doing something
    caretaker->Backup();
    originator->DoSomthing();

    caretaker->Backup();
    originator->DoSomthing();

    caretaker->Backup();
    originator->DoSomthing();
    cout << endl;
    caretaker->ShowHistory();
    cout << "\nClient: Now, let's rollback\n\n";
    caretaker->Undo();
    cout << "\nClient: Once more!\n\n";
    caretaker->Undo();

    delete originator;
    delete caretaker;
}

int main() {
    srand(static_cast<unsigned int>(std::time(NULL)));
    ClientCode();
    return 0;
}

