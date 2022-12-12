/**
 *
 * shifty quadtree (pa3)
 * sqtree.cpp
 * This file will be used for grading.
 *
 */

#include "sqtree.h"

// First Node constructor, given.
SQtree::Node::Node(pair<int, int> ul, int w, int h, RGBAPixel a, double v)
    : upLeft(ul), width(w), height(h), avg(a), var(v), NW(NULL), NE(NULL), SE(NULL), SW(NULL)
{
}

// Second Node constructor, given
SQtree::Node::Node(stats &s, pair<int, int> ul, int w, int h)
    : upLeft(ul), width(w), height(h), NW(NULL), NE(NULL), SE(NULL), SW(NULL)
{
  avg = s.getAvg(ul, w, h);
  var = s.getVar(ul, w, h);
}

// SQtree destructor, given.
SQtree::~SQtree()
{
  clear();
}

// SQtree copy constructor, given.
SQtree::SQtree(const SQtree &other)
{
  copy(other);
}

// SQtree assignment operator, given.
SQtree &SQtree::operator=(const SQtree &rhs)
{
  if (this != &rhs)
  {
    clear();
    copy(rhs);
  }
  return *this;
}

/* In general, a Node of size w x h has w*h-1 partitions.
 * The constructor first builds the stats object used to compute
 * the variability and average of image subrectangles so that it can
 * pick the best partition of a Node of size w x h in O(wh) time.
 * Then it recursively partitions Nodes, starting at the root and
 * always using the best partition,
 * Default tolerance is 0.0.
 */
/*
 * Every Node in the tree corresponds to a rectangular region
 * in the original PNG, represented by an (x,y) pair for the
 * upper left corner of the rectangle and an integer width and height.
 * In addition, the Node stores a pixel representing the average
 * color over the rectangle. It also stores a measure of color
 * variability over the rectangle.
 *
 * Every node's children correspond to a partition
 * of the node's rectangle into at most four smaller rectangles.
 * The partition is made by splitting the node's rectangle
 * horizontally and vertically so that the resulting (at least
 * two non-empty) rectangles have the smallest maximum variability.
 * In other words, consider every possible split and chose the
 * one that minimizes the maximum variability among the (at most) four
 * rectangles.*/

/**
 * SQtree constructor given tolerance for variance.
 */
SQtree::SQtree(PNG &imIn, double tol)
{
  stats s(imIn);
  pair<int, int> ul(0, 0);
  root = buildTree(s, ul, imIn.width(), imIn.height(), tol);
}

/**
 * Helper for the SQtree constructor.
 */
SQtree::Node *SQtree::buildTree(stats &s, pair<int, int> &ul,
                                int w, int h, double tol)
{
  
  //! valgrind error here?
  Node *curr = new Node(s, ul, w, h); // cout << "node " << i << " has been built" << endl; // cout << "<" << curr->upLeft.first << ", " << curr->upLeft.second << ">" << endl;
  if ((w == 1 && h == 1) || curr->var <= tol)
    return curr;
  pair<int, int> divisonPt = findDivision(s, ul, w, h);
  if (divisonPt.first == 0 && divisonPt.second == 0)
  {
  }
  else if (divisonPt.first == 0)
  {
    pair<int, int> horizontalDiv(ul.first, ul.second + divisonPt.second);
    curr->NE = buildTree(s, ul, w, divisonPt.second, tol);
    curr->SW = buildTree(s, horizontalDiv, w, h - divisonPt.second, tol); // why NW and SE only dividing into 2 parts (doesn't matter)
  }
  else if (divisonPt.second == 0)
  {
    pair<int, int> verticalDiv(ul.first + divisonPt.first, ul.second);
    curr->NW = buildTree(s, ul, divisonPt.first, h, tol);
    curr->SE = buildTree(s, verticalDiv, w - divisonPt.first, h, tol);
  }
  else
  {
    pair<int, int> verticalDiv(ul.first + divisonPt.first, ul.second);
    pair<int, int> horizontalDiv(ul.first, ul.second + divisonPt.second);
    pair<int, int> slantingDiv(ul.first + divisonPt.first, ul.second + divisonPt.second);
    curr->SW = buildTree(s, horizontalDiv, divisonPt.first, h - divisonPt.second, tol);
    curr->SE = buildTree(s, slantingDiv, w - divisonPt.first, h - divisonPt.second, tol);
    curr->NW = buildTree(s, ul, divisonPt.first, divisonPt.second, tol);
    curr->NE = buildTree(s, verticalDiv, w - divisonPt.first, divisonPt.second, tol);
  }
  return curr;
}

/**
 * Find the point to devide the current Node.
 */
