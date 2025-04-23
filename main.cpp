#include <iostream>
#include <vector>
#include <utility>
#include "gamemap.cpp"
#include <map>
using namespace std;

int main() { //USER INTERFACE

	GameMap map = generateMap("games_cleaned_3.csv");

          while (true) //menu loop
          {
		string sort;
                string game;
                string num;
                cout << "Please enter the game: ";
                getline(cin, game);
                cout << game << " Selected" << endl;
                cout << "How many similar games would you like to find?" << endl;
                getline(cin, num);
		cout << "Would you like to use heap or quick sort?(y-heap, anything else-quick)" << endl;
		getline(cin, sort);
                cout << "Finding " << num << " similar games to: " << game << endl;
                //Below is the code for the computation of the n most similar games
		auto nClosest = map.nClosest(game, stoi(num), true);

		if(sort == "y")
		{
			nClosest = map.nClosest(game, stoi(num), true);
		}
		else{
			nClosest = map.nClosest(game, stoi(num), false);
		}

		for (auto pair : nClosest) {
			cout << pair.first << " " << pair.second << endl;
		}

	
		cout << "Done." << endl;
        }


}

