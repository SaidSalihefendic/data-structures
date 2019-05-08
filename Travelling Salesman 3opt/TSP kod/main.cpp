#include <iostream>
#include "graf.h"
#include <string>
using namespace std;

int main() {

    clock_t t;
    vector<int> tura;
    int duzina;

    string filename("djibouti.txt");
    Graf G(filename);
    cout << endl << "------------------------------------" << endl << endl;
    cout << "<<<-- Travelling Salesman Problem - Greedy algoritmi i heuristike -->>>" << endl;
    cout << endl << "------------------------------------" << endl << endl;

    cout << "<<<< TURA POREDAK >>>>" << endl << endl;
        //TURA POREDAK
    t = clock();
    duzina = G.turaPoredak();
    t = clock() - t;
    cout << "Normalna: " << duzina << " | " << (float(t)) / CLOCKS_PER_SEC << "s" << endl;

    tura = G.vratiTuruPoredak();
    t = clock();
    duzina = G.dvaOpt(tura);
    t = clock() - t;
    cout << "2opt: " << duzina << " | " << (float(t)) / CLOCKS_PER_SEC << "s" << endl;

    tura = G.vratiTuruPoredak();
//    cout << "Provjera: " << G.duzinaTure(tura) << endl;
    t = clock();
    duzina = G.triOpt(tura);
    t = clock() - t;
    cout << "3opt bez 2opt: " << duzina << " | " << (float(t)) / CLOCKS_PER_SEC << "s" << endl;

    tura = G.vratiTuruPoredak();
//    cout << "Provjera: " << G.duzinaTure(tura) << endl;
    tura = G.vratiTuruSaDvaOpt(tura);
//    cout << "Provjera: " << G.duzinaTure(tura) << endl;
    t = clock();
    duzina = G.triOpt(tura);
    t = clock() - t;
    cout << "3opt sa 2opt: " << duzina << " | " << (float(t)) / CLOCKS_PER_SEC << "s" << endl;

    cout << endl << "------------------------------------" << endl << endl;
    cout << "<<<< TURA NAJBLIZI SUSJED >>>>" << endl << endl;

    t = clock();
    duzina = G.turaNajbliziSusjed();
    t = clock() - t;
    cout << "Normalna: " << duzina << " | " << (float(t)) / CLOCKS_PER_SEC << "s" << endl;

    tura = G.vratiTuruNajbliziSusjed(0);
    t = clock();
    duzina = G.dvaOpt(tura);
    t = clock() - t;
    cout << "2opt: " << duzina << " | " << (float(t)) / CLOCKS_PER_SEC << "s" << endl;

    tura = G.vratiTuruNajbliziSusjed(0);
//    cout << "Provjera: " << G.duzinaTure(tura) << endl;
    t = clock();
    duzina = G.triOpt(tura);
    t = clock() - t;
    cout << "3opt bez 2opt: " << duzina << " | " << (float(t)) / CLOCKS_PER_SEC << "s" << endl;

    tura = G.vratiTuruNajbliziSusjed(0);
//    cout << "Provjera: " << G.duzinaTure(tura) << endl;
    tura = G.vratiTuruSaDvaOpt(tura);
//    cout << "Provjera: " << G.duzinaTure(tura) << endl;
    t = clock();
    duzina = G.triOpt(tura);
    t = clock() - t;
    cout << "3opt sa 2opt: " << duzina << " | " << (float(t)) / CLOCKS_PER_SEC << "s" << endl;

    cout << endl << "------------------------------------" << endl << endl;
    cout << "<<<< TURA NAJMANJA GRANA >>>>" << endl << endl;

    t = clock();
    duzina = G.turaNajmanjaGrana();
    t = clock() - t;
    cout << "Normalna: " << duzina << " | " << (float(t)) / CLOCKS_PER_SEC << "s" << endl;

    tura = G.vratiTuruNajmanjaGrana();
    t = clock();
    duzina = G.dvaOpt(tura);
    t = clock() - t;
    cout << "2opt: " << duzina << " | " << (float(t)) / CLOCKS_PER_SEC << "s" << endl;

    tura = G.vratiTuruNajmanjaGrana();
//    cout << "Provjera: " << G.duzinaTure(tura) << endl;
    t = clock();
    duzina = G.triOpt(tura);
    t = clock() - t;
    cout << "3opt bez 2opt: " << duzina << " | " << (float(t)) / CLOCKS_PER_SEC << "s" << endl;

    tura = G.vratiTuruNajmanjaGrana();
//    cout << "Provjera: " << G.duzinaTure(tura) << endl;
    tura = G.vratiTuruSaDvaOpt(tura);
//    cout << "Provjera: " << G.duzinaTure(tura) << endl;
    t = clock();
    duzina = G.triOpt(tura);
    t = clock() - t;
    cout << "3opt sa 2opt: " << duzina << " | " << (float(t)) / CLOCKS_PER_SEC << "s" << endl;

    cout << endl << "------------------------------------" << endl << endl;

    cout << "<<<< RANDOM TURA >>>>" << endl << endl;
    vector<int> random = G.vratiRandomTuru();
    t = clock();
    duzina = G.duzinaTure(random);
    t = clock() - t;
    cout << "Normalna: " << duzina << " | " << (float(t)) / CLOCKS_PER_SEC << "s" << endl;

    tura = random;
    t = clock();
    duzina = G.dvaOpt(tura);
    t = clock() - t;
    cout << "2opt: " << duzina << " | " << (float(t)) / CLOCKS_PER_SEC << "s" << endl;

    tura = random;
//    cout << "Provjera: " << G.duzinaTure(tura) << endl;
    t = clock();
    duzina = G.triOpt(tura);
    t = clock() - t;
    cout << "3opt bez 2opt: " << duzina << " | " << (float(t)) / CLOCKS_PER_SEC << "s" << endl;

    tura = random;
//    cout << "Provjera: " << G.duzinaTure(tura) << endl;
    tura = G.vratiTuruSaDvaOpt(tura);
//    cout << "Provjera: " << G.duzinaTure(tura) << endl;
    t = clock();
    duzina = G.triOpt(tura);
    t = clock() - t;
    cout << "3opt sa 2opt: " << duzina << " | " << (float(t)) / CLOCKS_PER_SEC << "s" << endl;

    cout << endl << "------------------------------------" << endl << endl;


    return 0;
}
