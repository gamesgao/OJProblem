#include <iostream>
#include "LList.h"


using namespace std;

template <class T>
myLList<T>::myLList()
{
  header=new myNode<T>(1,NULL);
  fence=header;
  header->setNext(header);
  counter=1;
};

template<class T>
void myLList<T>::clear()
{
  for(int i=0;i<counter;i++)
  {
    fence=header;
    header=header->getNext();
    delete fence;
  }
  header=new myNode<T>;
  fence=header;
  header->setNext(header);
  counter=1;
};

template<class T>
bool myLList<T>::insert(const T &d1)
{
  fence->setNext(new myNode<T>(d1,fence->getNext()));
  counter++;
  return true;
};

//template<class T>
//bool myLList<T>::append(const T &d1)
//{
//  tail->getNext() = new myNode<T>(d1,NULL);
//  tail=tail->getNext();
//  counter++;
//  return true;
//}

template<class T>
void myLList<T>::prev()
{
  myNode<T> *temp=header;
  while (temp->getNext()!=fence) temp=temp->getNext();
  fence = temp;
};

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
};

template<class T>
myLList<T>::~myLList()
{
  for(int i=0;i<counter;i++)
  {
    fence=header;
    header=header->getNext();
    delete fence;
  }
};
