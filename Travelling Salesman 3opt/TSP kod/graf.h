#ifndef GRAF_H
#define GRAF_H
#include "grad.h"
#include "binarni.h"
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <climits>
#include <algorithm>
#include <cmath>
#include <ctime>
#include <cstdlib>

using namespace std;

class Graf {

    struct Grana {
        int tezina;
        int pocetak;
        int kraj;
        Grana(int tezina, int pocetak, int kraj):tezina(tezina),pocetak(pocetak),kraj(kraj) {}
        bool operator<(Grana druga) { return tezina<druga.tezina; }
    };

    int n;
    vector <Grad> gradovi;
    vector <vector <int> > udaljenosti;
    vector<Grana> grane;


    void ispisiTuru(vector<int>& tura);
    bool provjeriTuru(vector<int>& tura);
    int udaljenost(double x1, double y1, double x2, double y2) {
        return round(sqrt((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1)));
    }

    void dvaOptZamjena(vector<int>& tura, int i, int j);
    void triOptZamjena(int tip, vector<int>& tura, int i, int j, int k);

public:
    Graf(string filename);
    int turaNajbliziSusjed();
    int turaNajmanjaGrana();
    int turaPoredak();
    int duzinaTure(vector<int>& tura);

        //KONKRETNE TURE
    vector<int> vratiTuruNajbliziSusjed(int pocetni);
    vector<int> vratiTuruNajmanjaGrana();
    vector<int> vratiTuruPoredak();
    vector<int> vratiTuruSaDvaOpt(vector<int> tura);
    vector<int> vratiRandomTuru();

    int dvaOpt(vector<int>& tura);
    int triOpt(vector<int>& tura);
};

///-----------------------------------<< KONSTRUKTOR >>---------------------------------------///

Graf::Graf(string filename) {
    ifstream unos(filename);
    while(!unos.eof()) {
        int indeks;
        double latitude;
        double longitude;
        unos>>indeks;
        unos.get();
        unos>>latitude;
        unos.get();
        unos>>longitude;
        unos.get();
        gradovi.push_back(Grad(indeks,latitude,longitude));
    }// end while
    unos.close();

    n = gradovi.size();
    udaljenosti.resize(n);
    for(int i=0;i<n;i++)
        udaljenosti[i].resize(n);
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++) {
            udaljenosti[i][j] = udaljenost(gradovi[i].latitude,gradovi[i].longitude,gradovi[j].latitude,gradovi[j].longitude);
            if(i<j)
                grane.push_back(Grana(udaljenosti[i][j],i,j));
        }// end for j
}

///-----------------------------------<< RACUNANJE DUZINE TURE >>---------------------------------------///

int Graf::duzinaTure(vector<int>& tura) {
    int duzina_ture = 0;
    for(int i=0;i<tura.size();i++)
        duzina_ture += udaljenosti[tura[i]][tura[(i+1)%n]];
    return duzina_ture;
}

///-----------------------------------<< ISPIS TURE >>---------------------------------------///

void Graf::ispisiTuru(vector<int>& tura) {
    for(int i=0;i<tura.size();i++)
        cout<<tura[i]<<" ";
    cout<<endl;
}

///-----------------------------------<< PROVJERA VALIDNOSTI TURE >>---------------------------------------///

bool Graf::provjeriTuru(vector<int>& tura) {
    vector<bool> posjecen(n,false);
    if(tura.size() != n)
        return false;
    else {
        for(int i=0;i<n;i++) {
            if(tura[i]<0 || tura[i]>=n || posjecen[tura[i]] == true)
                return false;
            else posjecen[tura[i]] = true;
        }// end for i
    }// end else

    return true;
}

///-----------------------------------<< TURA NAJBLIZI SUSJED >>---------------------------------------///

int Graf::turaPoredak(){
    vector<int> tura;
    for(int i = 0; i < n; i++){
        tura.push_back(i);
    }

    return duzinaTure(tura);
}

///-----------------------------------<< TURA NAJBLIZI SUSJED >>---------------------------------------///

vector<int> Graf::vratiTuruPoredak(){
    vector<int> tura;
    for(int i = 0; i < n; i++){
        tura.push_back(i);
    }

    return tura;
}

///-----------------------------------<< TURA NAJBLIZI SUSJED >>---------------------------------------///

