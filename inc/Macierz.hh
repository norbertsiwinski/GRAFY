#ifndef MACIERZ_HH
#define MACIERZ_HH
#include "Graf.hh"
#define INF 999999

 class Macierz:public Graf{

private:

int **tab;
int waga;

public:

Macierz(int w, float g);
Macierz(){tab=nullptr;};

virtual void wyswietl_graf() override;
virtual void losowy_graf() override;
void Dijkstra_algorytm(std::string FileName,int wierzcholek,bool zapisz_sciezke, bool wyswietl);
int czytaj_plik(std::string nazwa_pliku);

};
void wyswietl_sciezke(int* dystans, int* poprzednik, int rozmiar);
int wez_najbliszy(int* dystans, bool* odwiedzone, int rozmiar);
void zapisz(std::string FileName, int* tmp_dist, int* parent,int rozmiar);
#endif