#include <iostream>
#include "GTreeByLCRS.h"

using namespace std;


int main()
{
  char fileAddr[100];
  cout<<"Please input tree 1 file: ";
  cin.getline(fileAddr,100);
  myTree tree1(fileAddr);
  cout<<"Please input tree 2 file: ";
  cin.getline(fileAddr,100);
  myTree tree2(fileAddr);
  cout<<"tree1:"<<endl;
  tree1.print();
  cout<<"tree2:"<<endl;
  tree2.print();
  tree1.UNION(tree2);
  cout<<"After union, tree1:"<<endl;
  tree1.print();


  return 0;
}
