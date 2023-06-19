/*
   Iterator Design Pattern

Intent: let you traverse elements of a collection
without exposing its underlying representation(list, stack, tree, etc)

   */

#include <iostream>
#include <string>
#include <vector>
using namespace std;

/*
   c++ has its own implementation of iterator that works with a different
   generic containers defined by the standard library
   */

template <typename T, typename U>
class Iterator {
    public:
        typedef typename std::vector<T>::iterator iter_type;
        Iterator(U* p_data, bool reverse = false): m_p_data_(p_data) {
            m_it_ = m_p_data_->m_data_.begin();
        }

        void First() {
            m_it_ = m_p_data_->m_data_.begin();
        }

        void Next() {
            ++m_it_;
        }

        bool IsDone() {
            return (m_it_ == m_p_data_->m_data_.end());
        }

        iter_type Current() {
            return m_it_;
        }

    private:
        U* m_p_data_; // a pointer to external vector<T>
        iter_type m_it_;
};

/*
   Generic Collections/Containers provides one or several methods
   for retrieving fresh iterator instance, compatible with the collection class.
   */

template <class T>
class Container {
    friend class Iterator<T, Container>;

    public:
    void Add(T a) {
        m_data_.push_back(a);
    }

    Iterator<T, Container>* CreateIterator() {
        return new Iterator<T, Container>(this);
    }
    private:
    std::vector<T> m_data_;

};

class Data {
    public:
        Data(int a = 0) : m_data_(a) {

        }
        void set_data(int a) {
            m_data_ = a;
        }
        int data() {
            return m_data_;
        }
    private:
        int m_data_;
};

/* 
   The client code may or may not know about the Concrete Iterator
   or Collection classes, for this implementation the container
   is generic so you can use with and int or with a custom class.
   */

void ClientCode() {
    cout << "_____________Iterator with int_______________" << endl;
    Container<int> cont;
    for (int i = 0; i < 10; ++i) {
        cont.Add(i);
    }
    Iterator<int, Container<int>>* it = cont.CreateIterator();
    // it is a pointer :)
    for (it->First(); !it->IsDone(); it->Next()) {
        cout << *it->Current() << endl;
    }

    Container<Data> cont2;
    Data a(100), b(1000), c(10000);
    cont2.Add(a);
    cont2.Add(b);
    cont2.Add(c);
    cout << "_____________Iterator with custom Class_____________" << endl;
    Iterator<Data, Container<Data>>* it2 = cont2.CreateIterator();
    for(it2->First(); !it2->IsDone(); it2->Next()) {
        std::cout << it2->Current()->data() << endl;
    }
    delete it;
    delete it2;
}

int main() {
    ClientCode();
    return 0;
}
