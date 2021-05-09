#include "Lista.hh"
#include "Macierz.hh"
#include <stdio.h>
#include <iostream>

using namespace std;


int main(){


clock_t start, stop;
double czas;

Macierz i(3,1);

i.losowy_graf();
start=clock();
i.Dijkstra_algorytm("zapis.txt",1,true,true);
stop=clock();
czas=(double)(stop-start)/CLOCKS_PER_SEC;
cout<<"czas:"<<czas<<endl;


ListaGraf L;
L.czytaj_plik("graf.txt");
L.wyswietl_graf();
L.Dijkstra_algorytm("zapis.txt",0,true,true);

cout<<endl;
Macierz M;
M.czytaj_plik("graf.txt");
//M.wyswietl_graf();
M.Dijkstra_algorytm("zapis.txt",0,true,true);

}