int Graf::turaNajbliziSusjed() {
    vector<int> tura;
    int pocetni = 0;
    vector<bool> posjecen(n,false);
    posjecen[pocetni] = true;
    tura.push_back(pocetni);
    for(int i=0;i<n-1;i++) {
        int trenutni = tura[tura.size()-1];
        int udaljenostNajblizeg = INT_MAX;
        int najblizi;
        for(int j=0;j<n;j++) {
            if(!posjecen[j] && udaljenosti[trenutni][j] < udaljenostNajblizeg) {
                udaljenostNajblizeg = udaljenosti[trenutni][j];
                najblizi = j;
            }// end if
        }// end for j
        posjecen[najblizi] = true;
        tura.push_back(najblizi);
    }// end for i

    //ispisiTuru(tura);
    if(provjeriTuru(tura))
        return duzinaTure(tura);
    else throw "Greska";
}

///-----------------------------------<< TURA NAJMANA GRANA >>---------------------------------------///

int Graf::turaNajmanjaGrana() {
    Ruta ruta(n);
    sort(grane.begin(),grane.end());
    vector<int> stepeni(n,0);
    int trenutna = 0;
    for(int i=0;i<n-1;i++) {
        while(true) {
            Grana trenutnaGrana = grane[trenutna];
            int pocetak = trenutnaGrana.pocetak;
            int kraj = trenutnaGrana.kraj;
            if(stepeni[pocetak] == 2 || stepeni[kraj] == 2) {
                trenutna++;
            continue;
            }// end if

            ruta.dodajGranu(pocetak,kraj);
            if(ruta.imaLiCiklusa(pocetak)) {
                ruta.obrisiGranu(pocetak,kraj);
                trenutna++;
                continue;
            }//end if
            else{
                stepeni[pocetak]++;
                stepeni[kraj]++;
                trenutna++;
                break;
            }//end else
        }//end while
    }//end for

    vector<int> tura = ruta.vratiTuru();
    //ispisiTuru(tura);

    if(provjeriTuru(tura))
        return duzinaTure(tura);
    else throw "Greska";
}

///-----------------------------<< VEKTOR TURE NAJBLIZI SUSJED >>---------------------------------------///

vector<int> Graf::vratiTuruNajbliziSusjed(int pocetni){
    vector<int> tura;
    vector<bool> posjecen(n,false);
    posjecen[pocetni] = true;
    tura.push_back(pocetni);
    for(int i=0;i<n-1;i++) {
        int trenutni = tura[tura.size()-1];
        int udaljenostNajblizeg = INT_MAX;
        int najblizi;
        for(int j=0;j<n;j++) {
            if(!posjecen[j] && udaljenosti[trenutni][j] < udaljenostNajblizeg) {
                udaljenostNajblizeg = udaljenosti[trenutni][j];
                najblizi = j;
            }// end if
        }// end for j
        posjecen[najblizi] = true;
        tura.push_back(najblizi);
    }// end for i

    //ispisiTuru(tura);
    if(provjeriTuru(tura))
        return tura;
    else throw "Greska";
}

///-----------------------------<< VEKTOR TURE NAJMANJA GRANA >>---------------------------------------///

vector<int> Graf::vratiTuruNajmanjaGrana(){
    Ruta ruta(n);
    sort(grane.begin(),grane.end());
    vector<int> stepeni(n,0);
    int trenutna = 0;
    for(int i=0;i<n-1;i++) {
        while(true) {
            Grana trenutnaGrana = grane[trenutna];
            int pocetak = trenutnaGrana.pocetak;
            int kraj = trenutnaGrana.kraj;
            if(stepeni[pocetak] == 2 || stepeni[kraj] == 2) {
                trenutna++;
            continue;
            }// end if

            ruta.dodajGranu(pocetak,kraj);
            if(ruta.imaLiCiklusa(pocetak)) {
                ruta.obrisiGranu(pocetak,kraj);
                trenutna++;
                continue;
            }//end if
            else{
                stepeni[pocetak]++;
                stepeni[kraj]++;
                trenutna++;
                break;
            }//end else
        }//end while
    }//end for

    vector<int> tura = ruta.vratiTuru();
    //ispisiTuru(tura);

    if(provjeriTuru(tura))
        return tura;
    else throw "Greska";
}

///-----------------------------------<< VEKTOR TURE SA DVA OPT OPTIMIZACIJOM >>---------------------------------------///

vector<int> Graf::vratiTuruSaDvaOpt(vector<int> tura){
    dvaOpt(tura);

    return tura;
}

///-----------------------------------<< VEKTOR TURE SA DVA OPT OPTIMIZACIJOM >>---------------------------------------///

