#include "WhatAreYouDoing.h"
#include "cctype"
#include "strlib.h"
using namespace std;

/* TODO: Read the comments in WhatAreYouDoing.h to see what this function needs to do, then
 * delete this comment.
 *
 * Don't forget about the tokenize function defined in WhatAreYouDoing.h; you'll almost
 * certainly want to use it.
            // lowercase the front
            string w="";
            for(string s:task){
                w+=s;
            }
            res.add(w);
            res+=allEmphasesOfHelper(res,task,point+1);
            // uppercase the front
            string temp=toUpperCase(task[point]);
            task[point]=temp;
            w="";
            for(string s:task){
                w+=s;
            }
            res.add(w);
            res+=allEmphasesOfHelper(res,task,point+1);
        this is the wrong way , because you unchoose it then you choose it ,which lead to the data change and was not the origin data , so the result differ
 */
// even a little parameter pass can affect the running time
// take a look in the case below , a &res parameter after call for more than 8000 cause a huge difference in the  runing time , the lowest part is by 冷日春宫 from zhihu.com， and my code was inspired by him
Set<string> allEmphasesOfHelper(Vector<string> &task,int point){
    Set<string> res;
    if(point==task.size()){
        string w;
        for(string s:task){
                w+=s;
            }
            res.add(w);
            return res;
    }
    else if(point<task.size() and isalpha(task[point][0])){
            // uppercase the case
            task[point]=toUpperCase(task[point]);
            res+=allEmphasesOfHelper(task,point+1);
            // lowercase the front
            task[point]=toLowerCase(task[point]);
            res+=allEmphasesOfHelper(task,point+1);
            return res;
    }else{
            res+=allEmphasesOfHelper(task,point+1);
            return res;
    }
}
Set<string> allEmphasesOf(const string& sentence) {
    /* TODO: Delete this line and the next one, then implement this function. */
    Vector<string> task;
    task=tokenize(sentence);
    for (int i = 0; i < task.size(); ++i) {
        task[i]=toLowerCase(task[i]);
    }
    return allEmphasesOfHelper(task,0);
}
// Set<string> allEmphasesOfHelper(Set<string>& res,Vector<string> &task,int point){
//     if(point==task.size()){
//         string w;
//         for(string s:task){
//             w+=s;
//         }
//         res.add(w);
//         return res;
//     }
//     else if(point<task.size() and isalpha(task[point][0])){
//         // uppercase the case
//         task[point]=toUpperCase(task[point]);
//         res+=allEmphasesOfHelper(res,task,point+1);
//         // lowercase the front
//         task[point]=toLowerCase(task[point]);
//         res+=allEmphasesOfHelper(res,task,point+1);
//         return res;
//     }else{
//         res+=allEmphasesOfHelper(res,task,point+1);
//         return res;
//     }
// }
// Set<string> allEmphasesOf(const string& sentence) {
//     /* TODO: Delete this line and the next one, then implement this function. */
//     Vector<string> task;
//     Set<string> res;
//     task=tokenize(sentence);
//     for (int i = 0; i < task.size(); ++i) {
//         task[i]=toLowerCase(task[i]);
//     }
//     return allEmphasesOfHelper(res,task,0);
// }
// bool isword(const string word)
// {
//     if(word==" ")return false;//题目已经约定，有效单词的第一位是字母且不会出现夹杂字母的情况
//     else if(!isalpha(word[0]))return false;
//     else return true;
// }
// Set<string> allEmphasesOfhelp(const Vector<string>&elems,
//                               Vector<string>&sofar,int point)
// {
//     Set<string> ans;
//     if(point==elems.size())//这条路走到头了，收进set
//     {
//         string w;
//         for(string s:sofar)w+=s;
//         ans+=w;
//         return ans;
//     }
//     else if(sofar.size()>0&&isword(elems[point]))
//     {/*Writter:(zhihu)凉宫春日*/
//         string tem1 = toUpperCase(sofar[point]);
//         string tem2 = sofar[point];
//         sofar[point]=tem1;//相当于选择这个元素
//         ans+=allEmphasesOfhelp(elems,sofar,point+1);
//         sofar[point]=tem2;//不选择
//         ans+=allEmphasesOfhelp(elems,sofar,point+1);
//         return ans;
//     }
//     else
//     {
//         ans+= allEmphasesOfhelp(elems,sofar,point+1);
//         return ans;
//     }
// }
// Set<string> allEmphasesOf(const string& sentence) {

