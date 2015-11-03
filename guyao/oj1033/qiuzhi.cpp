#include <iostream>

using namespace std;

long long power(int bn,int exp)
{
  long long temp=1;
  if(exp<0&&bn!=1&&bn!=-1) temp=0;
  if(bn==0) temp=0;

  for(int i=0;i<exp;i++)
  {
    temp*=bn;
  }
  if(bn==-1&&exp<0) temp=power(-1,-exp);
  return temp;
}

template <class T>
class myNode
{
  private:
    myNode<T> *next;
    T data;
  public:
    myNode(){next=NULL;};
    myNode(const T &newdata,myNode<T> *newnext):data(newdata){next=newnext;};
    void setdata(T &newdata){data=newdata;};
    const T &getdata() const {return data;};
    void setnext(myNode<T> *newnext){next=newnext;};
    myNode *getnext() const {return next;};
};

template <class T>
class myStack
{
  private:
    myNode<T> *top;

  public:
    myStack(){top=NULL;};
    ~myStack(){
      myNode<T> *tempNode;
      while(top)
      {
        tempNode=top;
        top=top->getnext();
        delete tempNode;
      }
    };
    bool pop(T &rdata){
      if(!top) return false;
      myNode<T> *tempNode=top;
      rdata=top->getdata();
      top=top->getnext();
      delete tempNode;
      return true;
    };
    void push(const T &newdata){
      top=new myNode<T> (newdata,top);
    };
    bool getTop(T &rdata){
      if(!top) return false;
      rdata=top->getdata();
      return true;
    };
    bool isEmpty() const {return !top;};
};


bool isNumber(char s)
{
  return s>='0'&&s<='9';
}

bool opePriority(const char op1,const char op2,const bool switchNegorAbs)
{
  int temp1,temp2;
  if(op1=='+') temp1=1;
  if(op1=='-'&&switchNegorAbs) temp1=4;
  if(op1=='-'&&!switchNegorAbs) temp1=1;
  if(op1=='*'||op1=='/') temp1=2;
  if(op1=='^') temp1=3;
  if(op2=='+') temp2=1;
  if(op2=='n') temp2=4;
  if(op2=='-') temp2=1;
  if(op2=='*'||op2=='/') temp2=2;
  if(op2=='^') temp2=3;
  if(temp1==4) return true;
  return temp1>temp2||(temp1==3&&temp2==3);
}

bool result(long long &res,myStack<char> &braceStack)
{
  //static long long count=-1;
  //count++;
  char temp;
  myStack<long long> numStack;
  myStack<char> opeStack;

  bool switchNegorAbs=true;
  bool longint=false;
  //enum operation{add=1,abs=2,mul=3,div=4,pow=5,neg=6};
  temp=cin.get();
  bool conflag=true;
  while(conflag)
  {
    if(temp==' ') {temp=cin.get();continue;}
    if(isNumber(temp))
    {
      if(!longint)
      {
        numStack.push(temp-'0');
        switchNegorAbs=false;
        longint=true;
      }
      else
      {
        long long inttemp;
        numStack.pop(inttemp);
        inttemp=inttemp*10+temp-'0';
        numStack.push(inttemp);
        switchNegorAbs=false;
      }

    }
    else longint=false;
    if(temp=='+'||temp=='-'||temp=='*'||temp=='/'||temp=='^')
    {
      if(opeStack.isEmpty())
      {
        if(temp=='-'&&switchNegorAbs) temp='n';
        opeStack.push(temp);
      }
      else
      {
        char opetemp;
        do
        {
          opeStack.pop(opetemp);
          if(opePriority(temp,opetemp,switchNegorAbs))
          {
            opeStack.push(opetemp);
            break;
          }
          else
          {
            long long t1=0,t2=0;
            if(opetemp=='n') {numStack.pop(t1);numStack.push(-t1);}
            if(opetemp=='-') {numStack.pop(t1);numStack.pop(t2);numStack.push(t2-t1);}
            if(opetemp=='+') {numStack.pop(t1);numStack.pop(t2);numStack.push(t2+t1);}
            if(opetemp=='*') {numStack.pop(t1);numStack.pop(t2);numStack.push(t2*t1);}
            if(opetemp=='/')
            {
              numStack.pop(t1);
              if(t1==0) {return false;}
              numStack.pop(t2);
              numStack.push(t2/t1);
            }
            if(opetemp=='^')
            {
              numStack.pop(t1);
              numStack.pop(t2);
              if(t1<=0&&t2==0) return false;
              numStack.push(power(t2,t1));
            }
          }
        }while(!opeStack.isEmpty());
        if(temp=='-'&&switchNegorAbs) temp='n';
        opeStack.push(temp);
      }
      switchNegorAbs=true;
    }
    if(temp=='\n'||temp==')')
    {
      char useless;
      if(temp==')')
      {
         if(!braceStack.pop(useless)) return false;
      }
      else
      {
        if(!braceStack.isEmpty()) return false;
      }

      if(!opeStack.isEmpty())
      {
        char opetemp;
        do
        {
          opeStack.pop(opetemp);
          long long t1=0,t2=0;
          if(opetemp=='n') {numStack.pop(t1);numStack.push(-t1);}
          if(opetemp=='-') {numStack.pop(t1);numStack.pop(t2);numStack.push(t2-t1);}
          if(opetemp=='+') {numStack.pop(t1);numStack.pop(t2);numStack.push(t2+t1);}
          if(opetemp=='*') {numStack.pop(t1);numStack.pop(t2);numStack.push(t2*t1);}
          if(opetemp=='/')
          {
            numStack.pop(t1);
            if(t1==0) {return false;}
            numStack.pop(t2);
            numStack.push(t2/t1);
          }
          if(opetemp=='^')
          {
            numStack.pop(t1);
            numStack.pop(t2);
            if(t1<=0&&t2==0) return false;
            numStack.push(power(t2,t1));
          }
        }while(!opeStack.isEmpty());
      }
      conflag=false;
      continue;
    }
    if(temp=='(')
    {
      braceStack.push(temp);
      if(!result(res,braceStack)) return false;
      numStack.push(res);
      switchNegorAbs=false;
    }
    temp=cin.get();
  }
  //if(!braceStack.isEmpty()&&count==0) return false;
  numStack.pop(res);
  return true;
}


int main()
{
  myStack<char> braceStack;
  long long res;
  if(result(res,braceStack)&&braceStack.isEmpty())
  {
    cout<<res;
  }
  else cout<<"Error";

  return 0;
}
