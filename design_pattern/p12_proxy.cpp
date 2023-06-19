#include <iostream>
#include <string>
using namespace std;
/*
   The Subject Interface declare common operation
   for both RealSubject and the Porxy.
   As long as the client works with the RealSubject
   using this interface, you'll be able to pass it
   a proxy instead of a real subject.
   */

class Subject {
    public:
        // common interface for both Proxy and RealSubject
        virtual void Request() const = 0;
};

/*
   The RealSubject contains some core business logic.
   Usually, RealSubject are capable of doing some useful
   work which may also be very slow or sensitive
   e.g. correcting input data.
   A Proxy can solve these issue without any change
   to the RealSubject's code
   */
class RealSubject : public Subject {
    public:
        void Request() const override {
            std::cout << "RealSubject: Handling request.\n";
        }
};

/*
   The Proxy has an interface identical to the RealSubject
   */
class Proxy : public Subject {
    private:
        RealSubject* real_subject_;
        bool CheckAccess() const {
            // some real check should go here
            cout << "Proxy: Checking access prior to firing a real request.\n";
            return true;
        }
        void LogAccess() const {
            cout << "Proxy: Logging the time of request.\n";
        }
    public:
        /*
           The Proxy maintains a reference to an object of the
           RealSubject class.
           It can be either lazy-loaded or passed to the Proxy
           by the client.
           */
        Proxy(RealSubject* real_subject):real_subject_(new RealSubject(*real_subject)){
        }
        ~Proxy() {
            delete real_subject_;
        }
        /*
           the most common application of the proxy pattern
           are lazy loading, caching, controlling the access, etc.
           A proxy can perform one of these things and then,
           depending on the request, pass the execution to the same
           method in a linked RealSubject object.
           */
        void Request() const override {
            if (this->CheckAccess()) {
                // delegate to RealSubject
                this->real_subject_->Request();
                // extra work can be done in proxy object
                this->LogAccess();
            }
        }
};

/*
   The client code is supposed to work with all objects
   (both subjects and proxies) via the Subject interface
   in order to support both real subjects and proxies.
    In real life, however, clients mostly work with their real subjects
    directly. In this case, to implement the pattern more easily, you can extend
    your proxy from the real subject's class.
   */
void ClientCode (const Subject& subject) {
    // ...
    subject.Request();
}

int main() {
    cout << "Client: Executing the client code with a real subject:\n";
    RealSubject* real_subject = new RealSubject();
    ClientCode(*real_subject);
    cout << endl;

    cout << "Client: Executing the same client code with a proxy:\n";
    Proxy* proxy = new Proxy(real_subject);
    ClientCode(*proxy);
    cout << endl;

    delete real_subject;
    delete proxy;
    return 0;
}