vector<int> Graf::vratiRandomTuru(){
    vector<int> tura = vratiTuruPoredak();
    srand(time(0));

    int pozicija1;
    int pozicija2;
    int pom;
    for(int i = 0; i < 2 * n; i++){
        pozicija1 = rand() % n;
        pozicija2 = rand() % n;
        pom = tura[pozicija1];
        tura[pozicija1] = tura[pozicija2];
        tura[pozicija2] = pom;
    }

    if(provjeriTuru(tura))
        return tura;
}

///-----------------------------------<< DVA OPT ZAMJENA >>---------------------------------------///

void Graf::dvaOptZamjena(vector<int>& tura, int i, int j){
    reverse(tura.begin() + i, tura.begin() + j + 1);
}

///--------------------------------------<< DVA OPT >>---------------------------------------///

int Graf::dvaOpt(vector<int>& tura){
    vector<int> pomocna = tura;

    int najmanjaUdaljenost = duzinaTure(tura);
    int pomocnaUdaljenost = 0;
    bool poboljsanje = true;

    while(poboljsanje){
        poboljsanje = false;
        for(int i = 0; i < n - 1; i++){
            for(int j = i + 1; j < n; j++){
                dvaOptZamjena(pomocna, i, j);
                pomocnaUdaljenost = duzinaTure(pomocna);
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


void Graf::triOptZamjena(int tip, vector<int>& tura, int i, int j, int k){
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


int Graf::triOpt(vector<int>& tura){
    vector<int> pomocna = tura;

    int najmanjaUdaljenost = duzinaTure(tura);
    int pomocnaUdaljenost = 0;
    bool poboljsanje = true;

    clock_t pocetak;
    pocetak = clock();
    double sekunde;

    while(poboljsanje){
        poboljsanje = false;
        for(int i = 0; i < n - 3; i++){
            for(int j = i + 1; j < n - 2; j++){
                for(int k = j + 1; k < n - 1; k++){
                    dvaOptZamjena(pomocna, j + 1, k);
                    pomocnaUdaljenost = duzinaTure(pomocna);

                    if(pomocnaUdaljenost < najmanjaUdaljenost){
                        najmanjaUdaljenost = pomocnaUdaljenost;
                        tura = pomocna;
                        poboljsanje = true;
                    }// end if
                    else
                        pomocna = tura; ///

                    dvaOptZamjena(pomocna, i + 1, j);
                    pomocnaUdaljenost = duzinaTure(pomocna);

                    if(pomocnaUdaljenost < najmanjaUdaljenost){
                        najmanjaUdaljenost = pomocnaUdaljenost;
                        tura = pomocna;
                        poboljsanje = true;
                    }// end if
                    else
                        pomocna = tura; ///

                    triOptZamjena(1, pomocna, i, j, k);
                    pomocnaUdaljenost = duzinaTure(pomocna);

                    if(pomocnaUdaljenost < najmanjaUdaljenost){
                        najmanjaUdaljenost = pomocnaUdaljenost;
                        tura = pomocna;
                        poboljsanje = true;
                    }// end if
                    else
                        pomocna = tura; ///

                    triOptZamjena(2, pomocna, i, j, k);
                    pomocnaUdaljenost = duzinaTure(pomocna);

                    if(pomocnaUdaljenost < najmanjaUdaljenost){
                        najmanjaUdaljenost = pomocnaUdaljenost;
                        tura = pomocna;
                        poboljsanje = true;
                    }// end if
                    else
                        pomocna = tura; ///

                    triOptZamjena(3, pomocna, i, j, k);
                    pomocnaUdaljenost = duzinaTure(pomocna);

                    if(pomocnaUdaljenost < najmanjaUdaljenost){
                        najmanjaUdaljenost = pomocnaUdaljenost;
                        tura = pomocna;
                        poboljsanje = true;
                    }// end if
                    else
                        pomocna = tura; ///

                    triOptZamjena(4, pomocna, i, j, k);
                    pomocnaUdaljenost = duzinaTure(pomocna);

                    if(pomocnaUdaljenost < najmanjaUdaljenost){
                        najmanjaUdaljenost = pomocnaUdaljenost;
                        tura = pomocna;
                        poboljsanje = true;
                    }// end if
                    else
                        pomocna = tura; ///

                    dvaOptZamjena(pomocna, i + 1, k);
                    pomocnaUdaljenost = duzinaTure(pomocna);

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


#endif // GRAF_H
