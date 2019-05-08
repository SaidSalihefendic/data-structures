//#ifndef FUNCTIONS_H
//#define FUNCTIONS_H
//
//#include <utility>
//#include <iostream>
//#include <iomanip>
//#include <cmath>
//using namespace std;
//
//int distance(pair<int, int> x, pair<int, int> y) {
//    return abs(x.first - y.first) + abs(x.second - y.second);
//}
//
//int mazeRow(char letter) {
//    if(letter < 'A' || letter > 'Z') throw "Neispravan unos slova!";
//
//    if(letter%2!=0) {
//        return (int(letter)-int('A'))*2;
//    } else return (int(letter)-int('B'))*2 +3;
//}
//
//void printMaze(vector<vector<int> > maze) {
//
//    int k=0, pom=0;
//    for(int i=0; i<maze.size(); i++) {
//        if(i==(4*k-1)) {
//            cout << char(int('A') + pom++) << "  ";
//        }
//
//        else if(i==(4*k)) {
//            cout << char(int('A') + pom++) << "  ";
//            k++;
//        }
//        else cout << "  ";
//
//        for(int j=0; j<maze[i].size(); j++) {
//
//            cout.width(2);
//            if(maze[i][j] != 0) cout << maze[i][j] << " ";
//            else cout << "   ";
//        }
//        cout << endl;
//    }
//
//}
//
//int shortestDistance(char firstWall, int firstPosition, char secondWall, int secondPosition) {
//    pair<int, int> x, y;
//    int pom;
//    x.second = firstPosition-1; /// Indeksiranje krece od 0
//    y.second = secondPosition-1;
//    x.first = ((pom = mazeRow(firstWall))%2) ? pom-1 : pom+1; /// Ako se slovo nalazi u neparnom redu onda joj se \
//                                                                  moze prici samo sa gornje strane inace sa donje strane
//
//    y.first = ((pom = mazeRow(secondWall))%2) ? pom-1 : pom+1;
//
//
//    return distance(x,y); /// TODO zavrsiti
//}
//
//#endif // FUNCTIONS_H
