/*-----------------------------------------------------------------------

Copyright (C) 2008 by Tommi Lindqvist
lindqvist.tommi@gmail.com

This file is part of IKS.

IKS is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

IKS is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with IKS.  If not, see <http://www.gnu.org/licenses/>. 

-------------------------------------------------------------------------*/

#include <cstdlib>
#include <iostream>
#include <math.h>
#include <fstream>
#include "lasku.h"
#include "btree.h"

/* ----------------------------------------------------
LUOKAN NIMI: Lasku
LUOKAN FUNKTIOT: kysely(), laske(), tulosta(), tallenna(), laske_leveys()
LUOKAN TOIMINTO: Kysyy käyttäjältä lähtötiedot, suorittaa laskutoimitukset,
ja tulostaa tulokset. Tulokset voi sitten tallentaa tekstitiedostoon.
------------------------------------------------------*/

using namespace std;

Lasku::Lasku()    // Konstruktori
{
	
}


Lasku::~Lasku()   // Destruktori
{
	
}

void Lasku::kysely()      //kysyy käyttäjältä lähtötiedot
{
    cout<<"\nKameravakio (mm): ";
    cin>> k_vakio;
    cin.ignore();
    c = (float)k_vakio / 1000;
    
    cout<<"\nIlmakuvan sivun pituus (cm): ";
    cin>> sk;
    cin.ignore();
    s_kuva = (float)sk / 100;
    
    cout<<"\nSuurin sallittu kuvausmittakaava: 1:";
    cin>> mb;
    cin.ignore();
    
    cout<<"\nHaluttu sivupeitto prosentteina: ";
    cin>> q;
    cin.ignore();
    
    cout<<"\nHaluttu pituuspeitto prosentteina: ";
    cin>> p;
    cin.ignore();
    
    if ( leveys == 0 )
    {
         cout<<"\nKuvattavan alueen leveys (m): ";
         cin>> leveys;
         cin.ignore();
    }
    
}

void Lasku::laske()                //suorittaa laskutoimituksen ja korjaa arvot tarvittaessa
{
    s_maasto = (s_kuva * mb) / 1;
    H = (c * mb) / 1;
    a = s_kuva * mb * (1 - ( (float)q / 100));
    reunavara = (H * 0.10) + (mb /100);
    L = leveys + (2 * reunavara);
    n = ((L - s_maasto) / a) + 1;
    b = s_kuva * mb * (1 - ( (float)p / 100));
    
    np = ceilf(n);
    
    if ( ( np - n ) > 0.1 ) {
         n = np;
         s_maasto = L / ( 0.3 + 0.7 * n );
         mb = (s_maasto * 1) / s_kuva;
         H = (c * mb) / 1;
         a = s_kuva * mb * (1 - (q / 100));
         reunavara = (H * 0.10) + (mb /100);
         L = leveys + (2 * reunavara);
         b = s_kuva * mb * (1 - (p / 100));
    }
    else {
         n = np;
    }
}

void Lasku::tulosta()          //tulostaa laskutoimituksen tulokset näytölle
{
    cout<<"-------------------------------------------\n\n";
    cout<<"Tulokset:\n\n";
    cout<<"Kuvausmittakaava: 1:"<< mb <<endl;
    cout<<"Kuvan sivun pituus maastossa: "<< s_maasto <<" m\n";
    cout<<"Lentokorkeus: "<< H <<" m\n";
    cout<<"Kuvausjonojen välimatka: "<< a <<" m\n";
    cout<<"Reunavara: "<< reunavara <<" m\n";
    cout<<"Kuvattavan alueen kokonaisleveys: "<< L <<" m\n";
    cout<<"Lentojonojen lkm: "<< n <<endl;
    cout<<"Kuvakanta: "<< b <<" m\n\n";
    cout<<"-------------------------------------------\n";
}

