import os
import random
import re
import sys

DAMPING = 0.85
SAMPLES = 10000


def main():
    if len(sys.argv) != 2:
        sys.exit("Usage: python pagerank.py corpus")
    corpus = crawl(sys.argv[1])
    ranks = sample_pagerank(corpus, DAMPING, SAMPLES)
    print(f"PageRank Results from Sampling (n = {SAMPLES})")
    for page in sorted(ranks):
        print(f"  {page}: {ranks[page]:.4f}")
    ranks = iterate_pagerank(corpus, DAMPING)
    print(f"PageRank Results from Iteration")
    for page in sorted(ranks):
        print(f"  {page}: {ranks[page]:.4f}")


def crawl(directory):
    """
    Parse a directory of HTML pages and check for links to other pages.
    Return a dictionary where each key is a page, and values are
    a list of all other pages in the corpus that are linked to by the page.
    """
    pages = dict()

    # Extract all links from HTML files
    for filename in os.listdir(directory):
        if not filename.endswith(".html"):
            continue
        with open(os.path.join(directory, filename)) as f:
            contents = f.read()
            links = re.findall(r"<a\s+(?:[^>]*?)href=\"([^\"]*)\"", contents)
            pages[filename] = set(links) - {filename}

    # Only include links to other pages in the corpus
    for filename in pages:
        pages[filename] = set(
            link for link in pages[filename]
            if link in pages
        )

    return pages


def transition_model(corpus, page, damping_factor):
    """
    Return a probability distribution over which page to visit next,
    given a current page.

    With probability `damping_factor`, choose a link at random
    linked to by `page`. With probability `1 - damping_factor`, choose
    a link at random chosen from all pages in the corpus.
    """
    res = dict()
    if len(corpus[page]) == 0:
        possiblity = 1 / len(corpus.keys())
        for p in corpus.keys():
            res[p] = possiblity
        return res
    total_page_number = len(corpus.keys())
    correspond_page = corpus[page]
    possibility_to_all_page = (1 - damping_factor) / total_page_number
    correspond_page_possiblity = damping_factor / len(correspond_page)
    for page in corpus.keys():
        res[page] = possibility_to_all_page
        if page in correspond_page:
            res[page] += correspond_page_possiblity
    return res



def sample_pagerank(corpus, damping_factor, n):
    """
    Return PageRank values for each page by sampling `n` pages
    according to transition model, starting with a page at random.

    Return a dictionary where keys are page names, and values are
    their estimated PageRank value (a value between 0 and 1). All
    PageRank values should sum to 1.
    """
    res = dict()
    n_copy = n
    for page in corpus.keys():
        res[page] = 0
    current_page= random.choices(list(corpus.keys()), k = 1)[0]
    res[current_page] += 1
    n -= 1
    while n > 0:
        transition_pages = transition_model(corpus, current_page, damping_factor)
        current_page = random.choices(population = list(transition_pages.keys()), weights = list(transition_pages.values()), k = 1)[0]
        res[current_page] += 1
        n -= 1
    for page in corpus.keys():
        res[page] /= n_copy
    return res
 
def iterate_pagerank(corpus, damping_factor):
    """
    Return PageRank values for each page by iteratively updating
    PageRank values until convergence.

    Return a dictionary where keys are page names, and values are
    their estimated PageRank value (a value between 0 and 1). All
    PageRank values should sum to 1.
    """
    res = dict()
    possibilty_to_all_page = (1 - damping_factor) / len(corpus.keys())
    for page in corpus.keys():
        res[page] = 1 / len(corpus.keys())
    changed = True
    while changed:
        changed = False
        new_res = {}
        for current_page in corpus.keys():
            rank = 0

            for other_page in corpus.keys():
                if current_page in corpus[other_page]:
                    rank += (res[other_page] / len(corpus[other_page]))
                elif len(corpus[other_page]) == 0:
                    rank += (res[other_page] / len(corpus.keys())) 

            rank *= damping_factor
            rank += possibilty_to_all_page
            new_res[current_page] = rank
        
        for page in corpus.keys():
            if abs(new_res[page] - res[page]) > 0.001:
                changed = True
                break
        res = new_res
    total = sum(res.values())
    res = {page: value/total for page, value in res.items()}
    return res


if __name__ == "__main__":
    main()
