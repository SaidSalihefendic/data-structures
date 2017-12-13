#ifndef POLINOM_H
#define POLINOM_H

#include <string>
#include <iostream>
using namespace std;

class Polinom
{
private:
    struct Clan
    {
        int koeficijent;
        int stepen;
        Clan* veza;

        Clan(int koeficijent, int stepen, Clan* veza) : koeficijent{koeficijent}, stepen{stepen}, veza{veza} {};
    };

    int duzina;
    Clan *pocetni, *krajnji;

    static int filtrirajKoeficijent(string izraz);
    static int filtrirajStepen(string izraz);

    void dodajClan(int koeficijent, int stepen);
    void dodajNaKraj(int koeficijent, int stepen);


    Clan* vratiPocetak() const { return pocetni; }
    void brisiIzaClana(Clan* pok);

public:
    Polinom();
    Polinom(const Polinom& kopija);
    ~Polinom();
    Polinom& operator=(const Polinom& kopija);

    void dodajClan(string izraz); //Sorted insertion
    int Velicina() const { return duzina; }

        //Operatori
    friend const Polinom operator+(const Polinom& lijevi, const Polinom& desni); //sabiranje
    friend const Polinom operator-(const Polinom& polinom); //unarni minus
    friend const Polinom operator-(const Polinom& lijevi, const Polinom& desni); //binarni minus
    friend const Polinom operator*(const Polinom& lijevi, const Polinom& desni); //mnozenje
    friend const Polinom operator^(const Polinom& polinom, int stepen); //stepenovanje sa intom
    friend const Polinom operator^(const Polinom& polinom, const Polinom& stepen);

        //Unos i ispis
    friend istream& operator >>(istream& pin, Polinom& polinom);
    friend ostream& operator <<(ostream& pout, const Polinom& polinom);
};

#endif // POLINOM_H


        //Koncept iteratora, mada nije potrebno da bude u polinomu, bilo je pokusaja da se iskoristi sort() funkcija
//    class iterator
//    {
//    private:
//        Clan* trenutni;
//    public:
//        iterator(Clan* trenutni) : trenutni{trenutni} {}
//
//        iterator& operator++() {
//            trenutni = trenutni->veza;
//            return *this;
//        }//end operator++
//
//        iterator operator++(int) {
//            iterator stari(trenutni);
//            ++(*this);
//            return stari;
//        }//end operator ++
//
//        bool operator ==(const iterator& it) {
//            return trenutni == it.trenutni;
//        }
//
//        bool operator !=(const iterator& it) {
//            return trenutni != it.trenutni;
//        }
//
//        iterator operator+(int broj) {
//            return *this;
//        }
//
//        string operator*() {
//            string clan = "";
//
//            clan.push_back(trenutni->koeficijent);
//            clan.push_back('x');
//            clan.push_back('^');
//            clan.push_back(trenutni->stepen);
//
//            return clan;
//        }
//
//        friend class Polinom;
//    };
//    iterator Pocetak() const { return iterator(pocetni); }
//    iterator Kraj() const { return iterator(krajnji); }

