#include <iostream>
#include <string>
#include <unordered_map>

using std::cout;
using std::endl;
using std::string;
using std::unordered_map;

// Prototype Design Pattern

// Intent: let you copy existing objects without making
// your code dependent on their classes.

enum Type { PROTOTYPE_1 = 0, PROTOTYPE_2 };

/**
  The example class that has cloning ability.
  We'll see how the values of fields with different types will be cloned.
   */

class Prototype {
  protected:
    string prototype_name_;
    float prototype_field_; // common to all sub-class
  public:
    Prototype() {}
    Prototype(string prototype_name) : prototype_name_(prototype_name) {}
    virtual ~Prototype() {}

    // abstract interface needs to define clone and return a pointer to base
    // Prototype
    virtual Prototype *Clone() const = 0;
    virtual void Method(float prototype_field) {
        this->prototype_field_ = prototype_field;
        cout << "Call Method from " << this->prototype_name_
             << " with field : " << this->prototype_field_ << endl;
    }
};

/**
  Concrte Prototype is a sub-class of abstract Prototype and it must implement
  its own version of Clone method In this example all data members of Prototype
  Class are in the Stack? If you have pointers in your properties for example:
  string* name_, you will need to implement the copy constructor to make sure
  you have a deep copy from the clone method.
  */

class ConcreteProtype1 : public Prototype {
  private:
    float concrete_prototype_field1_;

  public:
    // usually implement (at least have such a constructor) concrete prototype
    // constructor to take all necessary parameters for prototype construction
    // call base class constructor first

    // it helps to construct clone method by new () since constructor will only
    // release completed object once it finishes construction(no imcomplete
    // object will be released)

    ConcreteProtype1(string prototype_name, float concrete_prototype_field)
        : Prototype(prototype_name),
          concrete_prototype_field1_(concrete_prototype_field) {}

    // implement Clone with the help of copy constructor !!!
    // Notice that Clone method return a pointer to a new ConcreteProtype1
    // replica via pointer to base Prototype. the client (who calls the Clone
    // method) has the responsiblity to free that memory. If you have smart
    // pointer knowledge you may prefer unique_pointer here.
    Prototype *Clone() const override { return new ConcreteProtype1(*this); }
};

class ConcreteProtype2 : public Prototype {
  private:
    float concrete_prototype_field2_;

  public:
    ConcreteProtype2(string prototype_name, float concrete_prototype_field)
        : Prototype(prototype_name),
          concrete_prototype_field2_(concrete_prototype_field) {}

    Prototype *Clone() const override { return new ConcreteProtype2(*this); }
};

// simple factory
// provide pre-configured Prototypes to be cloned

class PrototypeFactory {
  private:
    unordered_map<Type, Prototype *, std::hash<int>> prototypes_;

  public:
    PrototypeFactory() {
        prototypes_[Type::PROTOTYPE_1] =
            new ConcreteProtype1("PROTOTYPE_1 ", 50.0f);
        prototypes_[Type::PROTOTYPE_2] =
            new ConcreteProtype2("PROTOTYPE_2 ", 60.0f);
    }

    // need to delete exising "Prototypes"
    ~PrototypeFactory() {
        delete prototypes_[Type::PROTOTYPE_1];
        delete prototypes_[Type::PROTOTYPE_2];
    }

    // provide an interface for client to create a clone of protypes
    // type is needed
    Prototype *CreatePrototype(Type type) { return prototypes_[type]->Clone(); }
};

void Client(PrototypeFactory &prototype_factory) {
    cout << "Let's create a Prototype1" << endl;
    Prototype *prototype = prototype_factory.CreatePrototype(Type::PROTOTYPE_1);
    // it is a concrete prototype actually.
    // but of course it can call the common Method in base class
    prototype->Method(90);
    delete prototype;
    cout << endl;

    cout << "Let's create a Prototype2" << endl;
    prototype = prototype_factory.CreatePrototype(Type::PROTOTYPE_2);
    prototype->Method(10);
    delete prototype;
    cout << endl;
}

int main() {
    PrototypeFactory *prototype_factory = new PrototypeFactory();
    Client(*prototype_factory);
    delete prototype_factory;
    return 0;
}
