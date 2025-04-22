#include <iostream>
#include <vector>
#include <utility>
#include "gamemap.cpp"
#include <map>
using namespace std;

int main() { //USER INTERFACE

	GameMap map = generateMap("games_cleaned_3.csv");

//        while (true) //menu loop
  //      {
		/*
                string game;
                string num;
                cout << "Please enter the game: ";
                getline(cin, game);
                cout << game << " Selected" << endl;
                cout << "How many similar games would you like to find?" << endl;
                getline(cin, num);
                cout << "Finding " << num << " similar games to: " << game << endl;
		*/
                //Below is the code for the computation of the n most similar games
	auto nClosest = map.nClosest("Galactic Bowling", 20, false);
	for (auto pair : nClosest) {
		cout << pair.first << " " << pair.second << endl;
	}

	/*cout << "Computing Similarity List" << endl;
	vector<pair<string, int>> similarity = map.similarityList("Galactic Bowling");//get the GameNode object of desired game, then generate a similarity list
	for (auto it : similarity){
		cout << endl << "Title: " << it.first << endl << " Similarity: " << it.second << endl;
	}
	cout << "Done." << endl;*/
                //
                //for(int i=0; i<num; i++)//Output n results
                //{
                    //cout << i << ": " << quicksort[num] or heapsort[num] << endl;
                //}
    //    }


}

