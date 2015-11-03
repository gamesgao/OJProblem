#include<iostream>
#include"MyVector.h"

using namespace std;

int main()
{
  myVector<int>  v;
  cout << "the initial size of v is: "<< v.mysize()<<"\nthe initial capacity of v is: " << v.mycapacity() << endl;
  v.push_back(2);
  cout << "after push 2, capacity of v is: " << v.mycapacity() << endl;
  v.push_back(3);
  cout << "after pust 3, capacity of v is: "<< v.mycapacity() << endl;
  v.push_back(4);
  cout << "after push 4, capacity of v is: "<< v.mycapacity() << endl;
  cout<<"the size of v is:  "<< v.mysize()<< "\nthe capacity of v is: "<< v.mycapacity() << endl;
  cout<<"contents of  v using [ ]: ";
  for (int i=0; i<v.mysize(); i++)
    cout << v[i] << " ";
  cout << endl;
  cout<<"contents of  v using iterator notation: ";
  myVector<int>::const_iterator p;
  for (p=v.begin(); p!=v.end(); p++)
    cout << *p << " ";
  cout << endl;
  return 0;
}
