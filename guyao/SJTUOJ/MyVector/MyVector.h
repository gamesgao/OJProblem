#ifndef MYVECTOR_H_INCLUDED
#define MYVECTOR_H_INCLUDED

#include <iostream>
using namespace std;

template <class T>
class myVector
{

  private:
    int Size;
    int Capacity;
    T *Data;

  public:
    class iterator;
    class const_iterator;

  public:
    explicit myVector(int initSize = 0);
    myVector(const myVector &R);
    ~myVector(){delete [] Data;};

    void resize(int newSize){Size=newSize;};  //The newSize must be smaller than Size
    void reserve(int newCapacity);  //The newCapacity must be bigger than Capacity

    T &operator[](int index) {return Data[index];};
    const T &operator[](int index) const {return Data[index];};

    bool empty() const {return Size==0;};
    int mysize() const {return Size;};
    int mycapacity() const {return Capacity;};

    void push_back(const T &x);
    void pop_back() {Size--;};

    const T &back() const {return Data[Size-1];};

    iterator begin() {return myVector<T>::iterator(0,this);};
    const_iterator begin() const {return myVector<T>::const_iterator(0,this);};
    iterator end() {return myVector<T>::iterator(Size-1,this);};
    const_iterator end() const {return myVector<T>::const_iterator(Size-1,this);};
};

template <class T>
class myVector<T>::iterator
{

    friend class myVector<T>::const_iterator;
    private:
      int posi;
      myVector<T> *upper;

    public:
      iterator(int newposi=0,myVector<T> *newupper=NULL):posi(newposi),upper(newupper){}; //must be refer to a vector before using!
      iterator(const myVector<T>::iterator &R):posi(R.posi),upper(R.upper){};

      bool operator==(const myVector<T>::const_iterator &other) const {return (upper==other.upper)&&(posi==other.posi);};
      bool operator!=(const myVector<T>::const_iterator &other) const {return (upper!=other.upper)||(posi!=other.posi);};
      bool operator==(const myVector<T>::iterator &other) const {return (upper==other.upper)&&(posi==other.posi);};
      bool operator!=(const myVector<T>::iterator &other) const {return (upper!=other.upper)||(posi!=other.posi);};

      myVector<T>::iterator &operator++();
      myVector<T>::iterator operator++(int fool);

      T &operator*() const {return (*upper)[posi];};
};

template <class T>
class myVector<T>::const_iterator
{
  friend class myVector<T>::iterator;
  private:
    int posi;
    myVector<T> *upper;

  public:
    const_iterator():posi(0),upper(NULL){};
    const_iterator(const myVector<T>::iterator &R):posi(R.posi),upper(R.upper){};

    bool operator==(const myVector<T>::const_iterator &other) const {return (upper==other.upper)&&(posi==other.posi);};
    bool operator!=(const myVector<T>::const_iterator &other) const {return (upper!=other.upper)||(posi!=other.posi);};
    bool operator==(const myVector<T>::iterator &other) const {return (upper==other.upper)&&(posi==other.posi);};
    bool operator!=(const myVector<T>::iterator &other) const {return (upper!=other.upper)||(posi!=other.posi);};

    myVector<T>::const_iterator &operator++();
    myVector<T>::const_iterator operator++(int fool);

    const T &operator*() const {return (*upper)[posi];};
};

#endif // MYVECTOR_H_INCLUDED









using namespace std;

template <class T>
myVector<T>::myVector(int initSize)
{
  Size=0;
  Capacity=initSize;
  Data=new T [Capacity];
}

template <class T>
myVector<T>::myVector(const myVector &R)
{
  Size=R.Size;
  Capacity=R.Capacity;
  Data=new T [Capacity];
  for(int i=0;i<Size;i++)
  {
    Data[i]=R.Data[i];
  }
}

template <class T>
void myVector<T>::reserve(int newCapacity)
{
  T *temp=Data;
  Data=new T [newCapacity];
  for(int i=0;i<Size;i++)
  {
    Data[i]=temp[i];
  }
  Capacity=newCapacity;
  delete [] temp;
}

template <class T>
void myVector<T>::push_back(const T &x)
{
  if(Size+1>Capacity)
  {
    if(Capacity==0) Capacity=1;
    else reserve(Capacity*2);
  }
  Data[Size++]=x;
}


template<class T>
class myVector<T>::iterator &myVector<T>::iterator::operator++()
{
  posi++;
  return *this;
}

template<class T>
class myVector<T>::iterator myVector<T>::iterator::operator++(int fool)
{
  myVector<T>::iterator temp=*this;
  posi++;
  return temp;
}

template<class T>
class myVector<T>::const_iterator &myVector<T>::const_iterator::operator++()
{
  posi++;
  return *this;
}

template<class T>
class myVector<T>::const_iterator myVector<T>::const_iterator::operator++(int fool)
{
  myVector<T>::const_iterator temp=*this;
  posi++;
  return temp;
}

