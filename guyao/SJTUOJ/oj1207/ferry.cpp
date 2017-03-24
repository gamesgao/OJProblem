#include <iostream>
#include <cstdio>

using namespace std;

template <class T>
class myNode
{
  private:
    T data;
    myNode *next;

  public:
    myNode(const T &newdata,myNode *newnext)
    {
      data=newdata;
      next=newnext;
    };
    myNode()
    {
      next=NULL;
    };
    myNode *getnext() const
    {
      return next;
    };
    void setnext(myNode *newnext)
    {
      next=newnext;
    }
    const T &getdata() const
    {
      return data;
    }
    void setdata(T &newdata)
    {
      data=newdata;
    }

};

template <class T>
class myQueueL
{
  private:
    myNode<T> *head;
    myNode<T> *rear;
    int length;

  public:
    myQueueL()
    {
      head=new myNode<T>();
      rear=head;
      length=0;
    };
    ~myQueueL()
    {
      while(head)
      {
        rear=head;
        head=head->getnext();
        delete rear;
      }
    };

    void enQueue(const T &newdata)
    {
      rear->setnext(new myNode<T>(newdata,NULL));
      rear=rear->getnext();
      length++;
    };

    bool deQueue(T &rdata)
    {
      if(rear==head) return false;
      myNode<T> *temp=head->getnext();
      rdata=temp->getdata();
      head->setnext(temp->getnext());
      if(temp==rear) rear=head;
      delete temp;
      length--;
      return true;
    };

    bool peak(T &rdata)
    {
      if(rear==head) return false;
      rdata=head->getnext()->getdata();
      return true;
    };
    int size() const {return length;};

    bool isEmpty() const {return rear==head;};

};

template <class T>
class myQueueA
{
  private:
    int head;
    int rear;
    T *data;
    int length;
    int maxSize;

  public:
    myQueueA(int size)
    {
      head=1;
      rear=0;
      data=new T [size+1];
      maxSize=size;
      length=0;
    };

    ~myQueueA() {delete [] data;};

    bool enQueue(const T &newdata)
    {
      if((rear+2)%maxSize==head) return false;
      rear=(rear+1)%maxSize;
      data[rear]=newdata;
      length++;
      return true;
    };

    bool deQueue(T &rdata)
    {
      if((rear+1)%maxSize==head) return false;
      rdata=data[head];
      head=(head+1)%maxSize;
      length--;
      return true;
    };

    bool peak(T &rdata)
    {
      if((rear+1)%maxSize==head) return false;
      rdata=data[head];
      return true;
    };
    int size() const {return length;};

    bool isEmpty() const {return (rear+1)%maxSize==head;};
};

int main()
{
  int N;
  int p,q;
  myQueueA<int> carQueue(100000);
  myQueueL<int> trunkQueue;
  cin>>N;
  for(int i=0;i<N;i++)
  {
    cin>>p>>q;
    if(p==0) carQueue.enQueue(q);
    if(p==1) trunkQueue.enQueue(q);
  }
  int carNum=carQueue.size();
  int trunkNum=trunkQueue.size();
  int cTime=0;
  double cartotalTime=0;
  double trunktotalTime=0;
  int count=0;
  int tempTime=0;
  while(!carQueue.isEmpty()||!trunkQueue.isEmpty())
  {
    count=0;
    carQueue.peak(tempTime);
    while(tempTime<=cTime&&!carQueue.isEmpty()&&count<8)
    {
      carQueue.deQueue(tempTime);
      cartotalTime+=cTime-tempTime;
      count++;
      carQueue.peak(tempTime);
    }
    trunkQueue.peak(tempTime);
    while(tempTime<=cTime&&!trunkQueue.isEmpty()&&count<10)
    {
      trunkQueue.deQueue(tempTime);
      trunktotalTime+=cTime-tempTime;
      count++;
      trunkQueue.peak(tempTime);
    }
    carQueue.peak(tempTime);
    while(tempTime<=cTime&&!carQueue.isEmpty()&&count<10)
    {
      carQueue.deQueue(tempTime);
      cartotalTime+=cTime-tempTime;
      count++;
      carQueue.peak(tempTime);
    }

    cTime+=10;
  }

  double aveTimeCar=cartotalTime/carNum;
  double aveTimeTrunk=trunktotalTime/trunkNum;

  printf("%.3f %.3f",aveTimeCar,aveTimeTrunk);
  return 0;

}
