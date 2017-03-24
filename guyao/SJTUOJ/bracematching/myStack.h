

#ifndef MYSTACK_H_INCLUDED
#define MYSTACK_H_INCLUDED
#include<iostream>

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
#endif // MYSTACK_H_INCLUDED
