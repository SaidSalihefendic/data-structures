#include "polinom.h"
#include <iostream>
#include <stack>
#include <vector>
#include <sstream>
#include <map>
#include <algorithm>

using namespace std;

///-------------------------------------------<<<DEFAULTNI KONSTRUKTOR>>>--------------------------------------------------------

Polinom::Polinom() {
    this->duzina = 0;
    this->pocetni = nullptr;
    this->krajnji = nullptr;
}

///-------------------------------------------<<<KONSTRUKTOR KOPIJE>>>--------------------------------------------------------

Polinom::Polinom(const Polinom& kopija) : Polinom() {
    for(Polinom::Clan* pok = kopija.pocetni; pok != nullptr; pok = pok->veza)
        dodajNaKraj(pok->koeficijent, pok->stepen);
}

///-------------------------------------------<<<OPERATOR DODJELE>>>--------------------------------------------------------

Polinom& Polinom::operator=(const Polinom& kopija) {
    if(this == &kopija) return *this;

        //Da obrisemo sta je bilo prethodno
    this->~Polinom();

    for(Polinom::Clan* pok = kopija.pocetni; pok != nullptr; pok = pok->veza)
        dodajNaKraj(pok->koeficijent, pok->stepen);

    return *this;
}

///-------------------------------------------<<<DESTRUKTOR>>>--------------------------------------------------------

Polinom::~Polinom() {
    if(pocetni == nullptr) return;
    while(pocetni->veza != nullptr)
        brisiIzaClana(pocetni);

    delete pocetni;
    pocetni = nullptr;
    krajnji = nullptr;
    duzina = 0; //just to make sure
}

///-------------------------------------------<<<BRISANJE IZA CLANA>>>--------------------------------------------------------

void Polinom::brisiIzaClana(Clan* pok){
        //Nemamo sta brisati
    if(pok->veza == nullptr || pok == nullptr)
        return;

    Clan* zaBrisanje = pok->veza;
    pok->veza = pok->veza->veza;
    delete zaBrisanje;
}

///-------------------------------------------<<<FILTRIRANJE KOEFICIJENTA>>>--------------------------------------------------------

int Polinom::filtrirajKoeficijent(string izraz) {
    ostringstream ss;
    int koeficijent = 1;
    int i = 0;
    bool jeNegativan = false;

        //Ukoliko je samo x, vracamo 1 kao koeficijent, smatramo da ima 1 ispred
    if(izraz.at(i) == 'x') return 1;

    if(izraz.at(i) == '-') {
        jeNegativan = true;
        i++;
    }//end if

    while(i != izraz.length() && izraz.at(i) >= '0' && izraz.at(i) <= '9') {
        ss << izraz.at(i);
        i++;
    }//end while

    istringstream si(ss.str());

    si >> koeficijent;

    if(jeNegativan)
        return -koeficijent;
    else
        return koeficijent;
}

///-------------------------------------------<<<FILTRIRANJE STEPENA>>>--------------------------------------------------------

int Polinom::filtrirajStepen(string izraz) {
    if(izraz == "") {
        cin.sync();
        throw "Neispravan unos izraza(prazan string)";
    }

    int stepen;
    int i = 0;

        //ignorisemo sve znakove do x, ako postoji, takodjer provjeravamo tacnost unosa
    while(izraz.at(i) != 'x') {
        if(izraz.at(i) != '*' && izraz.at(i) != ' ' && izraz.at(i) != '-' && (izraz.at(i) < '0' || izraz.at(i) > '9')) {
            cin.sync();
            throw "Neispravan unos clana (stepen)!";
        }

        i++;

        if(i == izraz.length())
            return 0; //Nema x u izrazu, pa je stepen 0
    }//end while


    izraz = izraz.substr(i, izraz.length());

    if(izraz.length() == 1) return 1; //ukoliko je samo "x", vracamo 1 kao stepen

        //TO-DO: Izignorisati whitespaces tokom provjere kape i broja
    else {
        i = 0;
        ostringstream ss;
        i++;

        if(izraz.at(i) != '^') {
            cin.sync();
            throw "Neispravan unos!";
        }

        i++;
        while(i != izraz.length() && izraz.at(i) >= '0' && izraz.at(i) <= '9') {
            ss << izraz.at(i);
            i++;
        }//end while

        if(ss.str() == "") {
            cin.sync();
            throw "Neispravan unos! (stepen, prazan string)";
        }

        istringstream si(ss.str());
        si>>stepen; //ubacujemo u stepen sto smo izvukli

        return stepen;
    }

}

