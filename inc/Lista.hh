#ifndef LISTA_HH
#define LISTA_HH
#include "Graf.hh"
#define INF 999999



class Krawedz{

protected:

int poczatek;
int koniec;
int waga;

Krawedz *nastKrawedz;

public:

int wez_poczatek(){return poczatek;}

int wez_koniec(){return koniec;}

int wez_wage(){return waga;}

void ustaw_wage(int waga_k){waga=waga_k;}

void wartosc(int p, int k, int w){

poczatek=p;
koniec=k;
waga=w; 
}

Krawedz *wez_nast(){return nastKrawedz;}

void ustaw_nast(Krawedz *N){
nastKrawedz= new Krawedz;
nastKrawedz=N;
  }






};


class Lista{

protected:
int rozmiar;
Krawedz *poczatek;

public:

Lista(){rozmiar=0; poczatek=NULL;}
Krawedz *wez_poczatek(){return poczatek;} 
int wez_rozmiar(){return rozmiar;}
void dodaj_krawedz(int p, int k, int w);
void wyswetl_liste();
int operator[](int pozycja);
void zmien_wage(int koniec, int waga);
};







class ListaGraf: public Graf{

Lista *tab;

public:

ListaGraf(){};
ListaGraf(int w, float g);

virtual void wyswietl_graf() override;
virtual void losowy_graf() override;
void Dijkstra_algorytm(std::string nazwa_pliku,int wierzcholek,bool zapisz_sciezke, bool wyswietl);
int czytaj_plik(std::string nazwa_pliku);


};

int wez_najbliszyl(int* dystans, bool* odwiedzone, int rozmiar);
void wyswietl_sciezkel(int* dystans, int* odwiedzone, int rozmiar);
void zapiszl(std::string FileName, int* tmp_dist, int* parent,int rozmiar);




#endif