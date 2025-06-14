#pragma once
#include <iostream>

template <typename T>

// The base unit of a Linked list [value, next]
struct Node {
    // data to hold on each node
    T value;
    // Pointer to next Node
    Node<T>* next;
    // Constructor
    Node(T value, Node<T>* next=nullptr) : value(value), next(next) {}
};


template <typename T>

class LinkedList {
    protected:
        // Head of the list
        Node<T>* head;
    
    public:
        // Constructor
        LinkedList() : head(nullptr) {}

        // Copy Constructor
        LinkedList(const LinkedList<T>& original) {
            if (original.empty()) {
                head = nullptr;
                return;
            }
            
            // Tracker for Original
            Node<T>* OrgCurr = original.head;

            // head of the new list
            head = new Node(OrgCurr->value);

            // Trakcer for the new list
            Node<T>* CpyCurr = head;
            
            OrgCurr = OrgCurr->next;
            while (OrgCurr) {
                CpyCurr->next = new Node(OrgCurr->value);
                CpyCurr = CpyCurr->next;
                OrgCurr = OrgCurr->next;
            }
        }

    // Accessing
        /* A geter method to give accsess to 'head' of the list. */
        Node<T>* getRoot() const {
            return this->head;
        }

        /* Retruns the length of the list (0 if empty). */
        int length() const {
            int len=0;
            Node<T>* curr = head;

            while (curr) { curr = curr->next; len++; };

            return len;
        }

        /* Add a new HeadNode element of the list. */
        void append(T data) {
            head = new Node(data, head);
        }

        /* Add a new Node element to the list based of a given position (0-base index).*/
        void insert(T data, int pos) {
            Node<T>* curr = head;

            // Negative Index => error
            if (pos < 0) throw std::range_error("Invalid index has given.");

            // Empty list OR index == 0 => Create new head
            if (this->empty() || !pos) { head = new Node(data, head); return; }

            // Index > length() => error
            if (pos > this->length()) throw std::out_of_range("Given index is Beyond the List size.");

            // Get the right-before node
            pos-=1;
            while ((curr) && (pos)) { curr = curr->next; pos--; }

            // Create new node at position
            curr->next = new Node(data, curr->next);
        }

        /* Reverse the order of list's elements. */
        void reverse() {
            Node<T>* prev = nullptr;
            Node<T>* curr = head;
            Node<T>* next = (curr)? curr->next : nullptr;

            // If the list is empty, while lopo will not execute
            while (next) {
                curr->next = prev;
                prev = curr;
                curr = next;
                next = next->next;
            }

            head = curr;
            if (curr) curr->next = prev;
        }


        /* Remove the first occurence of given data, and update the list accordingly. NOOP if Not Found. */
        void remove(T target) {
            if (this->empty()) throw std::range_error("Empty List!");

            // check for first element.
            // it's neccessary since the algorithm used rely on getting the right-before node.
            if (target == this->head->value) {
                Node<T>* temp = head;
                head = head->next;
                delete temp;

                return;
            }

            // Get curr to point to the node before the node containing the target.
            Node<T>* curr = head;
            while ((curr->next) && (curr->next->value != target))
                curr = curr->next;

            Node<T>* temp = curr->next;
            curr->next = temp->next;
            delete temp;
        }

        /* Remove a node from list based on its position, 1-based index. */
        void removeAt(int index) {
            if (index < 0) return;
            if ((index == 1) && (head)) {
                this->remove(head->value);
                return;
            }

            Node<T>* curr = head;
            int j = 1;

            while ((curr->next) && (++j != index)) {
                curr = curr->next;
            }

            // Out-of-range index, since we hit the end.
            // Better that use len() since it compromise time complexity.
            if (j != index) return;

            Node<T>* temp = curr->next;
            curr->next = temp->next;
            delete temp;
        }

        /* Return index of first occurence of given target, -1 if not found. *NOTE: 0-based index* */
        int find(T target) const {
            Node<T>* curr = head;
            int i = 0;
            while (curr) {
                if (curr->value == target) return i;

                i++;
                curr = curr->next;
            }
            return -1;
        }

        /* Check for empty list, returns a Boolean*/
        bool empty() const {
            return !(getRoot());
        }

        /* pseudo-destructor, preserving the head.*/
        void clean() {
            Node<T>* curr = head;
            Node<T>* temp = nullptr;

            while (curr) {
                temp = curr->next;
                delete curr;
                curr = temp;
            }
            head = nullptr;
        }

    // Operatros Overloading
        // For Outputing
    friend std::ostream& operator<<(std::ostream& os, LinkedList<T>& v) {
        if (v.empty()) {
            os << "()\n";
            return os;
        }

        Node<T>* curr = v.getRoot();
        while (curr) {
            os << '(' << curr->value << ')';
            os << " -> ";
            curr = curr->next;
        }

        os << "NULL\n";
        return os;
    }

        // Indexing
    T& operator[](int index) const {
        // Negative index
        if (index < 0) throw std::range_error("Invalid Index Has Given.");
        
        Node<T>* curr = head;
        while ((index--) && (curr))
            curr = curr->next;

        // Not hitting the end of the list.
        if (curr) return curr->value;

        // Index > this->length() => Out of boundaries Index
        throw std::out_of_range("Invalid Index Has Given.");
    }

        // Copy Assgnment Operator
    LinkedList& operator=(const LinkedList& original) {
        if (this == &original) return *this;

        Node<T>* OrgCurr = original.head;
        head = new Node(OrgCurr->value);
        Node<T>* CpyCurr = head;

        OrgCurr = OrgCurr->next;
        while (OrgCurr) {
            CpyCurr->next = new Node(OrgCurr->value);
            CpyCurr = CpyCurr->next;
            OrgCurr = OrgCurr->next;
        }

        return *this;
    }

    // Destructor
    ~LinkedList() {
        this->clean();
        delete this->head;
    }
};