///-------------------------------------------<<<DODAVANJE CLANA (SORTED INSERT), STRING VERZIJA>>>--------------------------------------------------------

void Polinom::dodajClan(string izraz) {
    if(izraz == "") {
        cin.sync();
        throw "Prazan string je ubacen!";
    }
        //Izvlacimo informacije koje nama treba iz datog izraza
    unsigned int stepen = filtrirajStepen(izraz);
    int koeficijent = filtrirajKoeficijent(izraz);

    dodajClan(koeficijent, stepen);
    //cout << "Dodan clan" << endl;
}//end dodajClan

///-------------------------------------------<<<DODAVANJE CLANA (SORTED INSERT), INT VERZIJA>>>--------------------------------------------------------

void Polinom::dodajClan(int koeficijent, int stepen) {
        //Ubacujemo sada cvor, tj. clan sa dobijenim koeficijentima i stepenima
    if(pocetni == nullptr)
        pocetni = krajnji = new Clan(koeficijent, stepen, nullptr);

    else if(koeficijent == 0 || stepen < 0)
        return; //ne dodajemo nulti clan niti clanove stepena manjeg od 0
    else {
        Clan *aktuelni = pocetni, *prethodni = pocetni;

        //Posto nemamo sentinel cvor, moramo provjeriti na pocetku odmah da li uneseni stepen najveci
        if(stepen > aktuelni->stepen) {
            pocetni = new Clan(koeficijent, stepen, pocetni);
        }//end if
        else {
                //Dolazimo do prvog cvora koji je stepena manjeg ili jednak datom stepenu
            while(aktuelni != nullptr && stepen < aktuelni->stepen) {
                prethodni = aktuelni;
                aktuelni = aktuelni->veza;
            }//end while

            if(aktuelni != nullptr && aktuelni->stepen == stepen) {
                aktuelni->koeficijent += koeficijent;
                return;
            }//end if
            else {
                prethodni->veza = new Clan(koeficijent, stepen, aktuelni);
            } //end else
        }//end else 2
    }//end else

    duzina++;
}
///-------------------------------------------<<<DODAVANJE CLANA NA KRAJU>>>--------------------------------------------------------

void Polinom::dodajNaKraj(int koeficijent, int stepen) {
    if(pocetni == nullptr)
        pocetni = krajnji = new Clan(koeficijent, stepen, nullptr);

    else if(koeficijent == 0 || stepen < 0) return;
    else {
        if(krajnji->stepen == stepen){
            krajnji->koeficijent += koeficijent;
        }
        else{
            krajnji->veza = new Clan(koeficijent, stepen, nullptr);
            krajnji = krajnji->veza;
        }
    }//end else

    duzina++;
}

///-------------------------------------------<<<OPERATOR SABIRANJA>>>--------------------------------------------------------

