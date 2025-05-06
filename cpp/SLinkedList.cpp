#include <iostream>

struct Node {
    /* Container of given data */
    // Holder of a value of type 'int', you may consider changing the type.
    int val;

    // Pointer to whatever is the next value
    Node* next;

    /* Create a new Container of a given data and a pointer to the next one. The pointer to next if NULL by default. */
    Node(int data = 0, Node* nxt = nullptr) : val(data), next(nxt) {}
};

// Create a Singly-Linked list.
class LinkedList {
    protected:
        // Pointer to the first element in the list
        Node* head;

    public:
        // Initializer of the list.
        LinkedList() : head(nullptr) {}

        /* A geter method to give accsess to 'head' of the list. */
        const Node* getRoot() {
            return head;
        }

        /* Display the list as: { (val) -> (val2) -> void }*/
        void show() {
            Node* curr = head;
            if (!curr) {
                std::cout << "Empty.\n";
                return;
            }

            while (curr) {
                std::cout << '(' << curr->val << ") -> ";
                curr = curr->next;
            }
            std::cout << "void.\n";
        }

        /* Retruns the length of the list (0 if empty). */
        const int len() {
            int len = 0;
            Node* curr = head;
            while (curr && ++len)
                curr = curr->next;

            return len;
        }

        /* Add a new HeadNode element of the list. */
        void add(int data = 0) {
            head = new Node(data, head);
        }

        /* Add a new Node element to the list based of a given position (1 base index). *NOTE* [pos<2: Add new head.]\n[])*/
        void addAt(int data, int pos) {
            Node* curr = head;
            if (!curr || pos <2) {
                head = new Node(data, head);
                return;
            }

            // get the right-before node
            pos-=2;
            while ((curr) && (pos--)) {
                curr = curr->next;
            }

            // create new node at position
            curr->next = new Node(data, curr->next);

        }

        /* Continuously add new Head of List with random integers between [startP, endP] (included). */
        void fill(int amount, int startP = -100, int endP = 100) {
            if (amount<0) return;

            srand(time(NULL));
            while (amount--) {
                head = new Node(rand() % (endP - startP + 1) + startP, head);
            }
        }

        /* Reverse the order of list's elements. */
        void reverse() {
            Node* prev = nullptr;
            Node* curr = head;
            Node* nxxt = (curr)? curr->next : nullptr;

            // if the list is empty, while loop wont execute
            while (nxxt) {
                curr->next = prev;
                prev = curr;
                curr = nxxt;
                nxxt = nxxt->next;
            }

            head = curr;
            if (curr) curr->next = prev;
        }

        /* Remove the first occurence of given data, and update the list accordingly. */
        void remove(int data) {
            if (!head) return;
            int value = head->val;

            // check for first element.
            // it's neccessary since the algorithm used rely on getting the right-before node.
            if (data == value) {
                Node* temp = head;
                head = head->next;
                delete temp;

                return;
            }

            Node* curr = head;
            while ((curr->next) && (curr->next->val != data))
                curr = curr->next;
            
            Node* temp = curr->next;
            curr->next = temp->next;
            delete temp;

        }

        /* Remove a node from list based on its position, 1-based index. */
        void removeAt(int index) {
            if (index < 0) return;
            if ((index == 1) && (head)) {
                this->remove(head->val);
                return;
            }

            Node* curr = head;
            int j = 1;

            while ((curr->next) && (++j != index)) {
                curr = curr->next;
            }

            // Out-of-range index, since we hit the end.
            // Better that use len() since it compromise time complexity.
            if (j != index) return;

            Node* temp = curr->next;
            curr->next = temp->next;
            delete temp;
        }

        /* Return index of first occurence of given target, -1 if not found.*/
        int find(int target) {
            Node* curr = head;
            int i = 1;
            while (curr) {
                if (curr->val == target) return i;
                i++;
                curr = curr->next;
            }
            return -1;
        }

        /* Check for empty list, returns a Boolean*/
        int isEmpty() {
            return this->len() == 0;
        }

        /* pseudo-destructor, preserving the head.*/
        void clean() {
            Node* curr = head;
            Node* temp = nullptr;

            while (curr) {
                temp = curr;
                curr = curr->next;
                delete temp;
            }
            head = nullptr;
        }

        /* A destructor, in a more elegant way. */
        void clear() {
            this->~LinkedList();
        }

        // Destructor
        ~LinkedList () {
            Node* curr = head;
            while (curr) {
                Node* temp = curr;
                curr = curr->next;
                delete temp;
            }
        }
};
