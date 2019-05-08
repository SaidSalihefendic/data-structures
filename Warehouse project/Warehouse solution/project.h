#ifndef PROJECT_H
#define PROJECT_H

#include <iostream>
#include <string>
#include <fstream>
#include <utility>
#include <cmath>
#include <iomanip>

#include <queue> /// Helper for path finding algorithms
#include <vector> /// Used for matrix representation
#include <list> /// Used for storing passes
using namespace std;

typedef pair<int, int> point;
class Maze {
public:
    Maze(string fileName);
    Maze();
    void printMaze(); /// Prints the input maze

    int shortestDistance(char firstWall, int firstPosition, char secondWall, int secondPosition); /// Returns the minimum distance using ?
    int shortestDistanceBFS(char firstWall, int firstPosition, char secondWall, int secondPosition); /// Returns the minimum distance from point x to point y using BFS
    int distance(point x, point y); /// Manhattan distance d((x,y),(a,b)) = |x-a|+|y-b|

    void printPasses(); /// REMOVE FROM FINAL VERSION

private:

    vector<vector<int> > maze; /// Matrix that represents the input maze
    list<point> passes; /// List of all passes in the graph

    int mazeRow(char letter); /// Function which returns the matrix row that can be accessed be the letter
    bool isValid(point current); /// Function that returns true if the position in the matrix is not out of bounds nor is a wall
};

/**************************************************** CONSTRUCTORS ****************************************************/
Maze::Maze() {};

Maze::Maze(string fileName) { /// TODO Double check the parser

    string helper; /// Doesn't do a thing, check if needed
    int rows, cols;

    ifstream input(fileName);

    input >> rows;
    input.get();
    input >> cols;
    input.get();

    if(rows % 2) throw "Broj kolona mora biti paran broj!";
    else if(rows < 0 || rows > 26) throw "Broj kolona mora biti u rasponu [0-26]!";

    maze.resize(2*rows);
    vector<int> util;

    for(int i=1; i<=cols; i++) util.push_back(i);

    int k=0;
    int pom;

    for(int i=0; i<2*rows; i++) {
        if(i==0 || i==2*rows-1) {
            maze[i] = util;

        } else if(i==(4*k+3)) {
            maze[i] = maze[i+1] = util;
            k++;

            point pass;

            if(input.eof() || input.peek()=='\n' || input.peek()==-1) throw "Neispravan format fajla1!";

            while(input.peek()!='\n') {
                if(input.eof()) break;
                input >> pom;

                if(pom > cols) throw "Neispravan unos!";

                maze[i][pom-1] = maze[i+1][pom-1] = 0; /// This is where we found a pass, we will only store the points right above the path
                passes.push_back(pass = make_pair(i-1, pom-1));

//                if(maze[i][pom-2]!=0) { /// If the left point is a wall
//                    passes.push_back(pass = make_pair(i-1, pom-1));
//                } else { /// Left is not a wall but we are still at a pass TODO
//                    if(maze[pass.first+1][pass.second-1]!=0) {
//                        pass = passes.back();
//                        passes.pop_back();
//                        pass.second++;
//                        passes.push_back(pass);
//                    } else {
//
//                    }
//                }

                if(input.peek()==',') input.get();
            }
            if(!input.eof()) input.get();

        } else {
            maze[i].resize(cols);
        }
    }

    if(!input.eof()) throw "Neispravan format fajla2!";

    input.close();
}


/**************************************************** UTILITY ****************************************************/
int Maze::mazeRow(char letter) {
    if(letter < 'A' || letter > 'Z') throw "Neispravan unos slova!";

    if(letter%2!=0) {
        return (int(letter)-int('A'))*2;
    } else return (int(letter)-int('B'))*2 +3;
}

bool Maze::isValid(point current) {
    if(current.first < 0 || current.first >= maze.size() || current.second < 0 || current.second >= maze[0].size()) return false;
    else if(maze[current.first][current.second] == 0) return true;
    else return false;
}

int Maze::distance(point x, point y) {
    return abs(x.first - y.first) + abs(x.second - y.second);
}

void Maze::printMaze() {
    int brojKolona = maze[0].size();

    int brojCifara = 0;
    while(brojKolona > 0){
        brojKolona /= 10;
        brojCifara++;
    }
    brojCifara++;

    int k=0, pom=0;
    for(int i=0; i<maze.size(); i++) {
        if(i==(4*k-1)) {
            cout << char(int('A') + pom++) << " ";
        }

        else if(i==(4*k)) {
            cout << char(int('A') + pom++) << " ";
            k++;
        }
        else cout << "  ";

        for(int j=0; j<maze[i].size(); j++) {
            if(maze[i][j] != 0) cout << setw(brojCifara) << maze[i][j];
            else cout << setw(brojCifara) << "-";
        }
        cout << endl;
    }

}

/**************************************************** NOT NEEDED ****************************************************/
void Maze::printPasses() {
    for(auto it=passes.begin(); it!=passes.end(); it++) cout << it->first << ", " << it->second << endl;
}