const Polinom operator+(const Polinom& lijevi, const Polinom& desni) {
    Polinom rezultat;

    Polinom::Clan* lijevi_pok = lijevi.pocetni;
    Polinom::Clan* desni_pok = desni.pocetni;

    while(lijevi_pok != nullptr && desni_pok != nullptr) {
            //Poredimo stepene, ukoliko se radi o vecem stepenu, samo ga dodamo u rezultat
        if(lijevi_pok->stepen > desni_pok->stepen) {
            rezultat.dodajNaKraj(lijevi_pok->koeficijent, lijevi_pok->stepen);
            lijevi_pok = lijevi_pok->veza;
        }//end if

        else if(desni_pok->stepen > lijevi_pok->stepen) {
            rezultat.dodajNaKraj(desni_pok->koeficijent, desni_pok->stepen);
            desni_pok = desni_pok->veza;
        }//end else if

        else {
            if(desni_pok->koeficijent + lijevi_pok->koeficijent != 0)
                rezultat.dodajNaKraj(desni_pok->koeficijent + lijevi_pok->koeficijent, lijevi_pok->stepen);
            lijevi_pok = lijevi_pok->veza;
            desni_pok = desni_pok->veza;
        }//end else
    }//end while

        //Sta je ostalo u drugom polinomu, dodajemo ga u rezultat
    for(lijevi_pok; lijevi_pok != nullptr; lijevi_pok = lijevi_pok->veza)
        rezultat.dodajNaKraj(lijevi_pok->koeficijent, lijevi_pok->stepen);

    for(desni_pok; desni_pok != nullptr; desni_pok = desni_pok->veza)
        rezultat.dodajNaKraj(desni_pok->koeficijent, desni_pok->stepen);

    return rezultat;
}

///-------------------------------------------<<<UNARNI MINUS>>>--------------------------------------------------------

const Polinom operator-(const Polinom& polinom) {
//    Polinom::Clan* pok = polinom.pocetni;
    Polinom rezultat;

    for(Polinom::Clan* pok = polinom.pocetni; pok != nullptr; pok = pok->veza)
        rezultat.dodajClan(-pok->koeficijent, pok->stepen);

    return rezultat;
}

///-------------------------------------------<<<OPERATOR ODUZIMANJA>>>--------------------------------------------------------

const Polinom operator-(const Polinom& lijevi, const Polinom& desni) {
    return lijevi + (-desni);
}

///-------------------------------------------<<<POMOCNA FUNKCIJA - POREDJIVANJE PAROVE PO STEPENIMA>>>--------------------------------------------------------

bool porediParove(pair<int, int> lijevi_par, pair<int, int> desni_par) {
    return lijevi_par.second > desni_par.second;
}

///-------------------------------------------<<<OPERATOR MNOZENJA>>>--------------------------------------------------------

const Polinom operator*(const Polinom& lijevi, const Polinom& desni) {
    Polinom rezultat;

    map<int, int> clanovi;

        //O(n^2)
    for(Polinom::Clan* lijevi_pok = lijevi.pocetni; lijevi_pok != nullptr; lijevi_pok = lijevi_pok->veza) {
        for(Polinom::Clan* desni_pok = desni.pocetni; desni_pok != nullptr; desni_pok = desni_pok->veza) {
            if(clanovi.find(lijevi_pok->stepen + desni_pok->stepen) == clanovi.end()) //TO-DO
                clanovi.insert(make_pair(lijevi_pok->stepen + desni_pok->stepen, lijevi_pok->koeficijent * desni_pok->koeficijent));
            else
                clanovi[lijevi_pok->stepen + desni_pok->stepen] += lijevi_pok->koeficijent * desni_pok->koeficijent;
        }//end for
    }//end for


    for(auto it = clanovi.rbegin(); it != clanovi.rend() ; it++){
        rezultat.dodajNaKraj(it->second, it->first); //Bit ce i nultih clanova, ali konstruktor kopije ce da rijesi probleme koje bude imao rezultat
    }

    return rezultat;
}

///-------------------------------------------<<<OPERATOR STEPENOVANJA - INT VERZIJA>>>--------------------------------------------------------

