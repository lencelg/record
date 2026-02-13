import java.util.Arrays;

public class CircularSuffixArray {
    private final int length;
    private final int[] res;

    private class CircularSuffix implements Comparable<CircularSuffix> {
        private final int idx;
        private final String text;

        private CircularSuffix(String s, int index) {
            this.idx = index;
            this.text = s;
        }


        private int length() {
            return text.length() / 2;
        }

        private char charat(int i) {
            return text.charAt(i + idx);
        }

        public int compareTo(CircularSuffix that) {
            if (this == that) return 0;
            int n = Math.max(this.length(), that.length());
            for (int i = 0; i < n; i++) {
                if (this.charat(i) < that.charat(i)) return -1;
                if (this.charat(i) > that.charat(i)) return 1;
            }
            return this.length() - that.length();
        }

        public int index() {
            return this.idx;
        }
    }

    // circular suffix array of s
    public CircularSuffixArray(String s) {
        if (s == null) throw new IllegalArgumentException("the string can not be null");
        this.length = s.length();
        String text = s + s;
        CircularSuffix[] cs = new CircularSuffix[length];
        for (int i = 0; i < length; i++)
            cs[i] = new CircularSuffix(text, i);
        Arrays.sort(cs);
        res = new int[length];
        for (int i = 0; i < length; i++) {
            res[i] = cs[i].index();
        }
    }


    // length of s
    public int length() {
        return length;
    }

    // returns index of ith sorted suffix
    public int index(int i) {
        if (i < 0 || i > length - 1)
            throw new IllegalArgumentException("the index is out of bound");
        return res[i];
    }

    // unit testing (required)
    public static void main(String[] args) {
        CircularSuffixArray csa = new CircularSuffixArray("ABRACADABRA!");
        System.out.println("length of s : " + csa.length());
        for (int i = 0; i < csa.length(); i++)
            System.out.println(csa.index(i));
    }
}
