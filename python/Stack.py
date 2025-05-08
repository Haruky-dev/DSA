class stack:
    def __init__(self):
        self.stack = []

    ''' Return Top element on the Stack. '''
    def peek(self) -> int:
        try:
            return self.stack[-1]
        
        except IndexError:
            print("Empty Stack.")
 
    ''' Add element on the Stack. '''
    def push(self, value: int):
        self.stack.append(value)

    ''' Delete the top element on the Stack. '''
    def pop(self):
        try:
            ret = self.stack[-1]

        except IndexError:
            print("Empty Stack.")
        
        else:
            del self.stack[-1]
            return ret
        
    ''' Return the Length of the Stack. '''
    def size(self):
        return len(self.stack)

    ''' Return True if the Stack is Empty, False otherwise. '''
    def isEmpty(self):
        return (not self.size())


if __name__ == "__main__":
    # Testings
    v = stack()
    v.push(3)
    v.push(2)
    print(v.peek())
    v.push(1)
    print(v.peek())
    x = v.pop()
    v.pop()
    print(v.isEmpty())