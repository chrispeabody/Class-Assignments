//Chris Peabody
//CS153 Section C
//Date: 5/12/2014
//File: MyBSTree.h
//Purpose: Header file for binary search tree class MyBSTree

#ifndef MYBSTREE_H
#define MYBSTREE_H

#include <iostream>
#include "abstractbstree.h"
#include <cmath>
using namespace std;

// Node
template <typename T>
struct TreeNode
{
  T m_data;
  TreeNode* m_right;
  TreeNode* m_left;

  TreeNode() : m_data(), m_right(NULL), m_left(NULL) {}

  TreeNode(T x, TreeNode* l, TreeNode* r)
  {
    m_data = x;
    m_right = l;
    m_left = r;
  }
};

//Recursive functions on nodes
template <typename T>
int rSize(const TreeNode<T>* t)
{
  if(t==NULL)
    return 0;
  else
    return rSize(t->m_left)+rSize(t->m_right)+1;
}

template <typename T>
int rHeight(const TreeNode<T> &t)
{
  int rh = t.m_right ? rHeight(*t.m_right) : 0;
  int lh = t.m_left ? rHeight(*t.m_left) : 0;
  return 1+max(rh,lh);
}

template <typename T>
const T& rFindMax(const TreeNode<T> &n)
{
  if(n.m_right == NULL)
    return n.m_data;
  else
    return  rFindMax(*n.m_right); 
}

template <typename T>
int rContains(const T&x, const TreeNode<T>* t)
{
  if(t==NULL)
    return -1;
  if(t->m_data==x)
    return 0;
  if(x<t->m_data)
  {
    int left = rContains(x, t->m_left);
    if(left<0)
      return -abs(left-1);
    else
      return 1+left;
  }
  else
  {
    int right = rContains(x, t->m_right);
    if(right<0)
      return -abs(right-1);
    else
      return 1+right;
  }
}

template <typename T>
void rInsert(const T& x, TreeNode<T>*& t)
{
  if(t==NULL)
    t = new TreeNode<T>(x, NULL, NULL);
  else
  {
    if(x < t->m_data)
      rInsert(x, t->m_left);
    else if(x > t->m_data)
      rInsert(x, t->m_right);
    else //Already is there
      return;
  }
}

//BRENDAN's VERSION
template <typename T>
void rRemove(const T& x, TreeNode<T>* &n)
{
  if(n==NULL)
    return;
  else if(x < n -> m_data)
    rRemove(x, n -> m_left);
  else if(x > n -> m_data)
    rRemove(x, n -> m_right);
  else //x == n -> m_data
  {
    if(n -> m_left != NULL && n -> m_right != NULL)
    {
     n -> m_data = rFindMax(*n -> m_left);
     rRemove(n -> m_data, n -> m_left);
    }
    else
    {
      TreeNode<T>* tmp = n;
      n = tmp -> m_left;
      if(n==NULL)
        n = tmp -> m_right;
      delete tmp;
    }
  }           
}

template <typename T>
void rPrintPreOrder(const TreeNode<T>* t)
{
  cout<<t->m_data<<endl;

  if(t->m_left!=NULL)
    rPrintPreOrder(t->m_left);
  if(t->m_right!=NULL)
    rPrintPreOrder(t->m_right);
}

template <typename T>
void rPrintPostOrder(const TreeNode<T>* t)
{
  if(t->m_left!=NULL)
    rPrintPostOrder(t->m_left);
  if(t->m_right!=NULL)
    rPrintPostOrder(t->m_right);

  cout<<t->m_data<<endl;
}

template <typename T>
void prettyPrint (const TreeNode<T>* t, int pad)
{
  string s(pad, ' ');
  if (t == NULL)
      cout << endl;
  else{
    prettyPrint(t->m_right, pad+4);
    cout << s << t->m_data << endl;
    prettyPrint(t->m_left, pad+4);
  }  
}

//Encapsulation class
template <typename T>
class MyBSTree : public AbstractBSTree<T>
{
private:
  TreeNode<T>* m_root;

public:
  MyBSTree() : m_root(NULL) {}

  // Encapsulated Functions
  virtual int size() const
  {
    return rSize(m_root);
  }
  
  virtual bool isEmpty() const
  {
    return (m_root==NULL);
  }

  virtual int height() const
  {
    return rHeight(*m_root);
  }

  virtual const T& findMax() const
  {
    TreeNode<T> *p = m_root;

    string no = "PANIC: Tree is Empty!!";   
    if(p==NULL)
      throw(no);
    while(p->m_right != NULL)
      p = p->m_right;  

    return p->m_data;
  }

  virtual const T& findMin() const
  {
    TreeNode<T> *p = m_root;
    string no = "PANIC: Tree is Empty!!";   
    if(p==NULL)
      throw(no);
    while(p->m_left != NULL)
      p = p->m_left;  

    return p->m_data;
  }

  virtual int contains(const T& x) const
  {
    int val= rContains(x, m_root);
    if(val<0)
      return val+1;
    else
      return val;
  }

  virtual void clear()
  {
    delete m_root;
    m_root = NULL;
  }

  virtual void insert(const T& x)
  {
    rInsert(x, m_root);
  }

  virtual void remove(const T& x)
  {
    rRemove(x, m_root);
  }

  virtual void printPreOrder() const
  {
    rPrintPreOrder(m_root);
  }

  virtual void printPostOrder() const
  {
    rPrintPostOrder(m_root);
  }

  virtual void print() const
  {
    prettyPrint(m_root, 0);
  }

  TreeNode<T>* clone(TreeNode<T>* n)
  {
    if(n==NULL)
      return n;
    else
      return new TreeNode<T>(n->m_data, clone(n->m_right), clone(n->m_left));
  }

  const MyBSTree<T>& operator=(const MyBSTree<T> &rhs)
  {
    if(this != &rhs)
    {
      clear();
      TreeNode<T>* p= new TreeNode<T>;
      TreeNode<T>* b= rhs.m_root;
      p = clone(b);

      this->m_root=p;
    }

    return *this;
  }

  MyBSTree(MyBSTree<T> &x)
  {
    *this=x;
  }

  ~MyBSTree()
  {
    clear();
  }
};

#endif