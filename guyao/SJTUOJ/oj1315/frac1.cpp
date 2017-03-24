#include <iostream>

using namespace std;

int GCD(int a, int b);

class myInt
{
  private:
    int un;
    int dn;
    double value;
  public:
    myInt(int newun,int newdn)
    {

      un=newun;
      dn=newdn;
      int dcg=GCD(un,dn);
      un/=dcg;
      dn/=dcg;
      value=(newun+0.0)/dn;
    };

    myInt()
    {
      un=dn=0;
      value=0;
    };

    myInt(const myInt & other)
    {
      un=other.un;
      dn=other.dn;
      value=other.value;
    };

    double getvalue() {return value;};
    void setvalue(int newun,int newdn)
    {
      un=newun;
      dn=newdn;
      int dcg=GCD(un,dn);
      un/=dcg;
      dn/=dcg;
      value=(newun+0.0)/dn;

    };
    void print()
    {
      cout<<un<<'/'<<dn<<endl;
    };
};

class myStack
{
  private:
    myInt data[160];
    int top;

  public:
    myStack()
    {
      top=-1;
    };

    void push(int a,int b)
    {
      top++;
      data[top].setvalue(a,b);
    };

    bool pop(myInt &rdata)
    {
      if(top==-1) return false;
      rdata=data[top];
      top--;
      return true;
    }

    bool getTop(myInt &rdata)
    {
      if(top==-1) return false;
      rdata=data[top];
      return true;
    }

    bool isEmpty() const {return top==-1;};
};


int GCD(int a, int b)
{
  int temp;
  if(a==0) return 1;
  if(a<b)
  {
    temp=a;
    a=b;
    b=temp;
  }
  while(a%b!=0)
  {
    temp=b;
    b=a%b;
    a=temp;
  }
  return b;
}

bool allEmpty(myStack *sset,int n)
{
  for(int i=1;i<n;i++) if(!sset[i].isEmpty()) return false;
  return true;
}

int main()
{
  int n=0;
  cin>>n;
  myStack StackSet[n];
  for(int i=0;i<n;i++)
  {
    if(i==0) {StackSet[0].push(1,1);StackSet[0].push(0,1);}
    else
    {
      for(int j=i;j>=1;j--)
      {
        if(GCD(i+1,j)==1) StackSet[i].push(j,i+1);
      }
    }
  }
  myInt min;
  myInt now;
  myInt tempint;
  StackSet[0].pop(tempint);
  tempint.print();
  int posi=0;
  while(!allEmpty(StackSet,n))
  {
    posi=1;
    min.setvalue(1,1);
    for(int i=1;i<n;i++)
    {
      if(!StackSet[i].getTop(now)) continue;
      if(min.getvalue()>now.getvalue())
      {
        min=now;
        posi=i;
      }
    }
    StackSet[posi].pop(min);
    min.print();
  }
  StackSet[0].pop(tempint);
  tempint.print();
  return 0;
}
