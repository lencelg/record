import nltk
import sys
import string

TERMINALS = """
Adj -> "country" | "dreadful" | "enigmatical" | "little" | "moist" | "red"
Adv -> "down" | "here" | "never"
Conj -> "and" | "until"
Det -> "a" | "an" | "his" | "my" | "the"
N -> "armchair" | "companion" | "day" | "door" | "hand" | "he" | "himself"
N -> "holmes" | "home" | "i" | "mess" | "paint" | "palm" | "pipe" | "she"
N -> "smile" | "thursday" | "walk" | "we" | "word"
P -> "at" | "before" | "in" | "of" | "on" | "to"
V -> "arrived" | "came" | "chuckled" | "had" | "lit" | "said" | "sat"
V -> "smiled" | "tell" | "were"
"""

NONTERMINALS = """
S -> NP VP | S Conj S | VP
NP -> N | Det N | Det Adj N | NP PP
VP -> V | V NP | V NP PP | VP PP | VP Adv
PP -> P NP
"""

grammar = nltk.CFG.fromstring(NONTERMINALS + TERMINALS)
parser = nltk.ChartParser(grammar)


def main():

    # If filename specified, read sentence from file
    if len(sys.argv) == 2:
        with open(sys.argv[1]) as f:
            s = f.read()

    # Otherwise, get sentence as input
    else:
        s = input("Sentence: ")

    # Convert input into list of words
    s = preprocess(s)

    # Attempt to parse sentence
    try:
        trees = list(parser.parse(s))
    except ValueError as e:
        print(e)
        return
    if not trees:
        print("Could not parse sentence.")
        return

    # Print each tree with noun phrase chunks
    for tree in trees:
        tree.pretty_print()

        print("Noun Phrase Chunks")
        for np in np_chunk(tree):
            print(" ".join(np.flatten()))


def preprocess(sentence):
    """
    Convert `sentence` to a list of its words.
    Pre-process sentence by converting all characters to lowercase
    and removing any word that does not contain at least one alphabetic
    character.
    """
    # res = nltk.tokenize.word_tokenize(sentence)
    # all_letters_list = list(string.ascii_letters)
    # upper_letters_list = list(string.ascii_uppercase)
    # word_to_remove = []
    # for i in range(len(res)):
    #     word = res[i]
    #     contians = False 
    #     str=""
    #     for index in range(len(word)):
    #         if word[index] in all_letters_list:
    #             contians = True
    #             if word[index] in upper_letters_list:
    #                 str += word[index].lower()
    #             else:
    #                 str += word[index]
    #         else:
    #             str += word[index]
    #     if contians:
    #         res[i] = str
    #         continue
    #     word_to_remove.append(res[i])
    # for word in word_to_remove:
    #     res.remove(word)
    # return res
    tokens = nltk.word_tokenize(sentence)
    return [token.lower() for token in tokens if any(char.isalpha() for char in token)]






def np_chunk(tree):
    """
    Return a list of all noun phrase chunks in the sentence tree.
    A noun phrase chunk is defined as any subtree of the sentence
    whose label is "NP" that does not itself contain any other
    noun phrases as subtrees.
    """
    chunks = []
    
    for subtree in tree.subtrees():
        if subtree.label() != 'NP':
            continue
            
        has_nested_np = False
        for subsubtree in subtree.subtrees():
            if subsubtree == subtree:
                continue
            if subsubtree.label() == 'NP':
                has_nested_np = True
                break
        
        if not has_nested_np:
            chunks.append(subtree)
    
    return chunks


if __name__ == "__main__":
    main()
