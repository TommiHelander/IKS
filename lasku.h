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

#ifndef LASKU_H
#define LASKU_H

/* ----------------------------------------------------
LUOKAN NIMI: Lasku
LUOKAN FUNKTIOT: kysely(), laske(), tulosta(), tallenna(), laske_leveys()
LUOKAN TOIMINTO: Kysyy käyttäjältä lähtötiedot, suorittaa laskutoimitukset,
ja tulostaa tulokset. Tulokset voi sitten tallentaa tekstitiedostoon.
------------------------------------------------------*/

class Lasku
{
public:
    
    Lasku();
    ~Lasku();
    
    // lähtötietojen muuttujat
    float c;
    float s_kuva;
    int mb;
    int q;
    int p;
    int leveys;
    
    int tallennusmuoto;
    
    // laske -funktion muuttujat
    float s_maasto;
    float H;
    float a;
    float reunavara;
    float L;
    float n;
    float b;
    
    // laske_leveys -funktion yleiset muuttujat
    float X_lista[20];
    float Y_lista[20];
    
    void kysely();
    void laske();
    void tulosta();
    void tallenna();
    void laske_leveys();
    
protected:
    int k_vakio;
    int sk;
    float np;
    
    // laske_leveys -funktion muuttujat tässä
    char choice;
    int kulmien_lkm;
    float x_koord;
    float y_koord;
    float x_pienin;
    float x_suurin;
    float y_pienin;
    float y_suurin;
    float dX;
    float dY;
		
};

#endif // LASKU_H
