import edu.princeton.cs.algs4.StdRandom;
import edu.princeton.cs.algs4.StdStats;

public class PercolationStats {
    private static final double CONFIDENCE_95 = 1.96;
    private double[] threshold;
    private int size;
    private int time;
    private double mean;
    private double dev;
    public PercolationStats(int n, int trials) {
        if (n <= 0 || trials <= 0) {
            throw new IllegalArgumentException();
        }
        threshold = new double[trials];
        time = trials;
        size = n;
        for (int i = 0; i < trials; i++) {
            Percolation p = new Percolation(n);
            while (!p.percolates()) {
                // random open site
                randomopensite(p);
            }
            threshold[i] = p.numberOfOpenSites() * 1.0 / (n * n);
        }
        mean = StdStats.mean(threshold);
        if (trials == 1) {
            dev = Double.NaN; 
        } else {
            dev = StdStats.stddev(threshold);
        }
    }
    private void randomopensite(Percolation p) {
        int row = StdRandom.uniformInt(1, size + 1);
        int col = StdRandom.uniformInt(1, size + 1);
        while (p.isOpen(row, col)) {
           row = StdRandom.uniformInt(1, size + 1);
           col = StdRandom.uniformInt(1, size + 1);
        }
        p.open(row, col);
    }
    public double mean() {
        return mean;
    }
    public double stddev() {
        return dev;
    }
    public double confidenceLo() {
        return mean - CONFIDENCE_95 * dev / Math.sqrt((double) time);
    }
    public double confidenceHi() {
        return mean + CONFIDENCE_95 * dev / Math.sqrt((double) time);
    }
    public static void main(String[] args) {
        PercolationStats ps = new PercolationStats(Integer.parseInt(args[0]), Integer.parseInt(args[1]));
        double m = ps.mean();
        double s = ps.stddev();
        double lowerbound = ps.confidenceLo();
        double upperbound = ps.confidenceLo();
        System.out.println("mean                     = " + m);
        System.out.println("stddev                   = " + s);
        System.out.println("95% confidence interval = " + "[" + lowerbound + ", " + upperbound + "]");

    }
}
