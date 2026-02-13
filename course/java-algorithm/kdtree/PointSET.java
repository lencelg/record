import edu.princeton.cs.algs4.Point2D;
import edu.princeton.cs.algs4.RectHV;
import edu.princeton.cs.algs4.SET;

import java.util.ArrayList;

public class PointSET {
    private SET<Point2D> pointset;

    public PointSET() {
        pointset = new SET<>();
    }

    public boolean isEmpty() {
        return pointset.isEmpty();
    }

    public int size() {
        return pointset.size();
    }

    // add the point to the set (if it is not already in the set)
    public void insert(Point2D p) {
        if (p == null) throw new IllegalArgumentException("the point to insert should not be null");
        if (!pointset.contains(p)) pointset.add(p);

    }

    public boolean contains(Point2D p) {
        if (p == null)
            throw new IllegalArgumentException("the point to look for should not be null");
        return pointset.contains(p);
    }

    // draw all points to standard draw
    public void draw() {
        for (Point2D temp : pointset)
            temp.draw();
    }

    // all points that are inside the rectangle (or on the boundary)
    public Iterable<Point2D> range(RectHV rect) {
        if (rect == null) throw new IllegalArgumentException("the rect should not be null");
        ArrayList<Point2D> res = new ArrayList<>();
        for (Point2D temp : pointset)
            if (rect.contains(temp))
                res.add(temp);
        return res;
    }

    // a nearest neighbor in the set to point p; null if the set is empty   
    public Point2D nearest(Point2D p) {
        if (p == null) throw new IllegalArgumentException();
        if (pointset.isEmpty()) return null;
        Point2D curpoint = null;
        double curdistance = Double.MAX_VALUE;
        for (Point2D temp : pointset) {
            double tempdistance = p.distanceTo(temp);
            if (curdistance > tempdistance) {
                curdistance = tempdistance;
                curpoint = temp;
            }
        }
        return curpoint;
    }
}