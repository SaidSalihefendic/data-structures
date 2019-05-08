#ifndef PROJECT_H
#define PROJECT_H

#include <iostream>
#include <string>
#include <fstream>
#include <utility>
#include <cmath>
#include <iomanip>

#include <queue>
#include <vector>
#include <list>
#include <algorithm>
using namespace std;

typedef pair<int, int> point;
class Maze {
private:
    vector<vector<int> > maze; /// Matrix that represents the input maze
    list<point> passes; /// List of all passes in the graph

    int mazeRow(char letter); /// Function which returns the matrix row that can be accessed be the letter
    bool isValid(point current); /// Function that returns true if the position in the matrix is not out of bounds nor is a wall

    void dvaOptZamjena(vector<int>& tura, int i, int j);
    void triOptZamjena(int tip, vector<int>& tura, int i, int j, int k);
    int duzinaTure(vector<int>& tura, vector<string>& initialTour);

public:
    Maze(string fileName);
    Maze();
    void printMaze(); /// Prints the input maze

    int shortestDistance(char firstWall, int firstPosition, char secondWall, int secondPosition); /// Returns the minimum distance using modified algorithm
    int shortestDistanceBFS(char firstWall, int firstPosition, char secondWall, int secondPosition); /// Returns the minimum distance from point x to point y using BFS
    int shortestDistanceModified(char firstWall, int firstPosition, char secondWall, int secondPosition);
    int distance(point x, point y); /// Manhattan distance d((x,y),(a,b)) = |x-a|+|y-b|
    bool isValidField(char wall, int position); /// Returns if it is a valid field/point in the maze. We define a valid field that such it is accessible to the wall from that position from above or below, depending on the side of the wall

    void printPasses(); /// FOR PRESENTATION PURPOSE

    int bestTour(vector<string>& initialTour);

    int dvaOpt(vector<int>& tura, vector<string>& initialTour);
    int triOpt(vector<int>& tura, vector<string>& initialTour);

};


/**************************************************** CONSTRUCTORS ****************************************************/
Maze::Maze() {};

Maze::Maze(string fileName) {
    int rows, cols;
    ifstream input(fileName);

    input >> rows;
    if(rows == 0) {
        input.close();
        return; /// Check
    }

    input.get();
    input >> cols;
    input.get();

    if(rows % 2) throw "Broj kolona mora biti paran broj!";
    else if(rows < 0 || rows > 26) throw "Broj kolona mora biti u rasponu [0-26]!";

    maze.resize(2*rows);
    vector<int> util;
    util.resize(cols, 0);
    maze[1] = maze[2] = util;

    for(int i=0; i<cols; i++) util[i] = i+1;

    int k=-2;
    int pom;

    maze[0] = util;

    for(int i=3; i<2*rows; i+=4) {
        if(i==2*rows-1) {
            maze[i] = util;
        } else {
            maze[i] = maze[i+1] = util;
            maze[i+2] = maze[i+3] = maze[1];

            while(input.peek()!='\n') {
                if(input.eof()) break;
                input >> pom;

                if(input.peek()==',') input.get();

                if(pom > cols) throw "Neispravan unos!";

                maze[i][pom-1] = maze[i+1][pom-1] = 0; /// This is where we found a pass, we will only store the points right above the path
//                passes.push_back(pass = make_pair(i+2, pom-1));
                if(maze[i][pom-2]!=0) { /// If the left point is a wall
                    passes.push_back(make_pair(i+2, pom-1));
                } else { /// Left is not a wall but we are still at a pass
                    if(maze[i][pom-3]!=0) { /// Path with width 2 for example
                        passes.push_back(make_pair(i+2, pom-1));
                    } else { /// Path with width 3 or more
                        passes.pop_back();
                        passes.push_back(make_pair(i+2, pom-1));
                    }
                }
            }
            if(!input.eof()) input.get();
        }
    }

    input.close();
}

/**************************************************** UTILITY ****************************************************/

bool Maze::isValidField(char wall, int position){
    return !(wall < 'A' || mazeRow(wall) >= maze.size() || position - 1 >= maze[0].size() || position - 1 < 0 || maze[mazeRow(wall)][position - 1] != 0);
}

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
    int cols = maze[0].size();

    int num = 0;
    while(cols > 0){
        cols /= 10;
        num++;
    }
    num++;

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
            if(maze[i][j] != 0) cout << setw(num) << maze[i][j];
            else cout << setw(num) << "-";
        }
        cout << endl;
    }

}


