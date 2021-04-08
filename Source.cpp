#include <iostream>
#include <cmath>
#include <algorithm>
#include <fstream>
#include <vector>
#include <iomanip>

struct dot {
	double x;		//koordinates tikrinamu tasku
	double y;
};

int skaiciuota = 0;				//kiek kartu suskaiciuota funkcija

double a = 6, b = 3;  //studento pazymejimo skc

std::vector<dot> taskai; //rastiems taskams isvesti i faila

bool Isrikiavimas(dot& s1, dot& s2) {		//ne visi taskai algoritme yra is eiles, todel juos surikiuoja
	return s1.x < s2.x;
}

double f_realizuota(double x) {
	double rez = ((x * x - a) * (x * x - a)) / b - 1;	
	skaiciuota++;
	return rez;
}

void Sortinimas() {
	std::sort(taskai.begin(), taskai.end(), Isrikiavimas);
	for (int i = 0; i < taskai.size(); i++) {				//isrikiuoja nuo maziausio iki didziausio
		if (i + 1 != taskai.size()) {						//kartais taskai dubliuojasi, nes gali buti
			if (taskai.at(i).x == taskai.at(i + 1).x) {		//naudojami keliems skaiciavimams, tai reikia istrinti pasikartojima
				taskai.erase(taskai.begin() + i);
				i--;
			}
		}

	}
}

void prideti(double x, double y) {
	dot taskas;
	taskas.x = x;
	taskas.y = y;
	taskai.push_back(taskas);
}

void Spausdinti(int a)
{
	std::ofstream RZ("RZ.txt");
	for (int i = 0; i < taskai.size(); i++) {
		RZ << std::setprecision(10) << taskai.at(i).x << " " << taskai.at(i).y << std::endl;
	}
	RZ << a << " kartu(s) vyko iteracija" << std::endl << skaiciuota << " kartu(s) vyko funkcijos skaiciavimas";
	RZ.close();
}



void f_dalijimas() {
	int k = 0, l = 2;
	double X1 = 0, X2 = 10, Y1, Y2, Y3, X3;		//1 ir 2 krastiniai, 3 vidurys
	while ((X2 - X1) > 0.0001) {
		if (l != 1) {
			Y1 = f_realizuota(X1);
			prideti(X1, Y1);
			Y2 = f_realizuota(X2);
			prideti(X2, Y2);
		}
		if (l != 0) {
			X3 = (X2 + X1) / 2;
			Y3 = f_realizuota(X3);
			prideti(X3, Y3);
		}
		if (Y1 < Y3) {		//taskai arciau minimumo tampa sekancio intervalo krastiniais taskais
			X2 = X3;
			Y2 = Y3;
			l = 1;
		}
		else if (Y2 < Y3) {
			X1 = X3;
			Y1 = Y3;
			l = 1;
		}
		else {
			X1 = (X3 + X1) / 2;		//sustumia krastines
			X2 = (X2 + X3) / 2;
			l = 0;
		}
		k++;
	}
	Sortinimas();
	Spausdinti(k);
}


void f_dalijimas_2() {
	double left = 0, right = 10, L, X1, X2, Xv, Y1, Y2, Yv;	//taskai
	int k = 0, l = 2; 

	L = 1; //tik pradzioje

	while (L > 0.0001) {

		L = right - left;

			X1 = left + (L / 4); 
			Y1 = f_realizuota(X1);
			prideti(X1, Y1);

			X2 = right - (L / 4);
			Y2 = f_realizuota(X2);
			prideti(X2, Y2);

			Xv = (X2 + X1) / 2;
			Yv = f_realizuota(Xv);
			prideti(Xv, Yv);
		
		if (Y1 < Yv) {	
			right = Xv;
		}
			else if (Y2 < Yv) {
				left = Xv;
			}
				else {	
					left = X1;
					right = X2;
				}
		k++;
	}
	Sortinimas();
	Spausdinti(k);

}

void f_pjuvis() {
	int o = 0;			//iteraciju skaiciavimui
	double W1, W2, Y1 = 0, Y2 = 0, l = 2, k = 0, d = 1, F = 0.618;  //F - fibonacio sk, 
	W1 = 1 - F;
	W2 = F;
	while (d - k > 0.00001)									//tikslumas iki -4laipsnio
	{
		if (l != 1) {		//perskaiciuojamas pirmas taskas
			Y1 = f_realizuota(W1 * 10);						//intervalas [0,10]
			prideti(W1 * 10, Y1);
		}
		if (l != 0) {					//perskaiciuojamas antras taskas
			Y2 = f_realizuota(W2 * 10);
			prideti(W2 * 10, Y2);
		}
		if (Y1 > Y2) {
			k = W1;
			W1 = W2;
			Y1 = Y2;
			W2 = k + F * (d - k);
			l = 1;
		}
		else {			//l = 2 pradzioje, skaiciuoja abu taskus
			d = W2;
			W2 = W1;
			Y2 = Y1;
			W1 = d - F * (d - k);
			l = 0;
		}
		o++;
	}
	if (l != 1) {
		Y1 = f_realizuota(W1 * 10);
		prideti(W1 * 10, Y1);
	}
	if (l != 0) {
		Y2 = f_realizuota(W2 * 10);
		prideti(W2 * 10, Y2);
	}
	Sortinimas();
	Spausdinti(o);
}

void f_niutonas() {
	int k = 0;
	double X1 = 5, X2 = 0; //pradinis turi but 5 pagal salyga S
	while (abs(X1 - X2) > 0.0001) {
		X2 = X1;
		X1 = X2 - ((X2 * X2 * X2 - X2*6) / (3 * (X2 * X2) - 6)); //X2 * a pakeista ir vietoj -1 i -6
		k++;
		prideti(X2, f_realizuota(X2));
	}
	Spausdinti(k);
}

int main(){
	

	std::cout << "1 - Dalijimo pusiau algoritmas" << std::endl
		<< "2 - Auksinio pjuvio algoritmas" << std::endl
		<< "3 - Niutono algoritmas" << std::endl
		<< "4 - Dalijimas ver. 2" << std::endl;

	int option;

	std::cin >> option;
	
	switch (option) {
	case 1:
		f_dalijimas();
		break;
	case 2:
		f_pjuvis();
		break;
	case 3:
		f_niutonas();
		break;
	case 4:
		f_dalijimas_2();		//algoritmas pagal destytoja
		break;
	default:
		std::cout << "Error" << std::endl;
	}


	return 0;
}