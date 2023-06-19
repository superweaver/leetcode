#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;

/*
   Flyweight Design Pattern

Intent: let you fit more objects into the available
amount of RAM by sharing common parts of state between multiple
objects, instead of keeping all of the data in each object.
   */

struct SharedState{
    string brand_;
    string model_;
    string color_;
    SharedState(const std::string &brand, const std::string &model, const std::string &color)
        : brand_(brand), model_(model), color_(color)
    {
    }

    friend ostream& operator << (ostream& os, const SharedState& ss){
        return os << "[" << ss.brand_ << " , " << ss.model_ << " , " << ss.color_ << " ]";
    }
};

struct UniqueState
{
    string owner_;
    string plates_;
    UniqueState(const std::string &owner, const std::string &plates)
        : owner_(owner), plates_(plates)
    {
    }

    friend std::ostream &operator<<(std::ostream &os, const UniqueState &us)
    {
        return os << "[ " << us.owner_ << " , " << us.plates_ << " ]";
    }
};

/*
   The Flyweight stores a common portion of the state (instrisic state)
   that belongs to multiple real business entities.
   !!!!
   The Flyweight accepts the rest of state(extrinsic state) via its method parameters.
   */
class Flyweight {
    private:
        SharedState* shared_state_;
    public:
        Flyweight(const SharedState* shared_state) : shared_state_(new SharedState(*shared_state)) {
        }
        Flyweight(const Flyweight& other) : shared_state_(new SharedState(*other.shared_state_)) {
        }
        ~Flyweight() {
            delete shared_state_;
        }
        SharedState* shared_state() const {
            return shared_state_;
        }
        // this is the operation done by complete object(include both Flyweight and UniqueState)
        void Operation(const UniqueState& unique_state) const {
            cout << "Flyweight: Displaying shared (" << *shared_state_ << ") and unique_state (" << unique_state << ") \n";
        }
};

/*
   The Flyweight factory creates and manages the Flyweight objects.
   It ensures that flyweights are shared correctly. When the client
   requests a flyweight, the factory either returns an existing instance
   or creates a new one, if it doesn't exist yet.
   */
class FlyweightFactory {
    private:
    unordered_map<string, Flyweight> flyweights_;
    string GetKey(const SharedState& ss) const {
        return  ss.brand_ + "_" + ss.model_ + "_" + ss.color_;
    }
    public:
    FlyweightFactory(std::initializer_list<SharedState> share_states) {
        for (const SharedState& ss : share_states) {
            this->flyweights_.insert(std::make_pair<std::string, Flyweight>(this->GetKey(ss), Flyweight(&ss)));
            //flyweights_[this->GetKey(ss)] = std::move(Flyweight(&ss));
        }
    }
    /**
     * Returns an existing Flyweight with a given state or creates a new one.
     */
    Flyweight GetFlyweight(const SharedState &shared_state)
    {
        std::string key = this->GetKey(shared_state);
        if (this->flyweights_.find(key) == this->flyweights_.end())
        {
            std::cout << "FlyweightFactory: Can't find a flyweight, creating new one.\n";
            this->flyweights_.insert(std::make_pair(key, Flyweight(&shared_state)));
            //flyweights_[key] = std::move(Flyweight(&shared_state));
        }
        else
        {
            std::cout << "FlyweightFactory: Reusing existing flyweight.\n";
        }
        return this->flyweights_.at(key);
    }

    void ListFlyweights() const {
        cout << "\n FlyweightFactory: I have " << this->flyweights_.size() << " flyweights:\n";
        for(const auto &p : this->flyweights_) {
            cout << p.first << endl;
        }
    }
};

// client?
void AddCarToPoliceDatabase (FlyweightFactory& ff, const string& plate, const string& owner,
        const string& brand, const string& model, const string& color){
    cout << "\nClient: Adding a car to database.\n";
    const Flyweight& flyweight = ff.GetFlyweight({brand, model, color});
    // The client code either stores or calculates extrinsic state and passes it
    // to the flyweight's methods.
    flyweight.Operation({owner, plate});
}

/*
   the client code usually creates a bunch of
pre-poulated flyweights in the initialization stage of application
   */

int main () {
    // note how to pass to constructor
    FlyweightFactory *factory = new FlyweightFactory({{"Chevrolet", "Camaro2018", "pink"}, {"Mercedes Benz", "C300", "black"}, {"Mercedes Benz", "C500", "red"}, {"BMW", "M5", "red"}, {"BMW", "X6", "white"}});
    factory->ListFlyweights();

    AddCarToPoliceDatabase(*factory,
                            "CL234IR",
                            "James Doe",
                            "BMW",
                            "M5",
                            "red");

    AddCarToPoliceDatabase(*factory,
                            "CL234IR",
                            "James Doe",
                            "BMW",
                            "X1",
                            "red");
    factory->ListFlyweights();
    // factory is changed (new Flyweigt is added)
    delete factory;

    return 0;
}

