class Node:

    def __init__(self, value, prev=None, next=None):

        self.value = value

        self.next = next

        self.prev = prev



class LinkedList:

    '''

        A Python implementation of a doubly linked list.



        Features:

        - O(1) append and removal at both ends.

        - Supports indexing, iteration, and containment.

        - Built-in support for len(), str(), del, +, and more.



        Example:

            ll = LinkedList()

            ll.append(10)

            ll.insert(5, 0)

            print(ll)  # (5) <> (10)

    '''

    def __init__(self) -> None:

        self.__head = None

        self.__tail = None

        self.__size = 0



    # Helper Methods

    def __CheckIndex(self, i: int) -> int:

        if self.empty():

            raise ValueError("Empty List.")

        

        elif i < 0:

            raise ValueError("Inappropriate i Value has Given.")

        

        elif i >= self.__size:

            raise IndexError("Given Index is Out Of Range.")

    def getHead(self):
        return self.__head

    ''' Returns a True if the list Is Empty. '''

    def empty(self) -> bool:

        return not self.__size

    

    ''' Add a new node element to the tail '''

    def append(self, value) -> None:

        if (not self.__head):

            self.__head = Node(value, next=self.__tail, prev=None)

            self.__tail = self.__head

        

        else:

            self.__tail = Node(value, prev=self.__tail, next=None)

            self.__tail.prev.next = self.__tail



        self.__size += 1



    ''' Position a new node element at a given index.'''

    def insert(self, value, index):

        # Invalid Index Values

            # Cannot use __CheckIndex(index) as it does skip the case when inserting at tail

        if (index < 0):

            raise ValueError("Invalid Value Provided.")

        elif index > len(self):

            raise IndexError("Given Index Is Out Of Range.")



        # Valid Index Values

        match index:

            # Adding a new head node

            case index if index == 0:

                if (self.empty()):

                    self.__head = Node(value)

                else:

                    self.__head = Node(value, next=self.__head)

            # Normal scenarios

            case _:

                # Get the right-before node

                curr = self.__head

                index-=1

                while (index and curr):

                    index -= 1

                    curr = curr.next



                # Creating the node

                NewNode = Node(value, curr, curr.next)

                # Case when adding to the tail

                if not curr.next:

                    self.__tail = NewNode

                else:

                    curr.next.prev = NewNode

                



                curr.next = NewNode



        self.__size += 1



    ''' Returns index of the first occurence of a given target, '-1' if not found. '''

    def find(self, target) -> int:

        if (self.empty()): return -1



        left = self.__head

        right = self.__tail

        i, j = (0, self.__size-1)



        # Case of a list with one node element

        if (left is right):

            if left.value == target: return 0

            else: return -1



        while not (left is right):

            if left.value == target:

                return i

            elif right.value == target:

                return j

            else:

                left = left.next

                right = right.prev

                i+=1

                j-=1



        return -1

    

    ''' Remove the first occurence of a Node which contains a given value. '''

    def remove(self, data=None):

        if (self.empty()): raise ValueError("Empty list.")

        

        # Removing head node

        if (self.__head.value == data) or (not data):

            temp = self.__head

            self.__head = self.__head.next

            del temp

        

        # Searching for node containing given value

        else:

            curr = self.__head

            while curr and (curr.value != data):

                curr = curr.next



            # Not Found Value

            if not curr:

                raise ValueError("Given Value Not Found.")

            

            # Deleting

            curr.prev.next = curr.next

            # tail or len(self) == 1 Case Removing

            if not curr.next:

                self.__tail = curr.prev

            else:

                curr.next.prev = curr.prev



            del curr



        # Tracking Size

        self.__size -= 1



    ''' Remove a Node Element Based on a Given Index. '''

    def removeAt(self, index: int):

        # Invalid Cases

        self.__CheckIndex(index)

        

        # Valid Cases

        if not index:

            temp = self.__head

            self.__head = self.__head.next 

            del temp

        else:

            curr = self.__head

            while curr and index:

                index -= 1

                curr = curr.next



            curr.prev.next = curr.next

            if curr.next:

                curr.next.prev = curr.prev

            else:

                self.__tail = curr.prev



            del curr



        self.__size -= 1



    ''' Destructor '''

    def clear(self) -> None:

        curr = self.__head

        while curr:

            temp = curr

            curr = curr.next

            del temp

        

        self.__head = None

        self.__tail = None



    # Operatos

    def __repr__(self) -> str:

        holder: list = []

        curr = self.__head



        if (not curr):

            return "()"

        

        while curr:

            holder.append("(%s)" % curr.value)

            curr = curr.next



        return " <> ".join(holder)

    

    def __len__(self) -> int:

        return self.__size

    

    def __getitem__(self, key: int):

        # Invalid Cases

        self.__CheckIndex(key)

        

        # Valid Cases

        curr = self.__head

        while curr and key:

            key -= 1

            curr = curr.next

        

        return curr.value

    

    def __setitem__(self, key: int, other) -> None:

        # Invaid Cases

        self.__CheckIndex(key)



        # Valid Cases

        curr = self.__head

        while curr and key:

            key -= 1

            curr = curr.next



        curr.value = other



    def __delitem__(self, key: int) -> None:

        # Invalid Cases

        self.__CheckIndex(key)



        # Valid Cases

        self.removeAt(key)



    def __contains__(self, value) -> bool:

        if (self.empty()): return False



        curr = self.__head

        while curr and curr.value != value:

            curr = curr.next



        return curr != None

    

    def __del__(self) -> None:

        self.clear()



    def __iter__(self):

        curr = self.__head

        while curr:

            yield curr.value

            curr = curr.next

    

    def __add__(self, other: 'LinkedList') -> 'LinkedList':

        ResultList = LinkedList()



        # LinkList + {LinkList, list, set, tuple}

        if isinstance(other, (type(self), list, set, tuple, str)):

            for item in self:

                ResultList.append(item)

            for item in other:

                ResultList.append(item)



            return ResultList

        

        else:

            raise ValueError(f"Invalid Value Has Given. Expected an iterable, Got '{type(other).__name__}' ")