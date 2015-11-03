#include <iostream>
//#include <stdio.h>

using namespace std;


bool equalstr(const char *s1,const char *s2);
int strlen(const char *s);


template <class T>
class myNode
{
  private:
    T data;
    myNode<T> *next;

  public:
    myNode(){next=NULL;};
    myNode(const T &newdata,myNode<T> *newnext):data(newdata),next(newnext) {};

    void setdata(const T &newdata) {data=newdata;};
    T &getdata() {return data;};
    void setnext(myNode<T> *newnext) {next=newnext;};
    myNode *getnext() const {return next;};
};

template <class T>
class mylist
{
  private:
    int clen;
    myNode<T> *header;
    myNode<T> *tail;
    myNode<T> *fence;

  public:
    mylist(){
      clen=0;
      header=new myNode<T>();
      tail=fence=header;
    };
    ~mylist(){
      while(header)
      {
        fence=header->getnext();
        delete header;
        header=fence;
      }
    };

    void append(const T &newdata){
      tail->setnext(new myNode<T> (newdata,tail->getnext()));
      tail=tail->getnext();
      clen++;
    };

    void insert(const T &newdata){
      fence->setnext(new myNode<T> (newdata,fence->getnext()));
      if(fence==tail) tail=tail->getnext();
      clen++;
    };

    void remove(){
      myNode<T> *temp;
      temp=fence->getnext();  //没有处理当fence=tail的情况
      fence->setnext(fence->getnext()->getnext());
      clen--;
      if(temp==tail) tail=fence;
      delete temp;
    };

    void tonext() {
      if(fence!=tail) fence=fence->getnext();
    };

    void setheader() {fence=header;};

    int getclen() const {return clen;};

    T &getdata(){return fence->getdata();}; //没有处理当fence=header的情况

};

void list(mylist<mylist<char> > &passage);
void ins(mylist<mylist<char> > &passage);
void del(mylist<mylist<char> > &passage);
void quit(mylist<mylist<char> > &passage);

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
  //freopen("data.in","r",stdin);
  //freopen("data.out","w",stdout);


  char instr[10];
  mylist<mylist<char> > passage;  //必须要空一格！！！
  int count=0;
  char temp;
  while(true)
  {
    temp=cin.get();
    if(temp=='*')
    {
      //count++;
      //if(count>=6) break;
      //continue;
      break;
    }
    else
    {
      passage.append(*(new mylist<char>()));
      passage.tonext();
      mylist<char> &temprow=passage.getdata();
      for(int i=0;i<count;i++) temprow.append('*');
      temprow.append(temp);
      while((temp=cin.get())!='\n')
      {
        temprow.append(temp);
      }
      temprow.append('\n');
    }
  }
  cin.getline(instr,10,'\n');
  cin.getline(instr,5,' ');
  while(!equalstr(instr,"quit"))
  {
    if(equalstr(instr,"list")) list(passage);
    else{
      if(equalstr(instr,"ins")) ins(passage);
      else{
        if(equalstr(instr,"del")) del(passage);
        else cout<<"Error!"<<endl;
      }
    }
    cin.getline(instr,5,' ');
  }
  quit(passage);
  return 0;
}

void list(mylist<mylist<char> > &passage)
{
  int n1,n2;
  cin>>n1>>n2;
  passage.setheader();
  if(n1<=0||n2<=0) {cout<<"Error!"<<endl;cin.get();return;}
  if(!(n1<=passage.getclen()&&n2<=passage.getclen())) {cout<<"Error!"<<endl;cin.get();return;}
  if(n1>n2) {cout<<"Error!"<<endl;cin.get();return;}
  for(int i=0;i<n1;i++)
  {
    passage.tonext();
  }
  for(int i=n1;i<=n2;i++)
  {
    mylist<char> &temprow=passage.getdata();
    temprow.setheader();
    for(int j=0;j<temprow.getclen();j++)
    {
      temprow.tonext();
      cout<<temprow.getdata();
    }
    passage.tonext();
  }
  cin.get();
}

void ins(mylist<mylist<char> > &passage)
{
  int n1,n2;
  char temp[100];
  cin>>n1>>n2;
  cin.get();
  cin.getline(temp,100,'\n');
  passage.setheader();
  if(n1<=0||n2<=0) {cout<<"Error!"<<endl;return;}
  if(n1>passage.getclen()) {cout<<"Error!"<<endl;return;}
  for(int i=0;i<n1;i++)
  {
    passage.tonext();
  }
  mylist<char> &temprow=passage.getdata();
  if(n2>temprow.getclen()+1) {cout<<"Error!"<<endl;return;}
  temprow.setheader();
  for(int i=0;i<n2-1;i++)
  {
    temprow.tonext();
  }
  int posi=0;
  while(temp[posi]!='\0')
  {
    temprow.insert(temp[posi]);
    temprow.tonext();
    posi++;
  }
}

void del(mylist<mylist<char> > &passage)
{
  int n1,n2;
  int num;
  cin>>n1>>n2>>num;
  passage.setheader();
  if(n1<=0||n2<=0) {cout<<"Error!"<<endl;cin.get();return;}
  if(n1>passage.getclen()||num<0) {cout<<"Error!"<<endl;cin.get();return;}
  for(int i=0;i<n1;i++)
  {
    passage.tonext();
  }
  mylist<char> &temprow=passage.getdata();
  if(n2>temprow.getclen()) {cout<<"Error!"<<endl;cin.get();return;}
  temprow.setheader();
  for(int i=0;i<n2-1;i++)
  {
    temprow.tonext();
  }
  if(num>temprow.getclen()-n2+1) {cout<<"Error!"<<endl;cin.get();return;}
  for(int i=0;i<num;i++)
  {
    temprow.remove();
  }
  cin.get();
}

void quit(mylist<mylist<char> > &passage)
{
  passage.setheader();
  passage.tonext();
  for(int i=1;i<=passage.getclen();i++)
  {
    mylist<char> &temprow=passage.getdata();
    temprow.setheader();
    for(int j=0;j<temprow.getclen();j++)
    {
      temprow.tonext();
      cout<<temprow.getdata();
    }
    passage.tonext();
  }
}
