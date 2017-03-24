#ifndef MQ_H_INCLUDED
#define MQ_H_INCLUDED

template<class T, class compare>
class myQueue
{
  private:
    T data[520];
    int rear;
    int head;
    int maxSize;
    int queueSize;
    compare comp;

  public:
    myQueue()
    {
      rear=0;
      head=1;
      maxSize=100000;
      queueSize=0;
    };

    bool enqueue(T newdata)
    {
      if((rear+2)%maxSize==head) return false;
      rear=(rear+1)%maxSize;
      int nowposi=rear;
      while(nowposi!=head)
      {
        if(comp(data[(nowposi-1+maxSize)%maxSize],newdata)) {data[nowposi]=data[(nowposi-1+maxSize)%maxSize];nowposi=(nowposi-1+maxSize)%maxSize;}
        else break;
      }
      data[nowposi]=newdata;
      queueSize++;
      return true;
    };

    T dequeue()
    {
      if((rear+1)%maxSize==head) return NULL;
      T temp=data[head];
      head=(head+1)%maxSize;
      queueSize--;
      return temp;
    };

    bool isEmpty() const
    {
      return (rear+1)%maxSize==head;
    };

    int getSize() const {return queueSize;};
};

#endif // MQ_H_INCLUDED