void Maze::printPasses() {
    for(auto it=passes.begin(); it!=passes.end(); it++) cout << "(" << it->first << ", " << it->second << ")" << endl;
    cout << endl;
}

/**************************************************** ALGORITHMS ****************************************************/
/**************************************************** BFS, O(V^2)****************************************************/
int Maze::shortestDistanceBFS(char firstWall, int firstPosition, char secondWall, int secondPosition) {
    if(secondWall < firstWall)
        return shortestDistanceBFS(secondWall, secondPosition, firstWall, firstPosition);
    if(firstWall < 'A' || mazeRow(firstWall) >= maze.size() || firstPosition - 1 >= maze[0].size() || firstPosition - 1 < 0)
        throw "Invalid first field!";
    else if(secondWall < 'A' || mazeRow(secondWall) >= maze.size() || secondPosition - 1 >= maze[0].size() || secondPosition - 1 < 0)
        throw "Invalid second field!";

    int pos = ((pos = mazeRow(firstWall))%2 == 0) ? pos+1 : pos-1 ;
    point x = make_pair(pos, firstPosition-1);
    pos = ((pos = mazeRow(secondWall))%2 == 0) ? pos+1 : pos-1 ;
    point y = make_pair(pos, secondPosition-1);

    queue<point> nodes; /// Fields in process
    vector<vector<int> > visited(maze.size()); /// Table that has a double roll, it is checked if it has a distance stored in that particular field, else it is 0 and can visit only where it is not a wall

    for(int i=0; i<visited.size(); i++) visited[i].resize(maze[i].size(), 0);

    nodes.push(x);
    visited[x.first][x.second] = 1;
    point current;

    while(!nodes.empty()) {
        current = nodes.front();
        nodes.pop();

        if(current == y) break; /// Already calculated path length
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

/************************************************ MODIFIED ALGORITHM ***************************************************/

int Maze::shortestDistanceModified(char firstWall, int firstPosition, char secondWall, int secondPosition){
    if(secondWall < firstWall)
        return shortestDistanceModified(secondWall, secondPosition, firstWall, firstPosition);

    if(isValidField(firstWall, firstPosition))
        throw "Invalid first field!";

    if(isValidField(secondWall, secondPosition))
        throw "Invalid second field!";

        ///We need to test the valid points in the maze, for example, a wall cannot be '?' or anything that is not in [A-Z]
    queue<pair<point, int> > q; ///This queue holds the pair of the points we want to visit. Idea came from fusing Dijkstra and BFS
    int pos = ((pos = mazeRow(firstWall))%2 == 0) ? pos+1 : pos-1 ;
    point beginningPoint = make_pair(pos, firstPosition-1);
    pos = ((pos = mazeRow(secondWall))%2 == 0) ? pos+1 : pos-1 ;
    point endPoint = make_pair(pos, secondPosition-1);

    int maxLevel = pos;
        ///We need to be careful where we need to begin with the iterator
    auto it = passes.begin();
    auto prev = passes.begin();
    while(it->first <= beginningPoint.first)
        prev = it++;
    int currLevel = it->first;

    int currDistance;
    q.push(make_pair(beginningPoint, 1));

    pair<point, int> currField;
    point currPoint;
    while(!q.empty()){
            ///We need a helper variable in case of multiple pairs with the same field, but different distances
        currField = q.front();
        currLevel = currField.first.first + 4;
        currLevel = (currLevel % 2 == 0) ? currLevel - 1 : currLevel;
        if(currLevel > maxLevel)
            break;
//        cout << "((" << currField.first.first << ", " << currField.first.second << "), " << currField.second << "); ";
        q.pop();

        while(((it->first == currLevel && it->second < currField.first.second) || it->first < currLevel) && it != passes.end())
            prev = it++;

        if(maze[currField.first.first+2][currField.first.second] == 0)
            q.push(make_pair(make_pair(currLevel, currField.first.second), currField.second + currLevel - currField.first.first));
            //first case, sink down TODO: Need aditional condition on to find the sinkhole, iterators are not enough, use maze?
        if(q.back().first != (*it) && (it->first == currLevel && it->second == currField.first.second))
            q.push(make_pair(*it, distance(currField.first, *it) + currField.second));

            //second case, has only one pass or only left passes
        else if((prev->first == currLevel && prev->first < it->first) || it == passes.begin())
            q.push(make_pair(*prev, distance(currField.first, *prev) + currField.second));

            //third case, has only one pass on the right
        else if(prev->first != currLevel || it == passes.begin())
            q.push(make_pair(*it, distance(currField.first, *it) + currField.second));
            //fourth case, general case
        else if(it != passes.end()){
            q.push(make_pair(*prev, distance(currField.first, *prev) + currField.second));
            q.push(make_pair(*it, distance(currField.first, *it) + currField.second));
        }
    }//end while

    int shortest = INT_MAX;
    while(!q.empty()){
//        cout << "((" <<  q.front().first.first << ", " << q.front().first.second << "), " << q.front().second << "); ";
        shortest = min(shortest, distance(q.front().first, endPoint) + q.front().second);
        q.pop();
    }//end while

    return shortest;
}

///-----------------------------------<< Duzina ture >>---------------------------------------///

int Maze::duzinaTure(vector<int>& tura, vector<string>& initialTour) {
    int duzina_ture = 0;
    int n = tura.size();
    for(int i=0; i < n; i++)
        duzina_ture += shortestDistanceModified(initialTour[tura[i]][0], int(initialTour[tura[i]][1] - '0'), initialTour[tura[(i + 1) % n]][0], int(initialTour[tura[(i + 1) % n]][1] - '0'));

    return duzina_ture;
}

///-----------------------------------<< DVA OPT ZAMJENA >>---------------------------------------///

void Maze::dvaOptZamjena(vector<int>& tura, int i, int j){
    reverse(tura.begin() + i, tura.begin() + j + 1);
}

///--------------------------------------<< DVA OPT >>---------------------------------------///

int Maze::dvaOpt(vector<int>& tura, vector<string>& initialTour){
    vector<int> pomocna = tura;
    int n = tura.size();

    int najmanjaUdaljenost = duzinaTure(tura, initialTour);
    int pomocnaUdaljenost = 0;
    bool poboljsanje = true;

    while(poboljsanje){
        poboljsanje = false;
        for(int i = 0; i < n - 1; i++){
            for(int j = i + 1; j < n; j++){
                dvaOptZamjena(pomocna, i, j);
                pomocnaUdaljenost = duzinaTure(pomocna, initialTour);
                if(pomocnaUdaljenost < najmanjaUdaljenost){
                    tura = pomocna;
                    najmanjaUdaljenost = pomocnaUdaljenost;
                    poboljsanje = true;
                }// end if
                else
                    pomocna = tura;
            }// end for j
        }// end for i
    }//end while

    return najmanjaUdaljenost;
}

///--------------------------------------<< TRI OPT ZAMJENA >>---------------------------------------///


void Maze::triOptZamjena(int tip, vector<int>& tura, int i, int j, int k){
    switch(tip){
    case 1:
//        cout << "Pozvan 1" << endl;
        dvaOptZamjena(tura, i + 1, j);
        dvaOptZamjena(tura, j + 1, k);
        break;
    case 2:
//        cout << "Pozvan 2" << endl;
        dvaOptZamjena(tura, i + 1, k);
        dvaOptZamjena(tura, i + 1, i + 1 + k - j);
        dvaOptZamjena(tura, i + 1 + k - j, k);
        break;
    case 3:
//        cout << "Pozvan 3" << endl;
        dvaOptZamjena(tura, i + 1, k);
        dvaOptZamjena(tura, i + 1, i + 1 + k - j);
        break;
    case 4:
//        cout << "Pozvan 4" << endl;
        dvaOptZamjena(tura, i + 1, k);
        dvaOptZamjena(tura, i + 1 + k - j, k);
        break;
    }
}

///--------------------------------------<< TRI OPT >>---------------------------------------///


int Maze::triOpt(vector<int>& tura, vector<string>& initialTour){
    vector<int> pomocna = tura;

    int najmanjaUdaljenost = duzinaTure(tura, initialTour);
    int pomocnaUdaljenost = 0;
    bool poboljsanje = true;
    int n = tura.size();

    clock_t pocetak;
    pocetak = clock();
    double sekunde;

    while(poboljsanje){
        poboljsanje = false;
        for(int i = 0; i < n - 3; i++){
            for(int j = i + 1; j < n - 2; j++){
                for(int k = j + 1; k < n - 1; k++){
                    dvaOptZamjena(pomocna, j + 1, k);
                    pomocnaUdaljenost = duzinaTure(pomocna, initialTour);

                    if(pomocnaUdaljenost < najmanjaUdaljenost){
                        najmanjaUdaljenost = pomocnaUdaljenost;
                        tura = pomocna;
                        poboljsanje = true;
                    }// end if
                    else
                        pomocna = tura; ///

                    dvaOptZamjena(pomocna, i + 1, j);
                    pomocnaUdaljenost = duzinaTure(pomocna, initialTour);

                    if(pomocnaUdaljenost < najmanjaUdaljenost){
                        najmanjaUdaljenost = pomocnaUdaljenost;
                        tura = pomocna;
                        poboljsanje = true;
                    }// end if
                    else
                        pomocna = tura; ///

                    triOptZamjena(1, pomocna, i, j, k);
                    pomocnaUdaljenost = duzinaTure(pomocna, initialTour);

                    if(pomocnaUdaljenost < najmanjaUdaljenost){
                        najmanjaUdaljenost = pomocnaUdaljenost;
                        tura = pomocna;
                        poboljsanje = true;
                    }// end if
                    else
                        pomocna = tura; ///

                    triOptZamjena(2, pomocna, i, j, k);
                    pomocnaUdaljenost = duzinaTure(pomocna, initialTour);

                    if(pomocnaUdaljenost < najmanjaUdaljenost){
                        najmanjaUdaljenost = pomocnaUdaljenost;
                        tura = pomocna;
                        poboljsanje = true;
                    }// end if
                    else
                        pomocna = tura; ///

                    triOptZamjena(3, pomocna, i, j, k);
                    pomocnaUdaljenost = duzinaTure(pomocna, initialTour);

                    if(pomocnaUdaljenost < najmanjaUdaljenost){
                        najmanjaUdaljenost = pomocnaUdaljenost;
                        tura = pomocna;
                        poboljsanje = true;
                    }// end if
                    else
                        pomocna = tura; ///

                    triOptZamjena(4, pomocna, i, j, k);
                    pomocnaUdaljenost = duzinaTure(pomocna, initialTour);

                    if(pomocnaUdaljenost < najmanjaUdaljenost){
                        najmanjaUdaljenost = pomocnaUdaljenost;
                        tura = pomocna;
                        poboljsanje = true;
                    }// end if
                    else
                        pomocna = tura; ///

                    dvaOptZamjena(pomocna, i + 1, k);
                    pomocnaUdaljenost = duzinaTure(pomocna, initialTour);

                    if(pomocnaUdaljenost < najmanjaUdaljenost){
                        najmanjaUdaljenost = pomocnaUdaljenost;
                        tura = pomocna;
                        poboljsanje = true;
                    }// end if
                    else
                        pomocna = tura; ///

                    sekunde = (clock() - pocetak) / double(CLOCKS_PER_SEC);


                    if(sekunde > 1800){
                        return najmanjaUdaljenost;
                    }//end if
                }// end for k
            }// end for j
        }// end for i
    }//end while

    return najmanjaUdaljenost;
}


int Maze::bestTour(vector<string>& initialTour){
    vector<int> tura(initialTour.size());
    for(int i = 0; i < tura.size(); i++)
        tura[i] = i;

    cout << "Inicijalna tura: ";
    for(int i = 0; i < tura.size(); i++)
        cout << initialTour[i] << " ";
    cout << endl << "Duzina inicijalne ture: " << duzinaTure(tura, initialTour) << endl << endl;


    triOpt(tura, initialTour);
        //Calculating total distance for the resulting tour in terms of the initial tour given in the argument
    int duzina =  duzinaTure(tura, initialTour);

        //Printing the final tour
    vector<string> finalTour;
    for(int i = 0; i < tura.size(); i++)
        finalTour.push_back(initialTour[tura[i]]);
    initialTour = finalTour;

    cout << "Konacna tura: ";
    for(int i = 0; i < tura.size(); i++)
        cout << finalTour[i] << " ";
    cout << endl << "Duzina inicijalne ture: " << duzina << endl << endl;

    return duzina;
}

#endif // PROJECT_H
