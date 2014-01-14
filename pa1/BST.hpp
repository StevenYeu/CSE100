#ifndef BST_HPP
#define BST_HPP
#include "BSTNode.hpp"
#include "BSTIterator.hpp"
#include <utility> // for std::pair

/*
 * Name: Matthew Schwegler
 * Login: cs100way
 * Student ID: A09293823
 * Assignment PA1
 */

template<typename Data>
class BST {

protected:

  /** Pointer to the root of this BST, or nullptr if the BST is empty */
  BSTNode<Data>* root;

  /** Number of Data items stored in this BST. */
  unsigned int isize;


public:

  /** iterator is an aliased typename for BSTIterator<Data>. */
  typedef BSTIterator<Data> iterator;

  /** Default constructor.
      Initialize an empty BST.
   */
  BST() : root(nullptr), isize(0)  {
  }


  /** Default destructor.
   *  It is virtual, to allow appropriate destruction of subclass objects.
   *  Delete every node in this BST.
   */ // 
  virtual ~BST() {

    //Call to clear
    clear();
  }

  /** Insert a Data item in the BST.
   *  Return a pair, with the pair's first member set to an
   *  iterator pointing to either the newly inserted element
   *  or to the equivalent element already in the set.
   *  The pair's second element is set to true
   *  if a new element was inserted or false if an
   *  equivalent element already existed.
   */ // 
  virtual std::pair<iterator,bool> insert(const Data& item) {
     /* Variable Declarations */
     BSTNode<Data>* insertNode = new BSTNode<Data>(item);
     bool insertSuccess;
     /* Body of Functions */
     
     //Compare the node to root and recurse down the tree
     //if root is null
     if (root == nullptr ){
        isize++;
        root = insertNode;
        return std::make_pair(BST<Data>::iterator(root), true );
     }
     //Check if item is root
     if ( item == root->data)
        return std::make_pair(BST<Data>::iterator(root), insertSuccess );

     //run helper insert method to insert new node
     insertSuccess = recurseInsert(insertNode, root);

     //Create pair and add to size
     isize++;
     return std::make_pair(BST<Data>::iterator(insertNode), insertSuccess );

         
    
  }


  /** Find a Data item in the BST.
   *  Return an iterator pointing to the item, or the end
   *  iterator if the item is not in the BST.
   */ //
  iterator find(const Data& item) const {
      //Declarations
      BSTNode<Data>* tempNode = root;

      if ( tempNode->data == item )
        return typename BST<Data>::iterator(tempNode);
      
      //Searches through the tree until match is found
      while ( tempNode->data != item ){
          
          //Checks if curr node is greater than item
          if ( tempNode->data > item ){

              if(tempNode->left)
                tempNode = tempNode->left;

              //else item not found
              else
                return end(); 
          }

          //move right if items is larger than curr node
          else{
              
              if( tempNode->right )
                  tempNode = tempNode->right;

              //else item not found
              else
                  return end();
          }
      }
      //item found
      return typename BST<Data>::iterator(tempNode);
  }

  
  /** Return the number of items currently in the BST.
   */ // 
  unsigned int size() const {
    //return isize
    return isize;
  }

  /** Remove all elements from this BST, and destroy them,
   *  leaving this BST with a size of 0.
   */ //
  void clear() {
    
      //Delete the tree Post Order Traversal
      deleteTree(root);
    
  }

  /** Return true if the BST is empty, else false.
   */ // 
  bool empty() const {
    if(root == nullptr)
        return true;
  }

  /** Return an iterator pointing to the first item in the BST.
   */ // 
  iterator begin() const {
    //Given the root go left return iterator
    BSTNode<Data>* tempNode = root;
    
    //while loop to iterate to leftmost node
    while(tempNode->left){
        tempNode = tempNode->left;
    }

    //return the left most node as an iterator
    return typename BST<Data>::iterator(tempNode); 

  }

  /** Return an iterator pointing past the last item in the BST.
   */
  iterator end() const {
    return typename BST<Data>::iterator(nullptr);
  }

/*Private section for helper functions
 *
 * Function: recurseInsert
 * Recurses through the list to insert according to BST Rules
 * Input: Node to inset, Node of current position
 *
 * */
private:
 bool recurseInsert(BSTNode<Data>* insert, BSTNode<Data>* tempNode){
    
     /*function body */
    
     //Compare and recurse
     if ( insert->data == tempNode->data )
         return false;
     
     else if ( insert->data < tempNode->data ){
         if (tempNode->left == nullptr ){
             tempNode->left = insert;
             insert->parent = tempNode;
             return true;
         }
         else
            tempNode = tempNode->left;
     }

     else if ( insert->data > tempNode->data ){
         if (tempNode->right == nullptr ){
             tempNode->right = insert;
             insert->parent = tempNode;
             return true;
         }
         else
            tempNode = tempNode->right;
     }

     //return
     return recurseInsert(insert, tempNode);
 }

 /*Function to delete the tree recursively given the root*/
 void deleteTree(BSTNode<Data>* start){
    //if Left exists
    if(start->left){
        deleteTree(start->left);
    }

    //If right exists
    if(start->right){
        deleteTree(start->right);
    }
    delete start;

 }
};


#endif //BST_HPP