//     Vector<string>elems=tokenize(sentence);

//     for(int i=0;i<elems.size();i++)
//         elems[i]=toLowerCase(elems[i]);//题目要求忽略原句子的大小写
//     return allEmphasesOfhelp(elems,elems,0);
// }
/* * * * * * Test Cases * * * * * */
#include "GUI/SimpleTest.h"

/* TODO: Add your own tests here. You know the drill - look for edge cases, think about
 * very small and very large cases, etc.
 */














/* * * * * * Test cases from the starter files below this point. * * * * * */

PROVIDED_TEST("Enumerates all options in a simple case.") {
    Set<string> expected = {
        "hello",
        "HELLO",
    };

    EXPECT_EQUAL(allEmphasesOf("Hello"), expected);
}

PROVIDED_TEST("Each option has the right length.") {
    string sentence = "Hello, world!";
    for (string option: allEmphasesOf(sentence)) {
        EXPECT_EQUAL(option.length(), sentence.length());
    }
}

PROVIDED_TEST("Enumerates all options in a more typical case.") {
    Set<string> expected = {
        "you are?",
        "you ARE?",
        "YOU are?",
        "YOU ARE?"
    };

    EXPECT_EQUAL(allEmphasesOf("You Are?"), expected);
}

PROVIDED_TEST("Stress Test: Recursion only branches on words (should take under a second)") {
    /* We're producing a string consisting of fifty copies of the * character. This tokenizes
     * into fifty separate stars. A star is the same whether or not you capitalize it - there
     * is no such thing as an "upper-case" or "lower-case" star. Therefore, your code should
     * not try to form two versions of the sentence, one with the star capitalized and one
     * without, because the two versions will end up being the same and the work to compute
     * both options will dramatically increase the runtime.
     *
     * For reference, if you do try branching the recursion and checking what happens both if
     * you capitalize the star and if you don't, you'll try exploring 2^50 different possible
     * capitalizations. That's 1,125,899,906,842,624 options, and even doing a billion of
     * these a second is going to take over two years to generate them all! And of course,
     * that's all wasted work, since there's only one way to capitalize this sentence, and
     * that's just to leave it as-is.
     *
     * If your code is hanging when this test is running, it likely means that your code is
     * trying to enumerate all of these options. See if you can edit your code so that, if
     * you're given a non-word token, you just leave it as-is and don't change anything.
     */
    string punctuation(50, '*'); // 50 copies of *

    /* The only emphasis is itself. */
    Set<string> expected = {
        punctuation
    };

    EXPECT_EQUAL(allEmphasesOf(punctuation), expected);
}

PROVIDED_TEST("Stress test: Generates each option once (should take at most a few seconds)") {
    /* This sentence has 13 words in it. There are therefore 2^13 = 8192 possible emphases for
     * the words there, which is a big number but not so large that the computer can't handle
     * it if generates each emphasis exactly once.
     *
     * On the other hand, if your code tries to generate the same emphases multiple times,
     * this test may take a very, very long time to complete, and might even appear to freeze
     * up.
     *
     * If your code gets stuck in this test, trace through your code and confirm that you can't
     * produce the same emphasis multiple times. Check to make sure you aren't, for example,
     * looping over every token in the input sentence and deciding which one to capitalize
     * next. The recursion here follows more of an include/exclude type pattern (more like
     * subsets and combinations) than it does a "which is next?" type pattern (more like
     * permutations).
     */
    string yeats = "Turing and turning in a widening gyre / the falcon cannot hear the falconer.";
    EXPECT_EQUAL(allEmphasesOf(yeats).size(), 8192);
}
