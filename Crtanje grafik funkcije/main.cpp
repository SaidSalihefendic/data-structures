/** PRVI DIO - Skontati kako upisivati x^2 u fajl grafik funkcije preko matrice, mora primati interval od a do b, pri cemu a i b unosi korisnik, matrica ce biti visine maximuma grafika funkcije
        DRUGI DIO - Implementirati Evaluator preko Stack-a za operacije +, *, -, /, ^, sin, cos, tan, sqrt,
        TRECI DIO - Modifikovati evaluator da prima funkciju po x i vrijednost x za tu funkciju, te da ispisuje vrijednost
        CETVRTI DIO - Implementirati MergeSort (ili InsertionSort) za listu listi po y varijabli (Zbog ispisa *)
        PETI DIO - Ispisati matricu u fajl "proba.txt"
        SESTI DIO - Implementirati crtanje grafike bez matrice
        SEDMI DIO - Na koliko decimala i koliko tacaka zeli korisnik

*/


#include<iostream>
#include<fstream>
#include<cstdlib>
#include<cmath>
#include "lista.h"

using namespace std;

///----------------------------------------------------------------------------------------

struct UredjeniPar
{
    double x;
    double y;

    UredjeniPar() : x(0), y(0) {}
    UredjeniPar(double x, double y) : x(x), y(y) {}
};

///----------------------------------------------------------------------------------------

    ///Funkcija za zaokruzivanje broja na dvije decimale
double zaokruzi(double broj)
{
    if(broj * 10 == int(broj)) return broj;

    double glavniBroj = int(broj * 10);

    return glavniBroj / 10;
}

///----------------------------------------------------------------------------------------

template<class Type>
void print(Type data)
{
    cout << data << " ";
}//end print

///----------------------------------------------------------------------------------------

void printParove(UredjeniPar par)
{
    cout << "(" << par.x << ", " << par.y << ")" << endl;
}


double func(double x)
{
    return cos(log(x));
}
///----------------------------------------------------------------------------------------

void grafikFunkcije(string funkcija, double a, double b, unsigned int profinjenje)
{
    //Uzimamo konkretnu funkciju x^2
    ofstream fout("proba.txt");
    List<UredjeniPar> listaParova;

    double epsilon = 0.0001; //ZBOG DOUBLE-A MORAMO UVESTI EPSILON

    double dio = (b - a) / profinjenje; //PROFINJENJE za X

    double brojac_x = zaokruzi(a);

    double maximum = zaokruzi(func(a)); //Pocetne vrijednosti funkcija od a
    double minimum = zaokruzi(func(a)); //Pocetne vrijednosti funkcija od a, prima funkciju i na koliko decimala
        //Uzimamo konkretne vrijednosti funkcije
    while(a <= b)
    {
        listaParova.pushBack(*(new UredjeniPar(zaokruzi(a), zaokruzi(func(a))))); //Umjeso a^2 na mjestu y, ovdje ce biti parse

            //Trazenje maximuma
        if(zaokruzi(func(a)) > maximum)
            maximum = zaokruzi(func(a));

            //Trazenje minimuma
        else if(zaokruzi(func(a)) < minimum)
            minimum = zaokruzi(func(a));

        a = a + dio;
    }//end while

    listaParova.processList(&printParove);

        ///VIDJETI JE LI TREBA SORTIRATI

        //Iscrtavanje grafik funkcije

    double brojac_y = maximum;

        //Petlja po x-u
    List<UredjeniPar>::node* pok = listaParova.Begin();
    List<UredjeniPar>::node* pok_y = listaParova.End()->prev;

        //Dupli for zbog liste, ispis na .txt grafik funkcije
    for(brojac_y; brojac_y >= minimum; brojac_y = brojac_y - 0.1)
    {
        for(List<UredjeniPar>::node* pok = listaParova.Begin(); pok != listaParova.End(); pok = pok->next)
        {

            if(pok->data.x + epsilon >= 0 && pok->data.x - epsilon <= 0 && brojac_y - epsilon < 0 && 0 < brojac_y + epsilon)
            {
                    //Gledamo je li grafik sijece srediste koordinatnog pocetka
                if(pok->data.y >= brojac_y - epsilon && pok->data.y <= brojac_y + epsilon)
                {
                    fout << "*";
                    //cout << pok->data.y << " ";
                }//end if ispis tacke
                else
                    fout << "+";
            } //END SREDNJI KOORDINATNI

            else if(pok->data.x == 0)
            {
                    //Gledamo je li grafik sijece y-osu
                if(pok->data.y >= brojac_y - epsilon && pok->data.y <= brojac_y + epsilon)
                {
                    fout << "*";
                    //cout << pok->data.y << " ";
                }//end if ispis tacke
                else
                    fout << "|";
            }//END y-OSA

            else if((brojac_y - epsilon < 0 && 0 < brojac_y + epsilon))
            {
                    //Gledamo je li grafik sijece x-osu
                if(pok->data.y >= brojac_y - epsilon && pok->data.y <= brojac_y + epsilon)
                {
                    fout << "*";
                    //cout << pok->data.y << " ";
                }//end if ispis tacke
                else
                    fout << "-";
            }//END x-OSA

                //ISPRAVNI GRAFIK FUNKCIJE
            else if(pok->data.y >= brojac_y - epsilon && pok->data.y <= brojac_y + epsilon)
            {
                fout << "*";
                //cout << pok->data.y << " ";
            }//end if
            else
                fout << " ";
        }//idemo kroz listu po x koordinati

        fout << endl;
        //cout << zaokruzi(brojac_y) << endl;


//        brojac_y = zaokruzi(brojac_y - 0.1); //ZAOKRUZIVANJE, PROBLEM DOUBLE

//        if(brojac_y == zaokruzi(brojac_y - 0.1))
//            brojac_y -= 1;
    }//end while

    fout.close();
} //END ISCRTAVANJE GRAFIK FUNKCIJE

