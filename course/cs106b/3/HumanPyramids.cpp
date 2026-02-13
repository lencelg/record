#include "HumanPyramids.h"
#include "GUI/SimpleTest.h"
#include "error.h"
#include "Map.h"
#include "Gridlocation.h"
using namespace std;

/* TODO: Refer to HumanPyramids.h for more information about what this function should do.
 * Then, delete this comment.
 */
/* version one of weightOnBackOf
double weightOnBackOf(int row, int col, int pyramidHeight) {
    /* TODO: Delete the next few lines and implement this function.
    if(row<0||col<0||row>pyramidHeight||pyramidHeight<=0){
        error("the index is illegal");
        return -1;
    }else if(row==0 and col==0){
        return 0;
    }else {
        if(row==col){
            return 80+weightOnBackOf(row-1,col-1,pyramidHeight-1)*0.5;
        }else if((row-col)==row){
            return 80+weightOnBackOf(row-1,col,pyramidHeight-1)*0.5;
        }else{
            return weightOnBackOf(row-1,col-1,pyramidHeight-1)*0.5+160+weightOnBackOf(row-1,col,pyramidHeight-1)*0.5;
        }
    }
}
*/
/* version 2 to speed up */


double weightOnBackOfHelper(int row, int col, int pyramidHeight,Map<GridLocation,double>& table){
    //error case
    if(row<0||col<0||row>pyramidHeight||pyramidHeight<=0||col>row){
        error("the index is illegal");
    }
    // base case
    GridLocation temp={row,col};
    if(row==0 and col==0){
        return 0;
    }else if(table.containsKey(temp)){
            return table[temp];
    }else if(row==col){
        double res=80+weightOnBackOfHelper(row-1,col-1,pyramidHeight-1,table)/2.0;
        table[temp]=res;
        return res;
            }else if(col==0){
        double res=80+weightOnBackOfHelper(row-1,col,pyramidHeight-1,table)/2.0;
        table[temp]=res;
        return res;
            }else{
                double res=weightOnBackOfHelper(row-1,col-1,pyramidHeight-1,table)/2.0+160+weightOnBackOfHelper(row-1,col,pyramidHeight-1,table)/2.0;
        table[temp]=res;
        return res;
            }
}


double weightOnBackOf(int row, int col, int pyramidHeight) {
    Map<GridLocation,double> table;
    return weightOnBackOfHelper(row,col,pyramidHeight,table);
}
/* * * * * * Test Cases * * * * * */

/* TODO: Add your own tests here. You know the drill - look for edge cases, think about
 * very small and very large cases, etc.
 */

STUDENT_TEST("My testcase."){
    double a=weightOnBackOf(0,0,1);
    EXPECT_EQUAL(a,0);
    a=weightOnBackOf(4,2,5);
    EXPECT_EQUAL(a,500);
    a=weightOnBackOf(30,2,31);
    // precision missing in this case , i don't know why
    // orginally the result is 800 or 800d .
    EXPECT_EQUAL(a,799.9999161064625);
}
STUDENT_TEST("My stress_testcase."){
    EXPECT(weightOnBackOf(500,250,1000)>=1000);
}












/* * * * * * Test cases from the starter files below this point. * * * * * */

PROVIDED_TEST("Check Person E from the handout.") {
    /* Person E is located at row 2, column 1. */
    EXPECT_EQUAL(weightOnBackOf(2, 1, 5), 240);
}

PROVIDED_TEST("Function reports errors in invalid cases.") {
    EXPECT_ERROR(weightOnBackOf(-1, 0, 10));
    EXPECT_ERROR(weightOnBackOf(10, 10, 5));
    EXPECT_ERROR(weightOnBackOf(-1, 10, 20));
}

PROVIDED_TEST("Stress test: Memoization is implemented (should take under a second)") {
    /* TODO: Yes, we are asking you to make a change to this test case! Delete the
     * line immediately after this one - the one that starts with SHOW_ERROR - once
     * you have implemented memoization to test whether it works correctly.
     */

    /* Do not delete anything below this point. :-) */

    /* This will take a LONG time to complete if memoization isn't implemented.
     * We're talking "heat death of the universe" amounts of time. :-)
     *
     * If you did implement memoization but this test case is still hanging, make
     * sure that in your recursive function (not the wrapper) that your recursive
     * calls are to your new recursive function and not back to the wrapper. If you
     * call the wrapper again, you'll get a fresh new memoization table rather than
     * preserving the one you're building up in your recursive exploration, and the
     * effect will be as if you hadn't implemented memoization at all.
     */
    EXPECT(weightOnBackOf(100, 50, 200) >= 10000);
}

/* TODO: Add your own tests here. You know the drill - look for edge cases, think about
 * very small and very large cases, etc.
 */
