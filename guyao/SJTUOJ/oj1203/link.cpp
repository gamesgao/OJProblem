#include <iostream>

using namespace std;

bool equalstr(const char *s1,const char *s2);
int strlen(const char *s);

template <class T>
class list
{
  template<class B>  //这里很重要，必须这么写不能直接用上面的T，不然相当于声明的是一个非模板函数，与下面的定义不符
  friend list<B> operator+(list<B> &a1,list<B> &a2);

  private:
    int clen;
    T *data;

  public:
    list();
    list(const list<T> & other);
    ~list() {delete [] data;};

    void setdata(int posi,T &newdata) {data[posi]=newdata;};
    void setclen(int n){clen=n;};
    list<T> &operator=(const list<T> & other);
    void print() const;


};

template <class T>
list<T>::list()
{
  clen=0;
  data = new T [20001];
}

template <class T>
list<T>::list(const list<T> & other)
{
  clen=other.clen;
  data = new T [20001];
  for(int i=0;i<clen;i++)
  {
    data[i]=other.data[i];
  }
}

template <class T>
list<T> &list<T>::operator=(const list<T> & other)
{
  clen=other.clen;
  data = new T [20001];
  for(int i=0;i<clen;i++)
  {
    data[i]=other.data[i];
  }
  return *this;
}

template <class T>
list<T> operator+(list<T> &a1,list<T> &a2)
{
  list<T> temp;
  temp.clen=a1.clen+a2.clen;
  for(int i=0;i<a1.clen;i++)
  {
    temp.data[i]=a1.data[i];
  }
  for(int i=a1.clen;i<temp.clen;i++)
  {
    temp.data[i]=a2.data[i-a1.clen];
  }
  return temp;
}

template <class T>
void list<T>::print() const
{
  for(int i=0;i<clen;i++)
  {
    cout<<data[i]<<' ';
  }
  cout<<endl;
}

int strlen(const char *s)
{
  int temp=0;
  while(s[temp]!='\0') temp++;
  return temp;
}

bool equalstr(const char *s1,const char *s2)
{
  if(strlen(s1)!=strlen(s2)) return false;
  for(int i=0;i<strlen(s1);i++)
  {
    if(s1[i]!=s2[i]) return false;
  }
  return true;
}


int main()
{
  char type[7];
  cin.getline(type,7);
  if(equalstr(type,"int"))
  {
    int temp;
    list<int> l1,l2,l3;
    int n,m;
    cin>>n>>m;
    l1.setclen(n);
    l2.setclen(m);
    for(int i=0;i<n;i++)
    {
      cin>>temp;
      l1.setdata(i,temp);
    }
    for(int i=0;i<m;i++)
    {
      cin>>temp;
      l2.setdata(i,temp);
    }
    l3 = l1 + l2;
    l3.print();
  }
  else
  {
    if(equalstr(type,"double"))
    {
      double temp;
      list<double> l1,l2,l3;
      int n,m;
      cin>>n>>m;
      l1.setclen(n);
      l2.setclen(m);
      for(int i=0;i<n;i++)
      {
        cin>>temp;
        l1.setdata(i,temp);
      }
      for(int i=0;i<m;i++)
      {
        cin>>temp;
        l2.setdata(i,temp);
      }
      l3=l1+l2;
      l3.print();
    }
    else
    {
      if(equalstr(type,"char"))
      {
        char temp;
        list<char> l1,l2,l3;
        int n,m;
        cin>>n>>m;
        l1.setclen(n);
        l2.setclen(m);
        for(int i=0;i<n;i++)
        {
          cin>>temp;
          l1.setdata(i,temp);
        }
        for(int i=0;i<m;i++)
        {
          cin>>temp;
          l2.setdata(i,temp);
        }
        l3=l1+l2;
        l3.print();
      }
      else return -1;
    }
  }
  return 0;
}
