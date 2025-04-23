//
// Created by Owner on 4/18/2025.
//
#include "sorts.h"

using namespace std;

//The code for quicksort was based off of the Module 9 UFOnline lecture code and modified for use in this project
int partition(vector<pair<string, int>>& sList, int low, int high) {
    int pivot = sList[low].second;
    int up = low, down = high;
    while (up < down) {
        for (int j = up; j < high; j++) {
            if (sList[up].second < pivot)
                break;
            up++;
        }
        for (int j = high; j > low; j--) {
            if (sList[down].second > pivot)
                break;
            down--;
        }
        if (up < down)
            swap(sList[up], sList[down]);
    }
    swap(sList[low], sList[down]);
    return down;
}
void quickSortHelper(vector<pair<string, int>>& sList, int low, int high) {
    /*
     Given a list of string, int pairs, reorganizes that list in descending int order
    */
    if (low < high) {
        int pivot = partition(sList, low, high);
        quickSortHelper(sList, low, pivot - 1);
        quickSortHelper(sList, pivot + 1, high);
    }
}

void quickSort(vector<pair<string, int>>& sList) {
    quickSortHelper(sList, 0, sList.size() - 1);
}

//Similarly code for heapsort was based off of the Module 6 UFOnline lecture pseudocode
void extractMax(vector<pair<string, int>>& sList) {
    int size = sList.size();
    sList[0] = sList[--size];
    sList.pop_back();
    heapifyUp(sList, 0);
}
//some of the logic is taken from my (Jonah's) edugator extractMax() programming quiz
void heapifyUp(vector<pair<string, int>>& sList, int i) {
    int maxChildIndex = i;
    bool hasMaxChild = false;
    if (2*i + 1 < sList.size())
        if (sList[2*i+1].second > sList[i].second) {
            maxChildIndex = 2*i + 1;
            hasMaxChild = true;
        }
    if (2*i + 2 < sList.size())
        if (sList[2*i+2].second > sList[maxChildIndex].second) {
            maxChildIndex = 2*i + 2;
            hasMaxChild = true;
        }
    if (hasMaxChild) {
        std::swap(sList[i], sList[maxChildIndex]);
        heapifyUp(sList, maxChildIndex);
    }
}

vector<pair<string, int>> heapSort(vector<pair<string, int>>& sList) {
    /*
    Given a list of string, int pairs, returns that list in descending int order
    */
    for (int i = sList.size()/2-1; i >= 0; i--) {
        heapifyUp(sList, i);
    }
    vector<pair<string, int>> sorted;
    while (!sList.empty()) {
        sorted.push_back(sList[0]);
        extractMax(sList);
    }

    return sorted;
}
