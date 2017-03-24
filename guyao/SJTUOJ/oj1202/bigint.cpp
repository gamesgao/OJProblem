#include <iostream>

using namespace std;

class node
{
  public:
    int num;
    node *next;

  public:
    node(int newnum,node *newnext);


};

class llist
{
  public:
    int clen;
    node *header;
    node *tail;
    node *fence;


  public:
    llist();
    llist(const llist &temp);
    ~llist();
    void append(int n);
    void appheader(int n);
    void nextnode(){fence=fence->next;};
    void setfenceheader(){fence=header;};
    int getnum() const;
    void setnum(int n);
};

class bigint
{
  private:
    llist *data;
  public:
    bigint(llist * newdata):data(newdata) {};
    bigint(const bigint &other):data(other.data) {};
    bigint operator+(bigint &other);
    void biprint();
    ~bigint() {delete data;};
};


node::node(int newnum,node *newnext)
{
  num=newnum;
  next=newnext;
}


llist::llist()
{
  clen=0;
  header=new node(0,NULL);
  fence=tail=header;
}

llist::llist(const llist &temp)
{
  clen=0;
  header=new node(0,NULL);
  fence=tail=header;
  for(int i=1;i<=temp.clen;i++)
  {
    this->append(temp.getnum());
  }
}

llist::~llist()
{
  node *temp;
  while(header)
  {
    temp=header;
    header=header->next;
    delete temp;
  }

}


void llist::append(int n)
{
  node *temp = new node(n,NULL);
  tail->next=temp;
  tail=tail->next;
  clen++;
}

void llist::appheader(int n)
{
  header->next=new node(n,header->next);
  clen++;
}


int llist::getnum() const
{
  return fence->num;
}

void llist::setnum(int n)
{
  fence->num=n;
}

bigint bigint::operator+(bigint &other)
{
  llist *temp =new llist;
  if((data->clen)>((other.data)->clen))
  {
    int jwei=0;
    int result;
    for(int i=1;i<=(other.data)->clen;i++)
    {
      data->nextnode();
      (other.data)->nextnode();
      result=(data->getnum()+(other.data)->getnum()+jwei)%10;
      jwei=(data->getnum()+(other.data)->getnum()+jwei)/10;
      temp->append(result);
    }
    for(int i=(other.data)->clen+1;i<=data->clen;i++)
    {
      data->nextnode();
      result=(data->getnum()+jwei)%10;
      jwei=(data->getnum()+jwei)/10;
      temp->append(result);
    }
    if(jwei==1) temp->append(1);
  }
  else
  {
    int jwei=0;
    int result;
    for(int i=1;i<=data->clen;i++)
    {
      data->nextnode();
      (other.data)->nextnode();
      result=(data->getnum()+(other.data)->getnum()+jwei)%10;
      jwei=(data->getnum()+(other.data)->getnum()+jwei)/10;
      temp->append(result);
    }
    for(int i=data->clen+1;i<=(other.data)->clen;i++)
    {
      (other.data)->nextnode();
      result=(((other.data)->getnum())+jwei)%10;
      jwei=((other.data)->getnum()+jwei)/10;
      temp->append(result);
    }
    if(jwei==1) temp->append(1);
  }
  return bigint(temp);
}

void bigint::biprint()
{
  llist templl;
  node * temp=data->header->next;
  while(temp)
  {
    templl.appheader(temp->num);
    temp=temp->next;
  }
  temp=(templl.header)->next;
  while(temp)
  {
    cout<<temp->num;
    temp=temp->next;
  }
  cout<<endl;
}





int main()
{
  int temp;
  llist *templl1=new llist;
  llist *templl2=new llist;
  while((temp=cin.get())!='\n')
  {
    temp-='0';
    templl1->appheader(temp);
  }
  while((temp=cin.get())!='\n')
  {
    temp-='0';
    templl2->appheader(temp);
  }
  bigint bi1(templl1),bi2(templl2),bi3=bi1+bi2;
  bi3.biprint();
  return 0;
}