const Polinom operator^(const Polinom& polinom, int stepen) {
        //Zbog rekurzivnog poziva
    if(stepen <= 0) {
        if(polinom.pocetni->stepen == 0 && polinom.pocetni->koeficijent == 0) {
            cin.sync();
            throw "Nedozvoljena operacija!";
        }
        Polinom jedinicni;
        jedinicni.dodajClan("1");
        return jedinicni;
    }//end if

    Polinom rezultat = polinom^(stepen / 2);

    if(stepen % 2 == 0)
        return rezultat * rezultat;
    else
        return polinom * rezultat * rezultat;
}

///-------------------------------------------<<<OPERATOR STEPENOVANJA - POLINOM VERZIJA>>>--------------------------------------------------------

const Polinom operator^(const Polinom& polinom, const Polinom& stepen) {
    if(stepen.pocetni->stepen > 0) {
        cin.sync();
        throw "Ne moze se dici polinom na stepen koji je takodjer polinom stepena veci od 0";
    }//end if

    else if(stepen.pocetni->koeficijent < 0) {
        cin.sync();
        throw "Ne moze se dici na negativan stepen!";
    }//end else if

    return (polinom^(stepen.pocetni->koeficijent));
}

///-------------------------------------------<<<ISPIS POMOCU OSTREAM>>>--------------------------------------------------------

ostream& operator <<(ostream& pout, const Polinom& polinom) {
        //Ukoliko se radi o praznom polinomu
    if(polinom.Velicina() == 0){
        pout << 0 << endl;
        return pout;
    }
    Polinom::Clan* aktuelni = polinom.pocetni;

    if(aktuelni->koeficijent < 0)
        cout << "-";
        //test da li duzina dobro radi
    for(int i = 0; i < polinom.duzina; i++) {
        if(abs(aktuelni->koeficijent) != 1)
            cout << abs(aktuelni->koeficijent);
        else if(abs(aktuelni->koeficijent) == 1 && aktuelni->stepen == 0)
            cout << abs(aktuelni->koeficijent);

        if(aktuelni->stepen == 1)
            cout << "x";
        else if(aktuelni->stepen > 1)
            cout << "x^" << aktuelni->stepen;

        aktuelni = aktuelni->veza;

            //treba
        if(aktuelni != nullptr) {
            if(aktuelni->koeficijent < 0)
                cout << " - ";
            else
                cout << " + ";
        }//end if
    }//end for

    cout << endl;
}

///-------------------------------------------<<<POMOCNA FUNKCIJA - VRSENJE OPERACIJE NAD STEKOM POLINOMA>>>--------------------------------------------------------

    //pomocne funkcije
void izvrsiOperaciju(stack<Polinom>& stek_polinoma, char operacija) {
    if(stek_polinoma.size() < 2) {
        cin.sync();
        throw "Nema dovoljno polinoma da se izvrsi operacija!";
    }


    Polinom drugi = stek_polinoma.top();
    stek_polinoma.pop();
    Polinom prvi = stek_polinoma.top();
    stek_polinoma.pop();

    Polinom rezultat;

    if(operacija == '+')
        rezultat = prvi + drugi;
    else if(operacija == '-')
        rezultat = prvi - drugi;
    else if(operacija == '*')
        rezultat = prvi * drugi;
    else if(operacija == '^')
        rezultat = prvi ^drugi;
    else {
        cin.sync();
        throw "Neocekivana operacija!";
    }

    stek_polinoma.push(rezultat);
}

///-------------------------------------------<<<POMOCNA FUNKCIJA - PREDNOST OPERACIJA>>>--------------------------------------------------------

int prednostOperacija(char operacija){
    if(operacija == '^') return 3;
    else if(operacija == '*') return 2;
    else if(operacija == '+' || operacija == '-') return 1;
    else return 0;
}

///-------------------------------------------<<<ISTREAM UNOS - EVALUATOR POLINOMA>>>--------------------------------------------------------

