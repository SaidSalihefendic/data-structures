#include <iostream>
#include <cstdlib>
//#include "fileparser.h"
//#include "functions.h"
#include "project2.h"
#include <string>
using namespace std;

void menu1(Maze& maze){
    char firstWall, secondWall;
    int firstPosition, secondPosition;

    cout << "Unesite prvo polje: ";
    cin >> firstWall >> firstPosition;
    cout << "Unesite drugo polje: ";
    cin >> secondWall >> secondPosition;

    cout << "Najkraca udaljenost: " << maze.shortestDistanceBFS(firstWall, firstPosition, secondWall, secondPosition) << endl;
    cout << "Modified: " << maze.shortestDistanceModified(firstWall, firstPosition, secondWall, secondPosition) << endl;
}

void menu2(Maze& maze){
    vector<string> tour;
    string field("A1");

    cout << "Unesite polja redom (N - kraj unosa): " << endl;
    while(field != "N" && field != "n"){
        cin >> field;

            //We need to check validity of the given field
        if(field != "N" && field != "n")
            tour.push_back(field);
    }

    cout << endl << endl;
    maze.bestTour(tour);

}

int main() {
    cout << "<<<<<<<<<<< Labirint >>>>>>>>>>>" << endl;

    string numOfLabirinth;
    cout << "Unesite redni broj labirinta: ";
    cin >> numOfLabirinth;
    system("cls");
    try {
        Maze maze("labirint" + numOfLabirinth + ".txt");
        cout << "Struktura labirinta: " << endl;

        while(true){
            maze.printMaze();
             //       cout << endl << "----------------------------------------------------" << endl << endl;
            //        cout << "Prolazi na ivicama: "<< endl;
            //        maze.printPasses();
            cout << endl << "----------------------------------------------------" << endl << endl;
            cout << "Odaberite: " << endl;
            cout << "1. Udaljenost izmedju dva polja" << endl;
            cout << "2. Najbolja data tura" << endl;
            cout << "3. Izadji" << endl << endl;
            int choice;
            cout << "Unos: ";
            cin >> choice;

            switch(choice){
            case 1:
                menu1(maze);
                break;
            case 2:
                menu2(maze);
                break;
            }

            if(choice == 3)
                break;

            system("pause");
            system("cls");
        }
    } catch(const char err[]) {
        cout << err << endl;
    }

    cout << endl << "----------------------------------------------------" << endl << endl;

    cout << "Kraj" << endl;
    return 0;
}
