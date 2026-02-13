/* *****************************************************************************
 *  Name:
 *  Date:
 *  Description:
 **************************************************************************** */

import edu.princeton.cs.algs4.In;
import edu.princeton.cs.algs4.StdDraw;
import edu.princeton.cs.algs4.StdOut;

import java.util.ArrayList;
import java.util.Arrays;

public class BruteCollinearPoints {

    private ArrayList<LineSegment> segmentArrayList = new ArrayList<>();

    public BruteCollinearPoints(Point[] points) {
        if (points == null) {
            throw new IllegalArgumentException();
        }
        int size = points.length;
        for (int i = 0; i < size; i++) {
            if (points[i] == null)
                throw new IllegalArgumentException();
        }
        for (int i = 0; i < size; i++) {
            for (int j = i + 1; j < size; j++) {
                if (points[i].compareTo(points[j]) == 0) {
                    throw new IllegalArgumentException();
                }
            }
        }
        if (size < 4) return;
        Point[] copy = new Point[size];
        copy = Arrays.copyOf(points, size);
        Arrays.sort(copy);
        for (int i = 0; i < size; i++) {
            for (int j = i + 1; j < size; j++) {
                for (int k = j + 1; k < size; k++) {
                    for (int h = k + 1; h < size; h++) {
                        double s1 = copy[i].slopeTo(copy[j]);
                        double s2 = copy[i].slopeTo(copy[k]);
                        double s3 = copy[i].slopeTo(copy[h]);
                        if (s1 == s2 && s1 == s3) {
                            segmentArrayList.add(new LineSegment(copy[i], copy[h]));
                        }
                    }
                }
            }
        }
    }


    public int numberOfSegments() {
        return segmentArrayList.size();
    }

    public LineSegment[] segments() {
        LineSegment[] res = new LineSegment[numberOfSegments()];
        int i = 0;
        for (LineSegment x : segmentArrayList)
            res[i++] = x;
        return res;
    }

    public static void main(String[] args) {
        // read the n points from a file
        In in = new In(args[0]);
        int n = in.readInt();
        Point[] points = new Point[n];
        for (int i = 0; i < n; i++) {
            int x = in.readInt();
            int y = in.readInt();
            points[i] = new Point(x, y);
        }

        // draw the points
        StdDraw.enableDoubleBuffering();
        StdDraw.setXscale(0, 32768);
        StdDraw.setYscale(0, 32768);
        for (Point p : points) {
            p.draw();
        }
        StdDraw.show();

        // print and draw the line segments
        BruteCollinearPoints collinear = new BruteCollinearPoints(points);
        for (LineSegment segment : collinear.segments()) {
            StdOut.println(segment);
            segment.draw();
        }
        StdDraw.show();
    }
}
