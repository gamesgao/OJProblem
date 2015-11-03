#include <iostream>

using namespace std;

int main()
{
  int sTime[5001]={0};
  int eTime[5001]={0};
  int temps=0;
  int tempe=0;
  int N=0;
  cin>>N;
  for(int i=0;i<N;i++)
  {
    cin>>temps>>tempe;
    sTime[i]=temps;
    eTime[i]=tempe;
    for(int j=i-1;j>=0;j--)
    {
      if(sTime[j]<=temps) break;
      else
      {
        sTime[j+1]=sTime[j];
        sTime[j]=temps;
      }
    }
    for(int j=i-1;j>=0;j--)
    {
      if(eTime[j]<=tempe) break;
      else
      {
        eTime[j+1]=eTime[j];
        eTime[j]=tempe;
      }
    }
  }
  sTime[N]=1000001;
  eTime[N]=1000001;
  int pointers=0,pointere=0;
  int milkNum=0;
  int beginTimerlt=0,beginTimeidle=0;
  int rlt=0,nowrlt=0,idle=0,nowidle=0;
  bool rltbegin=false,idlebegin=false;
  for(int i=0;i<2*N;i++)
  {
    if(sTime[pointers]<=eTime[pointere])
    {
      if(milkNum==0)
      {
        beginTimerlt=sTime[pointers];
        rltbegin=true;
        if(idlebegin) nowidle=sTime[pointers]-beginTimeidle;
        if(idle<nowidle) idle=nowidle;
        idlebegin=false;
      }
      pointers++;
      milkNum++;
    }
    else
    {

      milkNum--;
      if(milkNum==0)
      {
        beginTimeidle=eTime[pointere];
        idlebegin=true;
        if(rltbegin) nowrlt=eTime[pointere]-beginTimerlt;
        if(rlt<nowrlt) rlt=nowrlt;
        rltbegin=false;
      }
      pointere++;
    }
  }
  cout<<rlt<<' '<<idle<<endl;





  return 0;
}
