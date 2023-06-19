#include <iostream>
#include <string>
#include <vector>

using namespace std;

/*
   The Handler interface declares
   a method for building the chain of handlers.
   It also declares a method for executing a request.
   */
class Handler {
    public:
        virtual Handler* SetNext(Handler* handler) = 0;
        virtual string Handle(string request) = 0;
};

/*
   The default chaining behavior can be implemented inside a base handler class.
   */
class AbstractHandler : public Handler {
    private:
        Handler* next_handler_;
    public:
        AbstractHandler(): next_handler_(nullptr){}

        Handler* SetNext(Handler* handler) override {
            // Returning a handler from here will let us link handlers in a convenient
            // way like this:
            // $monkey->setNext($squirrel)->setNext($dog);
            return this->next_handler_ = handler;
        }
        string Handle(string request) override {
            if (this->next_handler_) {
                return this->next_handler_->Handle(request);
            }
            return {};
        }
};

/* All Concrete Handlers either handle a request or pass it to the next handler
   in the chain.
   */
class MonkeyHandler : public AbstractHandler {
    public:
        string Handle(string request) override {
            if (request == "Banana")  {
                return "Monkey: I'll eat the " + request + "\n.";
            } else {
                // it means call next->Handle, which has been given in default impmentaton in AbstractHandler;
                return AbstractHandler::Handle(request);
            }
        }
};

class SquirrelHandler : public AbstractHandler {
    public:
        string Handle(string request) override {
            if (request == "Nut")  {
                return "Squirrel: I'll eat the " + request + "\n.";
            } else {
                return AbstractHandler::Handle(request);
            }
        }
};

class DogHandler : public AbstractHandler {
    public:
        string Handle(string request) override {
            if (request == "MeatBall")  {
                return "Dog: I'll eat the " + request + "\n.";
            } else {
                return AbstractHandler::Handle(request);
            }
        }
};

/*
   The client code is usually suited to work with a single handler.
   In most cases, it is not even aware that the handler is part of a chain.
   */

void ClientCode(Handler& handler) {
    vector<string> food = {"Nut", "Banana", "Cup of coffee"};
    for (const auto& f : food) {
        cout << "Client: Who wants a " << f << "?\n";
        const string result = handler.Handle(f);
        if (!result.empty()) {
            cout << " " << result;
        } else {
            cout << " " << f << " was left untouched.\n";
        }
    }
}

/*
   The other part of the client code constructs the actual chain.
   */

int main() {
    MonkeyHandler *monkey = new MonkeyHandler;
    SquirrelHandler *squirrel = new SquirrelHandler;
    DogHandler *dog = new DogHandler;
    monkey->SetNext(squirrel)->SetNext(dog);

    /* The client should be able to send a request to any handler, 
       not just the first one in the chain.
       */
    cout << "Chain: Monkey > Squirrel > Dog\n\n";
    ClientCode(*monkey);
    cout << "\n";
    cout << "Subchain: Squirrel > Dog\n\n";
    ClientCode(*squirrel);
    // note: single link, not circular link

    delete monkey;
    delete squirrel;
    delete dog;
    return 0;
}
