#include <iostream>
#include "myStack.h"

using namespace std;

bool InfixToPostfix(char * &result);
int main()
{
  char *result=NULL;
  if(InfixToPostfix(result)) {cout<<result;delete [] result;}
  else cout<<"Error";
  return 0;
}


bool InfixToPostfix(char* &result)
{
  myStack<char> opeStack;
  myStack<char> resultStack;
  char temp;
  bool negOrsub=true;
  while(true)
  {
    temp=cin.get();
    if(temp>='0'&&temp<='9')
    {
      while(temp>='0'&&temp<='9')
      {
        resultStack.push(temp);
        temp=cin.get();
      }
      resultStack.push(' ');
      negOrsub=false;
    }
    else if(temp!='-') negOrsub=true;
    if(temp==' ') continue;
    if(temp=='(') opeStack.push(temp);
    if(temp=='+'||temp=='-'||temp=='*'||temp=='/'||temp=='^')
    {
      if(temp=='-'&&negOrsub) temp='n';
      if(temp=='-'&&!negOrsub) negOrsub=true;
      opeStack.push(temp);
    }
    if(temp==')')
    {
      opeStack.pop(temp);
      while(temp!='(')
      {
        resultStack.push(temp);
        resultStack.push(' ');
        opeStack.pop(temp);
      }
      negOrsub=false;
    }
    if(temp=='\n')
    {
      while(opeStack.pop(temp))
      {
        if(temp=='(') return false;
        resultStack.push(temp);
        resultStack.push(' ');
      }
      break;
    }
  }
  while(resultStack.pop(temp)) opeStack.push(temp);
  int len=opeStack.getSize();
  result=new char [len+1];
  int count=0;
  while(opeStack.pop(temp))
  {
    result[count]=temp;
    count++;
  }
  result[count]='\0';
  return true;
}
