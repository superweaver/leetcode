#include <algorithm>
#include <iostream>
#include <list>
#include <string>

using namespace std;
/**
  The base Component class declares common operations for both
  simple and complex objects of a composition.
  */
class Component {
    protected:
        Component* parent_;
        /**
          Optionally, the base component can declare an interface for setting
          and accessing a parent of the component in a tree structure.
          It can provide some default implementation for these methods.
          */
    public:
        virtual ~Component() {}
        void SetParent(Component* parent){
            this->parent_ = parent;
        }
        Component* GetParent() {
            return this->parent_;
        }
        /*
           In some cases, it would be beneficiall to define the child-management
           operations right in the base Component class. This way, you won't need to
           expose any concrete Component classes to the client code, even during the 
           object tree assembly. The downside is that these method will be empty for the 
           leaf-level components.
           */
        virtual void Add(Component* component) {}
        virtual void Remove(Component* component) {}

        /*
           You can provide a method that lets the client code figure out whether
           a component can bear children.
           */
        virtual bool IsComposite() const {
            return false;
        }
        /*
           the base Component may implement some default behavior
           or leave it to concrete classes (by declaring the method containing the behavior as abstract).
           */
        virtual string Operation() const = 0;
};
/*
   The leaf represents the end objects of a composition.
   A leaf can't have any children.

   Usually, it is the leaf objects that do the actual work, whereas Composite
   objects only delegate to their sub-components.
   */
class Leaf : public Component {
    public:
        string Operation() const override {
            return "Leaf";
        }
};

/*
   The Composite class represents the complex components that may have children
   Usually, the Composite object delegate the actual work to their children and then
   "sum-up" the result.
   */
class Composite : public Component {
    protected:
        list<Component*> children_;

    public:
        /* A composite object can add or remove other components
           (may be simple or complex) to or from its children list
           */
        void Add(Component* component) override {
            this->children_.push_back(component);
            component->SetParent(this);
        }

        /**
         * Have in mind that this method removes the pointer to the list but doesn't
         * frees the memory, you should do it manually or better use smart pointers.
         */
        void Remove(Component* component) override {
            this->children_.remove(component); component->SetParent(nullptr); // component is not freed } bool IsComposite() { return true;
}
/**
 * The Composite executes its primary logic in a particular way. It traverses
 * recursively through all its children, collecting and summing their results.
 * Since the composite's children pass these calls to their children and so
 * forth, the whole object tree is traversed as a result.
 */
string Operation() const override {
    string result;
    for (const Component* c : children_) {
        if (c == children_.back()) {
            result += c->Operation();
        } else {
            result += c->Operation() + "+";
        }
    }
    return "Branch(" + result + ")";
}
};
/*
   the client code works with all the components via the base interface.
   */

void ClientCode(Component* component) {
    cout << "RESULT: " << component->Operation();
}
/**
 * Thanks to the fact that the child-management operations are declared in the
 * base Component class, the client code can work with any component, simple or
 * complex, without depending on their concrete classes.
 */            
void ClientCode2(Component* component1, Component* component2) {
    if (component1->IsComposite()) {
        component1->Add(component2);
    }
    cout << "RESULT: " << component1->Operation();
}


int main() {
    Component* simple = new Leaf;
    cout << "Client: I have gotten a simple component" << endl;
    ClientCode(simple);
    cout << "\n\n";

    /* ...as well as the complex composites.
    */

    Component *tree = new Composite;
    Component *branch1 = new Composite;

    Component *leaf_1 = new Leaf;
    Component *leaf_2 = new Leaf;
    Component *leaf_3 = new Leaf;
    branch1->Add(leaf_1);
    branch1->Add(leaf_2);
    Component *branch2 = new Composite;
    branch2->Add(leaf_3);
    tree->Add(branch1);
    tree->Add(branch2);
    std::cout << "Client: Now I've got a composite tree:\n";
    ClientCode(tree);
    std::cout << "\n\n";

    std::cout << "Client: I don't need to check the components classes even when managing the tree:\n";
    ClientCode2(tree, simple);
    std::cout << "\n";

    delete simple;
    delete tree;
    delete branch1;
    delete branch2;
    delete leaf_1;
    delete leaf_2;
    delete leaf_3;
    return 0;
}
