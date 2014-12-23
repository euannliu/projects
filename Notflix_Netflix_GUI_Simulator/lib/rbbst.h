/*
 * rbbst.h
 *
 *  Created on: Apr 14, 2014
 *      Author: kempe
 */

#include <iostream>
#include <exception>
#include <cstdlib>
#include "bst.h"

using namespace std;

/* -----------------------------------------------------
 * Red-Black Nodes 
 ------------------------------------------------------*/

enum Color {red, black};

template <class KeyType, class ValueType>
class RedBlackNode : public Node<KeyType, ValueType>
{
public:
	RedBlackNode (KeyType k, ValueType v, RedBlackNode<KeyType, ValueType> *p)
	: Node<KeyType, ValueType> (k, v, p)
	  { color = red; extraBlack = false; }

	virtual ~RedBlackNode () {}

	Color getColor () const
	{ return color; }

	void setColor (Color c)
	{ color = c; }
	
	bool extraBlack;

        /* The type casting allows us to treat getParent, getLeft, getRight
           as returning RedBlackNode instead of Node */
	virtual RedBlackNode<KeyType, ValueType> *getParent () const
	{ return (RedBlackNode<KeyType,ValueType>*) this->_parent; }

	virtual RedBlackNode<KeyType, ValueType> *getLeft () const
	{ return (RedBlackNode<KeyType,ValueType>*) this->_left; }

	virtual RedBlackNode<KeyType, ValueType> *getRight () const
	{ return (RedBlackNode<KeyType,ValueType>*) this->_right; }

protected:
	Color color;
};

/* -----------------------------------------------------
 * Red-Black Search Tree
 ------------------------------------------------------*/

template <class KeyType, class ValueType>
class RedBlackTree : public BinarySearchTree<KeyType, ValueType>
{
public:
  RedBlackTree()
  {
  	BinarySearchTree<KeyType,ValueType>::root=NULL;
  }
  void add (KeyType key, ValueType value)
  {
  	bool same = false;
  	Node<KeyType,ValueType> *temp_new_cast = new RedBlackNode<KeyType,ValueType>(key,value,NULL);
  	RedBlackNode<KeyType,ValueType> *temp_new = (RedBlackNode<KeyType,ValueType>*) temp_new_cast;
  	//Node<KeyType,ValueType> *temp_hold_cast;
  	RedBlackNode<KeyType,ValueType> *temp_hold;// = (RedBlackNode<KeyType,ValueType>*) temp_hold_cast;
  	
  	temp_new->setLeft(NULL);
  	temp_new->setRight(NULL);
  	//Adding
  	if(BinarySearchTree<KeyType,ValueType>::root==NULL)
  	{
  		temp_new->RedBlackNode<KeyType,ValueType>::setColor(black);
  		BinarySearchTree<KeyType,ValueType>::root = temp_new;
  	}
  	/*else if(BinarySearchTree<KeyType,ValueType>::lookup(temp_new->getKey()))
  	{
  		
  		//BinarySearchTree<KeyType,ValueType>::lookup(temp_new->getKey()) = temp_new->getValue();
  		same = true;
  	}*/
  	else
  	{
  		temp_hold = (RedBlackNode<KeyType,ValueType>*) BinarySearchTree<KeyType,ValueType>::root;
  		while(!same) //Traversing the tree
  		{
  			if(temp_hold->getKey()==temp_new->getKey())
  			{
  				temp_hold->setValue(temp_new->getValue());
  				same = true;
  				break;
  			}
	  		else if(temp_hold->getKey()<temp_new->getKey()) //if NEW is greater than HOLD
	  		{
	  			if(temp_hold->getRight()!=NULL)
	  				temp_hold = temp_hold->getRight();
	  			else
	  			{
	  				temp_hold->setRight(temp_new);
	  				temp_new->setParent(temp_hold);
	  				break;
	  			}
	  		}
	  		else
	  		{
	  			if(temp_hold->getLeft()!=NULL)
	  				temp_hold = temp_hold->getLeft();
	  			else
	  			{
	  				temp_hold->setLeft(temp_new);
	  				temp_new->setParent(temp_hold);
	  				break;
	  			}
	  		}
	  	}
  	}
  	
  	//replace temp_new with some arbitrary temp pointer and make this into a helper function
  	if(!same)
		if(temp_new->getParent()!=NULL)
	  		if(temp_new->getColor()==red && temp_new->getParent()->getColor()==red)
	  			DoubleRed(temp_new_cast);
  }
  /* This one is yours to implement.
     It should add the (key, value) pair to the tree, 
     making sure that it remains a valid Red-Black Tree.
     If the key is already in the tree (with a possibly different associated value),
     then it should overwrite the value with the new one.
     We strongly recommend defining suitable (private) helper functions. */
     

