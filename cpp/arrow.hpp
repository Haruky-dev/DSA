#pragma once

#include <iostream>
#include <memory>
#include <algorithm>
#include <initializer_list>

using std::unique_ptr, std::make_unique, std::copy, std::move;

template <typename T>

class Arrow {
    private:
        size_t size_;
        size_t capacity_;
        const double FACTOR = 1.5;
        unique_ptr<T[]> arr;

        void resize() {
            // Increment capacity
            capacity_ = (!capacity_)? 1 : capacity_*FACTOR + 1;

            // Allocate new space corresponding to the new capacity_.
            unique_ptr<T[]> newArr = make_unique<T[]>(capacity_);

            // Move old data to a new bigger Home.
            if (arr)
                copy(arr.get(), arr.get()+size_, newArr.get());

            // Returns ownership to arr.
            arr = move(newArr);
        }

        bool isFull() const { return size_ == capacity_; }       

    public:
        // Constructor
        Arrow() : size_(0), capacity_(0), arr(nullptr) {}

        // Copy Constructor
        Arrow(const Arrow<T>& original) {
            arr = make_unique<T[]>(original.capacity_);
            copy(original.arr.get(), original.arr.get()+original.size(), arr.get());
            size_ = original.size_;
            capacity_ = original.capacity_;
        }

        // Initialization Cosntructor
        Arrow(std::initializer_list<T> init) : arr(make_unique<T[]>(init.size())), size_(init.size()), capacity_(init.size()) {
            copy(init.begin(), init.end(), arr.get());
        }

        /* Destructor. */
        ~Arrow() = default;

    // Iterating

        T* begin() { return arr.get(); }
        T* end() { return arr.get()+size_; }

        const T* begin() const { return arr.get(); }
        const T* end() const { return arr.get()+size_; }

    // Infos

        /* Returns Number of elements in arrow. */
        size_t size() const { return size_; }

        /* Returns the maximum possible size of arrow before being resized. */
        size_t capacity() const { return capacity_; }

        /* Returns index of first occurence of a target. Returns -1 otherwise. */
        int find(const T target, const bool& sorted = 0) const {
            // Linear search assuming the arrow isn't sorted.
            for (int i = 0; i<size_; i++)
                if (arr[i] == target)
                    return i;
            
            return -1;
        }

        /* Returns 'true' if the arrow is currently empty. */
        bool empty() const { return this->size_ == 0; }

        /* Returns 'true' if the arrow does contains a given T value. */
        bool contains( const T& element, const bool& sorted = 0) const {
            return this->find(element, sorted) != -1;
        }

    // Memory management

        /* Delete Allocated memory. By moving elements to a new Fit home.,*/
        void shrink() {
            // Already shrinked.
            if (!size_) {
                arr.reset();
                capacity_ = 0;
            } else if (capacity_ > size_) {
                unique_ptr<T[]> newArr = make_unique<T[]>(size_);
                copy(arr.get(), arr.get()+size_, newArr.get());
                arr = move(newArr);
                capacity_ = size_;
            }
        }

        /* Pre-allocate a range of memory corresponding to a given amount. */
        void reserve(const size_t& amount) {
            // Already have enough space
            if (amount <= capacity_ - size_) return;

            // reserve the given amount of space
            capacity_ = size_+amount;
            
            unique_ptr<T[]> newArr = make_unique<T[]>(capacity_);
            copy(arr.get(), arr.get()+size_, newArr.get());
            arr = move(newArr);
        }

        /* Empty the arrow. */
        void clear() {
            // Reset to defaul
            arr.reset();
            size_ = 0;
            capacity_ = 0;
        }

    // Modification

        /* Add new Last element to arrow. */
        void append(const T& value, bool log = 0) {
            if (size_ >= capacity_) this->resize();

            arr[size_++] = value;
        }

        /* Insert an element at a given index in range [0, size). NO-OP if index>size or index<0 */
        void insert(const T& value, int index) {
            if ((index > size_) || (index < 0))
                throw std::out_of_range("Given Index is Out of range!");

            // Insertion in the end == appending
            if (index == size_) {
                this->append(value);
                return;
            }

            // Declaration and check-out for available space
            if (size_ >= capacity_) this->resize();

            // Right shift element from index
            for (int i = size_; i>index; i--)
                arr[i] = move(arr[i-1]);

            arr[index] = value;
            size_++;
        }

        /* Remove element at given index. Default = Remvove Last. */
        void pop(int index = -1) {  
            // Empty arr. NO-OP
            if (this->empty()) throw std::range_error("Empty arrow!");
            
            // Relying on a default value -> pop last element
                // or size
            if (index == -1) { index = size_-1; }

            // Negative index
            if (index < 0)
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

            // left-shift elements, overrite the value to pop.
            for (int i = index; i<size_-1; i++)
                arr[i] = move(arr[i+1]);

            size_--;
        }

    // Operators
        friend std::ostream& operator<<(std::ostream& os, const Arrow<T>& v) {
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

        /* Return READ-ONLY value stored at given index. Also suports in-range negative index, -1 starting from last to first */
        const T& operator[](const int& index) const {
            // Support cycle indexing.
            if (index < 0) {
                // Valid negative index.
                if (-1*index <= size_)
                    return arr[size_+index];

                // Out of boundaries index.
                else
                    throw std::out_of_range("Invalid given index.");
            }

            // Normale case indexing.
            if (index < size_)
                return arr[index];
                // return *(arr+index);

            // Out of boundaries index.
            else
                throw std::out_of_range("Invalid given index.");
        }

        /* Return MODIFIABLE value stored at given index. Also supports in-range negative index, -1 starting from last to first */
        T& operator[](const int& index) {
            // Repeating same logic

            // Support cycle indexing.
            if (index < 0) {
                // Valid negative index.
                if (-1*index <= size_)
                    return arr[size_+index];

                // Out of boundaries index.
                else
                    throw std::out_of_range("Invalid given index.");
            }

            // Normale case indexing.
            if (index < size_)
                return arr[index];
                // return *(arr+index);

            // Out of boundaries index.
            else
                throw std::out_of_range("Invalid given index.");
        }

        // Copy assignment operator.
        Arrow& operator=(const Arrow& original) {
            if (this != &original) {
                arr = make_unique<T[]>(original.capacity_);
                copy(original.arr.get(), original.arr.get() + original.size_, arr.get());
                size_ = original.size_;
                capacity_ = original.capacity_;
            }

            return *this;
        }
};
