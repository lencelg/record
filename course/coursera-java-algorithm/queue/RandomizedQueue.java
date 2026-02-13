import edu.princeton.cs.algs4.StdRandom;

import java.util.Iterator;
import java.util.NoSuchElementException;

/* *****************************************************************************
 *  Name: Lencelg
 *  Date:
 *  Description:
 **************************************************************************** */
public class RandomizedQueue<Item> implements Iterable<Item> {
    private static final double FACTOR = 0.25;
    private int size = 0;
    private int capacity = 8;
    private Item[] array;

    // construct an empty randomized queue
    public RandomizedQueue() {
        array = (Item[]) new Object[capacity];
    }

    // is the randomized queue empty?
    public boolean isEmpty() {
        return size == 0;
    }

    // return the number of items on the randomized queue
    public int size() {
        return size;
    }

    private double calration() {
        return size * 1.0 / capacity;
    }

    private void resize(int newcapacity) {
        Item[] newarray = (Item[]) new Object[newcapacity];
        for (int i = 0; i < size; i++)
            newarray[i] = array[i];
        array = newarray;
        capacity = newcapacity;
    }

    // add the item
    public void enqueue(Item item) {
        if (item == null) throw new IllegalArgumentException();
        if (size == capacity) {
            resize(capacity * 2);
        }
        array[size++] = item;
    }

    // remove and return a random item
    public Item dequeue() {
        if (isEmpty()) throw new NoSuchElementException();
        if (calration() <= FACTOR) {
            resize(capacity / 2);
        }
        int number = StdRandom.uniformInt(0, size);
        Item item = array[number];
        array[number] = array[--size];
        array[size] = null;
        return item;
    }

    // return a random item (but do not remove it)
    public Item sample() {
        if (isEmpty()) throw new NoSuchElementException();
        return array[StdRandom.uniformInt(0, size)];
    }

    // return an independent iterator over items in random order
    public Iterator<Item> iterator() {
        return new RQIterator();
    }

    private class RQIterator implements Iterator<Item> {
        private Item[] copyarray;
        private int current;

        public RQIterator() {
            copyarray = (Item[]) new Object[size];
            for (int i = 0; i < size; i++)
                copyarray[i] = array[i];
            StdRandom.shuffle(copyarray);
            current = size;
        }

        @Override
        public boolean hasNext() {
            return current != 0;
        }

        @Override
        public Item next() {
            if (!hasNext()) throw new NoSuchElementException();
            Item item = copyarray[--current];
            copyarray[current] = null;
            return item;
        }

        @Override
        public void remove() {
            throw new UnsupportedOperationException();
        }

    }

    // unit testing (required)
    // again the main method code from FlyingPig ,just for less work in unit test .
    public static void main(String[] args) {
        RandomizedQueue<String> rq = new RandomizedQueue<>();
        for (int i = 0; i < 18; i++) {
            rq.enqueue("A" + i);
        }
        System.out.println("first iterator");
        for (String s : rq) {
            System.out.print(s + " ");
        }
        System.out.println();
        System.out.println("second iterator ");
        for (String s : rq) {
            System.out.print(s + " ");
        }
        System.out.println();
        for (int i = 0; i < 18; i++) {
            System.out.print("deque ");
            System.out.print(rq.dequeue());
            System.out.println(". remain " + rq.size() + " elements. now capacity ");
        }
    }
}