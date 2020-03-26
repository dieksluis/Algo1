// Implementatie van klasse Mastermind.

#include <iostream>
#include <fstream>   // om in te lezen
#include <string>
#include <stdlib.h>
#include <utility>
#include <vector>
#include "standaard.h"
#include "bomberman.h"

using namespace std;

//*************************************************************************

Bomberman::Bomberman ()
{
  // TODO: implementeer deze functie 
	for (int i = 0; i < 21; i++)
		for (int j = 0; j < 21; j++)
			speelveld[i][j] = '-';
}  // default constructor

//*************************************************************************

Bomberman::~Bomberman ()
{
  // TODO: implementeer zo nodig deze functie

}  // destructor

//*************************************************************************

bool Bomberman::leesin (const char *invoernaam)
{
  // TODO: implementeer deze functie
  string x;
  char kar;
	ifstream ifs (invoernaam);
	if (ifs.is_open()) {
			ifs >> nrrijen;
			ifs >> nrkolommen;
			for (int i = 1; i <= nrrijen; i++) {
				for (int j = 1; j <= nrkolommen; j++) {
					ifs.get(kar);
					if (kar == '\n')
						ifs.get(kar);
					speelveld[i][j] = kar;
				}//for
			}//for
	}//if
	else 
		return false;
	return true;
}  // leesin

//*************************************************************************

int Bomberman::getnrrijen ()
{
  return nrrijen;

}

//*************************************************************************

int Bomberman::getnrkolommen ()
{
  return nrkolommen;

}

//*************************************************************************

char Bomberman::getvakje (int rij, int kolom)
{
  return speelveld[rij][kolom];

}  // getvakje

vector <pair <int,int> > Bomberman::bepaalnietequivalentezetten ()
{
    vector <pair <int,int> > zetten;
    vector < vector <int> > score;
    bool uniek;
    int x, y, index;
    for (int i = 1; i <= nrrijen; i++)
        for (int j = 1; j <= nrkolommen; j++)
            if((geweest[i][j]) && speelveld[i][j] != 'x' && speelveld[i][j] != '+') {
                uniek = true;
                vector<int> krat;
                //krat.push_back(0);
                y = i;
                //cout << "vakje: " << j << " , " << i << endl;
                while (y > 0 && (speelveld[y][j] != 'x' && speelveld[y][j] != '+'))
                    y--;
                if (speelveld[y][j] == '+')
                    krat.push_back(kratten[y][j]);
                x = j;
                while (x <= nrkolommen && (speelveld[i][x] != 'x' && speelveld[i][j] != '+'))
                    x++;
                if (speelveld[i][x] == '+')
                    krat.push_back(kratten[i][x]);
                y = i;
                while (y <= nrrijen && (speelveld[y][j] != 'x' && speelveld[y][j] != '+'))
                    y++;
                if (speelveld[y][j] == '+')
                    krat.push_back(kratten[y][j]);
                x = j;
                while (x > 0 && (speelveld[i][x] != 'x' && speelveld[i][j] != '+'))
                    x--;
                if (speelveld[i][x] == '+')
                    krat.push_back(kratten[i][x]);
                sort(krat.begin(), krat.end(), greater<int>());
                index = 0;
                while (index < score.size()){
                    if ((score[index].size() == krat.size()) && (score[index] == krat) ) {
                        uniek = false;
                    }//if
                    index++;
                }//while
                if (uniek){
                    score.push_back(krat);
                    pair <int,int> coordinaat;
                    coordinaat.first = i;
                    coordinaat.second = j;
                    zetten.push_back(coordinaat);
                }//if
            }//if
    /*int t = 0;
    int deletes = 0;
    while (t < score.size()){
        if (score[t][0] == -1){
            zetten.erase(zetten.begin() + (t - deletes));
            deletes++;
        }//if
        t++;
    }//while
     */
    return zetten;

}  // bepaalnietequivalentezetten

//*************************************************************************

