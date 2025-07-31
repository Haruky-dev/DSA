package src;
// import java.util.Iterator;

public class sLinkedList<T> {
    public static class Node<T> {
        T value;
        Node<T> next;

        Node(T value, Node<T> next) {
            this.value = value;
            this.next = next;
        }

        private boolean hasValue() { return (this.value != null)? true : false; }
        private boolean hasNext() { return (this.next != null )? true : false; }
    }

    private Node<T> head;
    private Node<T> tail;
    private int length;
    private final boolean valid( int index ) throws IllegalAccessError, ArrayIndexOutOfBoundsException {
        if (index < 0)
            throw new IllegalArgumentException("Invalid Index! Index MUST BE >= 0");

        else if ( index >= this.length )
            throw new ArrayIndexOutOfBoundsException("Given Index is Out of Bounds.");


        return true;
    }

    public sLinkedList() {
        this.head = this.tail = null;
    }


    public void append (T element) {
        this.head = new Node<>(element, head);
        length++;
    }

    public final int len() { return this.length; }
    public final boolean isEmpty() { return this.length == 0; }

    public final boolean contains ( T element ) {
        Node<T> curr = this.head;

        while ( curr.hasNext() ) {
            if ( curr.value == element ) { return true; }
            curr = curr.next;
        }

        return false;
    }

    public final int indexOf( T element ) {
        int i = 0;

        Node<T> curr = this.head;
        while ( curr.hasNext() ) {
            if ( curr.value == element ) return i;
            curr = curr.next;
            i++;
        }
        return -1;
    }
    
    public T remove ( T element ) {
        Node<T> temp, curr;
        curr = this.head;

        if ( this.head.value == element ) {
            this.head = this.head.next;
            return this.head.value;
        }
        
        while ( curr.hasNext() ) {
            if (curr.next.value == element) break;

            curr = curr.next;
        }

        // Not found
        if (!curr.hasNext()) return null;

        curr.next = temp = ( curr.hasNext() )? curr.next.next : null;
        
        return ( temp.hasValue() )? temp.value : null;
    }

    public final T get ( int index ) {
        if (!valid(index) || (this.isEmpty())) return null;
        
        Node<T> curr = this.head;
        int count = 0;

        while (( count++ != index ) && ( curr.hasNext() ))
            curr = curr.next;

        return (curr.hasValue())? curr.value : null;
    }

    public void set ( int index, T value ) {
        if (!valid(index) || (this.isEmpty())) return;

        Node<T> curr = this.head;
        int count = 0;
        while (curr.hasNext() && (count++ != index))
            curr = curr.next;

        curr.value = value;
    }

    @Override
    public final boolean equals (Object obj) {
        if (this == obj) return true;
        if (!( obj instanceof sLinkedList )) return false;

        sLinkedList<?> that = (sLinkedList<?>) obj;

        Node<?> thisCurr = this.head;
        Node<?> thatCurr = that.head;

        while (thisCurr!=null && thatCurr!=null) {
            if (thisCurr.value != thatCurr.value) return false;

            thisCurr = thisCurr.next;
            thatCurr = thatCurr.next;
        }

        return (thisCurr==null && thatCurr==null);
    }

    @Override
    public final String toString() {
        String holder = "{";

        if (this.head == null) {
            return holder + '}';
        } else if (this.length == 1) {
            return holder + this.head.value.toString() + '}';
        }

        // else
        Node<T> curr = this.head;
        while (curr.next != this.tail) {
            holder += curr.value.toString() + ", ";
            curr = curr.next;
        }

        return holder + curr.value.toString() + '}';
    }

}