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

#ifndef NODE_H
#define NODE_H

/*
 * 
 */
class Node
{
	public:
           
		Node();          //konstruktori                                    
		
		~Node();         //destruktori
		
		float key_value;
		Node *left;
		Node *right;
		
};

#endif // NODE_H
