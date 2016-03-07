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
#include "lasku.h"


using namespace std;

void avaa();

int main(int x)
{
    Lasku lasku;
    int valinta;
    if ( x == 1 )
    {
        cout<<"IKS 0.1.5.0 Copyright (C) 2008 by Tommi Lindqvist\n";
        cout<<"This software is released under the GNU General Public License.\nFor more information read License.txt.\n";
    }
    cout<<"\n1) Laske leveyden perusteella\n";
    cout<<"2) Laske kulmapisteiden perusteella\n";
    cout<<"3) Avaa laskelmaraportti\n";
    cout<<"4) Lopeta\n\n";
    cout<<"Valitse 1-4: ";
    
    cin>> valinta;
    cin.ignore();
    
    switch( valinta ) {
            case 1:
            {     
                lasku.leveys = 0;
                char choice;
                 
                lasku.kysely();                
                lasku.laske();
                lasku.tulosta();
                 
                cout<<"\nHaluatko tallentaa laskelmaraportin tekstitiedostoon? (k/e)";
                cin>> choice;
                cin.ignore();
                if ( choice == 'k' ) {
                     lasku.tallennusmuoto = 1;
                     lasku.tallenna();
                }
                break;
            }     
            case 2: 
            {   
                char choice;
                 
                lasku.laske_leveys();
                lasku.kysely();
                lasku.laske();
                lasku.tulosta();
                 
                cout<<"\nHaluatko tallentaa laskelmaraportin tekstitiedostoon? (k/e)";
                cin>> choice;
                cin.ignore();
                if ( choice == 'k' ) {
                      lasku.tallennusmuoto = 2;
                      lasku.tallenna();
                }
                break;
            }
            case 3:
                avaa();
                cin.get();
                break;
                 
            case 4:
                return 0;
                break;
                 
            default:
                 cout<<"Ei oikea valinta. Palaa valikkoon...\n";
                 cin.get();
                 break;
    }
    main(x+1);
}
