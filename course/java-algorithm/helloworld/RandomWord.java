import edu.princeton.cs.algs4.StdIn;
import edu.princeton.cs.algs4.StdOut;
import edu.princeton.cs.algs4.StdRandom;

public class RandomWord {
    public static void main(String[] args){
        String champion = "";
        String temp;
        int cur = 1;
        while(!StdIn.isEmpty()){
            temp = StdIn.readString(); 
            if (StdRandom.bernoulli(1.0 / cur)) {
                champion = temp;
            } 
            cur++;
        }
        StdOut.println(champion);
    }
}
