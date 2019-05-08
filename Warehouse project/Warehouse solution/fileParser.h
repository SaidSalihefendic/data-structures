//#ifndef FILEPARSER_H
//#define FILEPARSER_H
//
//#include <fstream>
//#include <iostream>
//#include <string>
//#include <vector>
//using namespace std;
//
//vector<vector<int> > parseFile(string fileName) {
//
//    string helper;
//    int rows, cols;
//
//    ifstream input(fileName);
//
//    input >> rows;
//    input.get();
//    input >> cols;
//    input.get();
//
//    if(rows % 2) throw "Broj kolona mora biti paran broj!";
//    else if(rows < 0 || rows > 26) throw "Broj kolona mora biti u rasponu [0-26]!";
//
//    vector<vector<int> > maze(2*rows);
//    vector<int> util;
//
//    for(int i=1; i<=cols; i++) util.push_back(i);
//
//    int k=0;
//    int pom;
//
//    for(int i=0; i<2*rows; i++) {
//        if(i==0 || i==2*rows-1) {
//            maze[i] = util;
//
//        } else if(i==(4*k+3)) {
//            maze[i] = maze[i+1] = util;
//            k++;
//
//            if(input.eof() || input.peek()=='\n' || input.peek()==-1) throw "Neispravan format fajla1!";
//
//            while(input.peek()!='\n') {
//                if(input.eof()) break;
//                input >> pom;
//
//                if(pom > cols) throw "Neispravan unos!";
//
//                maze[i][pom-1] = maze[i+1][pom-1] = 0;
//
//                if(input.peek()==',') input.get();
//            }
//            if(!input.eof()) input.get();
//
//        } else {
//            maze[i].resize(cols);
//        }
//    }
//
//    if(!input.eof()) throw "Neispravan format fajla2!";
//
//    input.close();
//    return maze;
//}
//
//#endif // FILEPARSER_H
//
