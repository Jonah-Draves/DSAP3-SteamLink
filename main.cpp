#pragma once
#include "sorts.h"

#include <iostream>
#include <vector>
#include <string>

using namespace std;


int loadDataSet(string filename){

        vector<vector<string>> dataset; //data is stored in a vector of vectors
        //each vector in this vector goes as follows: <ID, Title, Genre, Tags>
        ifstream file(filename);

        if (!file.is_open()) {  //if the requested file is not valid
                cout << "Could not open " << filename << endl;
                return 0;
        }
        string currentline;
        int counter = 0;
        while (getline(file, currentline)){//Read each line of the file and extract the desired cells
                stringstream ss(currentline);
                string cell;
                //cout << "FullLine: " << currentline << endl << endl << endl;
                vector<string> cellvector;
                for(int i=0; getline(ss, cell, '|'); i++){
                        if (i == 0) cellvector.push_back(cell);//cout << "ID: " << cell << endl;
                        if (i == 1) cellvector.push_back(cell);//cout << "Title: " << cell << endl;
                        if (i == 35) cellvector.push_back(cell);//cout << "Genre: " << cell << endl;
                        if (i == 36) cellvector.push_back(cell);//cout << "Tags: " << cell << endl;
                        counter++;
                }
                if (counter == 4){
                        dataset.push_back(cellvector);
                        counter = 0;
                        cellvector.erase(cellvector.begin(), cellvector.end());
                }
        //cout << endl << endl << endl;

        }
        cout << "Database loaded" << endl;
        return 0;

}

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
