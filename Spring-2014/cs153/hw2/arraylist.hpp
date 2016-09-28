//Chris Peabody
//2/19/2014
//cs153
//file: arraylist.hpp
//purpose: the definitions of the arraylist class functions

#include <iostream>
using namespace std;

template <typename T>
ArrayList<T>::~ArrayList()
{
  clear();
}

template <typename T>
ArrayList<T>& ArrayList<T>::operator=(const ArrayList<T>& rhs)
{
  if(this!=&rhs)
  {
    if(m_data!=NULL)
      delete []m_data;
    m_data = new T[rhs.max()];
    m_max = rhs.max();
    m_size = rhs.size();

    for(int k=0; k<rhs.size(); k++)
      m_data[k]=rhs[k];
  }

  return *this;
}

template <typename T>
ArrayList<T>::ArrayList(const ArrayList<T>& cpy)
{
  m_data = new T[0];
  *this = cpy;
}

template <typename T>
int ArrayList<T>::size() const
{
  return m_size;
}

template <typename T>
const T& ArrayList<T>::first() const
{
  if(m_size>0)
    return m_data[0];
  else
    cout<<"//----------ATTEMPTING TO ACCESS FIRST OF EMPTY LIST----------//";
    return m_errobj;
}

template <typename T>
T& ArrayList<T>::operator[](int i)
{
  if(i<m_size && i>=0)
    return m_data[i];
  else
    cout<<"//----------ATTEMPTING TO ACCESS INVALID INDEX----------//";
    return m_errobj;
}

template <typename T>
const T& ArrayList<T>::operator[](int i) const
{
  if(i<m_size && i>=0)
    return m_data[i];
  else
    cout<<"//----------ATTEMPTING TO ACCESS INVALID INDEX----------//";
    return m_errobj;
}

template <typename T>
int ArrayList<T>::find(const T& x)
{
  int index = 0;
  bool found = false;
  for(int k=0; k<m_size && found==false; k++)
  {
    if (m_data[k]==x)
    {
      index = k;
      found = true;
    }
  }

  if (found == false)
    index = -1;

  return index;
}

template <typename T>
void ArrayList<T>::clear()
{
  m_size = 0;
  m_data = 0;
  delete []m_data;
  m_data = NULL;

  return;
}

template <typename T>
void ArrayList<T>::insert_back(const T& x)
{
  if(m_data == NULL)
    m_data = new T[m_max];

  if(m_size>=m_max)
  {
    T* tmp = new T[(m_max++)*2];
    for(int k=0; k<m_size; k++)
      tmp[k]=m_data[k];
    delete []m_data;
    m_data = tmp;
    m_max *= 2;
  }
  

  m_data[m_size]=x;
  m_size++;

  return;
}

template <typename T>
void ArrayList<T>::insert(const T& x, int i)
{
  if(i<0 || i>m_size)
    cout<<"//----------ATTEMPTING TO INSERT AT INVALID INDEX----------//";

  if(m_size>=m_max)
  {
    T* tmp = new T[(m_max++)*2];
    for(int k=0; k<m_size; k++)
      tmp[k]=m_data[k];
    delete []m_data;
    m_data = tmp;
    m_max *= 2;
  }
  
  for(int k=m_size; k>i; k--)
    m_data[k]=m_data[k-1];

  m_data[i]=x;
  m_size++;

  return;
}

template <typename T>
void ArrayList<T>::remove(int i)
{
  if(i<0 || i>m_size)
    cout<<"//----------ATTEMPTING TO REMOVE INVALID INDEX----------//";
  if(i<m_size && i>0)
  {
    for(int k=i; k<m_size-1; k++)
      m_data[k] = m_data[k+1];
    m_size--;
  }

  if(m_size<m_max/4)
  {
    T* tmp = new T[m_max/2];
    for(int k=0; k<m_size; k++)
      tmp[k]=m_data[k];
    delete []m_data;
    m_data=tmp;
    m_max=m_max/2;
  }

  return;
}

template <typename T>
void ArrayList<T>::swap(int i, int k)
{
  if(m_size < i || m_size < k)
    cout<<"//----------ATTEMPTING TO SWAP AT INVALID INDEX(ES)----------//";

  T tmp = m_data[i];
  m_data[i] = m_data[k];
  m_data[k] = tmp;

  return;
}

template <typename T>
void ArrayList<T>::append(const ArrayList<T>& alist)
{
  m_max += alist.m_max;
  T* tmp = new T[m_max];

  for(int j=0; j<m_size; j++)
    tmp[j] = m_data[j];

  for(int k = 0; k<alist.size(); k++)
    tmp[m_size+k]=alist[k];

  m_size+=alist.size();
  delete []m_data;
  m_data = tmp;

  return; //NOTE TO SELF: if it doesn't work, make it compound insert_back() instead
}

template <typename T>
void ArrayList<T>::purge()
{
  T tmp;
  for(int k=0; k<m_size; k++)
  { 
    tmp = m_data[k];

    for(int n=k+1; n<m_size; n++)
    {
      if(m_data[n]==tmp)
        remove(n);
    }
  }

  return;
}