#include <iostream>

using namespace std;

class bigint
{
  friend bigint operator+(const bigint &op1,const bigint &op2);
  friend bigint operator-(const bigint &op1,const bigint &op2);
  //friend bigint operator*(const bigint &op1,const bigint &op2);
  friend bool operator>(const bigint &op1,const bigint &op2);
  friend bool operator>=(const bigint &op1,const bigint &op2);
  //friend bool operator<(const bigint &op1,const bigint &op2);
  friend ostream &operator<<(ostream &os,const bigint &op);

  private:
    int data[1000];
    int length;
  public:
    bigint(){
      for(int i=0;i<1000;i++) data[i]=0;
      length=0;
    };
    bigint(const bigint &other){
      for(int i=0;i<1000;i++) data[i]=0;
      length=other.length;
      for(int i=0;i<length;i++) data[i]=other.data[i];
    };
    bigint(char *num){
      for(int i=0;i<1000;i++) data[i]=0;
      int posi=0;
      while(num[posi]!='\0') posi++;
      for(int i=0;i<posi;i++)
      {
        data[i]=num[posi-i-1]-'0';
      }
      length=posi;
    };
    bigint(int other){
      for(int i=0;i<1000;i++) data[i]=0;
      length=0;
      int posi=0;
      while(other!=0)
      {
        data[posi]=other%10;
        other=other/10;
        posi++;
        length++;
      }
    };

    bigint &operator=(const bigint &other){
      for(int i=0;i<1000;i++) data[i]=0;
      length=other.length;
      for(int i=0;i<length;i++) data[i]=other.data[i];
      return *this;
    };

    void minus1()
    {
      int up=0;
      if(data[0]-1<0) {data[0]=data[0]-up+10;up=1;}
      else data[0]=data[0]-up;
      for(int i=1;i<length;i++)
      {
        if(data[i]-up>=0) {data[i]=data[i]-up;up=0;}
        else {data[i]=data[i]-up+10;up=1;}
      }
      int curlength=0;
      for(int i=0;i<length;i++)
      {
        if(data[i]!=0) curlength=i+1;
      }
      length=curlength;
    }

    void multi2()
    {
      int up=0;
      int temp;
      for(int i=0;i<length;i++)
      {
        temp=data[i];
        data[i]=(temp*2+up)%10;
        up=(temp*2+up)/10;
      }
      if(up!=0) {data[length]=up;length++;}
    }

};

bool operator>(const bigint &op1,const bigint &op2)
{
  if(op1.length>op2.length) return true;
  if(op1.length<op2.length) return false;
  for(int i=op1.length-1;i>=0;i--)
  {
    if(op1.data[i]>op2.data[i]) return true;
    if(op1.data[i]<op2.data[i]) return false;
  }
  return false;
}

bool operator>=(const bigint &op1,const bigint &op2)
{
  if(op1.length>op2.length) return true;
  if(op1.length<op2.length) return false;
  for(int i=op1.length-1;i>=0;i--)
  {
    if(op1.data[i]>op2.data[i]) return true;
    if(op1.data[i]<op2.data[i]) return false;
  }
  return true;
}


bigint operator+(const bigint &op1,const bigint &op2)
{
  int maxlength;
  bigint result;
  if(op1.length>op2.length) maxlength=op1.length;
  else maxlength=op2.length;
  int up=0;
  for(int i=0;i<maxlength;i++)
  {
    result.data[i]=(op1.data[i]+op2.data[i]+up)%10;
    up=(op1.data[i]+op2.data[i]+up)/10;
  }
  if(up==0) result.length=maxlength;
  else {result.data[maxlength]=up;result.length=maxlength+1;}
  return result;


}

bigint operator-(const bigint &op1,const bigint &op2)
{
  int maxlength;
  bigint result;
  if(op1.length>op2.length) maxlength=op1.length;
  else maxlength=op2.length;
  int up=0;
  for(int i=0;i<maxlength;i++)
  {
    if(op1.data[i]-op2.data[i]-up<0) {result.data[i]=op1.data[i]-op2.data[i]-up+10;up=1;}
    else {result.data[i]=op1.data[i]-op2.data[i]-up;up=0;}
  }
  int curlength=0;
  for(int i=0;i<maxlength;i++)
  {
    if(result.data[i]!=0) curlength=i+1;
  }
  result.length=curlength;
  return result;
}

ostream &operator<<(ostream &os,const bigint &op)
{
  for(int i=op.length-1;i>=0;i--)
  {
    os<<op.data[i];
  }
  return os;
}



int main()
{
  char temp[1001];
  cin.getline(temp,1001);
  bigint people(temp);
  bigint lower(1),upper(2);
  while(!(temp>=lower&&!(temp>=upper))) {lower.multi2();upper.multi2();}
  //cout<<lower<<' '<<upper<<endl;
  bigint result=temp-lower;
  result.multi2();
  result=result+1;
  cout<<result;
  return 0;
}
