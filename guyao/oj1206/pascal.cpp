#include <iostream>

using namespace std;

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
    bool isEmpty() const {return !top;};
};



bool matchbegin(char &temp)
{
  temp=cin.get();
  if(temp=='e') temp=cin.get();
  else return false;
  if(temp=='g') temp=cin.get();
  else return false;
  if(temp=='i') temp=cin.get();
  else return false;
  if(temp=='n') temp=cin.get();
  else return false;
  if(temp==' '||temp=='\n') return true;
  else return false;

}

bool matchif(char &temp)
{
  temp=cin.get();
  if(temp=='f') temp=cin.get();
  else return false;
  if(temp==' '||temp=='\n') return true;
  else return false;
}

bool matchthen(char &temp)
{
  temp=cin.get();
  if(temp=='h') temp=cin.get();
  else return false;
  if(temp=='e') temp=cin.get();
  else return false;
  if(temp=='n') temp=cin.get();
  else return false;
  if(temp==' '||temp=='\n') return true;
  else return false;
}


char matche(char &temp)
{
  temp=cin.get();
  if(temp=='n')
  {
    temp=cin.get();
    if(temp=='d') temp=cin.get();
    else return '\0';
    if(temp==' '||temp=='\n') return 'd';
    else return '\0';
  }
  else
  {
    if(temp=='l') temp=cin.get();
    else return '\0';
    if(temp=='s') temp=cin.get();
    else return '\0';
    if(temp=='e') temp=cin.get();
    else return '\0';
    if(temp==' '||temp=='\n') return 'e';
    else return '\0';
  }
}

bool testpascal(bool &end)
{
  char temp;
  bool ind=true;
  myStack<char> resultStack;
  while(true)
  {
    temp=cin.get();
     if(temp==-1)
    {
      break;
    }
    if(temp=='b'&&ind)
    {
      if(matchbegin(temp)) resultStack.push('b');
    }
    if(temp=='i'&&ind)
    {
      if(matchif(temp))
      {
        //if(resultStack.isEmpty()) return false;  //果然if可以在外面。。。
        resultStack.push('i');
      }
      continue;
    }
    if(temp=='t'&&ind)
    {
      if(matchthen(temp))
      {
        char useless;
        if(!resultStack.pop(useless)) return false;
        if(useless=='i') {resultStack.push(useless);resultStack.push('t');}
        else return false;
      }
    }
    if(temp=='e'&&ind)
    {
      char result=matche(temp);
      if(result=='e')
      {
        char useless;
        if(!resultStack.pop(useless)) return false;
        else
        {
          if(useless=='t')
          {
            if(!resultStack.pop(useless)) return false;
            if(useless!='i') return false;
          }
          else return false;
        }
      }
      else
      {
        if(result=='d')
        {
          char useless;
          do
          {
            if(!resultStack.pop(useless)) return false;
            if(useless=='i') return false;
            if(useless=='t')
            {
              if(!resultStack.pop(useless)) return false;
              if(useless!='i') return false;
            }
          }while(useless!='b');
        }
      }
    }
    if(temp==' '||temp=='\n') ind=true;
    else ind=false;

  }
  end=true;
  if(!resultStack.isEmpty()) return false;
  return true;
}





int main()
{
  bool end=false;
  if(testpascal(end)) cout<<"Match!"<<endl;
  else
  {
    if(!end)
    {
      while(cin.get()!=-1);
    }
    cout<<"Error!"<<endl;
  }
  return 0;
}