/**************************************************** ALGORITHMS ****************************************************/
/**************************************************** BFS, O(V^2)****************************************************/
int Maze::shortestDistanceBFS(char firstWall, int firstPosition, char secondWall, int secondPosition) {

    int pos = ((pos = mazeRow(firstWall))%2 == 0) ? pos+1 : pos-1 ;
    point x = make_pair(pos, firstPosition-1);
    pos = ((pos = mazeRow(secondWall))%2 == 0) ? pos+1 : pos-1 ;
    point y = make_pair(pos, secondPosition-1);

    queue<point> nodes; /// Polja koja treba obraditi
    vector<vector<int> > visited(maze.size()); /// Matrica u kojoj polje nije obidjeno ako je vrijednost na poziciji jednako nuli, svaki drugi broj\
                                                predstavlja najkracu udaljenost od pocetnog cvora

    for(int i=0; i<visited.size(); i++) visited[i].resize(maze[i].size(), 0);

    nodes.push(x);
    visited[x.first][x.second] = 1;
    point current;

    while(!nodes.empty()) {
        current = nodes.front();
        nodes.pop();

        if(current == y) break; /// Za ovaj cvor je vec obradjena udaljenost od pocetnog cvora
        point pom;

        if(isValid(pom = make_pair(current.first+1, current.second)) && visited[pom.first][pom.second]==0) {
            nodes.push(pom);
            visited[pom.first][pom.second] = visited[current.first][current.second] + 1;
        }
        if(isValid(pom = make_pair(current.first-1, current.second)) && visited[pom.first][pom.second]==0) {
            nodes.push(pom);
            visited[pom.first][pom.second] = visited[current.first][current.second] + 1;
        }
        if(isValid(pom = make_pair(current.first, current.second+1)) && visited[pom.first][pom.second]==0) {
            nodes.push(pom);
            visited[pom.first][pom.second] = visited[current.first][current.second] + 1;
        }
        if(isValid(pom = make_pair(current.first, current.second-1)) && visited[pom.first][pom.second]==0) {
            nodes.push(pom);
            visited[pom.first][pom.second] = visited[current.first][current.second] + 1;
        }
    }

    return visited[current.first][current.second];
}

/**************************************************** A*, O(?)****************************************************/
int Maze::shortestDistance(char firstWall, int firstPosition, char secondWall, int secondPosition) {

    point x, y;
    int pom;
    x.second = firstPosition-1; /// Indeksiranje krece od 0
    y.second = secondPosition-1;
    x.first = ((pom = mazeRow(firstWall))%2) ? pom-1 : pom+1; /// Ako se slovo nalazi u neparnom redu onda joj se \
                                                                  moze prici samo sa gornje strane inace sa donje strane
    if(!maze[pom][x.second] || x.second < 0 || x.second >= maze[pom].size()) throw "Polje nije zid!";
    y.first = ((pom = mazeRow(secondWall))%2) ? pom-1 : pom+1;
    if(!maze[pom][y.second] || y.second < 0 || y.second >= maze[pom].size()) throw "Polje nije zid!";

    if(firstWall > secondWall) {
        point z = x;
        x = y;
        y = z;
//        cout << x.first << ", " << x.second << "; " << y.first << ", " << y.second << endl;
    } /// The rest works with x as the higher of the two points

    auto it = passes.begin();
    for(it; it->first < x.first; it++) {}
//    cout << it->first << ", " << it->second << endl;

    vector<list<point> > adjacent;
    vector<list<int> > distances;
    adjacent.push_back(list<point> {});
    distances.push_back(list<int> {});
    int position = it->first;
    int level = 0;

    for(it; it!=passes.end() && it->first < y.first; it++) {
        if(it->first == position) {
            adjacent[level].push_back(*it);
            if(level == 0){
                distances[level].push_back(distance(*it, x));
            }
            else{
                int minDistance = INT_MAX;
                auto pomIt = distances[level-1].begin();
                for(auto it2 = adjacent[level-1].begin(); it2 != adjacent[level - 1].end(); it2++){
                    minDistance = min(distance(*it2, *it) + *pomIt, minDistance);
                    pomIt++;
                }
                distances[level].push_back(minDistance);
            }
        } else {
            position = it->first;
            level++;
            adjacent.push_back(list<point> {});
            distances.push_back(list<int> {});
            adjacent[level].push_back(*it);
            int minDistance = INT_MAX;
            auto pomIt = distances[level-1].begin();
            for(auto it2 = adjacent[level-1].begin(); it2 != adjacent[level - 1].end(); it2++){
                minDistance = min(distance(*it2, *it) + *pomIt, minDistance);
                pomIt++;
            }
            distances[level].push_back(minDistance);
        }
    }
//
    for(int i=0; i<distances.size(); i++) {
        for(auto it=distances[i].begin(); it!=distances[i].end(); it++) {
            cout << *it << "; ";
        }
        cout << endl;
    }

    int minDistance = INT_MAX;
    int lastLevel = adjacent.size() - 1;
    auto pomIt = distances[lastLevel].begin();
    for(auto it = adjacent[lastLevel].begin(); it != adjacent[lastLevel].end(); it++){
        minDistance = min(distance(*it, y) + *pomIt, minDistance);
        pomIt++;
    }


    if(adjacent[0].size() == 0)
        return distance(x, y) + 1;

    return minDistance + 1;
}


#endif // PROJECT_H
