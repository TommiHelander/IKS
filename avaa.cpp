/*---------------------------------------------------------------------

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

-----------------------------------------------------------------------*/

#include <cstdlib>
#include <iostream>
#include <fstream>

using namespace std;

/*-------------------------------------------------------------------------------------
FUNKTIO: avaa()
TEHTÄVÄ: Avaa tallennetun tekstitiedoston luettavaksi näytölle
--------------------------------------------------------------------------------------*/

void avaa()
{
	char valinta;
	char polku[60] = "C:\\Program Files\\IKS\\IKS_Data\\";
	char kokopolku[80];

	cout<<"Polku: '"<< polku <<"'. Muuta [m] Jatka [j] ";
	cin>> valinta;
	cin.ignore();
	
	if ( valinta == 'm' ) {
		cout<<"\nUusi polku (HUOM! Erota kansiot kahdella (2) kenoviivalla '\\'): ";
		cin.getline( polku, 60, '\n' );
	}
	char nimi[20];
    cout<<"Tiedostonimi: ";
    cin.getline( nimi, 20, '\n' );
	kokopolku[0] = '\0';
	strcat( kokopolku, polku );
	strcat( kokopolku, nimi );
    ifstream tiedosto ( kokopolku );
     
    if ( !tiedosto.is_open() ) {
		cout<<"Virhe: Tiedostoa ei ole tai sitä ei voi avata. Tarkista polku ja tiedostonimi.\n";
    }
    else {
         char x;
         while ( tiedosto.get( x ) ) {
               cout<< x;
         }
    }
}
