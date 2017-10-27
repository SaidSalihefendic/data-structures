#include <iostream>
#include <ctime>
#include <cstdlib>
#include "lista.h"

using namespace std;

template<class Tip>
void Ispisi(Tip &element) {
  cout<<element<< " ";
}

void Uduplaj(int &broj) {
  broj*=2;
}


template<class Tip>
void Merge(Lista<Tip>& lista, typename Lista<Tip>::Cvor* p, typename Lista<Tip>::Cvor* q, typename Lista<Tip>::Cvor* r)
{
    typename Lista<Tip>::Cvor *temp_aktuelni_lijevi = p, *temp_aktuelni_desni = q->veza, *prethodni_desni = q->veza;

    if(p == r)
        return;

    else if(p->veza == r)
    {
        cout << "2 elementa su u pitanju";
        if(p->element > r->element)
            lista.swap_(p, r);

        return;
    }
        //Primjenjujemo modifikaciju InsertionSort-a
    while(temp_aktuelni_lijevi != q->veza)
    {
        if(temp_aktuelni_lijevi->element > q->veza->element)
        {
            Tip temp_vrijednost = q->veza->element;
            temp_aktuelni_desni = q->veza;

            while(temp_aktuelni_desni != r)
            {
                //cout << "Usli u petlju" << endl;
                    //Ukoliko je sa desne strane liste element veci od lijeve strane, prekidamo petlju
                if(temp_aktuelni_desni->veza->element > temp_aktuelni_lijevi->element)
                    break;
                temp_aktuelni_desni->element = temp_aktuelni_desni->veza->element;
                    //Zamjena elemenata
                //lista.swap_(prethodni_desni, temp_aktuelni_desni);

                    //Posto je jednostruko povezana lista, uzimamo prethodni
//                prethodni_desni = temp_aktuelni_desni;
                temp_aktuelni_desni = temp_aktuelni_desni->veza;
            }//end while2
            //cout << "Izasli iz petlje" << endl;

            temp_aktuelni_desni->element = temp_aktuelni_lijevi->element;
            temp_aktuelni_lijevi->element = temp_vrijednost;

                //zamijenimo prethodni od velikog broja
//            lista.swap_(temp_aktuelni_lijevi, prethodni_desni);

            temp_aktuelni_desni = q->veza;
        }//end if

        temp_aktuelni_lijevi = temp_aktuelni_lijevi->veza;
    }//end while

//    return lista;
}

template <class Tip>
void MergeSort(Lista<Tip>& lista, typename Lista<Tip>::Cvor* poc, typename Lista<Tip>::Cvor* kraj)
{
    if(poc == kraj)
    {
        return;
    }//end if

    else if(poc->veza == kraj){
        if(poc->element > kraj->element)
        {
            lista.swap_(poc, kraj);
        }//end if
        return;
    }//end else if

//    cout << "Prije sredine" << endl;
    //

    typename Lista<Tip>::Cvor* sredina = poc;
    typename Lista<Tip>::Cvor* pom;
        //TRAZENJE SREDINE
    for(pom = poc; pom != kraj; pom = pom->veza)
    {
        pom = pom->veza;
        if(pom == kraj || pom == nullptr)
            break;

        sredina = sredina->veza;
    }
//    cout << "Poslije sredine" << endl;

    MergeSort(lista, poc, sredina);
    MergeSort(lista, sredina->veza, kraj);

//    cout << "Prosli MergeSort" << endl;

    Merge(lista, poc, sredina, kraj);
}

int main()
{
    Lista<char> lista;

    srand(time(0));
//
    const int N = 100000;
    for(int i = 0 ; i < N; i++)
        lista.DodajNaKraj(char(rand()%26 + int('a')));

    //lista.ObradiSveElemente(&Ispisi);
    cout << endl;

    cout << lista.sredina()->element << endl << endl;
    MergeSort(lista, lista.Pocetak(), lista.Kraj());

    //lista.ObradiSveElemente(&Ispisi);
}



//    lista.DodajNaKraj(1);
//    lista.DodajNaKraj(3);
//    lista.DodajNaKraj(6);
//    lista.DodajNaKraj(2);
//    lista.DodajNaKraj(5);
//    lista.DodajNaKraj(7);
//    lista.DodajNaKraj(-1);
//    lista.DodajNaKraj(-2);
//    lista.DodajNaKraj(-3);
//    lista.DodajNaKraj(-4);



//    lista.ObradiSveElemente(&Ispisi);
//    cout << endl;
//    cout << lista.Pocetak()->veza->veza->veza->element << endl;
//
//    Merge(lista, lista.Pocetak(), lista.Pocetak()->veza->veza->veza->veza, lista.Kraj());

//    cout << endl;
//
//    lista.swap_(lista.Pocetak(), lista.Kraj());
//    lista.ObradiSveElemente(&Ispisi);
//    cout << endl;

//  Lista<int> lista;
//
//  lista.DodajNaKraj(2);
//  lista.DodajNaKraj(5);
//  Lista<int> druga(lista);
//  druga.ObradiSveElemente(&Ispisi);
//  lista.DodajNaPocetak(11);
//
//  Lista<int>::Cvor *pok = lista.Pocetak();
//  pok = pok->veza;
//
//  lista.IzbrisiCvor(pok);
//  lista.ObradiSveElemente(&Ispisi);
//  cout<<lista.Pocetak()->element<<endl;
//  cout<<lista.Kraj()->element<<endl;
//  lista.DodajNaKraj(7);
//  lista.ObradiSveElemente(&Uduplaj);
//  lista.ObradiSveElemente(&Ispisi);
