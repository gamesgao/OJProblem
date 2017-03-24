#include <iostream>
#include "myStack.h"

using namespace std;

bool bracematch();


int main()
{
  if(bracematch()) cout<<"the input string is brace-matching";
  else cout<<"the input string is not brace-matching";
  return 0;
}

bool bracematch()
{
  bool flag=true;
  char temp,rdata;
  myStack<char> braceStack;
  temp=cin.get();
  while(temp!='\n')
  {
    if(temp=='(') braceStack.push(temp);
    if(temp==')')
    {
     if(!braceStack.pop(rdata)) {flag=false;break;}
    }
    temp=cin.get();
  }
  if(!braceStack.isEmpty()) flag=false;
  return flag;
}