void Bomberman::drukaf () {
    vector < pair <int, int> > a;
	for (int i = 1; i <= nrrijen; i++){
		for (int j = 1; j <= nrkolommen; j++)
			cout << speelveld[i][j];
		cout << endl;
	}//for
    a = bepaalnietequivalentezetten ();
    for (int k = 0; k < a.size(); k++)
        cout << a.at(k).first << "," << a.at(k).second << endl;
}  // drukaf

//*************************************************************************

bool Bomberman::eindstand ()
{
  // TODO: implementeer deze functie

  return false;

}  // eindstand

bool Bomberman::mogelijk (int rij, int kolom) { 
	if ((rij > nrrijen) || (rij < 1))
		return false;
	else if ((kolom > nrkolommen) || (kolom < 1)) 
		return false; 
	else if (getvakje(rij, kolom) == 'x' || getvakje(rij, kolom) == '+')
		return false;
	else 
		return true; 
}//mogelijk

void Bomberman::locatie() {
	for (int i = 1; i <= nrrijen; i++)
		for (int j = 1; j <= nrkolommen; j++) {
			if (speelveld[i][j] == 'o') {
				spelerY = i;
				spelerX = j;
			}//if
		}//for
}//locatie

bool Bomberman::bereikbaar (int rij, int kolom) {
	for (int i = 1; i <= nrrijen; i++)
		for (int j = 1; j <= nrkolommen; j++) {
			if (speelveld[i][j] != '-') 
				geweest[i][j] = true;
			else 
				geweest[i][j] = false;
		}//for
	DFS(spelerY, spelerX, rij, kolom);
    if (geweest[rij][kolom] == true && speelveld[rij][kolom] != '+' && speelveld[rij][kolom] != 'x')
        return true;
    else
        return false;
}//bereikbaar

void Bomberman::DFS(int hY, int hX, int dY, int dX){
	geweest[hY][hX] = true;
	if ((hY > 1) && geweest[hY-1][hX] == false)
		DFS(hY-1, hX, dY, dX);
	if ((hX < nrkolommen) && geweest[hY][hX+1] == false)
		DFS(hY, hX+1, dY, dX);
	if ((hY < nrrijen) && geweest[hY+1][hX] == false)
		DFS(hY+1, hX, dY, dX);
	if ((hX > 1) && geweest[hY][hX-1] == false)
		DFS(hY, hX-1, dY, dX);	
}//DFS

//*************************************************************************

void Bomberman::plaatsbom (int bomrij, int bomkolom)
{	
	locatie(); //update locatie speler
	if (!(mogelijk(bomrij, bomkolom)))
		cout << "Zet buiten bord of op krat! Denk eens na..." << endl;
	else if (bereikbaar(bomrij, bomkolom)){
		speelveld[bomrij][bomkolom] = 'o';
		speelveld[spelerY][spelerX] = '-';
		locatie(); //update locatie speler
	}//else if
	else 
		cout << "Zet niet bereikbaar." << endl;
}  // plaatsbom

void Bomberman::kratNummer() {
    int teller = 1;
    for (int i = 1; i <= nrrijen; i++)
        for (int j = 1; j <= nrkolommen; j++)
            if (speelveld[i][j] == '+'){
                kratten[i][j] = teller;
                teller++;
            }//if
            
}//kratNummer


//*************************************************************************



//*************************************************************************

int Bomberman::aantalbommen (int &aantalstanden, int &optrij, int &optkolom)
{
  // TODO: implementeer deze functie

  return 0;

}  // aantalbommen

//*************************************************************************

int Bomberman::aantalkrattengretig (int &goederij, int &goedekolom)
{
  // TODO: implementeer deze functie

  return 0;

}  // aantalkrattengretig

//*************************************************************************

int Bomberman::aantalbommengretig (int &goederij, int &goedekolom)
{
  // TODO: implementeer deze functie

  return 0;

}  // aantalbommengretig

//*************************************************************************
