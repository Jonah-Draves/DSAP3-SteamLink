#include <iostream>
#include <vector>
#include <string>

using namespace std;

int getSimilarity(const vector<string>& baseTags, const vector<string>& targetTags) {
    /*
    Given two vectors of string game tags, returns an int representing how many strings were
    found in both vectors.

    Assumptions:
    Both vectors are in alphabetical order, as is default for our dataset.
    */
    int similarity = 0;
    auto baseIter = baseTags.begin();
    auto targetIter = targetTags.begin();
    while (baseIter != baseTags.end() && targetIter != targetTags.end()) {
        if ((*baseIter).size() == (*targetIter).size()) {
            if (*baseIter == *targetIter) {
                similarity++;
                baseIter++;
                targetIter++;
                continue;
            }
        }
        if (*baseIter < *targetIter) {
            baseIter++;
        }
        else {
            targetIter++;
        }
    }
    return similarity;
}

int main() {
    vector<string> b = {"Adventure", "Fantasy", "Sci-Fi"};
    vector<string> t = {"Action", "Fantasy", "Graphic", "Mythology", "Sci-Fi"};

    cout << getSimilarity(b, t) << endl;

    vector<string> b2 = {"Adventure", "Fantasb", "Sci-Fi"};
    vector<string> t2 = {"Action", "Fantasy"};

    cout << getSimilarity(b2, t2) << endl;

    return 0;
}
