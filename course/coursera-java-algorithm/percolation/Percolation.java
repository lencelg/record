import edu.princeton.cs.algs4.WeightedQuickUnionUF;

public class Percolation {

    private WeightedQuickUnionUF grid;
    private WeightedQuickUnionUF backwash;
    private int openNum;
    private boolean[][] openrecord;
    private int size;

    public Percolation(int n) {
        if (n <= 0) {
            throw new IllegalArgumentException();
        }
        grid = new WeightedQuickUnionUF(n * n + 2);
        backwash = new WeightedQuickUnionUF(n * n + 1);
        openrecord = new boolean[n + 1][n + 1];
        size = n;
        openNum = 0;
        for (int i = 1; i <= size; i++) {
            for (int j = 1; j <= size; j++) {
                openrecord[i][j] = false;
            }
        }
        for (int i = 1; i <= size; i++) {
            grid.union(gridPos(1, i), size * size);
            backwash.union(gridPos(1, i), size * size);
            grid.union(gridPos(size, i), size * size + 1);
        }
    }
    public void open(int row, int col)  {
        if (row > size || col > size || row < 1 || col < 1) {
            throw new IllegalArgumentException();
        }
        if (!isOpen(row, col)) {
            openrecord[row][col] = true;
            openNum++;
            connect(row, col);
        }
    }
    private int gridPos(int row, int col) {
        return size * (row - 1) + col - 1;
    }
    private void connect(int row, int col) {
        if (row > 1 && isOpen(row - 1, col)) {
            grid.union(gridPos(row, col), gridPos(row - 1, col));
            backwash.union(gridPos(row, col), gridPos(row - 1, col));
        }
        if (row + 1 <= size && isOpen(row + 1, col)) {
            grid.union(gridPos(row, col), gridPos(row + 1, col));
            backwash.union(gridPos(row, col), gridPos(row + 1, col));
        }
        if (col > 1 && isOpen(row, col - 1)) {
            grid.union(gridPos(row, col), gridPos(row, col - 1));
            backwash.union(gridPos(row, col), gridPos(row, col - 1));
        }
        if (col + 1 <= size && isOpen(row, col + 1)) {
            grid.union(gridPos(row, col), gridPos(row, col + 1));
            backwash.union(gridPos(row, col), gridPos(row, col + 1));
        }
    }
    public boolean isOpen(int row, int col) {
        if (row > size || col > size || row < 1 || col < 1) {
            throw new IllegalArgumentException();
        }
        return openrecord[row][col];
    }
    public boolean isFull(int row, int col) {
        if (row < 1 || col < 1 || row > size || col > size) {
            throw new IllegalArgumentException();
        }
        return openrecord[row][col] && (backwash.find(gridPos(row, col)) == backwash.find(size  * size));
    }
    public int numberOfOpenSites() {
        return openNum;
    }
    public boolean percolates() {
        if (openNum == 0) {
            return false;
        }
        return grid.find(size * size) == grid.find(size * size + 1);
    }
    public static void main(String[] args) {
        // optional for debug
    }
}
