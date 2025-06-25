# Import dLinkedList from Haruky-dev GitHub Repository
# -----------------------------------------------------------------
import requests # for downlaoding stuff
import os # to manipulate paths
import sys # to adjust look-up directories

AbsolutePath = os.path.abspath(__file__) # Get path to file from root
BASE_DIR = os.path.dirname(AbsolutePath) # Extract the Directory

FNAME = os.path.join(BASE_DIR, "dLinkedList.py") # Construct path to the new file
URL = "https://raw.githubusercontent.com/Haruky-dev/DSA/main/python/dLinkedList.py"


if not os.path.exists(FNAME): # Check if path already exists in it's proper place
    response = requests.get(URL) # Download the file (dLinkedList.py)
    if response.status_code == 200: # Succesfull process
        with open(FNAME, 'w', encoding='utf-8') as f: # Open dLinkedList.py
            f.write(response.text) # write it to the local file

    else:
        raise Exception("Error while trying to fetch important files.")

sys.path.insert(0, BASE_DIR) # Add file to look-up list for modules
import dLinkedList # Import it
# -----------------------------------------------------------------

# Actual Implementation after getting 'dLinkedList' helper Module
class Queue:
    '''
        Relies on dLinkedList.py , which defines the LinkedList class.
        Automatically downloads 'dLinkedList.py' from GitHub if not found in the
            working directory.

    '''
    def __init__(self) -> None:
       # Private member used of type LinkedList used to store queue elements 
        self.__holder = dLinkedList.LinkedList()


    ''' Adds a new element to the back (tail) of the queue. O(1) '''
    def enqueue(self, value) -> None:
        self.__holder.append(value)

    ''' Removes and returns the element at the front (head) of the queue. O(1) '''
    def dequeue(self) -> None:
        if (self.__holder.empty()):
            raise IndexError("Empty Queue!")
        
        temp = self.__holder[0]
        self.__holder.remove()
        return temp

    ''' Returns the value at the front of the queue without removing it. O(1) '''
    def peek(self):
        return self.__holder[0] if not self.empty() else None
    
    ''' Checks whether the queue is empty. (True if empty) O(1) '''
    def empty(self) -> bool:
        return self.__holder.empty()
    
    # Ops
    ''' Returns a string representation of the queue for printing and debugging.
        Queue([ value1 < value2 < ... < valueN ]) '''
    def __repr__(self) -> str:
        return f"Queue([ {' < '.join(repr(i) for i in self.__holder)} ])"
    
    ''' Returns the number of elements in the queue. (len(self)) O(1) '''
    def __len__(self) -> int:
        return len(self.__holder)
    
    ''' Deletes an element at a specific index in the queue. '''
    def __delitem__(self, key: int) -> None:
        del self.__holder[key]

    ''' Checks if a value exists in the queue. (value in self) '''
    def __contains__(self, value) -> bool:
        return value in self.__holder

    def __del__(self) -> None:
        del self.__holder

    ''' Enable iterating through self. '''
    def __iter__(self):
        curr = self.__holder.getHead()

        while curr:
            yield curr.value
            curr = curr.next

    ''' Supports Equality check for '==' Operator. '''
    def __eq__(self, other) -> bool:
        if not isinstance(other, type(self)):
            raise ValueError("Invalid Operation.")
            
        elif len(self) != len(other):
            return False
        
        for i, j in zip(self, other):
            print(i, j)
            if i != j: return False

        return True