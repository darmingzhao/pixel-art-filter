#ifndef _TWODTREE_H_
#define _TWODTREE_H_

#include <utility>
#include "util/PNG.h"
#include "util/RGBAPixel.h"
#include "stats.h"

using namespace std;
using namespace util;

/*
 * This is a structure used in decomposing an image
 * into rectangles of similarly colored pixels.
 * This is a slight modification of a Kd tree of dimension 2.
 */

class twoDtree {
private:
   /*
   * Node class is encapsulated. 
   * Users should not know anything about its implementation.
   */
   class Node {
   public:
      //Node constructor
      Node(pair<int,int> ul, pair<int,int> lr, RGBAPixel a);

      pair<int,int> upLeft; 
      pair<int,int> lowRight;
      RGBAPixel avg;
      //ptr to left subtree
      Node * left;
      //ptr to right subtree
      Node * right;
   };
  
public:
   /*
    * Since this structure will allocate dynamic memory, we define
    * the following next three functions.
    */

   /*
    * twoDtree destructor.
    * Destroys all of the memory associated with the
    * current twoDtree. This function should ensure that
    * memory does not leak on destruction of a twoDtree.
    */
   ~twoDtree();

   /*
    * Copy constructor for a twoDtree.
    * @param other The twoDtree we are copying.
    */
   twoDtree(const twoDtree & other);

   /*
    * Overloaded assignment operator for twoDtrees.
    * @param rhs The right hand side of the assignment statement.
    */
   twoDtree & operator=(const twoDtree & rhs);

   /*
    * Constructor that builds a twoDtree out of the given PNG.
    * Every leaf in the tree corresponds to a pixel in the PNG.
    * Every non-leaf node corresponds to a rectangle of pixels 
    * in the original PNG, represented by an (x,y) pair for the 
    * upper left corner of the rectangle and an (x,y) pair for 
    * lower right corner of the rectangle. In addition, the Node
    * stores a pixel representing the average color over the 
    * rectangle. 
    *
    * Every node's left and right children correspond to a partition
    * of the node's rectangle into two smaller rectangles. The node's
    * rectangle is split by the horizontal or vertical line that 
    * results in the two smaller rectangles whose sum of squared 
    * differences from their mean is as small as possible.
    *
    * The left child of the node will contain the upper left corner
    * of the node's rectangle, and the right child will contain the
    * lower right corner.
    *
    * This function will build the stats object used to score the 
    * splitting lines.
    */
   twoDtree(PNG & imIn);

   /*
    * Render returns a PNG image consisting of the pixels
    * stored in the tree. 
    * Draws every leaf node's rectangle onto a PNG canvas using the 
    * average color stored in the node.
    * @Return PNG images of pixels stored in tree
    */
   PNG render();

   /*
    * Trims subtrees as high as possible in the tree.
    * A subtree is pruned (cleared) if at least the percentage of its leaves are
    * within tolerance of the average color stored in the root of the subtree. 
    * Pruning criteria should be evaluated on the original tree, not 
    * on a pruned subtree. (we only expect that trees would be pruned once.)
    * @Param pct percentage of leaves
    * @Param tol tolerance for pruning
    */
   void prune(double pct, int tol);

private:
   //ptr to the root of the twoDtree
   Node* root;

   //height of PNG represented by the tree
   int height;
   //width of PNG represented by the tree
   int width;

   /*
    * Destroys all dynamically allocated memory associated with the
    * current twoDtree class.
    */
   void clear();

   /*
    * Copies the parameter other twoDtree into the current twoDtree.
    * Does not free any memory. Used by copy constructor and op=.
    * @param other The twoDtree to be copied.
    */
   void copy(const twoDtree & other);

   /*
    * Private helper function for the constructor. Builds
    * the tree according to the specification of the constructor.
    * @param s Contains the data used to split the rectangles
    * @param ul upper left point of current node's rectangle.
    * @param lr lower right point of current node's rectangle.
    * @Return pointer to pixel node
    */
   Node * buildTree(stats & s,pair<int,int> ul, pair<int,int> lr);

   /*
    * Recursive helper function for clear()
    * @Param rootD is a node of the tree
    */
   void deleteTree(Node* &rootD);

   /*
    * Recursive helper function for copy()
    * @Param other is a node of the tree
    * @Return pointer to copied node
    */
   Node * copyTree(Node* other);

   /*
    * Recursive helper function for render()
    * @Param roote is a node in the tree
    * @Param img is the PNG image
    */
   void changeLeafColour(Node* root, PNG &img);

   /*
    * Recursive helper function for prune()
    * @Param node if the node to be pruned
    * @Param pct is the percentage of leaf nodes
    * @Param tol is the tolerance for pruning
    */
   void toPrune(Node* &node, double pct, int tol);

   /*
    * Recursive helper function for toPrune()
    * @Param subRoot is the node to prune
    * @Param child is the node of subRoote
    * @Param withinTol is the number of nodes within tolerance at subRoot
    * @Param totalNodes is thetotal nodes at subRoot
    * @Param tol is the tolerance for pruning
    */
   void calculateDistance(Node* &subRoot, Node* &child, double &withinTol, double &totalNodes, int tol);
};

#endif