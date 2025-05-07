#pragma once
// #ifndef SLINKEDLIST_HPP
// #define SLINKEDLIST_HPP

struct Node {
    int val;
    Node* next;
    Node(int data, Node* nxt=nullptr);
};
 
class LinkedList {
    protected:
        Node* head;

    public:
        // Constructor/Desctructor
        LinkedList();
        ~LinkedList();

        // Acsess
        Node* getRoot() const;

        // Display & properties
        void show() const;
        int len() const;
        bool isEmpty();

        // Modification
        void add(int data=0);
        void addAt(int data, int pos);
        void fill(int amount, int startP=-100, int endP=100);
        void reverse();
        void remove(int data);
        void removeAt(int index);
        
        // Search
        int find(int target);

        // Memory mangement
        void clean();
        void clear();
};