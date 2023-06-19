#include <iostream>
/**
  Each distinct product of a product family should have a base interface.
  All variants of the product must implement this interface.
  */

// eg: Abstract Chair
class AbstractProductA {
  public:
    virtual ~AbstractProductA(){};
    // interface for common behavior of ProductA
    virtual std::string UsefulFunctionA() const = 0;
};

/**
  Concrete Products are created by corresponding Concrete factories.
  */
// morden style chair
class ConcreteProductA1 : public AbstractProductA {
  public:
    // override the common behavior of ProductA
    std::string UsefulFunctionA() const override {
        return "The result of the product A1";
    }
};

// victorian style chair
class ConcreteProductA2 : public AbstractProductA {
  public:
    // override the common behavior of ProductA
    std::string UsefulFunctionA() const override {
        return "The result of the product A2";
    }
};

/**
  here is the base interface of another product.
  All products can interact with each other,
  but proper interaction is possible only when products of
  the same concrete variant.
  */

// eg: interaction between same style of chair and desk (another product)

class AbstractProductB {
    // eg: Desk
    /**
      Product B is able to do its own things...
       */
  public:
    virtual ~AbstractProductB(){};
    virtual std::string UsefulFunctionB() const = 0;
    /**
      but it also can collaborate with ProductA.

      The Abstract Factor makes sure that all products it creates are of
      the same variant (Hai: same style -> same family of products) and thus,
      compatible.
      */
    virtual std::string
    AnotherUsefulFunctionB(const AbstractProductA &collaborator) const = 0;
};

/**
  Concrete Products are created by corresponding Concrete factories.
  */
// morden style desk
class ConcreteProductB1 : public AbstractProductB {
  public:
    // override the common behavior of ProductB
    std::string UsefulFunctionB() const override {
        return "The result of the product B1";
    }

    /**
      the variant, Product B1, is only able to work correctly with the variant,
      ProductA1. Nevertheless, it accepts any instance of AbstractProductA as an
      argument
      */
    std::string AnotherUsefulFunctionB(
        const AbstractProductA &collaborator) const override {
        const std::string result =
            collaborator.UsefulFunctionA(); // common interface
        return "The result of the B1 collaborating with ( " + result + " )";
    }
};

// victorian style of desk
class ConcreteProductB2 : public AbstractProductB {
  public:
    // override the common behavior of ProductB
    std::string UsefulFunctionB() const override {
        return "The result of the product B2";
    }

    /**
      the variant, Product B2, is only able to work correctly with the variant,
      ProductA2. Nevertheless, it accepts any instance of AbstractProductA as an
      argument
      */
    std::string AnotherUsefulFunctionB(
        const AbstractProductA &collaborator) const override {
        const std::string result =
            collaborator.UsefulFunctionA(); // common interface
        return "The result of the B2 collaborating with ( " + result + " )";
    }
};

/**
  The abstract factory interface declares a set of methods that return different
  abstrcat products.
  The products are called a family and are related by a high-level theme or
  concept. Products of one family are usually able to collaborate among
  themselves. A family of products my have several variants(different products),
  but the products of one variant(one style) are incompatible with products of
  another variant(style).
   */

// the production is done by concrete factories
// each concrete factory produce one style/variant of all products

class AbstractFactory {
  public:
    // for each product, a common interface to produce it must be delared here.
    virtual AbstractProductA *CreateProductA() const = 0;
    virtual AbstractProductB *CreateProductB() const = 0;
};

/**
  Concrete factories produce a family of products that belong to a single
  variant (style). The factory guarantees that resulting products are
  compatible. (of same style) Note that signatures of the concrete factory's
  methods return an abstract prodcut,(via pointer to abstract product) while
  inside the method a concrete product is instantiated.
  */

class ConcreteFactory1 : public AbstractFactory {
  public:
    AbstractProductA *CreateProductA() const override {
        return new ConcreteProductA1();
    }

    AbstractProductB *CreateProductB() const override {
        return new ConcreteProductB1();
    }
};
/**
  Each Concrete Factory has a corresponding product variant.
   */
class ConcreteFactory2 : public AbstractFactory {
  public:
    AbstractProductA *CreateProductA() const override {
        return new ConcreteProductA2();
    }

    AbstractProductB *CreateProductB() const override {
        return new ConcreteProductB2();
    }
};

/**
The client code works with factories and products only through abstract
types: AbstractFactory and AbstractProduct.
This lets you pass any factory or product subclass to the client without
breaking it
   */
void ClientCode(const AbstractFactory &factory) {

    const AbstractProductA *product_a = factory.CreateProductA();
    const AbstractProductB *product_b = factory.CreateProductB();
    std::cout << product_b->UsefulFunctionB() << "\n";
    std::cout << product_b->AnotherUsefulFunctionB(*product_a) << "\n";
    delete product_a;
    delete product_b;
}

int main() {
    std::cout << "Client: Testing client code with the first factory type:\n";
    ConcreteFactory1 *f1 = new ConcreteFactory1();
    ClientCode(*f1);
    delete f1;
    std::cout << std::endl;

    std::cout << "Client: Testing client code with the second factory type:\n";
    ConcreteFactory2 *f2 = new ConcreteFactory2();
    ClientCode(*f2);
    delete f2;
    std::cout << std::endl;
}
