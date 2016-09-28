//Chris Peabody
//2-6-2014
//CS153
//purpose: To define the gmatrix class functions
//file: gmatrix.cpp

#include <iostream>
#include "gmatrix.h"
using namespace std;

GMatrix::GMatrix(int c, int r, int s, int d)
{
  m_cols = c;
  m_rows = r;

  m_data= new int*[m_rows];
  for(int k=0; k<m_rows; k++)
    m_data[k] = new int[m_cols];

  for(int k=0; k<m_rows; k++)
    for(int x=0; x<m_cols; x++)
      m_data[k][x]=s+d*(x+k);
}

GMatrix::~GMatrix()
{
  for(int k=0; k<m_rows; k++)
    delete []m_data[k];
  delete []m_data;
}

const GMatrix& GMatrix::operator=(const GMatrix& rhs)
{
  if(this != &rhs)
  {
    for(int k=0; k<m_rows; k++)
      delete []m_data[k];
    delete []m_data;

    m_cols = rhs.m_cols;
    m_rows = rhs.m_rows;

    m_data = new int*[m_rows];
    for(int k=0; k<m_rows; k++)
      m_data[k] = new int[m_cols];

    for(int k=0; k<m_rows; k++)
      for(int x=0; x<m_cols; x++)
        m_data[k][x]=rhs.m_data[k][x];
  }
  return *this;
}

GMatrix::GMatrix(const GMatrix& rhs)
{
  m_data = new int*[1];
  m_data[0] = new int[1];
  *this = rhs;
}

std::ostream& operator<< (std::ostream& out, const GMatrix& gm)
{
  for(int k = 0; k<gm.m_rows; k++)
  {
    for(int x = 0; x<gm.m_cols; x++)
      cout<<"\t"<<gm.m_data[k][x];
    cout<<endl;
  }

 return out;
}