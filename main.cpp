#include <iostream>
#include <vector>
#include <utility>
#include <chrono>
#include "gamemap.cpp"
#include <map>
using namespace std;

int main() { //USER INTERFACE
	GameMap map = generateMap("games_cleaned_3.csv");

	while (true) //menu loop
	{
		string sortType;
		string game;
		string numSimilar;
		int similarCount;
		cout << "Please enter the game:";
		getline(cin, game);
		if (!map.isNameIn(game)) {
		    cout << "That game's name is not recognized. Please try again" << endl;
		    continue;
		}
		cout << game << " Selected" << endl;
		cout << "How many similar games would you like to find? (1-100)" << endl;
		getline(cin, numSimilar);
		similarCount = stoi(numSimilar);
		if (similarCount <= 0 || similarCount > 100) {
		    cout << "You must query at least one similar game, and less than one-hundred. Please try again" << endl;
		    continue;
		}
		cout << "Would you like to use heap or quick sort? (heap or quick?)" << endl;
		getline(cin, sortType);
		cout << "Finding " << numSimilar << " similar games to: " << game << endl;
		//Below is the code for the computation of the n most similar games
		auto nClosest = map.nClosest(game, similarCount, true);
		if (sortType == "heap") {
			nClosest = map.nClosest(game, similarCount);
		}
		else if (sortType == "quick") {
			nClosest = map.nClosest(game, similarCount, false);
		}
		else if (sortType == "compare") {
			auto heapStart = std::chrono::high_resolution_clock::now();
			nClosest = map.nClosest(game, similarCount, true);
			auto end = std::chrono::high_resolution_clock::now();
			auto heapDuration = std::chrono::duration_cast<std::chrono::microseconds>(end - heapStart);
			auto quickStart = std::chrono::high_resolution_clock::now();
			nClosest = map.nClosest(game, similarCount, false);
			end = std::chrono::high_resolution_clock::now();
			auto quickDuration = std::chrono::duration_cast<std::chrono::microseconds>(end - quickStart);
			std::cout << "Heapsort executed in: " << heapDuration.count() << " microseconds vs. " << quickDuration.count() << " for quicksort."<< std::endl;
			continue;
		}
		else {
			cout << "No such sort type, please try again" << endl;
		}
		for (auto pair : nClosest) {
			cout << pair.first << " \tSimilarity: " << pair.second << endl;
		}

		cout << "Done." << endl;
	}

}

