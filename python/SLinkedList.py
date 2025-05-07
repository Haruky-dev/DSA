    # for self.fill()
from random import randint

class Node:
    def __init__(self, data, nxt=None):
        self.data = data
        self.next_node = nxt

class LinkedList:
    ''' Initialize the list. '''
    def __init__(self):
        self.head = None

    ''' Enable a stylish representation using print() '''
    def __repr__(self) -> str:
        holder: list = []
        curr = self.head

        if (not curr):
            return "Empty."
        
        while curr:
            if curr is self.head:
                holder.append("[Head: %s]" % curr.data)
            elif curr.next_node is None:
                holder.append("[Tail: %s]" % curr.data)
            else:
                holder.append("[%s]" % curr.data)
            curr = curr.next_node
        return " > ".join(holder)
    
    ''' Return an integer representing the lenght of List.'''
    def size(self) -> int:
        length = 0
        curr = self.head
        while curr:
            curr = curr.next_node
            length+=1
        
        return length

    ''' Add a new HeadNode element of the list. '''
    def add(self, content) -> None:
        self.head = Node(data=content, nxt=self.head)

    ''' Add a new Node element to the list based o fa given position (1-based index) *NOTE* (if position>len(LinkedList): No Change is made.) '''
    def addAt(self, content, pos: int) -> None:
        if (pos > self.size() + 1): return
        curr = self.head
        if (not curr) or (pos <2):
            self.head = Node(content, self.head)
            return
        
        pos-=2
        while (curr and pos):
            pos-=1
            curr = curr.next_node

        curr.next_node = Node(content, curr.next_node)

    ''' Randomize n(n == amount) element of the LinkedList of element in [startP, endP] Included. '''
    def fill(self, amount: int, startP = -100, endP = 100) -> None:
        if (amount<0): return
        if (endP<=startP): return

        while (amount):
            n = randint(startP, endP)
            self.head = Node(n, self.head)
            amount -= 1

    ''' Reverse the elements order of the LinkedList '''
    def reverse(self) -> None:
        prev = None
        curr = self.head
        nxxt = curr.next_node if (curr) else None

        while (nxxt):
            curr.next_node = prev
            prev = curr
            curr = nxxt
            nxxt = nxxt.next_node

        self.head = curr
        if (curr): curr.next_node = prev

    ''' Return position of the first occurence of a given target, -1 if not found.'''
    def search(self, target) -> int:
        curr = self.head
        i: int = 1
        while curr:
            if curr.data == target: return i

            curr = curr.next_node
            i+=1
        return -1
    
    ''' Delete the first occurence of a Node containing a given content. '''
    def remove(self, content) -> None:
        if (not self.head): return

        value = self.head.data
        if (value == content):
            temp = self.head
            self.head = self.head.next_node
            del temp

            return

        curr = self.head
        while (curr.next_node) and (curr.next_node.data != content):
            curr = curr.next_node

        temp = curr.next_node
        curr.next_node = temp.next_node
        del temp

    ''' Delete a based of a given index. *NOTE* (if index>len(LinkedList): NO Change is made.)'''
    def removeAt(self, index: int) -> None:
        # 1-based index
        if index<=0: return

        if index == 1 and self.head:
            self.remove(self.head.data)

        curr = self.head
        j = 2
        while (curr.next_node) and (j != index):
            j += 1
            curr = curr.next_node

        if (j != index): return

        temp = curr.next_node
        curr.next_node = temp.next_node
        del temp

    ''' Return True if the LinkedList is empty, False otherwise. '''
    def isEmpty(self) -> bool:
        return self.size() == 0
    
    ''' Empty the LinkedList, preserving the head and set it to NULL.'''
    def clean(self) -> None:
        curr = self.head
        temp = None
        
        while (curr):
            temp = curr
            curr = curr.next_node
            del temp

        self.head = None

    ''' Entirely delete the LinkedList, any attemtion of accessing afterwars leads to an AttributeError (No head).'''
    def clear(self) -> None:
        self.clean()
        del self.head