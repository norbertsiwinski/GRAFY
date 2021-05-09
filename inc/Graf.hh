#ifndef GRAF_HH
#define GRAF_HH
#include <iostream>
#include <stdio.h>
#include <fstream>


class Graf{

protected:

int wierzcholek;
float gestosc;

public:

Graf(){};
Graf(int w, float g){

wierzcholek=w;
gestosc=g;
}

int wez_wierzcholek(){return wierzcholek;}
float wez_gestosc(){return gestosc;}


virtual void wyswietl_graf()=0;
virtual void losowy_graf()=0;

};

#endif 