#include<iostream>
#include"Node.h"


using namespace std;

template <class T>
myNode<T>::myNode()
{
  next=NULL;
  data=NULL;
};

template <class T>
myNode<T>::myNode(T &d1,myNode *n1)
{
  next=n1;
  data=d1;
};

template <class T>
T &myNode<T>::getData() const
{
  return data;
};

template <class T>
myNode<T> *myNode<T>::getNext() const
{
  return next;
};

