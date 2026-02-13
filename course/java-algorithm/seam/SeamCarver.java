/* *****************************************************************************
 *  Name:
 *  Date:
 *  Description:
 **************************************************************************** */
import edu.princeton.cs.algs4.Picture;
import java.awt.Color;
public class SeamCarver {
    private final int width;
    private final int height;
    private Picture cur;
    private double energy[][];
    // create a seam carver object based on the given picture
    public SeamCarver(Picture picture) {
        if (picture == null) throw new IllegalArgumentException("the picture can not be null");
        width = picture.width();
        height = picture.height();
        cur = new Picture(picture);
        energy = new double[width][height];
        for (int i = 0; i < width; i++) {
            energy[i][0] = 1000;
            energy[i][height - 1] = 1000;
        }
        for (int i = 0; i < height; i++) {
            energy[0][i] = 1000;
            energy[width - 1][i] = 1000;
        }
        for (int i = 1; i < width - 1; i++)
            for (int j = 1; j < height - 1; j++)
                energy[i][j] = compute(i, j);
    }

    // current picture
    public Picture picture() {
        return cur;
    }

    // width of current picture
    public int width() {
        return width;
    }

    // height of current picture
    public int height() {
        return height;
    }

    // energy of pixel at column x and row y
    public double energy(int x, int y) {
        if (x < 0 || x > width - 1 || y < 0 || y > height - 1)
            throw new IllegalArgumentException("the index is out of bound");
        return energy[x][y];
    }
    private double compute(int x, int y) {
        double d_x = compute_x(x, y);
        double d_y = compute_y(x, y);
        return Math.sqrt(d_x + d_y);
    }
    private double compute_x(int x, int y){
         Color left = cur.get(x - 1, y);
         Color right = cur.get(x + 1, y);
         double diffred = Math.pow(left.getRed() - right.getRed(), 2);
         double diffgreen = Math.pow(left.getGreen() - right.getGreen(), 2);
         double diffblue = Math.pow(left.getBlue() - right.getBlue(), 2);
         return diffred + diffgreen + diffblue;
    }

    private double compute_y(int x, int y){
        Color down = cur.get(x, y - 1);
        Color up = cur.get(x, y + 1);
        double diffred = Math.pow(down.getRed() - up.getRed(), 2);
        double diffgreen = Math.pow(down.getGreen() - up.getGreen(), 2);
        double diffblue = Math.pow(down.getBlue() - up.getBlue(), 2);
        return diffred + diffgreen + diffblue;
    }
    // sequence of indices for horizontal seam
    public int[] findHorizontalSeam() {
        int[] res = new int[width];
        for (int i = 1; )
    }

    // sequence of indices for vertical seam
    public int[] findVerticalSeam()

    // remove horizontal seam from current picture
    public void removeHorizontalSeam(int[] seam)

    // remove vertical seam from current picture
    public void removeVerticalSeam(int[] seam)

    //  unit testing (optional)
    public static void main(String[] args) {
        //optional
    }

}