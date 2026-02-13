/* *****************************************************************************
 *  Name: Lencelg
 *  Date:
 *  Description:
 **************************************************************************** */

import edu.princeton.cs.algs4.Digraph;
import edu.princeton.cs.algs4.DirectedCycle;
import edu.princeton.cs.algs4.In;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Map;
import java.util.Set;

public class WordNet {
    private final Digraph wordnet;
    private final Map<String, Set<Integer>> nounsynsets;
    private final ArrayList<String> orisynsets;
    private final SAP s;

    // constructor takes the name of the two input files
    public WordNet(String synsets, String hypernyms) {
        if (synsets == null || hypernyms == null)
            throw new IllegalArgumentException("the input file should not be null");
        nounsynsets = new HashMap<>();
        orisynsets = new ArrayList<>();
        processsynsets(synsets);
        wordnet = new Digraph(nounsynsets.size());
        processhypernyms(hypernyms);
        checkcycle(wordnet);
        checkroots();
        s = new SAP(wordnet);
    }

    private void processsynsets(String synsetsfile) {
        In in = new In(synsetsfile);
        while (!in.isEmpty()) {
            String[] temp = in.readLine().split(",");
            int id = Integer.parseInt(temp[0]);
            String key = temp[1];
            String[] wordstring = temp[1].split(" ");
            for (int i = 0; i < wordstring.length; i++) {
                key = wordstring[i];
                orisynsets.add(key);
                if (nounsynsets.get(key) == null)
                    nounsynsets.put(key, new HashSet<>());
                nounsynsets.get(key).add(id);
            }
        }
    }

    private void processhypernyms(String hypernymsfile) {
        In in = new In(hypernymsfile);
        while (!in.isEmpty()) {
            String[] temp = in.readLine().split(",");
            int v = Integer.parseInt(temp[0]);
            for (int i = 1; i < temp.length; i++) {
                int w = Integer.parseInt(temp[i]);
                wordnet.addEdge(v, w);
            }
        }
    }

    private void checkcycle(Digraph target) {
        DirectedCycle dc = new DirectedCycle(target);
        if (dc.hasCycle())
            throw new IllegalArgumentException("the wordnet graph should not has a cycel");
    }

    private void checkroots() {
        int roots = 0;
        for (int i = 0; i < nounsynsets.size(); i++) {
            if (wordnet.outdegree(i) == 0) {
                roots++;
                if (roots >= 2) {
                    throw new IllegalArgumentException(
                            "word net should not have more than one root");
                }
            }
        }
    }

    // returns all WordNet nouns
    public Iterable<String> nouns() {
        return nounsynsets.keySet();
    }

    // is the word a WordNet noun?
    public boolean isNoun(String word) {
        return nounsynsets.containsKey(word);
    }

    // distance between nounA and nounB (defined below)
    public int distance(String nounA, String nounB) {
        if (!isNoun(nounA) || !isNoun(nounB))
            throw new IllegalArgumentException("no noun should be null");
        return s.length(nounsynsets.get(nounA), nounsynsets.get(nounB));
    }

    // a synset (second field of synsets.txt) that is the common ancestor of nounA and nounB
    // in a shortest ancestral path (defined below)
    public String sap(String nounA, String nounB) {
        if (!isNoun(nounA) || !isNoun(nounB))
            throw new IllegalArgumentException("no noun should be null");
        return orisynsets.get(s.ancestor(nounsynsets.get(nounA), nounsynsets.get(nounB)));
    }

    // do unit testing of this class
    public static void main(String[] args) {
        return;
    }
}
