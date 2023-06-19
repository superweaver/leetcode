// https://refactoring.guru/design-patterns/factory-method/cpp/example
#include <iostream>
/**
 * The Product interface declares the operations that all concrete classes must
 * implement

 * Hai: This is an interface (pure virtual) for product (what the factory want
 to prodce), the common interface of this Product is defined in Operation().
 however, each concrete product should have its own implementation of Operation.
 */

class Product {
  public:
    virtual ~Product() {}

    virtual std::string Operation() const = 0;
};

/**
 * Concrete Prodct provide varisous implementations of the Product interface
 * Hai: any ConcreteProduct is responsible for defining its own implementation
 * of the common interface of Operation()
 */
class ConcreteProduct1 : public Product {
  public:
    std::string Operation() const override {
        return "{result of ConcreteProduct1}";
    }
};

class ConcreteProduct2 : public Product {
  public:
    std::string Operation() const override {
        return "{result of ConcreteProduct2}";
    }
};

/**
  The Creator class declares the factory method that is supposed to return
  an object of a Prodct class.
  The Creator's subclasses usually provide the implementation of this method.
  */

class Creator {
    /*
       Note that the Creator may also provide some default implementation of the
       factory method
       */
  public:
    virtual ~Creator(){};
    /*
Hai: FactoryMethod is the interface for "building" products
each concrete creator will override this "building" method to return pointer to
subclass objects.
       */
    virtual Product *FactoryMethod() const = 0;
    /*
       Also note that, despide its name, the Creator's primary responsibility is
       not creating products. Usually, it constains some core business logic
       that relies on Product objects, returned by the factory method.
       Subclasses can indirectly change that business logic by overriding the
       factory method and return a different type of prodcut from it.
       */
    /*
Hai: common interface with default implementation
       */
    std::string SomeOperation() const {
        // Call the factory method to create a Product object.
        Product *product = this->FactoryMethod();
        // Now, use this product.
        std::string result =
            "Creator: The same creator's code has just worked with " +
            product->Operation();
        delete product;
        return result;
    }
};

/**
  Concrete Creators override the factory method in order to change the resulting
  product's type.
  */
class ConcreteCreator1 : public Creator {
    /* note:
       the signature of the method still uses the abstract product type,
       even through the concrete product is actually returned from the method.
       This way the Creator can stay independent of concrete product classes.
       */
  public:
    Product *FactoryMethod() const override { return new ConcreteProduct1(); }
};

class ConcreteCreator2 : public Creator {
  public:
    Product *FactoryMethod() const override { return new ConcreteProduct2(); }
};

/*
   The client code works with an instance of a concrete creator, albeit through
   its base interface. As long as the client keeps working with the creator via
   the base interface, you can pass it any creator's subclass.
   */

void ClientCode(const Creator &creator) {
    std::cout
        << "Client: I'm not aware of the creator's class, but it still works.\n"
        << creator.SomeOperation() << std::endl;
}

/*
   The Application picks a creator's type depending on the configuration or
   environment.
   */
int main() {
    std::cout << "App: Launched with ConcreteCreator1. \n";
    Creator *creator1 = new ConcreteCreator1();
    ClientCode(*creator1);
    std::cout << std::endl;

    std::cout << "App: Launched with ConcreteCreator2. \n";
    Creator *creator2 = new ConcreteCreator1();
    ClientCode(*creator2);
    std::cout << std::endl;

    delete creator1;
    delete creator2;
    return 0;
}