///----------------------------------------------------------------------------------------

int main()
{
    double a, b;
    unsigned int profinjenje;
    cout << "Unesite a (minimum segmenta): ";
    cin >> a;

    cout << "Unesite b (maximum segmenta): ";
    cin >> b;

    cout << "Unesite broj tacaka: ";
    cin >> profinjenje;

    cout << endl;

    string funkcija("");
    cout << "Unesite funkciju: ";
    getline(cin, funkcija);
    cout << endl;
    try
    {
        grafikFunkcije(funkcija, a, b, profinjenje);
    } catch(string err)
    {
        cout << err << endl;
    }

    cout << endl;

    return 0;
}



///----------------------------------------------------------------------------------------

/* OVO RADI SIGURNO
void grafikFunkcije(string funkcija, double a, double b, unsigned int profinjenje)
{
    //Uzimamo konkretnu funkciju x^2
    ofstream fout("proba.txt");
    List<UredjeniPar> listaParova;

    double epsilon = 0.0001; //ZBOG DOUBLE-A MORAMO UVESTI EPSILON

    double dio = (b - a) / profinjenje; //PROFINJENJE za X

    double brojac_x = zaokruzi(a);

    double maximum = zaokruzi(func(a)); //Pocetne vrijednosti funkcija od a
    double minimum = zaokruzi(func(a)); //Pocetne vrijednosti funkcija od a, prima funkciju i na koliko decimala
        //Uzimamo konkretne vrijednosti funkcije
    while(a <= b)
    {
        listaParova.pushBack(*(new UredjeniPar(zaokruzi(a), zaokruzi(func(a))))); //Umjeso a^2 na mjestu y, ovdje ce biti parse

            //Trazenje maximuma
        if(zaokruzi(func(a)) > maximum)
            maximum = zaokruzi(func(a));

            //Trazenje minimuma
        else if(zaokruzi(func(a)) < minimum)
            minimum = zaokruzi(func(a));

        a = a + dio;
    }//end while

    listaParova.processList(&printParove);

        ///VIDJETI JE LI TREBA SORTIRATI

        //Iscrtavanje grafik funkcije

    double brojac_y = maximum;

        //Petlja po x-u
    List<UredjeniPar>::node* pok = listaParova.Begin();
    List<UredjeniPar>::node* pok_y = listaParova.End()->prev;

        //Dupli for zbog liste, ispis na .txt grafik funkcije
    for(brojac_y; brojac_y >= minimum; brojac_y = brojac_y - 0.1)
    {
        for(List<UredjeniPar>::node* pok = listaParova.Begin(); pok != listaParova.End(); pok = pok->next)
        {

            if(pok->data.x + epsilon >= 0 && pok->data.x - epsilon <= 0 && brojac_y - epsilon < 0 && 0 < brojac_y + epsilon)
            {
                    //Gledamo je li grafik sijece srediste koordinatnog pocetka
                if(pok->data.y >= brojac_y - epsilon && pok->data.y <= brojac_y + epsilon)
                {
                    fout << "*";
                    //cout << pok->data.y << " ";
                }//end if ispis tacke
                else
                    fout << "+";
            } //END SREDNJI KOORDINATNI

            else if(pok->data.x + epsilon >= 0 && pok->data.x - epsilon <= 0)
            {
                    //Gledamo je li grafik sijece y-osu
                if(pok->data.y >= brojac_y - epsilon && pok->data.y <= brojac_y + epsilon)
                {
                    fout << "*";
                    //cout << pok->data.y << " ";
                }//end if ispis tacke
                else
                    fout << "|";
            }//END y-OSA

            else if((brojac_y - epsilon < 0 && 0 < brojac_y + epsilon))
            {
                    //Gledamo je li grafik sijece x-osu
                if(pok->data.y >= brojac_y - epsilon && pok->data.y <= brojac_y + epsilon)
                {
                    fout << "*";
                    //cout << pok->data.y << " ";
                }//end if ispis tacke
                else
                    fout << "-";
            }//END x-OSA

                //ISPRAVNI GRAFIK FUNKCIJE
            else if(pok->data.y >= brojac_y - epsilon && pok->data.y <= brojac_y + epsilon)
            {
                fout << "*";
                //cout << pok->data.y << " ";
            }//end if
            else
                fout << " ";
        }//idemo kroz listu po x koordinati

        fout << endl;
        //cout << zaokruzi(brojac_y) << endl;


//        brojac_y = zaokruzi(brojac_y - 0.1); //ZAOKRUZIVANJE, PROBLEM DOUBLE

//        if(brojac_y == zaokruzi(brojac_y - 0.1))
//            brojac_y -= 1;
    }//end while

    fout.close();
} //END ISCRTAVANJE GRAFIK FUNKCIJE*/