istream& operator >>(istream& pin, Polinom& polinom){
    stack<Polinom> stek_polinoma;
    stack<char> operacije;
    char prethodni = '(';

        //Evaluator
    while(cin.peek() != '\n'){
        //cout << char(cin.peek()) << endl;
            //Da preskacemo white-space znakove
        while(cin.peek() == ' ') cin.get();

            //trazimo sada clanove
        if((cin.peek() >= '0' && cin.peek() <= '9')) {
            string clan = "";
                //kupimo citav clan
            while(pin.peek() != ' ' && pin.peek() != '\n' && pin.peek() != '+' && pin.peek() != '-' && pin.peek() != '*' && pin.peek() != '(' && pin.peek() != ')' && pin.peek() != '^' && pin.peek() != 'x'){
                clan.push_back(cin.peek()); //sada kupimo znak po znak
                pin.get();
            }//end while

            Polinom p;
            p.dodajClan(clan);
            stek_polinoma.push(p);
            prethodni = '0'; //da se zna da je u pitanju clan
        }//end if

        else if(pin.peek() == 'x') {
            if(prethodni == ')' || prethodni == 'x') {
                pin.sync();
                throw "Neispravan unos clanova!";
            }//end if

            if(prethodni == '0')
                operacije.push('*');
            Polinom p;
            p.dodajClan("x");
            stek_polinoma.push(p);
            pin.get();
            prethodni = 'x';
        }//end if

            //ako smo naisli na operaciju
        else if(prednostOperacija(pin.peek()) > 0){
            char znak;
            pin >> znak;

            if(prethodni == '+' || (prethodni == '(' && prednostOperacija(znak) > 1)){
                pin.sync();
                throw "Neocekivan operator!";
            }

            if(prednostOperacija(znak) == 1 && prethodni == '(') {
                Polinom nula;
                nula.dodajClan("0");

                stek_polinoma.push(nula);
            }

            while(!operacije.empty() && prednostOperacija(operacije.top()) >= prednostOperacija(znak)) {
                izvrsiOperaciju(stek_polinoma, operacije.top());
                operacije.pop();
            }//end while

            operacije.push(znak);
            prethodni = '+'; //Fleg za oznaku operacije
        }//end if

        else if(pin.peek() == '(') {
            if(prethodni == '0' || prethodni == ')' ||prethodni == 'x')
                operacije.push('*');

            operacije.push('(');
            pin.get(); //Pushamo zagradu u operacije
            prethodni = '(';
        }//end else if

        else if(pin.peek() == ')') {
            while(!operacije.empty() && operacije.top() != '(') {
                izvrsiOperaciju(stek_polinoma, operacije.top());
                operacije.pop();
            }//end while

                //Ukoliko nemamo nista na steku operacija, to znaci da nismo naisli na otvorenu zagradu
            if(operacije.empty()) {
                pin.sync();
                throw "Nisu balansirane zagrade!";
            }//end if
            operacije.pop(); //Skidamo zagradu
            pin.get();
            prethodni = ')';
        }//end else if

        else {
                //Da mozemo imati podrzan whitespace nakon unosa
            if(pin.peek() == '\n')
                break;

            pin.sync();
            throw "Neocekivani znak!";
        }//else
    }//end while
        //sta je ostalo na steku operacija, izvrsimo
    while(!operacije.empty()) {
        if(operacije.top() == '(') {
            pin.sync();
            throw "Neizbalansirane zagrade!";
        }//end if

        izvrsiOperaciju(stek_polinoma, operacije.top());
        operacije.pop();
    }//end while

    pin.get(); //da izbjegnemo \n znak na kraju unosa

    if(stek_polinoma.empty()) {
        pin.sync();
        throw "Greska pri unosu polinoma! Prazan stek polinoma!";
    }


    polinom = stek_polinoma.top();
    stek_polinoma.pop();

    if(!stek_polinoma.empty()) {
        pin.sync();
        throw "Greska pri unosu polinoma! Viska polinoma u steku!";
    }

    return pin;
}

///----------------------------------------------------------------------------------------------------------------------
