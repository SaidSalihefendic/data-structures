#include "lista.h"
#ifndef LISTA_CPP
#define LISTA_CPP

///--------------------------------------------------------------------------------------------------------------------------------------------------------

template <typename Tip>
void Lista<Tip>::DodajNaPocetak(Tip element) {
  pocetak = new Cvor(element,pocetak);
  if(Prazna())
    kraj = pocetak;
  velicina++;
}

///--------------------------------------------------------------------------------------------------------------------------------------------------------

template <typename Tip>
void Lista<Tip>::DodajNaKraj(Tip element) {
  if(Prazna())
    DodajNaPocetak(element);
  else {
    kraj = kraj->veza = new Cvor(element,nullptr);
    velicina++;
  }
}

///--------------------------------------------------------------------------------------------------------------------------------------------------------

template <typename Tip>
void Lista<Tip>::UmetniIzaCvora(Cvor *pok, Tip element) {
  if(pok == nullptr)
    DodajNaPocetak(element);
  else if(pok==kraj)
    DodajNaKraj(element);
  else {
    pok->veza = new Cvor(element, pok->veza);
    velicina++;
  }
}

///--------------------------------------------------------------------------------------------------------------------------------------------------------

template <typename Tip>
void Lista<Tip>::IzbrisiCvor(Cvor *pok) {
  if(pok==nullptr)
    throw "Nemoguce je izbrisati";
  if(velicina == 1) {
    delete pocetak;
    pocetak = kraj = nullptr;
  }
  else if(pok==kraj) {
    Cvor *tekuci = pocetak;
    while(tekuci->veza!=kraj)
        tekuci = tekuci->veza;
    delete tekuci->veza;
    tekuci->veza = nullptr;
    kraj = tekuci;
  }
  else {
    if(pok->veza == kraj)
        kraj = pok;
    Cvor *za_brisanje = pok->veza;
    pok->element = pok->veza->element;
    pok->veza = pok->veza->veza;
    delete za_brisanje;
  }
  velicina--;
}

///--------------------------------------------------------------------------------------------------------------------------------------------------------

template <typename Tip>
Lista<Tip>::~Lista() {
  while(!Prazna())
    IzbrisiCvor(pocetak);
}

///--------------------------------------------------------------------------------------------------------------------------------------------------------

template <typename Tip>
Lista<Tip>::Lista(const Lista<Tip>& kopija):pocetak(nullptr),
kraj(nullptr), velicina(0) {
  for(Cvor *tekuci = kopija.pocetak;tekuci!=nullptr;tekuci=tekuci->veza)
    DodajNaKraj(tekuci->element);
}

///--------------------------------------------------------------------------------------------------------------------------------------------------------

template <typename Tip>
Lista<Tip>& Lista<Tip>:: operator=(Lista<Tip> &kopija) {
  if(this==&kopija)
    return *this;
  this->~Lista();
  for(Cvor *tekuci = kopija.pocetak;tekuci!=nullptr;tekuci=tekuci->veza)
    DodajNaKraj(tekuci->element);
  return *this;
}

///--------------------------------------------------------------------------------------------------------------------------------------------------------

template <typename Tip>
void Lista<Tip>::ObradiSveElemente(void (*akcija)(Tip&)) {
  for(Cvor *tekuci = pocetak;tekuci!=nullptr;tekuci=tekuci->veza)
    akcija(tekuci->element);
}

///--------------------------------------------------------------------------------------------------------------------------------------------------------

template <typename Tip>
void Lista<Tip>::swap_(Cvor* pok1, Cvor* pok2)
{
    Tip temp = pok1->element;
    pok1->element = pok2->element;
    pok2->element = temp;
}

///--------------------------------------------------------------------------------------------------------------------------------------------------------

template <class Tip>
typename Lista<Tip>::Cvor* Lista<Tip>::sredina() const
{
        //Slucaj ukoliko imamo praznu listu
    if(pocetak == nullptr or velicina == 0)
        throw "Lista je prazna";

    else if(velicina == 1 || velicina == 2)
        return pocetak;

    Cvor* srednjak = this->pocetak;

        //Idemo sada da dobijemo sredinu
    for(Cvor* pomocni = this->pocetak; pomocni != nullptr; pomocni = pomocni->veza)
    {
        if(pomocni->veza == nullptr)
            break;

        pomocni = pomocni->veza;

        srednjak = srednjak->veza;


    }

    return srednjak;
}
#endif // LISTA_CPP
