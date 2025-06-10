#pragma once

#include "..\\Headers\\arrow.hpp"

template <typename T>

class Stack {
    private:
        Arrow<T> tower;
    
    public:
        // Constructor
        Stack() {}

        // Copy Constructor
        Stack(const Stack& original) : tower(original.tower) {}
        // Stack(const Stack& original) {
        //     if (!tower.empty()) {
        //         tower.clea
        //         for (int i = 0; i<tower.size(); i++)
        //             original.tower[i];
        //     }
        // }


        /* Add new element on top of the stack. */
        void push(const T value) {
            tower.append(value);
            std::cout << "Size: " << tower.size() << '\n';
            std::cout << "Cap: " << tower.capacity() << '\n';
        }

        /* Remove the top of the stack. */
        void pop() {
            tower.pop(tower.size() - 1);
        }

        /* Returns the top of the stack. */
        T& peek() const {
            return tower[tower.size() - 1];
        }

        /* Returns the current length of the stack. */
        int length() const {
            return tower.size();
        }

        /* Check if the stack is empty. */
        bool empty() const {
            return tower.empty();
        }

        /* Delete the stack from memory. */
        void clear() {
            tower.clear();
        }

        /* Check if a given target does exist in the stack. DOES NOT RETURN ITS INDEX. */
        bool contains(const T& value) const {
            if (tower.find(value) + 1)
                return true;
            
            return false;
        }

        // Destroyer
        ~Stack() = default;
};