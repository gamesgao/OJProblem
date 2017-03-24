#include <iostream>

using namespace std;



int main()
{
  int a,b,c,y1,y2;
  int m[12]={31,28,31,30,31,30,31,31,30,31,30,31};
  int mx[12]={31,29,31,30,31,30,31,31,30,31,30,31};
  char* monthstr[12]={"01","02","03","04","05","06","07","08","09","10","11","12"};
  char* daystr[31]{"01","02","03","04","05","06","07","08","09","10","11","12","13","14","15","16","17","18","19","20","21","22","23","24","25","26","27","28","29","30","31"};
  cin>>a>>b>>c>>y1>>y2;
  int xinqi=2;
  int year=1850;
  int month=1;
  int day=1;
  int days=365;
  c=c%7;
  for(;year<y1;year++)
  {
    days=365;
    if(year%400==0||(year%100!=0&&year%4==0)) days=366;
    xinqi=(xinqi+days)%7;
  }
  for(;year<=y2;year++)
  {
    month=1;
    day=1;
    int tempxinqi=xinqi;
    int sum=0;
    int count=0;
    for(;month<a;month++)
    {
      if(year%400==0||(year%100!=0&&year%4==0)) sum+=mx[month-1];
      else sum+=m[month-1];
    }
    tempxinqi=(tempxinqi+sum)%7;
    if(year%400==0||(year%100!=0&&year%4==0))
    {
      bool get=false;
      for(;day<=mx[month-1];day++)
      {
        if(tempxinqi==c) count++;
        if(count==b) {get=true;break;}
        tempxinqi=(tempxinqi+1)%7;
      }
      if(get) cout<<year<<'/'<<monthstr[month-1]<<'/'<<daystr[day-1]<<endl;
      else cout<<"none"<<endl;
    }
    else
    {
      bool get=false;
      for(;day<=m[month-1];day++)
      {
        if(tempxinqi==c) count++;
        if(count==b) {get=true;break;}
        tempxinqi=(tempxinqi+1)%7;
      }
      if(get) cout<<year<<'/'<<monthstr[month-1]<<'/'<<daystr[day-1]<<endl;
      else cout<<"none"<<endl;
    }
    days=365;
    if(year%400==0||(year%100!=0&&year%4==0)) days=366;
    xinqi=(xinqi+days)%7;
  }


  return 0;
}
