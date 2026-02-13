import edu.princeton.cs.algs4.BinaryStdIn;
import edu.princeton.cs.algs4.BinaryStdOut;

public class BurrowsWheeler {
    // apply Burrows-Wheeler transform,
    // reading from standard input and writing to standard output
    public static void transform() {
        String s = BinaryStdIn.readString();
        String text = s + s;
        CircularSuffixArray CSA = new CircularSuffixArray(s);
        StringBuilder ss = new StringBuilder();
        for (int i = 0; i < s.length(); i++) {
            int index = CSA.index(i);
            if (index == 0) BinaryStdOut.write(i);
            ss.append(text.charAt(index + s.length() - 1));
        }
        for (int i = 0; i < s.length(); i++)
            BinaryStdOut.write(ss.charAt(i));
        BinaryStdOut.close();
    }

    // apply Burrows-Wheeler inverse transform,
    // reading from standard input and writing to standard output
    public static void inverseTransform() {
        int first = BinaryStdIn.readInt();
        String s = BinaryStdIn.readString();

        int N = s.length();
        int R = 256;
        int[] count = new int[R + 1];
        char[] aux = new char[N];
        int[] next = new int[N];
        for (int i = 0; i < N; i++)
            count[s.charAt(i) + 1]++;
        for (int r = 0; r < R; r++)
            count[r + 1] += count[r];
        for (int i = 0; i < N; i++) {
            int tmp = count[s.charAt(i)]++;
            aux[tmp] = s.charAt(i);
            next[tmp] = i;
        }

        for (int i = 0; i < N; i++) {
            BinaryStdOut.write(aux[first]);
            first = next[first];
        }
        BinaryStdOut.close();
    }

    // if args[0] is "-", apply Burrows-Wheeler transform
    // if args[0] is "+", apply Burrows-Wheeler inverse transform
    public static void main(String[] args) {
        String mode = args[0];
        if (mode.equals("-")) transform();
        else if (mode.equals("+")) inverseTransform();
        else throw new IllegalArgumentException("no mode availiable except - and +");
    }
}