	void remove (KeyType key)
	{
		bool extrablacksituation = false;
		bool existance = false;
		if(BinarySearchTree<KeyType,ValueType>::root != NULL)
		{
			//search through tree
  			RedBlackNode<KeyType,ValueType> *current = (RedBlackNode<KeyType,ValueType>*) BinarySearchTree<KeyType,ValueType>::root;
  			RedBlackNode<KeyType,ValueType> *successor = (RedBlackNode<KeyType,ValueType>*) BinarySearchTree<KeyType,ValueType>::root;
			while(true)
			{
				if(key==current->getKey())
				{
					existance = true;
					break;
				}
				else if(key<current->getKey())
				{
					if(current->getLeft()!=NULL)
						current = current->getLeft();
					else
						break;
				}
				else if(key>current->getKey())
				{
					if(current->getRight()!=NULL)
						current = current->getRight();
					else
						break;
				}
			}
			if(existance)
			{
				//Case 1 (base case || leaf)
				if(current->getLeft() == NULL && current->getRight() == NULL)
				{
					bool theroot=false;
					if(BinarySearchTree<KeyType,ValueType>::root == current)
					{
						BinarySearchTree<KeyType,ValueType>::root = NULL;
						theroot=true;
					}
					if(!theroot)
					{
						if(current->getColor()==black)
						{
							current->extraBlack = true;
							ExtraBlack(current);
						}
					}
					if(current->getParent()!=NULL)
					{
						if(current == current->getParent()->getLeft())
							current->getParent()->setLeft(NULL);
						else if(current == current->getParent()->getRight())
							current->getParent()->setRight(NULL);
					}
					delete current;
				}
					
				//Case 2 (current has one child)
				else if(current->getLeft() == NULL || current->getRight() == NULL)
				{
					if (current->getLeft() == NULL && current->getRight() != NULL)
						successor = current->getRight();
					else if (current->getLeft() != NULL && current->getRight() == NULL)
						successor = current->getLeft();
					
					if(current == BinarySearchTree<KeyType,ValueType>::root)
						BinarySearchTree<KeyType,ValueType>::root = successor;
						
					successor->setColor(black);
					
					if(current->getParent()!=NULL)
					{
						successor->setParent(current->getParent());
						if(current == current->getParent()->getLeft())
							current->getParent()->setLeft(successor);
						else
							current->getParent()->setRight(successor);
					}
					else
						successor->setParent(NULL);
						
					current = NULL;
				}
				//Case 3 (current has two children)
				else if(current->getLeft() !=NULL && current->getRight() != NULL)
				{
					bool leftside = false;
					if(current->getLeft()->getRight()!=NULL)
					{
						successor = current->getLeft();
						leftside=true;
					}
					else if(current->getParent()!=NULL)
					{
						if(current == current->getParent()->getLeft())
						{
							successor = current->getLeft();
							leftside = true;
						}
						else
							successor = current->getRight();
					}
					else
						successor = current->getRight();
					
					if(leftside)
					{
						while(successor->getRight()!=NULL)
							successor = successor->getRight();
					
						//3a successor has no right child
						if(successor->getRight()==NULL)
						{
							if(current == BinarySearchTree<KeyType,ValueType>::root)
								BinarySearchTree<KeyType,ValueType>::root = successor;
					
							if(successor != current->getLeft())
							{
								successor->getParent()->setRight(successor->getLeft());
								successor->setLeft(current->getLeft());
								current->getLeft()->setParent(successor);
							}
							successor->setRight(current->getRight());
							current->getRight()->setParent(successor);	
						
							if(current->getParent()!=NULL)
							{
								successor->setParent(current->getParent());
								if(current == current->getParent()->getRight())
									current->getParent()->setRight(successor);
								else
									current->getParent()->setLeft(successor);
							}
							else
								successor->setParent(NULL);
						
							//If successor is black and has a right child
							if(successor->getColor() == black && successor->getLeft()!=NULL)
							{
								successor->getLeft()->extraBlack = true;
								extrablacksituation = true;
							}
						
							//changing color of successor
							successor->setColor(current->getColor());
						
						
							
							current = NULL;
						}
					}
					else
					{
						while(successor->getLeft()!=NULL)
							successor = successor->getLeft();
					
						//3a successor has no left child
						if(successor->getLeft()==NULL)
						{
							if(current == BinarySearchTree<KeyType,ValueType>::root)
								BinarySearchTree<KeyType,ValueType>::root = successor;
					
							if(successor != current->getRight())
							{
								successor->getParent()->setLeft(successor->getRight());
								successor->setRight(current->getRight());
								current->getRight()->setParent(successor);
							}
							successor->setLeft(current->getLeft());	
							current->getLeft()->setParent(successor);
							
							if(current->getParent()!=NULL)
							{
								successor->setParent(current->getParent());
								if(current == current->getParent()->getLeft())
									current->getParent()->setLeft(successor);
								else
									current->getParent()->setRight(successor);
							}
							else
								successor->setParent(NULL);
						
							//If successor is black and has a right child
							if(successor->getColor() == black && successor->getRight()!=NULL)
							{
								successor->getRight()->extraBlack = true;
								extrablacksituation = true;
							}
						
							//changing color of successor
							successor->setColor(current->getColor());
							current = NULL;
						}
					}
				}
			}
			
			if(extrablacksituation)
			{
				successor = successor->getRight();
				ExtraBlack(successor);
			}
		}
	}
	
private:
	//Node<KeyType,ValueType> *root;	
	
