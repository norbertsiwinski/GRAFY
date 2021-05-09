#include "Macierz.hh"
using namespace std;

Macierz::Macierz(int w, float g): Graf(w, g){
	
tab = new int* [w];
	for (int i = 0; i < w; i++)
	{
		tab[i] = new int[w];
	}


	for (int j = 0; j < w; j++)
	{
		for (int i = 0; i < w; i++)
			tab[j][i] = INF;
	}

};


void Macierz::wyswietl_graf(){

int w=wez_wierzcholek();

for(int i=0; i<w; i++){

for(int j=0; j<w; j++){

cout<<tab[i][j]<<" ";

}
cout<<endl;
}
}





void Macierz::losowy_graf(){

int rozmiar = wez_wierzcholek();
float gestosc = wez_gestosc();
int krawedzie = (gestosc*rozmiar*(rozmiar-1))/2;


	 srand(time(NULL));
	 for (int i = 0; i < krawedzie; i++)
		{
            int losowy_poczatek = rand() % rozmiar;
			int losowy_koniec = rand() % rozmiar;
			 float losowa_waga = rand() % 1000+1;
           

			if (tab[losowy_poczatek][losowy_koniec] ==INF && tab[losowy_koniec][losowy_poczatek] == INF && losowy_poczatek != losowy_koniec)
				{
					tab[losowy_poczatek][losowy_koniec] = losowa_waga;
					tab[losowy_koniec][losowy_poczatek] = losowa_waga;
				}
			else
				i--;
	}
		}


int wez_najbliszy(int* dystans, bool* odwiedzone, int rozmiar){


int min_wartosc= INF;
int min_wezel=0;

for(int i=0; i<rozmiar; i++){

	if(!odwiedzone[i] && dystans[i]< min_wartosc){

		min_wartosc=dystans[i];
		min_wezel=i;
	}
}

return min_wezel;
}


void Macierz::Dijkstra_algorytm(std::string nazwa_pliku,int wierzcholek,bool zapisz_sciezke, bool wyswietl){

int rozmiar=wez_wierzcholek();

int* poprzednik=new int[rozmiar];
int *dystans=new int[rozmiar];

for(int i=0; i<rozmiar; i++){
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
		 int najbliszy = wez_najbliszy(dystans, odwiedzone, rozmiar);
		 odwiedzone[i] = true;

		 for (int j = 0; j < rozmiar; j++)
			{
			 if (tab[najbliszy][j] != INF && dystans[j] > dystans[najbliszy] + tab[najbliszy][j])
				{
					dystans[j] = dystans[najbliszy] + tab[najbliszy][j];
					poprzednik[j] = najbliszy;
				}
			}
	 }

		 if (wyswietl == true){
			wyswietl_sciezke(dystans, poprzednik,rozmiar);
			}
		 if(zapisz_sciezke == true){
			zapisz(nazwa_pliku, dystans, poprzednik,rozmiar);
			 }



}

void wyswietl_sciezke(int* dystans, int* poprzednik, int rozmiar){

for(int i=0; i<rozmiar; i++){

int pomoc=poprzednik[i];

cout<< i << " <-";

 while (pomoc != -1)
		 {
			 std::cout << pomoc << " <- ";
			 pomoc = poprzednik[pomoc];
		 }
		 std::cout << "Dystans: " << dystans[i];
		 std::cout << std::endl;
	 }



}

int Macierz::czytaj_plik(std::string nazwa_pliku){


int poczatek_d;
	 int poczatek_w, koniec, waga;
		 int krawedzie;

		 std::fstream file;
		 file.open(nazwa_pliku, std::ios::in);

		 if (file.good())
		 {
			 file >> krawedzie >> wierzcholek >> poczatek_d;

			 tab = new int* [wierzcholek];

			 for (int i = 0; i < wierzcholek; i++)
			 {
				 tab[i]=new int[wierzcholek];}

			for (int j = 0; j <wierzcholek; j++)
		 {
			 for (int i = 0; i < wierzcholek; i++)
				 tab[j][i] = INF;
			 
		 }



			 while (!file.fail())
		 {
			 file >> poczatek_w >> koniec>> waga;
			 tab[poczatek_w][koniec] = waga;
			 tab[koniec][poczatek_w] = waga;
		 }
		 }
		 file.close();

		 return  poczatek_d;

}



	 void zapisz(std::string FileName, int* dystans, int* poprzednik,int rozmiar)
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
