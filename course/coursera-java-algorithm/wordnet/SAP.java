/* *****************************************************************************
 *  Name: Lencelg
 *  Date:
 *  Description:
 **************************************************************************** */

import edu.princeton.cs.algs4.BreadthFirstDirectedPaths;
import edu.princeton.cs.algs4.Digraph;
import edu.princeton.cs.algs4.In;
import edu.princeton.cs.algs4.StdIn;
import edu.princeton.cs.algs4.StdOut;

public class SAP {
    private Digraph graph;

    // constructor takes a digraph (not necessarily a DAG)
    public SAP(Digraph G) {
        if (G == null)
            throw new IllegalArgumentException("the graph should not be null");

        graph = new Digraph(G);
    }

    // length of shortest ancestral path between v and w; -1 if no such path
    public int length(int v, int w) {
        BreadthFirstDirectedPaths bfs1 = new BreadthFirstDirectedPaths(graph, v);
        BreadthFirstDirectedPaths bfs2 = new BreadthFirstDirectedPaths(graph, w);
        int vectix = graph.V();
        int min = Integer.MAX_VALUE;
        for (int i = 0; i < vectix; i++) {
            if (bfs1.hasPathTo(i) && bfs2.hasPathTo(i))
                min = Math.min(min, bfs1.distTo(i) + bfs2.distTo(i));
        }
        return min == Integer.MAX_VALUE ? -1 : min;
    }

    // a common ancestor of v and w that participates in a shortest ancestral path; -1 if no such path
    public int ancestor(int v, int w) {
        BreadthFirstDirectedPaths bfs1 = new BreadthFirstDirectedPaths(graph, v);
        BreadthFirstDirectedPaths bfs2 = new BreadthFirstDirectedPaths(graph, w);
        int vertices = graph.V();
        int minPath = graph.V();
        int commonAncestor = -1;
        for (int i = 0; i < vertices; i++) {
            if (bfs1.hasPathTo(i) && bfs2.hasPathTo(i)) {
                int currentPath = bfs1.distTo(i) + bfs2.distTo(i);
                if (currentPath < minPath) {
                    minPath = currentPath;
                    commonAncestor = i;
                }
            }
        }
        return commonAncestor;
    }

    // length of shortest ancestral path between any vertex in v and any vertex in w; -1 if no such path
    public int length(Iterable<Integer> v, Iterable<Integer> w) {
        if (v == null || w == null)
            throw new IllegalArgumentException("the arguement should not be null");
        int min = Integer.MAX_VALUE;
        for (Integer tempv : v) {
            for (Integer tempw : w) {
                int cur = length(tempv, tempw);
                min = min < cur ? min : cur;
            }
        }
        return min == Integer.MAX_VALUE ? -1 : min;
    }

    // a common ancestor that participates in shortest ancestral path; -1 if no such path
    public int ancestor(Iterable<Integer> v, Iterable<Integer> w) {
        // not implement
        if (v == null || w == null)
            throw new IllegalArgumentException("the arguement should not be null");
        for (Integer temp : v)
            if (temp == null) throw new IllegalArgumentException();
        for (Integer temp : w)
            if (temp == null) throw new IllegalArgumentException();
        return -1;
    }

    // do unit testing of this class
    public static void main(String[] args) {
        In in = new In(args[0]);
        Digraph G = new Digraph(in);
        SAP sap = new SAP(G);
        while (!StdIn.isEmpty()) {
            int v = StdIn.readInt();
            int w = StdIn.readInt();
            int length = sap.length(v, w);
            int ancestor = sap.ancestor(v, w);
            StdOut.printf("length = %d, ancestor = %d\n", length, ancestor);
        }
    }
}