void Lasku::tallenna()         // tallentaa laskelmaraportin tekstitiedostoon
{
     char projekti[20];
     char nimi[20];
	 char polku[60] = "C:\\Program Files\\IKS\\IKS_Data\\";
     char kokopolku[80];
	 char valinta;

     cout<<"Projektinimi: ";
     cin.getline( projekti, 20, '\n' );
     cout<<"Tiedostonimi: ";
     cin.getline( nimi, 20, '\n' );
	 cout<<"Polku: '"<< polku <<"'. Muuta [m] Jatka [j]";
	 cin>> valinta;
	 cin.ignore();

	 if ( valinta == 'm' )
	 {
		 cout<<"Uusi polku: ";
		 cin.getline( polku, 60, '\n' );
	 }

     kokopolku[0] = '\0';
     strcat( kokopolku, polku );
     strcat( kokopolku, nimi );
     ofstream tiedosto ( kokopolku );
     
     tiedosto<<"IKS LASKELMARAPORTTI\n\n";
     tiedosto<<"--------------------------------------------------\n\n";
     tiedosto<<"PROJEKTI: "<< projekti << "\n\n";
     tiedosto<<"--------------------------------------------------\n\n";
     
     switch ( tallennusmuoto ) {
            case 1:
                 tiedosto<<"LASKELMATYYPPI: Kuvattavan alueen leveyden perusteella\n\n";
                 tiedosto<<"--------------------------------------------------\n\n";
                 tiedosto<<"LÄHTÖTIETOJA:\n\n";
                 break;
            case 2:
                 tiedosto<<"LASKELMATYYPPI: Kuvattavan alueen kulmien koordinaattien perusteella\n\n";
                 tiedosto<<"--------------------------------------------------\n\n";
                 tiedosto<<"LÄHTÖTIETOJA:\n\n";
                 tiedosto<<"Kulmapisteiden koordinaatit:\n\n";
                 int x;
                 for ( x = 0; x < kulmien_lkm; x++ ) {
                     tiedosto<<"Piste "<< x + 1 <<"-> X: "<< X_lista[x] <<" Y: "<< Y_lista[x] <<endl;
                 }
                 tiedosto<<"\nKuvattavan alueen leveys koordinaattien perusteella: "<< leveys <<" m\n\n";
                 break;
     }          
     tiedosto<<"Kameravakio: "<< k_vakio <<" mm\n";
     tiedosto<<"Sivun pituus kuvassa: "<< sk <<" cm\n";
     tiedosto<<"Sivupeitto: "<< q <<" %\n";
     tiedosto<<"Pituuspeitto: "<< p <<" %\n";
     tiedosto<<"Kuvattavan alueen leveys: "<< leveys <<" m\n\n";
     tiedosto<<"--------------------------------------------------\n\n";
     tiedosto<<"LASKENNAN TULOKSET:\n\n";
     tiedosto<<"Kuvausmittakaava: 1:"<< mb <<"\n";
     tiedosto<<"Sivun pituus maastossa: "<< s_maasto <<" m\n";
     tiedosto<<"Lentokorkeus: "<< H <<" m\n";
     tiedosto<<"Kuvausjonojen välimatka: "<< a <<" m\n";
     tiedosto<<"Reunavara: "<< reunavara <<" m\n";
     tiedosto<<"Kuvattavan alueen kokonaisleveys: "<< L <<" m\n";
     tiedosto<<"Lentojonojen lkm: "<< n <<"\n";
     tiedosto<<"Kuvakanta: "<< b <<" m\n\n";
     tiedosto<<"--------------------------------------------------\n\n";
     
     tiedosto.close();
     cout<<"Laskelmaraportti tallennettu kohteeseen '"<< kokopolku <<"'!\n";
     cin.get();
}

// sijoittaa käyttäjän antamat koordinaatit x- ja y-binääripuihin joista se laskee kuvattavan alueen leveyden
void Lasku::laske_leveys()                  
{
    Btree x_tree;
    Btree y_tree;
                 
    cout<<"\nKuvattavan alueen kulmien lkm: ";
    cin>> kulmien_lkm;
    cin.ignore();
    
    float x_lista[20];
    float y_lista[20];
                 
    int x = 0;
    do {
       cout<<"\n"<<"Piste "<< x + 1 <<":\n\n";
       cout<<"X: ";
       cin>> x_koord;
       cin.ignore();
       x_lista[x] = x_koord;
       X_lista[x] = x_lista[x];
       x_tree.insert( x_koord );
                     
       cout<<"Y: ";
       cin>> y_koord;
       cin.ignore();
       y_lista[x] = y_koord;
       Y_lista[x] = y_lista[x];
       y_tree.insert( y_koord );
                     
       x++;
    } while ( x < kulmien_lkm );
                 
    x_tree.search_smallest();
    x_pienin = x_tree.pienin;
    x_tree.search_biggest();
    x_suurin = x_tree.suurin;
    y_tree.search_smallest();
    y_pienin = y_tree.pienin;
    y_tree.search_biggest();
    y_suurin = y_tree.suurin;
                 
    dX = x_suurin - x_pienin;
    dY = y_suurin - y_pienin;
                 
    if ( dX < dY )
    {
       leveys = (int)dX;
    }
    else
    {
        leveys = (int)dY;
    }
    
    cout<<"\nKuvattavan alueen leveys on "<< leveys <<" m\n";
    cout<<"Laske painamalla ENTER\n";
    cin.get();
    
    /*x_tree.destroy_tree();
    y_tree.destroy_tree();*/
    
}
