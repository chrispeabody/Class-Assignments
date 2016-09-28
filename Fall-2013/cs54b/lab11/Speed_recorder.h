//Name: CHRIS PEABODY
//Class: CS54 section B
//Date: 11/5/2013
//file: Speed_recorder.h
//purpose: header for our special class

#include <iostream>
using namespace std;

class Speed_recorder
{
  private:
    int m_id;
    int m_numEntries;
    float m_avgSpeed;
    int m_totSpeeds;
  public:
    Speed_recorder(const int id):m_id(id),m_numEntries(0),
                                m_avgSpeed(0),m_totSpeeds(0){}

    //Desc: Enters a new speed into the total
    //Pre: none
    //Post: totSpeeds, numEntries, and avgSpeeds will be updated                        
    void addSpeed(const int speed);

    //Desc: gets the id of the company
    //Pre: none
    //Post: returns m_id
    int getId();

    //Desc: gets the total entries in the company
    //Pre: none
    //Post: returns m_numEntries
    int getTotalEntries();

    //Desc: 
    //Pre:
    //Post: 
    float getAverageSpeed();
};