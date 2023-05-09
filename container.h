#pragma once
#include <iostream>


template <typename T>
class Container {
private:
    template <typename T>
    struct Node {
    private:
        Node<T>* next;
        Node<T>* prev;
        T data;

    public:
        Node(Node<T>* n = nullptr, Node<T>* p = nullptr) : next(n), prev(p) {}

        Node(T &d, Node<T>* n = nullptr, Node<T>* p = nullptr) : Node(n, p) {
            data = d;
        }

        T get() {
            return data;
        }

        Node<T>* get_next() {
            return next;
        }

        Node<T>* get_prev() {
            return prev;
        }

        void set(T &new_data) {
            data = new_data;
        }

        void set_next(Node<T>* new_next) {
            next = new_next;
        }

        void set_prev(Node<T>* new_prev) {
            prev = new_prev;
        }
    };

    class Iterator {
    private:
        Node<T>* current;

    public:
        Iterator(Node<T>* _current) : current(_current) {}

        bool operator!=(Iterator other) {
            return current != other.current;
        }

        Iterator operator++() {
            current = current->get_next();
            return *this;
        }

        Iterator operator--() {
            current = current->get_prev();
            return *this;
        }

        T value() {
            return current->get();
        }
    };

    Node<T>* tech;
    int len;

public:
    Container() : len(0), tech(new Node<T>()) {
        tech->set_next(tech);
        tech->set_prev(tech);
    }

    int size() {
        return len;
    }

    bool is_empty() {
        return len == 0;
    }

    void push(T data) {
        Node<T>* tmp = new Node<T>(data, tech->get_next(), tech);
        tech->get_next()->set_prev(tmp);
        tech->set_next(tmp);
        len++;
    }

    void push_back(T data) {
        Node<T>* tmp = new Node<T>(data, tech, tech->get_prev());
        tech->get_prev()->set_next(tmp);
        tech->set_prev(tmp);
        len++;
    }

    T pop() {
        if (!is_empty()) {
            T data = tech->get_next()->get();
            Node<T>* tmp = tech->get_next()->get_next();
            delete tech->get_next();
            tech->set_next(tmp);
            tmp->set_prev(tech);
            len--;
            return data;
        }
        return tech->get();
    }

    T pop_back() {
        if (!is_empty()) {
            T data = tech->get_prev()->get();
            Node<T>* tmp = tech->get_prev()->get_prev();
            delete tech->get_prev();
            tech->set_prev(tmp);
            tmp->set_next(tech);
            len--;
            return data;
        }
        return tech->get();
    }

    void clear() {
        while (len > 0) {
            pop();
        }
    }

    void swap_containers(Container<T> &first, Container<T> &second) {
        std::swap(first->tech, second->tech);
        std::swap(first->len, second->len);
    }

    Iterator begin() {
        return Iterator(tech->get_next());
    }

    Iterator end() {

        return tech;
    }

    void reverse() {
        Node<T>* i = tech->get_next();
        Node<T>* j = tech->get_prev();
        T tmp;
        while (i != j && i != j->get_prev()) {
            tmp = i->get();
            i->set(j->get());
            j->set(tmp);
            i = i->get_next();
            j = j->get_prev();
        }
    }

    ~Container() {
        clear();
    }
};
