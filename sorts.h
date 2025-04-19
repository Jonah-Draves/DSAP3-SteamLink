#include <string>
#include <utility>
#include <vector>

using namespace std;

int partition(vector<pair<string, int>>& sList, int low, int high); //sList stands for "similarity list"
void quickSortHelper(vector<pair<string, int>>& sList, int low, int high);
void quickSort(vector<pair<string, int>>& sList);
void extractMax(vector<pair<string, int>>& sList);
void heapifyUp(vector<pair<string, int>>& sList, int i);
vector<pair<string, int>> heapSort(vector<pair<string, int>>& sList);