//Chris Peabody
//CS153
//3/6/2014
//file: linkedlist.hpp
//Purpose: to define the prototyped functions in linkedlist.h

#include <iostream>
using namespace std;

//--------BIG THREE (TWO)--------//
template <typename T>
const LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& rhs)
{
  this->clear();
  const LinkedList *p = &rhs;

  while(p->m_next != NULL)
  {
    this->insert_front(p->m_data);
    p=p->m_next;
  }

  this->reverse();

  return *this;
}

template <typename T>
LinkedList<T>::LinkedList(const LinkedList<T>& rhs)
{
  m_next = NULL;
  *this = rhs;
}

//--------ACCESSORS--------//
template <typename T>
int LinkedList<T>::size() const
{
  const LinkedList* p= this;
  int counter = 0;

  while(p->m_next != NULL)
  {
    counter++;
    p=p->m_next;
  }

  return counter;
}

template <typename T>
bool LinkedList<T>::isEmpty() const
{
  return(m_next==NULL);
}

template <typename T>
LinkedList<T>* LinkedList<T>::getFirstPtr()
{
  if (isEmpty() == false)
    return this;
  else
  {
    cout<<"!-- ERROR : PANIC in LINKEDLIST!! getFirstPtr()";
    return NULL;
  }
}

template <typename T>
LinkedList<T>* LinkedList<T>::getLastPtr()
{
  LinkedList* p= this;

  if (isEmpty() == false)
    while(p->m_next->m_next != NULL)
      p=p->m_next;
  else
  {
    cout<<"!-- ERROR : PANIC in LINKEDLIST!! getLastPtr()";
    return NULL;
  }
  

  return p;
}

template <typename T>
LinkedList<T>* LinkedList<T>::getAtPtr(int i)
{
  LinkedList* p=this;

  if(size()>=i)
    for(int k=0; k<i; k++)
      p=p->m_next;
  else
  {
    cout<<"!-- ERROR : PANIC in LINKEDLIST!! getAtPtr(int i)";
    return NULL;
  }

  return p;
}

//--------MUTATORS--------//
template <typename T>
void LinkedList<T>::clear()
{
  LinkedList* p = this;

  while(p->m_next!=NULL)
  {
    p=this->m_next;
    this->m_next=p->m_next;
    delete p;
  }

  return;
}

template <typename T>
void LinkedList<T>::insert_front(const T& x)
{
  LinkedList *node = new LinkedList;
  node->m_next=this->m_next;
  this->m_next=node;
  node->m_data=this->m_data;
  this->m_data=x;

  return;
}

template <typename T>
void LinkedList<T>::insert(const T& x, LinkedList<T>* pos)
{
  LinkedList *tmp = new LinkedList;
  tmp->m_data = pos->m_data;
  tmp->m_next = pos->m_next;

  pos->m_data=x;
  pos->m_next=tmp;

  return;
}

template <typename T>
void LinkedList<T>::remove(LinkedList<T>* pos)
{
  if(pos->m_next != NULL)
  {
    LinkedList* tmp=pos->m_next;
    pos->m_data = tmp->m_data;
    pos->m_next = tmp->m_next;

    delete tmp;
  }
}

//--------COMPLEX--------//
template <typename T>
bool LinkedList<T>::operator==(const LinkedList<T>& rhs) const
{
  const LinkedList *p = this;
  const LinkedList *r = &rhs;

  while(p->m_next != NULL && r->m_next != NULL)
  {
    if(p->m_data == r->m_data)
    {
      p = p->m_next;
      r = r->m_next;
    }
    else
      return false;
  }

  if(p->m_data != r->m_data)
    return false;
  else
    return true;
}

template <typename T>
LinkedList<T>* LinkedList<T>::find(const T& x)
{
  LinkedList *p = this;
  LinkedList *pos = new LinkedList;
  pos = NULL;

  while(p->m_next!=NULL&&pos==NULL)
  {
    if (p->m_data==x)
      pos=p;
    p=p->m_next;
  }

  return pos;
}

template <typename T>
void LinkedList<T>::reverse()
{
  //So same head can be used, store info that head will be (tail values)
  T temp = getLastPtr()->m_data;

  //Chop tail
  remove(getLastPtr());

  //Start pointer train for orignal pointers (SKipping head)
  LinkedList *p = this;

  //Create new string of values
  LinkedList *n = new LinkedList;

  while(p->m_next!=NULL)
  {
    n->insert_front(p->m_data); //Insert old values (excluding head) into new chain
    p=p->m_next;
  }

  //clear old chain
  clear();

  //link head to new train
  m_next = n;

  //Set head to correct value (from old tail)
  m_data = temp;

  return;
}

template <typename T>
void LinkedList<T>::append(const LinkedList<T>& xlist)
{
  LinkedList *p = getLastPtr();
  const LinkedList *r = &xlist;

  //p=p->m_next;

  while(r->m_next!=NULL)
  {
    insert(r->m_data, p);
    p=p->m_next;
    r=r->m_next;
  }

  return;
}