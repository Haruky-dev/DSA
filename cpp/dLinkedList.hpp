#pragma once
#include <stdexcept>
#include <iostream>

// Doubly Linked List
// --------------------
// A generic doubly linked list implementation in C++.
// Features:
// - Supports all Primitive data Types.
// - Supports bidirectional traversal via custom iterator.
// - Range-based for loop compatible using begin()/end() and rbegin()/rend().
// - Core list operations: append, insert, remove, removeAt, find, clear, length, etc.
// - Manual memory management (no smart pointers used).
// - Iterator design allows modification and read-access of node values directly.
// Features:
// - Indexing Op [] (*0-Based Index*).
// - Stream Extraction Op << (For Console Printing).
// - Copy Assignment Op = .


template <typename T>

class dLinkedList {
    protected:
        Node<T>* head;
        Node<T>* tail;
        int len;

    private:
        struct Node {
            T value;
            Node<T>* next;
            Node<T>* prev;
            Node(T value, Node<T>* prev=nullptr, Node<T>* next=nullptr) : value(value), prev(prev), next(next) {}
        };

        class Iterator {
            Node<T>* curr;
            public:
                // Constructor
                Iterator(Node<T>* node) : curr(node) {}

                /* Ops */
                // Derefrencing
                T& operator* () const { return curr->value; }
                // Comparison
                bool operator== (const Iterator& other) const { return this->curr == other.curr; }
                bool operator!= (const Iterator& other) const { return !(*this == other); }

                // Increment
                Iterator operator++ () {
                    this->curr = curr->next;
                    return *this;
                }
                Iterator operator++ (int) {
                    Iterator temp = *this;
                    // ++(*this);
                    this->curr = curr->next;
                    return temp;
                }
                // Decrement
                Iterator operator-- () {
                    curr = curr->prev;
                    return *this;
                }
                Iterator operator-- (int) {
                    Iterator temp = *this;
                    // --(*this);
                    this->curr = curr->next;
                    return temp;
                }
        };


    public:
        // Constructor
        dLinkedList() : head(nullptr), tail(nullptr), len(0) {}

        // Copy Constructor
        dLinkedList(const dLinkedList<T>& original) {
            if (original.empty())
                this->head = nullptr;

            else {
                // Keeping track of each node in original and create it into the new list
                Node<T>* OrgCurr = original.getHead();
                this->head = new Node<T>(OrgCurr->value);
                Node<T>* CpyCurr = this->head;

                OrgCurr = OrgCurr->next;
                while (OrgCurr) {
                    CpyCurr->next = new Node<T>(OrgCurr->value, CpyCurr);
                    CpyCurr = CpyCurr->next;
                    OrgCurr = OrgCurr->next;
                }
                this->tail = CpyCurr;
            }   
        }

        // Destructor
        ~dLinkedList() {
            this->clean();
            delete this->tail;
        }

        Node<T>* getHead() const { return this->head; }
        Node<T>* getTail() const { return this->tail; }

        // Helper method for cheking valid indecies
        void CheckKey(int key) const {
            if (this->empty())
                throw std::out_of_range("Empty List.");

            if (key < 0)
                throw std::invalid_argument("Negative Indecies ARE NOT supported.");

            if (key >= len)
                throw std::out_of_range("Out of Boundaries Key Given.");
        }

        /* Returns 'true' if the list Is Empty. */
        bool empty() const { return !len; }

        /* append given value to list, (append to the end, new tail) */
        void append(const T& value) {
            // Empty List => new head
            if (this->empty()) {
                // this->head = new Node(value, nullptr, this->tail);
                // this->tail = this->head;
                this->tail = new Node(value);
                this->head = this->tail;
            }

            else {
                this->tail = new Node<T>(value, this->tail);
                this->tail->prev->next = this->tail;
            }

            len++;
        }

        /* Insert a given value at a given index. */
        void insert(int index, const T& value) {
            if (index < 0)
                throw std::invalid_argument("Negative Indecies ARE NOT supported.");

            if (index < len)
                throw std::out_of_range("Out of Boundaries Key Given.");


            if (!index) {
                this->head = new Node<T>(value, nullptr, this->head);

                if (this->head->next)
                this->head->next->prev = this->head;
            }

            else if (index == len) {
                this->append(value);
            }

            else {
                Node<T>* curr = this->getHead();

                while ((curr) && (--index)) { curr = curr->next; }

                Node<T>* newNode = new Node<T>(value, curr, curr->next);
                curr->next->prev = newNode;
                curr->next = newNode;
            }
        }

