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
void quickSort(vector<pair<string, int>>& sList, int low, int high) {
    /*
     Given a list of string, int pairs, reorganizes that list in descending int order
    */
    if (low < high) {
        int pivot = partition(sList, low, high);
        quickSort(sList, low, pivot - 1);
        quickSort(sList, pivot + 1, high);
    }
}