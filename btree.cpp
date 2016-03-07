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
#include "btree.h" 
#include "node.h"

using namespace std;

// konstruktori
Btree::Btree()
{
	root = NULL;
}

// destruktori
Btree::~Btree()
{
	destroy_tree();
}

void Btree::destroy_tree( Node *leaf )
{
     if ( leaf != NULL )
     {
          destroy_tree( leaf->left );
          destroy_tree( leaf->right );
          delete leaf;
     }
}

void Btree::insert( float key, Node *leaf )
{
     if ( key < leaf->key_value )
     {
          if ( leaf->left != NULL )
          {
               insert( key, leaf->left );
          }
          else
          {
              leaf->left = new Node;
              leaf->left->key_value = key;
              leaf->left->left = NULL;
              leaf->left->right = NULL;
          }
     }
     else if ( key >= leaf->key_value )
     {
          if ( leaf->right != NULL )
          {
               insert( key, leaf->right );
          }
          else
          {
              leaf->right = new Node;
              leaf->right->key_value = key;
              leaf->right->left = NULL;
              leaf->right->right = NULL;
          }
     }
}

Node *Btree::search_smallest( Node *leaf )
{
    if (leaf != NULL )
    {
             if ( leaf->left != NULL )
             {
                  return search_smallest( leaf->left );
             }
             else
             {
                 pienin = leaf->key_value;
                 return leaf;
             }
    }
}

Node *Btree::search_biggest( Node *leaf )
{
    if ( leaf != NULL )
    {
         if ( leaf->right != NULL )
         {
              return search_biggest( leaf->right );
         }
         else
         {
             suurin = leaf->key_value;
             return leaf;
         }
    }
}

void Btree::insert( float key )
{
     if ( root != NULL )
     {
          insert( key, root );
     }
     else
     {
         root = new Node;
         root->key_value = key;
         root->left = NULL;
         root->right = NULL;
     }
}

Node *Btree::search_smallest()
{
     return search_smallest( root );
}

Node *Btree::search_biggest()
{
     return search_biggest( root );
}

void Btree::destroy_tree()
{
     destroy_tree( root );
}
