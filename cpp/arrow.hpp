#pragma once

#include <iostream>

template <typename T>

class Arrow {
    private:
        int size_;
        int capacity_;
        const double Factor = 1.5;
        T* arr = nullptr;

        void resize() {
            // Increment capacity
            capacity_ *= Factor;

            // Allocate new space corresponding to the new capacity_.
            T* newArr = new T[capacity_]{};

            // Move old data to a new bigger Home.
            std::move(arr, arr + size_, newArr);

            // Delete old data placeholder
            delete[] arr;

            // Returns ownership to arr.
            arr = newArr;
        }

        bool isFull() const { return size_ == capacity_; }       

    public:
        // Constructor
        Arrow(int S = 0) : size_(0) {
            capacity_ = (S <= 0)? 1 : S;
            arr = new T[capacity_]{};
        }

        // Copy Constructor
        Arrow(const Arrow<T>& original) {
            size_ = original.size_;
            capacity_ = original.capacity_;
            for (int i = 0; i<size_; i++)
                arr[i] = original.arr[i];
        }

    // Infos

        /* Returns Number of elements in arrow. */
        int size() const { return size_; }

        /* Returns the maximum possible size of arrow before being resized. */
        int capacity() const { return capacity_; }

        /* Returns index of first occurence of a target. Returns -1 otherwise. */
        int find(const T target) const {
            // Linear search assuming the arrow isn't sorted.
            for (int i = 0; i<size_; i++)
                if (*(arr + i) == target)
                    return i;
            
            return -1;
        }

        /* Returns 'true' if the arrow is currently empty. */
        bool empty() const { return size_ == 0; }

    // Memory management

        /* Delete Allocated memory. By moving elements to a new Fit home.,*/
        void shrink() {
            // Already shrinked.
            if ((capacity_ == size_) || (!size_)) return;

            T* newArr = new T[size_]{};
            std::move(arr, arr+size_, newArr);
            delete[] arr;
            arr = newArr;
            capacity_ = size_;
        }

        /* Pre-allocate a range of memory corresponding to a given amount. */
        void reserve(int amount) {
            if (amount <= 0) return;

            T* newArr = new T[capacity_ + amount];
            std::move(arr, arr+size_, newArr);
            delete[] arr;
            arr = newArr;
            capacity_ += amount;
        }

        /* Empty the arrow. */
        void clear() {
            // Delete the holder
            delete[] arr;

            // Reset to defaul
            arr = new T[1]{};
            size_ = 0;
            capacity_ = 1;
        }

    // Modification

        /* Add new Last element to arrow. */
        void append(const T value) {
            if (this->isFull())
                this->resize();

            arr[size_++] = value;
        }

        /* Insert an element at a given index in range [0, size). NO-OP if index>size or index<0 */
        void insert(const T value, int index) {
            if ((index > size_) || (index < 0))
                throw std::out_of_range("Given Index is Out of range!");

            // Insertion in the end == appending
            if (index == size_) {
                this->append(value);
                return;
            }

            // Declaration and check-out for available space
            capacity_ = (capacity_>size_)? capacity_ : size_ * Factor;
            T* newArr = new T[capacity_]{};
            size_++;

            if (index == 0)
                std::move(arr, arr+size_, newArr+1);

            else {
                std::move(arr, arr+index, newArr);
                std::move(arr+index, arr+size_, newArr+index+1);
            }

            // Deletation and transfer ownership
            delete[] arr;
            arr = newArr;
            
            // Appropriate addition
            if (!index)
                arr[0] = value;
            else
                arr[index] = value;
        }


        void pop(int index = -1) {
            // Empty arr. NO-OP
            if (this->empty())
                throw std::range_error("Empty arrow!");

            // Negative index
            else if (index < 0)
                throw std::invalid_argument("Invalid index has given.");

            // Removing last
            else if (index == size_-1) {
                // No actual removing in this case just considering a new end.
                size_--;
                return;
            }

            // Removing the only element in arrow
            else if (size_ == 1){
                this->clear();
                return;
            }

            index = (index == -1)? size_-1 : index;
            // Acctual removing. (Moving to new holder skipping element at given index.
            T* newArr = new T[size_-1]{};

            if (index == 0) {
                std::move(arr+1, arr+size_, newArr);
                goto del; // Skipping the regular case deletation.
            }

            // Move first half [start, i)
            std::move(arr, arr+index, newArr);
            // Move sec half (i, end]
            std::move(arr+index+1, arr+size_, newArr+index);

            del:
                delete[] arr;
                arr = newArr;
                size_--;
        }

    // Operators
        friend std::ostream& operator<<(std::ostream& os, Arrow<T>& v) {
            // Empty arrow. 
            if (v.empty()) {
                os << "[]\n";
                return os;
            }

            os << '[';
            for (int i = 0; i<v.size_-1; i++)
                os << v.arr[i] << ", ";
            
            os << v.arr[v.size_-1];
            os << "]\n";

            return os;
        }

        T& operator[](int index) const {
            // Support cycling indexing.
            if (index < 0) {
                // Valid negative index.
                if (-1*index <= size_)
                    return *(arr+size_+index);

                // Out of boundaries index.
                else
                    throw std::out_of_range("Invalid given index.");
            }

            // Normale case indexing.
            if (index < size_)
                return *(arr+index);

            // Out of boundaries index.
            else
                throw std::out_of_range("Invalid given index.");
        }

        // Copy assignment operator.
        Arrow& operator=(const Arrow& original) {
            if (this == &original) return *this;

            delete[] arr;
            arr = new T[original.capacity_];
            size_ = original.size_;
            capacity_ = original.capacity_;

            for (int i = 0; i<original.size_; ++i)
                arr[i] = original.arr[i];

            return *this;
        }

    /* Destoryer. */
    ~Arrow() { delete[] arr; }
};