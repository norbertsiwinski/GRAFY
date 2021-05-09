#include <iostream>
#include <stdio.h>
#include "Lista.hh"

using namespace std;


void Lista::zmien_wage(int koniec, int waga){

Krawedz *pomoc=new Krawedz;
pomoc= poczatek;

for (int i = 0; i < koniec; i++)
	{
		pomoc= pomoc->wez_nast();
	}

 pomoc->ustaw_wage(waga);
}






void Lista::dodaj_krawedz(int p, int k, int g){

Krawedz *nast=new Krawedz;
nast->wartosc(p,k,g);

if(poczatek==NULL){
 poczatek=nast;
}
else{

Krawedz *pomoc = poczatek;
poczatek=nast;
nast->ustaw_nast(pomoc);

}
rozmiar++;
}





void Lista::wyswetl_liste(){

Krawedz *pomoc=poczatek;

while(pomoc){

cout<< pomoc->wez_poczatek()<< " waga:" << pomoc->wez_wage() <<" "<< pomoc -> wez_koniec()<< endl;

pomoc=pomoc->wez_nast();
}

}

int Lista::operator[](int pozycja){

Krawedz *pomoc=new Krawedz;
pomoc=poczatek;

for (int i = 0; i < pozycja; i++)
			pomoc = pomoc->wez_nast();

	return pomoc->wez_wage();

}





/*************/

ListaGraf::ListaGraf(int w, float g):Graf(w,g){


	tab=new Lista[w];

for(int i=0; i<w; i++){
			for (int j = 0; j < w; j++)
					tab[i].dodaj_krawedz(i,j,INF);
			}
};







void ListaGraf::losowy_graf(){

int rozmiar = wez_wierzcholek();
float gestosc = wez_gestosc();
int krawedzie = (gestosc*rozmiar*(rozmiar-1))/2;


srand(time(NULL));
		for (int i = 0; i < krawedzie; i++)
		{
			int losowy_poczatek = rand() % rozmiar;
			int losowy_koniec = rand() % rozmiar;
			 int losowa_waga = rand() % rozmiar;
			

	 if (tab[losowy_koniec][losowy_poczatek] == INF && tab[losowy_poczatek][losowy_koniec] == INF && losowy_poczatek != losowy_koniec)
			 {
				

				 tab[losowy_koniec].zmien_wage(losowy_poczatek,losowa_waga);
				 tab[losowy_poczatek].zmien_wage(losowy_koniec,losowa_waga);
			 }
			 else
				 i--;
		}

}


void ListaGraf::wyswietl_graf(){


		 int rozmiar = wez_wierzcholek();

		 for (int i = 0; i < rozmiar; i++)
		 {
			 if (i == 0)
				 std::cout << std::endl << "First Edge" << std::endl;

			 else if (i != rozmiar - 1)
				 std::cout << std::endl << "Next Edge: " << std::endl;

			 else
				 std::cout << std::endl << "Last Edge: " << std::endl;

			 
		 for (int j = 0; j < rozmiar; j++){
			
		 if (tab[i][j] != INF)
				 std::cout << i << "->" << "Weight:" << tab[i][j] << "->" << j << std::endl;
		 }
	 }
}





	 int wez_najbliszyl(int* dystans, bool* odwiedzone, int rozmiar)
	 {
		
		 int min_wartosc = INF;
		 int min_wezel= 0;

		 for (int i = 0; i < rozmiar; i++)
		 {
			 if (!odwiedzone[i] && dystans[i] < min_wartosc)
			 {
				 min_wartosc = dystans[i];
				 min_wezel = i;
			 }
		 }
		 return min_wezel;
	 }



void ListaGraf::Dijkstra_algorytm(std::string nazwa_pliku,int wierzcholek,bool zapisz_sciezke, bool wyswietl){

int rozmiar = wez_wierzcholek();

		 int* poprzednik = new int[rozmiar];
		 int* dystans = new int[rozmiar];
		 for (int i = 0; i < rozmiar; i++)
		 {
			 poprzednik[i] = 0;
			 dystans[i] = INF;
		 }
		 dystans[wierzcholek] = 0;
		 poprzednik[wierzcholek] = -1;


		 bool* odwiedzone = new bool[rozmiar];
		 for (int i = 0; i < rozmiar; i++)
			 odwiedzone[i] = false;


		 for (int i = 0; i < rozmiar; i++)
		 {
			 int najblizszy = wez_najbliszyl(dystans,odwiedzone,rozmiar);
			 odwiedzone[i] = true;

			 for (int j = 0; j < rozmiar; j++)
			 {
				 if (tab[najblizszy][j] != INF && dystans[j] > dystans[najblizszy] + tab[najblizszy][j])
				 {
					 dystans[j] = dystans[najblizszy] + tab[najblizszy][j];
					 poprzednik[j] = najblizszy;
				 }
			 }
		 }


		 if (wyswietl == true){
			wyswietl_sciezkel(dystans, poprzednik,rozmiar);
			}
		 if(zapisz_sciezke == true){
			zapiszl(nazwa_pliku, dystans, poprzednik,rozmiar);
			 }

	 }



 void wyswietl_sciezkel(int* dystans, int* poprzednik, int rozmiar)
	 {
	
		 for (int i = 0; i < rozmiar; i++) {
			 int temp = poprzednik[i];
			 std::cout << i << " <- ";
			 while (temp != -1)
			 {
				 std::cout << temp << " <- ";
				 temp = poprzednik[temp];
			 }
			 std::cout << "Dystans: " << dystans[i];
			 std::cout << std::endl;
		 }
	 }



	 void zapiszl(std::string FileName, int* dystans, int* poprzednik,int rozmiar)
	 {

	
		 std::fstream file;
		 file.open(FileName, std::ios::out);

		 if (file.good())
		 {
			 for (int i = 0; i < rozmiar; i++) {
				 int temp = poprzednik[i];
				 file << i << " <- ";
				 while (temp != -1)
				 {
					 file << temp << " <- ";
					 temp = poprzednik[temp];
				 }
				 file << "Dystans: " << dystans[i];
				 file << std::endl;
			 }
			 file.close();
		 }
	 }


int ListaGraf::czytaj_plik(std::string nazwa_pliku){


int poczatek_d;
		 int poczatek_w, koniec, waga;
		 int krawedzie;

		 std::fstream file;
		 file.open(nazwa_pliku, std::ios::in);

		 if (file.good())
		 {
			 file >> krawedzie >> wierzcholek >> poczatek_d;

		
			 tab = new Lista[wierzcholek];

			 for (int i = 0; i < wierzcholek; i++)
			 {
				 for (int j = 0; j < wierzcholek; j++)
					 tab[i].dodaj_krawedz(i,j, INF);
			 }


			 while (!file.fail())
			 {
				 file >> poczatek_w >> koniec >> waga;
				 tab[poczatek_w].zmien_wage(koniec, waga);
				 tab[koniec].zmien_wage(poczatek_w, waga);
			 }
		 }
		 file.close();

		 return  poczatek_d;
	 }


