import edu.princeton.cs.algs4.Point2D;
import edu.princeton.cs.algs4.RectHV;

public class kdTree {
    private class Node {
        private int height = 0;
        private Node left;
        private Node right;
        private Point2D point;

        Node(Point2D p) {
            this.point = p;
            this.left = null;
            this.right = null;
        }
    }

    private Node root = null;
    private int size = 0;

    // construct an empty set of points
    public kdTree() {
    }

    // is the set empty?
    public boolean isEmpty() {
        return size == 0;
    }

    // number of points in the
    public int size() {
        return size;
    }

    private boolean isodd(Node cur) {
        return cur.height % 2 == 1;
    }

    private Node inserthelper(Node node, Node newnode) {
        newnode.height++;
        if (node == null)
            node = newnode;
        Point2D temp = node.point;
        Point2D p = newnode.point;
        if (isodd(node)) {
            if (temp.x() > p.x()) node.left = inserthelper(node.left, newnode);
            else if (temp.x() < p.x()) node.right = inserthelper(node.right, newnode);
            else return null;
        }
        else {
            if (temp.y() > p.y()) node.left = inserthelper(node.left, newnode);
            else if (temp.y() < p.y()) node.right = inserthelper(node.right, newnode);
            else return null;
        }
        return null;
    }

    // add the point to the set (if it is not already in the set)
    public void insert(Point2D p) {
        if (p == null) throw new IllegalArgumentException();
        if (!contains(p)) {
            Node newnode = new Node(p);
            inserthelper(root, newnode);
        }
    }

    private boolean contains(Node node, Point2D p) {
        if (node == null)
            return false;
        Point2D temp = node.point;
        if (isodd(node)) {
            if (temp.x() > p.x()) return contains(node.left, p);
            else if (temp.x() < p.x()) return contains(node.right, p);
            else return true;
        }
        else {
            if (temp.y() > p.y()) return contains(node.left, p);
            else if (temp.y() < p.y()) return contains(node.right, p);
            else return true;
        }
    }

    // does the set contain point p?
    public boolean contains(Point2D p) {
        if (p == null)
            throw new IllegalArgumentException("the point2D to look for should not be null");
        return contains(root, p);
    }

    private void drawodd(Point2D oddpoint) {

    }

    private void draweven(Point2D evenpoint) {

    }

    private void drawhelper(Node curnode) {
        if (curnode == null)
            return;
        Point2D curpoint = curnode.point;
        if (isodd(curnode))
            drawodd(curpoint);
        else draweven(curpoint);
        drawhelper(curnode.left);
        drawhelper(curnode.right);
    }

    // draw all points to standard draw
    public void draw() {
        drawhelper(root);
    }

    // all points that are inside the rectangle (or on the boundary)
    public Iterable<Point2D> range(RectHV rect) {
    }

    // a nearest neighbor in the set to point p; null if the set is empty
    public Point2D nearest(Point2D p) {
    }

    // unit testing of the methods (optional) 
    public static void main(String[] args) {
        // optional for debug
    }
}   