	void DoubleRed(Node<KeyType,ValueType> *temp_cast)
	{
	
		// Will refer to new item as "K", parent as "P", and grandparent as "G"
	
  		RedBlackNode<KeyType,ValueType> *temp = (RedBlackNode<KeyType,ValueType>*) temp_cast;
  		//If G exists
  		if(temp->getParent()->getParent()!=NULL)
  		{
  			//Node<KeyType,ValueType> *temp_p1 = temp->getParent();
  			//Node<KeyType,ValueType> *temp_p2 =  temp->getParent()->getParent();
  			RedBlackNode<KeyType,ValueType> *temp_p1 = temp->getParent(); //temp's parent
  			RedBlackNode<KeyType,ValueType> *temp_p2 = temp->getParent()->getParent(); //temp's parent's parent
  			//If P is on left side of G
  			if(temp_p1 == temp_p2->getLeft())
  			{
  				//Case1: if P's sibling is black or null
	  			if(temp_p2->getRight()==NULL || temp_p2->getRight()->getColor() == black)
	  			{
	  				//If K is to left of P
	  				if(temp == temp_p1->getLeft())
	  				{
	  					//Check if the new G is the new root
	  					if(temp_p2==BinarySearchTree<KeyType,ValueType>::root)
	  						BinarySearchTree<KeyType,ValueType>::root = temp_p1;
	  				
	  					//sets P's parent to be G's parent and sets G's parent's child to P
	  					if(temp_p2->getParent()!=NULL)
	  					{
	  						temp_p1->setParent(temp_p2->getParent());
	  						if(temp_p2->getParent()->getRight()==temp_p2)
	  							temp_p2->getParent()->setRight(temp_p1);
	  						else if(temp_p2->getParent()->getLeft()==temp_p2)
	  							temp_p2->getParent()->setLeft(temp_p1);
	  					}
	  					else
	  						temp_p1->setParent(NULL);
	  				
	  					//Give's P's right to G's left
	  					if(temp_p1->getRight()!=NULL)
	  					{
	  						temp_p1->getRight()->setParent(temp_p2);
	  						temp_p2->setLeft(temp_p1->getRight());
	  					}
	  					else
	  					{
	  						temp_p2->setLeft(NULL);
	  					}
	  						
	  					//Setting G to P's right
	  					temp_p2->setParent(temp_p1);
	  					temp_p1->setRight(temp_p2);
	  					
	  					//Setting K to P's left
	  					temp->setParent(temp_p1);
	  					temp_p1->setLeft(temp);
	  					
	  					temp_p1->setColor(black);
	  					temp_p2->setColor(red);
	  					temp->setColor(red);
	  				}
	  				//If K is right of P
	  				else
	  				{
	  					//Check if K will be the new root
	  					if(temp_p2==BinarySearchTree<KeyType,ValueType>::root)
	  						BinarySearchTree<KeyType,ValueType>::root = temp;
	  						
	  					//Setting K's new Parent
	  					if(temp_p2->getParent()!=NULL)
	  					{
	  						temp->setParent(temp_p2->getParent());
	  						if(temp_p2->getParent()->getRight()==temp_p2)
	  							temp_p2->getParent()->setRight(temp);
	  						else if(temp_p2->getParent()->getLeft()==temp_p2)
	  							temp_p2->getParent()->setLeft(temp);
	  					}
	  					else
	  						temp->setParent(NULL);
	  					
	  					temp_p1->setParent(temp);
	  					//Setting Parent's new Right
	  					if(temp->getLeft()!=NULL)
	  					{
	  						temp->getLeft()->setParent(temp_p1);
	  						temp_p1->setRight(temp->getLeft());
	  					}
	  					else
	  						temp_p1->setRight(NULL);
	  					
	  					temp_p2->setParent(temp);
	  					//Setting Grandparent's new Left
	  					if(temp->getRight()!=NULL)
	  					{
	  						temp->getRight()->setParent(temp_p2);
	  						temp_p2->setLeft(temp->getRight());
	  					}	
	  					else
	  						temp_p2->setLeft(NULL);
	  					
	  					//Setting K's children
	  					temp->setLeft(temp_p1);
	  					temp->setRight(temp_p2);

	  					temp_p1->setColor(red);
	  					temp_p2->setColor(red);
	  					temp->setColor(black);
	  				}
	  			}
	  			//Case2: if parent's sibling is red
	  			else
	  			{
	  				if(temp_p2!=BinarySearchTree<KeyType,ValueType>::root)
	  					temp_p2->setColor(red);
	  				temp_p1->setColor(black);
	  				temp_p2->getRight()->setColor(black);
	  				if(temp_p2->getParent()!=NULL)
	  					if(temp_p2->getColor()==red && temp_p2->getParent()->getColor()==red)
	  						DoubleRed(temp_p2);
	  			}
	  		}
  			//If on right side		
  			else
  			{
	  			if(temp_p2->getLeft()==NULL || temp_p2->getLeft()->getColor() == black)
	  			{
	  				//If temp is to the right
	  				if(temp == temp_p1->getRight())
	  				{
	  					//Check if the new G is the new root
	  					if(temp_p2==BinarySearchTree<KeyType,ValueType>::root)
	  						BinarySearchTree<KeyType,ValueType>::root = temp_p1;
	  				
	  					//sets P's parent to be G's parent and sets G's parent's child to P
	  					if(temp_p2->getParent()!=NULL)
	  					{
	  						temp_p1->setParent(temp_p2->getParent());
	  						if(temp_p2->getParent()->getRight()==temp_p2)
	  							temp_p2->getParent()->setRight(temp_p1);
	  						else if(temp_p2->getParent()->getLeft()==temp_p2)
	  							temp_p2->getParent()->setLeft(temp_p1);
	  					}
	  					else
	  						temp_p1->setParent(NULL);
	  				
	  					//Give's P's right to G's left
	  					if(temp_p1->getLeft()!=NULL)
	  					{
	  						temp_p1->getLeft()->setParent(temp_p2);
	  						temp_p2->setRight(temp_p1->getLeft());
	  					}
	  					else
	  					{
	  						temp_p2->setRight(NULL);
	  					}
	  					
	  					temp_p2->setParent(temp_p1);
	  					temp_p1->setLeft(temp_p2);
	  					
	  					temp->setParent(temp_p1);
	  					temp_p1->setRight(temp);
	  					
	  					temp_p1->setColor(black);
	  					temp_p2->setColor(red);
	  					temp->setColor(red);
	  				}
	  				else
	  				{
	  					//Check if K will be the new root
	  					if(temp_p2==BinarySearchTree<KeyType,ValueType>::root)
	  						BinarySearchTree<KeyType,ValueType>::root = temp;
	  						
	  					
	  					if(temp_p2->getParent()!=NULL)
	  					{
	  						temp->setParent(temp_p2->getParent());
	  						if(temp_p2->getParent()->getRight()==temp_p2)
	  							temp_p2->getParent()->setRight(temp);
	  						else if(temp_p2->getParent()->getLeft()==temp_p2)
	  							temp_p2->getParent()->setLeft(temp);
	  					}
	  					else
	  						temp->setParent(NULL);
	  					
	  					temp_p1->setParent(temp);
	  					//Setting Parent's new Left
	  					if(temp->getRight()!=NULL)
	  					{
	  						temp->getRight()->setParent(temp_p1);
	  						temp_p1->setLeft(temp->getRight());
	  					}
	  					else
	  						temp_p1->setLeft(NULL);
	  					
	  					temp_p2->setParent(temp);
	  					//Setting Grandparent's new Right
	  					if(temp->getLeft()!=NULL)
	  					{
	  						temp->getLeft()->setParent(temp_p2);
	  						temp_p2->setRight(temp->getLeft());
	  					}	
	  					else
	  						temp_p2->setRight(NULL);
	  					
	  					//Setting K's children
	  					temp->setRight(temp_p1);
	  					temp->setLeft(temp_p2);
	  					
	  					temp_p1->setColor(red);
	  					temp_p2->setColor(red);
	  					temp->setColor(black);
	  				}
	  			}
	  			else
	  			{
	  				if(temp_p2!=BinarySearchTree<KeyType,ValueType>::root)
	  					temp_p2->setColor(red);
	  				temp_p1->setColor(black);
	  				temp_p2->getLeft()->setColor(black);
	  				
	  				if(temp_p2->getParent()!=NULL)
	  					if(temp_p2->getColor()==red && temp_p2->getParent()->getColor()==red)
	  						DoubleRed(temp_p2);
	  			}
  			}
  		}
	}
	void ExtraBlack(RedBlackNode<KeyType,ValueType> *current)
	{
		//Left Side
		if(current == current->getParent()->getLeft() && current->getParent()->getRight()!=NULL) 
		{
			RedBlackNode<KeyType,ValueType> *parent = current->getParent();
			RedBlackNode<KeyType,ValueType> *sibling = current->getParent()->getRight();
			//Case 1: sibling is red
			if(sibling->getColor() == red)
			{
				if(parent->getParent()!=NULL)
				{
					if(parent==BinarySearchTree<KeyType,ValueType>::root)
						BinarySearchTree<KeyType,ValueType>::root = sibling;
						
					if(parent == parent->getParent()->getLeft())
						parent->getParent()->setLeft(sibling);
					else
						parent->getParent()->setRight(sibling);
						
					sibling->setParent(parent->getParent());
					parent->setParent(sibling);
					
					if(sibling->getLeft()!=NULL)
					{
						parent->setRight(sibling->getLeft());
						sibling->getLeft()->setParent(parent);
					}
					else
						parent->setRight(NULL);
					
					sibling->setLeft(parent);
					
					parent->setColor(red);
					sibling->setColor(black);
					
					ExtraBlack(current);
				}
			}
			//Case 2: sibling is black
			else if(sibling->getColor() == black)
			{
				RedBlackNode<KeyType,ValueType> *left = sibling->getLeft();
				RedBlackNode<KeyType,ValueType> *right = sibling->getRight();
				
				
				bool check = false;
				bool rightpath = false;
				if(left != NULL && right == NULL){
					if(left->getColor()==black)
						check = true;}
						
				else if(left == NULL && right != NULL){
					if(right->getColor()==black)
						check = true;}
						
				else if(left == NULL && right == NULL)
					check = true;
					
				else if(left != NULL && right != NULL){
					if(left->getColor()==black && right->getColor()==black)
						check = true;}
				
				if(check) // if both of sibling's children are black
				{
					if(current->getParent()!=BinarySearchTree<KeyType,ValueType>::root)
					{
						sibling->setColor(red);
						current->extraBlack = false;
						current->getParent()->extraBlack = true;
						ExtraBlack(current->getParent());
					}
				}
				
				if(right != NULL)
				{
					if(right->getColor()==red)
					{
						rightpath = true;
						if(parent==BinarySearchTree<KeyType,ValueType>::root)
							BinarySearchTree<KeyType,ValueType>::root = sibling;
						
						if(parent->getParent()!=NULL)
						{
							if(parent == parent->getParent()->getLeft())
								parent->getParent()->setLeft(sibling);
							else if(parent == parent->getParent()->getRight())
								parent->getParent()->setRight(sibling);
									
							sibling->setParent(parent->getParent());
						}
						else
							sibling->setParent(NULL);
							
						parent->setParent(sibling);
					
						if(sibling->getLeft()!=NULL)
						{
							parent->setRight(sibling->getLeft());
							sibling->getLeft()->setParent(parent);
						}
						else	
							parent->setRight(NULL);
					
						sibling->setLeft(parent);
						
						right->setColor(black);
						sibling->setColor(parent->getColor());
					
						current->extraBlack = false;
					}
				}
				if(left != NULL && !rightpath)
				{
					if(left->getColor()==red)
					{
						parent->setRight(left);
						sibling->setParent(left);
						
						if(left->getRight()!=NULL)
						{
							sibling->setLeft(left->getRight());
							left->getRight()->setParent(sibling);
						}
						else
							sibling->setRight(NULL);
						
						left->setParent(parent);
						left->setRight(sibling);
						
						left->setColor(black);
						sibling->setColor(red);
						ExtraBlack(current);
					}
				}
			}
		}
		//Right Side
		else if(current == current->getParent()->getRight() && current->getParent()->getLeft()!=NULL)
		{
			RedBlackNode<KeyType,ValueType> *parent = current->getParent();
			RedBlackNode<KeyType,ValueType> *sibling = current->getParent()->getLeft();
			
			//Case 1: sibling is red
			if(sibling->getColor() == red)
			{
				if(parent->getParent()!=NULL)
				{
					if(parent==BinarySearchTree<KeyType,ValueType>::root)
						BinarySearchTree<KeyType,ValueType>::root = sibling;
						
					if(parent == parent->getParent()->getRight())
						parent->getParent()->setRight(sibling);
					else
						parent->getParent()->setLeft(sibling);
						
					sibling->setParent(parent->getParent());
					parent->setParent(sibling);
					
					if(sibling->getRight()!=NULL)
					{
						parent->setLeft(sibling->getRight());
						sibling->getRight()->setParent(parent);
					}
					else
						parent->setLeft(NULL);
					
					sibling->setRight(parent);
					
					parent->setColor(red);
					sibling->setColor(black);
					
					ExtraBlack(current);
				}
			}
			//Case 2: sibling is black
			else if(sibling->getColor() == black)
			{
				RedBlackNode<KeyType,ValueType> *left = sibling->getLeft();
				RedBlackNode<KeyType,ValueType> *right = sibling->getRight();
				
				bool check = false;
				bool rightpath = false;
				if(right != NULL && left == NULL){
					if(right->getColor()==black)
						check = true;}
						
				else if(right == NULL && left != NULL){
					if(left->getColor()==black)
						check = true;}
						
				else if(right == NULL && left == NULL)
					check = true;
					
				else if(right != NULL && left != NULL){
					if(right->getColor()==black && left->getColor()==black)
						check = true;}
						
				if(check) // if both of sibling's children are black
				{
					if(current->getParent()!=BinarySearchTree<KeyType,ValueType>::root)
					{
						sibling->setColor(red);
						current->extraBlack = false;
						current->getParent()->extraBlack = true;
						ExtraBlack(current->getParent());
					}
				}
				
				if(left != NULL)
				{
					if(left->getColor()==red)
					{
						rightpath = true;
						if(parent==BinarySearchTree<KeyType,ValueType>::root)
						{
							BinarySearchTree<KeyType,ValueType>::root = sibling;
						}
						
						if(parent->getParent()!=NULL)
						{
							if(parent == parent->getParent()->getLeft())
								parent->getParent()->setLeft(sibling);
							else if(parent == parent->getParent()->getRight())
								parent->getParent()->setRight(sibling);
									
							sibling->setParent(parent->getParent());
						}
						else
							sibling->setParent(NULL);
							
						parent->setParent(sibling);
					
						if(sibling->getRight()!=NULL)
						{
							parent->setLeft(sibling->getRight());
							sibling->getRight()->setParent(parent);
						}
						else
							parent->setLeft(NULL);
					
						sibling->setRight(parent);
						
						left->setColor(black);
						sibling->setColor(parent->getColor());
					
						current->extraBlack = false;
					}
				}
				if(right != NULL && !rightpath)
				{
					if(right->getColor()==red)
					{
						parent->setLeft(right);
						sibling->setParent(right);
						
						if(right->getLeft()!=NULL)
						{
							sibling->setRight(right->getLeft());
							right->getLeft()->setParent(sibling);
						}
						else
							sibling->setRight(NULL);
						
						right->setParent(parent);
						right->setLeft(sibling);
						
						right->setColor(black);
						sibling->setColor(red);
						ExtraBlack(current);
					}
				}
			}
		}
	}
};