        /* Returns Index of first occurence of a given value, -1 otherwise. */
        int find(const T& target) const {
            if (this->empty()) return -1;

            Node<T>* leftN = this->getHead();
            Node<T>* rigthN = this->getTail();

            int i, j;
            i = 0, j = this->len-1;

            if (leftN == rigthN)
                if (leftN->value == target) return 0;
                else return -1;

            while (i <= j) {
                if (leftN->value == target) return i;
                else if (rigthN->value == target) return j;

                leftN = leftN->next; i++;
                rigthN = rigthN->prev; j--;
            }

            return -1;
        }

        /* Delete first node containing a given value, raise OutOfRange error if not found */
        void remove(T target) {
            if (this->empty())
                throw std::logic_error("Empty List.");

            // Getting the node to delete
            Node<T>* curr = this->getHead();
            while ((curr->next) && (curr->value != target)) { curr = curr->next; }

            // In the middle
            if (curr->next)
                curr->next->prev = curr->prev;
            // In tail
            else {
                // Not found
                if (curr->value != target)
                    throw std::out_of_range("Given value was NOT FOUND.");
                // Removing tail
                this->tail = curr->prev;
            }

            // In the middle
            if (curr->prev)
                curr->prev->next = curr->next;
            // In head
            else
                this->head = curr->next;

            delete curr;
        }

        /* Remove a node placed at a given index. 0-based index. */
        void removeAt(int& index) {
            this->CheckKey(index);

            // Check removing head/tail
            if (not index) {
                this->remove(this->head->value);
                return;
            }

            if (index == this->len-1) {
                Node<T>* temp = this->tail;
                this->tail = this->tail->prev;
                this->tail->next = nullptr; 
                delete temp;
                return;
            }

            Node<T>* curr = this->getHead();
            while ((curr) && (index--)) curr = curr->next;

            // In the middle
            if (curr->next)
                curr->next->prev = curr->prev;
            // In tail
            else {
                // Removing tail
                this->tail = curr->prev;
            }

            // In the middle
            if (curr->prev)
                curr->prev->next = curr->next;
            // In head
            else
                this->head = curr->next;

            delete curr;
        }

        /* Erase all nodes in the list, making it empty. */
        void clean() {
            Node<T>* curr = this->getHead();
            Node<T>* temp = nullptr;

            while (curr) {
                temp = curr;
                delete temp;
                curr = curr->next;
            }
            this->head = this->tail = nullptr;
        }

        /* Destruct the list. */
        void clear() {
            this->clean();

            delete head;
            delete tail;
        }

        // Copy assignment operators
        dLinkedList& operator= (const dLinkedList& original) {
            if (this == &original) return *this;

            Node<T>* OrgCurr = original.getHead();
            this->clear();

            while (OrgCurr) {
                this->append(OrgCurr->value);
                OrgCurr = OrgCurr->next;
            }

            return *this;
        }

        // Printing to console for debugging purposses
        friend std::ostream& operator<< (std::ostream& os, dLinkedList<T>& self) {
            Node<T>* curr = self.getHead();

            // Empty
            if (!curr)
                os << "[]\n";

            // 1 node
            else if (!curr->next)
                os << '[' << curr->value << "]\n";

            else {
                os << '[';

                while (curr->next) {
                    os << curr->value << ", ";
                    curr = curr->next;
                }

                os << curr->value << "]\n";
            }

            return os;
        }

        T& operator[] (int key) const {

            this->CheckKey(key);

            Node<T>* curr = this->getHead();

            while ((curr) && (key--)) { curr = curr->next; }

            return curr->value;
        }


        // Iteration
        Iterator begin() { return Iterator(this->head); }
        Iterator end() { return Iterator(nullptr); }
        Iterator rbegin() { return Iterator(this->tail); }
        Iterator rend() { return Iterator(nullptr) ;}
};