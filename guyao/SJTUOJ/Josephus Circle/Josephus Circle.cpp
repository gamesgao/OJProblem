//A function to solve the Josephus Circle problem.
//author :Gaoyu


#include <iostream>
#include "LList.h"

using namespace std;

int JCSolved(int NumberofPeople,int Inter)
{
  myLList<int> JC;
  int temp;
  for(int i=0;i<NumberofPeople-1;i++)
  {
    JC.insert(i+2);
    JC.next();
  }
  JC.setStart();
  if((JC.getcount())==1) return JC.getValue();
  for(int i=0;i<Inter-2;i++)
  {
    JC.next();
  }
  JC.remove(temp);
  while((JC.getcount())!=1)
  {
    for(int i=0;i<Inter-1;i++)
    {
      JC.next();
    }
    JC.remove(temp);
  }
  return JC.getValue();
}

int main()
{
  int renshu,jiange;
  cout<<"Please input the number of people and the interval (renshu jiange):";
  cin>>renshu>>jiange;
  cout<<JCSolved(renshu,jiange);
  return 0;
}