pair<int, int> SQtree::findDivision(stats &s, pair<int, int> &ul,
                                     int w, int h)
{
  double maxVar;
  double minVar;
  pair<int, int> divisonPt;
  for (int i = 0; i < w; i++)
  {
    for (int j = 0; j < h; j++)
    {
      if (i == 0 && j == 0)
      {
        minVar = s.getVar(ul, w, h);
        divisonPt = ul;
      }
      else if (i == 0)
      {
        pair<int, int> horizontalDiv(ul.first, ul.second + j);
        double topVar = s.getVar(ul, w, j);
        double bottomVar = s.getVar(horizontalDiv, w, h - j);
        maxVar = max(topVar, bottomVar);
        if (maxVar <= minVar)
        {
          minVar = maxVar;
          pair<int, int> currDiv(i, j);
          divisonPt = currDiv;
        }
      }
      else if (j == 0)
      {
        pair<int, int> verticalDiv(ul.first + i, ul.second);
        double leftVar = s.getVar(ul, i, h);
        double rightVar = s.getVar(verticalDiv, w - i, h);
        maxVar = max(leftVar, rightVar);
        if (maxVar <= minVar)
        {
          minVar = maxVar;
          pair<int, int> currDiv(i, j);
          divisonPt = currDiv;
        }
      }
      else
      {
        pair<int, int> verticalDiv(ul.first + i, ul.second); //! how to visualize this (1, 0) // cout <<  verticalDiv.first << ", " <<  verticalDiv.second << endl;
        pair<int, int> horizontalDiv(ul.first, ul.second + j);
        pair<int, int> slantingDiv(ul.first + i, ul.second + j);
        double NW = s.getVar(ul, i, j);
        double NE = s.getVar(verticalDiv, w - i, j);
        double SW = s.getVar(horizontalDiv, i, h - j);
        double SE = s.getVar(slantingDiv, w - i, h - j);
        maxVar = max(max(NW, NE), max(SW, SE));
        if (maxVar <= minVar)
        {
          minVar = maxVar;
          pair<int, int> currDiv(i, j);
          divisonPt = currDiv;
        }
      }
    }
  }

  return divisonPt;
}

/**
 * Render SQtree and return the resulting image.
 */
PNG SQtree::render()
{
  // Your code here.
  PNG result;
  result.resize(root->width, root->height); //! but isn't root private?
  renderRecursion(result, root);
  return result;
}

void SQtree::renderRecursion(PNG &result, Node *root) //! how is this working down the tree tolerance?
{
  if (root == NULL)
  {
    return; //! need a return statement here?
  }
  if (root->NW == NULL && root->NE == NULL && root->SW == NULL && root->SE == NULL)
  {
    for (int i = root->upLeft.first; i < root->upLeft.first + root->width; i++)
    {
      for (int j = root->upLeft.second; j < root->upLeft.second + root->height; j++)
      {
        RGBAPixel *curr = result.getPixel(i, j);
        *curr = root->avg; // cout << root->avg.r << "  " << root->avg.g << "  " << root->avg.b << endl;
      }
    } // cout << "<" << root->upLeft.first << ", " << root->upLeft.second << ">" << endl; //return;
  }
  renderRecursion(result, root->NW);
  renderRecursion(result, root->NE);
  renderRecursion(result, root->SW);
  renderRecursion(result, root->SE);
}

/**
 * Delete allocated memory.
 */
void SQtree::clear()
{
  // Your code here.
  clearRecursion(root);
}

void SQtree::clearRecursion(Node *root)
{
  if (root == NULL)
  {
    return;
  }
  if (root->NW == NULL && root->NE == NULL && root->SW == NULL && root->SE == NULL)
  {
    delete root;
    // return;
  }
  else
  {
    clearRecursion(root->NW);
    clearRecursion(root->NE);
    clearRecursion(root->SW);
    clearRecursion(root->SE);
    delete root;
    // return;
  }
}



void SQtree::copy(const SQtree &other)
{
  // Your code here.
  Node *rootOther = other.root;
  //copyRecursion(rootOther, root); //! memory leak when second line not commented (not freed properly)
  root = new Node(rootOther->upLeft, rootOther->width, rootOther->height, rootOther->avg, rootOther->var);
  root->NW = copyRecursion(rootOther->NW, root->NW);
  root->NE = copyRecursion(rootOther->NE, root->NE);
  root->SW = copyRecursion(rootOther->SW, root->SW);
  root->SE = copyRecursion(rootOther->SE, root->SE); //! memory leak if above? 

  //! why seg fault if I remove this? - have not defined root (and can't call copy on empty space)
}


SQtree::Node *SQtree::copyRecursion(Node *rootOther, Node *rootNew)
{
  if (rootOther == NULL)
    return NULL;
  rootNew = new Node(rootOther->upLeft, rootOther->width, rootOther->height, rootOther->avg, rootOther->var);
  rootNew->NW = copyRecursion(rootOther->NW, rootNew->NW);
  rootNew->NE = copyRecursion(rootOther->NE, rootNew->NE);
  rootNew->SW = copyRecursion(rootOther->SW, rootNew->SW);
  rootNew->SE = copyRecursion(rootOther->SE, rootNew->SE);
  return rootNew;
}

int SQtree::size()
{
  // Your code here.
  int num = 0;
  sizeRecursion(num, root);
  return num;
}

void SQtree::sizeRecursion(int &num, Node *root) //! why is it & num
{
  if (root == NULL)
  {
    // return; //! I need to have return when doing nothing?
  }
  else
  {
    num++;
    sizeRecursion(num, root->NW);
    sizeRecursion(num, root->NE);
    sizeRecursion(num, root->SW);
    sizeRecursion(num, root->SE);
    // return;
  }
}