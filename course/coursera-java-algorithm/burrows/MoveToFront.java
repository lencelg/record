import edu.princeton.cs.algs4.BinaryStdIn;
import edu.princeton.cs.algs4.BinaryStdOut;

import java.util.LinkedList;

public class MoveToFront {
    private static final int R = 256;
    private static LinkedList<Character> cc;

    private static void init() {
        cc = new LinkedList<>();
        for (char i = 0; i < R; i++)
            cc.add(i);
    }

    // apply move-to-front encoding, reading from standard input and writing to standard output
    public static void encode() {
        init();
        while (!BinaryStdIn.isEmpty()) {
            char c = BinaryStdIn.readChar();
            int index = cc.indexOf(c);
            BinaryStdOut.write(index, 8);
            char t = cc.remove(index);
            cc.add(0, t);
        }
        BinaryStdOut.close();
    }

    // apply move-to-front decoding, reading from standard input and writing to standard output
    public static void decode() {
        init();
        while (!BinaryStdIn.isEmpty()) {
            int p = BinaryStdIn.readChar();
            char t = cc.remove(p);
            BinaryStdOut.write(t);
            cc.add(0, t);
        }
        BinaryStdOut.close();
    }

    // if args[0] is "-", apply move-to-front encoding
    // if args[0] is "+", apply move-to-front decoding
    public static void main(String[] args) {
        String mode = args[0];
        if (mode.equals("-"))
            encode();
        else if (mode.equals("+"))
            decode();
        else
            throw new IllegalArgumentException("no mode except for - and +");
    }
}
