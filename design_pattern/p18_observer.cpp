/*
   observer design pattern

   let you define a subscription mechanism to notify
   multiple objects about any events that happen to
   the object they're observing.

   The Subject is also called the Publisher
   and the Observer is often called the Subscriber
   */

#include <iostream>
#include <list>
#include <string>

using namespace std;

// abstract interface
class IObserver {
    public:
        virtual ~IObserver(){}
        // message_from_subject is the context from publisher
        // then each concrete Observer can update according to this context
        virtual void Update(const string& message_from_subject) = 0;
};

// interface for publisher
class ISubject {
    public:
        virtual ~ISubject(){}
        // subscribe
        virtual void Attach(IObserver* observer) = 0;
        // unsubscribe
        virtual void Detach(IObserver* observer) = 0;
        // notify each Observer in list
        virtual void Notify() = 0;
};

/*
   The Subject owns some important state
   and notifies observers when the state changes.
 */

class Subject : public ISubject {
    public:
        virtual ~Subject() {
            cout << "Bye, I was the Subject" << endl;
        }
        void Attach(IObserver* observer) override {
            list_observer_.push_back(observer);
        }
        void Detach(IObserver* observer) override {
            list_observer_.remove(observer);
        }
        void Notify() override {
            list<IObserver*>::iterator iterator = list_observer_.begin();
            HowManyObserver();
            while(iterator != list_observer_.end()) {
                (*iterator)->Update(message_);
                ++iterator;
            }
        }

        void CreateMessage(string message = "Empty"){
            this->message_ = message;
            Notify();
        }
        void  HowManyObserver() {
            cout << "There are " << list_observer_.size() << " observers in the list.\n";
        }

        /**
         * Usually, the subscription logic is only a fraction of what a Subject can
         * really do. Subjects commonly hold some important business logic, that
         * triggers a notification method whenever something important is about to
         * happen (or after it).
         */
        void SomeBusinessLogic() {
            this->message_ = "change message message_";
            Notify();
            cout << "I'm about to do something important\n";
        }

    private:
        list<IObserver*> list_observer_;
        // message_ is the state (information that observers are interested in)
        string message_;
};

class Observer : public IObserver {
    public:
        // link them together when construction
        Observer(Subject& subject) : subject_(subject){
            this->subject_.Attach(this); // is this "available"?
            cout << "Hi, I'm the Observer \"" << ++Observer::static_number_ << "\".\n";
            this->number_ = Observer::static_number_;
        }
        virtual ~Observer() {
            cout << "Goodbye, I was the Observer \"" << this->number_ << "\".\n";
        }

        void Update(const string& message_from_subject) override {
            message_from_subject_ = message_from_subject;
            PrintInfo();
        }

        void RemoveMeFromTheList() {
            this->subject_.Detach(this);
            cout << "Observer \"" << this->number_ << "\" removed from the list.\n";
        }
        void PrintInfo() {
             std::cout << "Observer \"" << this->number_ << "\": a new message is available --> " << this->message_from_subject_ << "\n";
        }
    private:
        string message_from_subject_;
        Subject& subject_;
        static int static_number_;
        int number_;
};

int Observer::static_number_ = 0;

void ClientCode() {
    Subject* subject = new Subject;
    Observer* observer1 = new Observer(*subject);
    Observer* observer2 = new Observer(*subject);
    Observer* observer3 = new Observer(*subject);
    Observer* observer4 = nullptr;
    Observer* observer5 = nullptr;
    // notify is conducted inside CreateMessage()
    subject->CreateMessage("Hello world! :D");
    // drop 3
    observer3->RemoveMeFromTheList();

    subject->CreateMessage("The weather is hot today! :p");
    // add 4
    observer4 = new Observer(*subject);
    // drop 2
    observer2->RemoveMeFromTheList();
    // add 5
    observer5 = new Observer(*subject);

    subject->CreateMessage("My new car is great! ;)");

    observer5->RemoveMeFromTheList();
    observer4->RemoveMeFromTheList();
    observer1->RemoveMeFromTheList();

    delete observer1;
    delete observer2;
    delete observer3;
    delete observer4;
    delete observer5;
    delete subject;
}

int main() {
    ClientCode();
    return 0;
}

