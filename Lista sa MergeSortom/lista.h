#ifndef LISTA_H
#define LISTA_H

template <typename Tip>
class Lista {
  public:
  struct Cvor {
    Tip element;
    Cvor *veza;
    Cvor(Tip element, Cvor *veza):element{element},veza{veza}{}
  };
  private:
  int velicina;
  Cvor *pocetak, *kraj;
  public:
      Lista():pocetak{nullptr},kraj{nullptr},velicina{0}{}
      Lista(const Lista<Tip>& kopija);
      ~Lista();
      Lista<Tip> &operator=(Lista<Tip> &kopija);
      bool Prazna() { return velicina==0;}
      Cvor *Pocetak() { return pocetak; }
      Cvor *Kraj() { return kraj; }
      void DodajNaPocetak(Tip element);
      void DodajNaKraj(Tip element);
      void UmetniIzaCvora(Cvor *pok, Tip element);
      void IzbrisiCvor(Cvor *pok);
      void ObradiSveElemente(void (*akcija)(Tip&));

      void swap_(Cvor* pok1, Cvor* pok2);
      Cvor* sredina() const;
};

#include "lista.cpp"

#endif // LISTA_H
