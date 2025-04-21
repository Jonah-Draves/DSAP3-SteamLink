#pragma once
#include "sorts.h"

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

    /*Tests for similarity
     *vector<string> b = {"Adventure", "Fantasy", "Sci-Fi"};
    vector<string> t = {"Action", "Fantasy", "Graphic", "Mythology", "Sci-Fi"};

    cout << getSimilarity(b, t) << endl;

    vector<string> b2 = {"Adventure", "Fantasb", "Sci-Fi"};
    vector<string> t2 = {"Action", "Fantasy"};

    cout << getSimilarity(b2, t2) << endl;*/

    vector<pair<string, int>> sample;
    sample.push_back({"01001", 1});
    sample.push_back({"01112", 0});
    sample.push_back({"01003", 3});
    sample.push_back({"04", 4});
    sample.push_back({"0005", 3});
    sample.push_back({"006", 2});
    sample.push_back({"01", 1});
    sample.push_back({"010123", 0});
    sample.push_back({"01116", 2});
    sample.push_back({"17", 1});
    vector<pair<string, int>> sample2 = sample;
    quickSort(sample);

    cout << "QuickSort:" << endl;
    for (auto iter : sample) {
        cout << iter.first << " " << iter.second << endl;
    }
    vector<pair<string, int>> sorted = heapSort(sample2);
    cout << "HeapSort:" << endl;
    for (auto iter : sorted) {
        cout << iter.first << " " << iter.second << endl;
    }

    return 0;
}
