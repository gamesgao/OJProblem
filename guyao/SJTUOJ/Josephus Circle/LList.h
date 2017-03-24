//A class of cycled linked list
//author :Gaoyu


#include "List.h"
#include "Node.h"

#include <iostream>

using namespace std;

#ifndef MYLLIST
#define MYLLIST

template <class T>
class myLList:public myList<T>
{
  private:
    myNode<T> *header;
    myNode<T> *tail;
    myNode<T> *fence;
    int counter;

  public:
    myLList();
    virtual void clear();
    virtual bool insert(const T&);
    virtual bool remove(T&);
    virtual void setStart() {fence=header;};
    virtual void prev();
    virtual void next(){ fence = fence->getNext(); };
    virtual ~myLList();
    int getcount(){return counter;};
    T getValue(){return fence->getData();};
};
#endif // MYLLIST

//module class implement
template <class T>
myLList<T>::myLList()
{
  header=new myNode<T>(1);
  fence=header;
  header->setNext(header);
  counter=1;
}

template<class T>
void myLList<T>::clear()
{
  for(int i=0;i<counter;i++)
  {
    fence=header;
    header=header->getNext();
    delete fence;
  }
  header=new myNode<T>(1);
  fence=header;
  header->setNext(header);
  counter=1;
}

template<class T>
bool myLList<T>::insert(const T &d1)
{
  fence->setNext(new myNode<T>(d1,fence->getNext()));
  counter++;
  return true;
}

template<class T>
void myLList<T>::prev()
{
  myNode<T> *temp=header;
  while (temp->getNext()!=fence) temp=temp->getNext();
  fence = temp;
}

template<class T>
bool myLList<T>::remove(T &d1)
{
  d1=fence->getNext()->getData();
  myNode<T> *temp=fence->getNext();
  fence->setNext(temp->getNext());
  if(header==temp) header=temp->getNext();
  delete temp;
  counter--;
  return true;
}

template<class T>
myLList<T>::~myLList()
{
  for(int i=0;i<counter;i++)
  {
    fence=header;
    header=header->getNext();
    delete fence;
  }
}

