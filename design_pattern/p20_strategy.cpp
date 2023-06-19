#include <iostream>
#include <string>
#include <algorithm>
#include <memory>
// #include <string_view>

using namespace std;

/*
   The Strategy interface declares operations common to all
   supported versions of some algorithm

   The Context uses this interface to call the algorithm defined
   by Concrete Strategies.
   */
class Strategy {
    public:
        virtual ~Strategy() {}
        virtual string doAlgorithm(std::string_view data) const = 0;
};

/*
   The Context defines the interface of interest to clients.
   */
class Context {
/*
   The Context maintains a reference to one of the Strategy
     * objects. The Context does not know the concrete class of a strategy. It
     * should work with all strategies via the Strategy interface.
   */
    private:
     /**
     * Usually, the Context accepts a strategy through the constructor, but also
     * provides a setter to change it at runtime.
     */
        unique_ptr<Strategy> strategy_;
    public:
        explicit Context(unique_ptr<Strategy> && strategy) : strategy_(std::move(strategy)) {
        }
        /*
           Usually, the Context allows replacing a Strategy object at runtime.a
           */
        void set_strategy(unique_ptr<Strategy>&& strategy) {
            strategy_ = std::move(strategy);
        }

        /*
           The Context delegates work to certain Strategy object
           instead of implementing multiple versions of the algorithm on its own.
           */
        void doSomeBusinessLogic() const {
            if (this->strategy_) {
                cout << "Context: Sorting data using the strategy(not sure how it'll do it)\n";
                string result = this->strategy_->doAlgorithm("aecbd");
            } else {
                cout << "Context: Strategy is not set" << endl;
            }
        }
};

/*
   Concrete Strategies implement the algorithm while following the base 
   Strategy interface. The interface makes them interchangable in the context.
   */
class ConcreteStrategyA : public Strategy {
    public:
        string doAlgorithm(string_view data) const override {
            string result(data);
            sort(std::begin(result), std::end(result));
            return result;
        }
};

class ConcreteStrategyB : public Strategy {
    public:
        string doAlgorithm(string_view data) const override {
            string result(data);
            sort(std::begin(result), std::end(result), std::greater<>());
            return result;
        }
};


/*
Note:Client code picks a concrete Strategy
and pass it to the context. The client should be aware of the diffeences
between strategies in order to make the right choice.
   */
void clientCode() {
    Context context(std::make_unique<ConcreteStrategyA>());
    cout << "Client: Strategy is set to normal sorting.\n";
    context.doSomeBusinessLogic();
    cout << endl;
    cout << "Client: Strategy is set to reverse sorting.\n";
    context.set_strategy(std::make_unique<ConcreteStrategyB>());
    context.doSomeBusinessLogic();
}

int main() {
    clientCode();
    return 0;
}
