#include <iostream>

using namespace std;

class myClock
{
  private:
    int data[3][3];

  public:
    myClock(int newdata[3][3])
    {
      for(int i=0;i<3;i++)
      {
        for(int j=0;j<3;j++)
        {
          data[i][j]=newdata[i][j]%12;
        }
      }
    };

    void init(const myClock &other)
    {
      for(int i=0;i<3;i++)
      {
        for(int j=0;j<3;j++)
        {
          data[i][j]=other.data[i][j];
        }
      }
    };

    void op1()
    {
      //A
      data[0][0]=(data[0][0]+3)%12;
      //B
      data[0][1]=(data[0][1]+3)%12;
      //D
      data[1][0]=(data[1][0]+3)%12;
      //E

      data[1][1]=(data[1][1]+3)%12;

    };

    void op2()
    {
      //A

      data[0][0]=(data[0][0]+3)%12;

      //B

      data[0][1]=(data[0][1]+3)%12;

      //C

      data[0][2]=(data[0][2]+3)%12;

    };

    void op3()
    {
      //B

      data[0][1]=(data[0][1]+3)%12;

      //C

      data[0][2]=(data[0][2]+3)%12;

      //E

      data[1][1]=(data[1][1]+3)%12;

      //F

      data[1][2]=(data[1][2]+3)%12;

    };

    void op4()
    {
      //A

      data[0][0]=(data[0][0]+3)%12;

      //D

      data[1][0]=(data[1][0]+3)%12;

      //G

      data[2][0]=(data[2][0]+3)%12;

    };

    void op5()
    {
      //B

      data[0][1]=(data[0][1]+3)%12;

      //D

      data[1][0]=(data[1][0]+3)%12;

      //E

      data[1][1]=(data[1][1]+3)%12;

      //F

      data[1][2]=(data[1][2]+3)%12;

      //H

      data[2][1]=(data[2][1]+3)%12;

    };

    void op6()
    {
      //C

      data[0][2]=(data[0][2]+3)%12;

      //F

      data[1][2]=(data[1][2]+3)%12;

      //I

      data[2][2]=(data[2][2]+3)%12;

    };

    void op7()
    {
      //D

      data[1][0]=(data[1][0]+3)%12;

      //E

      data[1][1]=(data[1][1]+3)%12;

      //G

      data[2][0]=(data[2][0]+3)%12;

      //H

      data[2][1]=(data[2][1]+3)%12;

    };

    void op8()
    {
      //G

      data[2][0]=(data[2][0]+3)%12;

      //H

      data[2][1]=(data[2][1]+3)%12;

      //I

      data[2][2]=(data[2][2]+3)%12;

    };

    void op9()
    {
      //E

      data[1][1]=(data[1][1]+3)%12;

      //F

      data[1][2]=(data[1][2]+3)%12;

      //H

      data[2][1]=(data[2][1]+3)%12;

      //I

      data[2][2]=(data[2][2]+3)%12;

    };

    bool getSuit() const {
      for(int i=0;i<3;i++)
      {
        for(int j=0;j<3;j++) if(data[i][j]!=0) return false;
      }
      return true;
    };
};

void opChoose(int op,myClock &cl)
{
  switch(op)
  {
    case 1: cl.op1();break;
    case 2: cl.op2();break;
    case 3: cl.op3();break;
    case 4: cl.op4();break;
    case 5: cl.op5();break;
    case 6: cl.op6();break;
    case 7: cl.op7();break;
    case 8: cl.op8();break;
    case 9: cl.op9();break;
  }
}

bool baoli(const myClock &cl,int *nowSolution)
{
  myClock tempcl1(cl);
  myClock nowclock(tempcl1);
  for(int i1=nowSolution[0];i1<4;i1++)
  {

    for(int i=0;i<i1;i++) opChoose(1,nowclock);
    nowSolution[0]=i1;
    if(nowclock.getSuit()) return true;
    myClock tempcl2(nowclock);
    for(int i2=nowSolution[1];i2<4;i2++)
    {
      for(int i=0;i<i2;i++) opChoose(2,nowclock);
      nowSolution[1]=i2;
      if(nowclock.getSuit()) return true;
      myClock tempcl3(nowclock);
      for(int i3=nowSolution[2];i3<4;i3++)
      {
        for(int i=0;i<i3;i++) opChoose(3,nowclock);
        nowSolution[2]=i3;
        if(nowclock.getSuit()) return true;
        myClock tempcl4(nowclock);
        for(int i4=nowSolution[3];i4<4;i4++)
        {
          for(int i=0;i<i4;i++) opChoose(4,nowclock);
          nowSolution[3]=i4;
          if(nowclock.getSuit()) return true;
          myClock tempcl5(nowclock);
          for(int i5=nowSolution[4];i5<4;i5++)
          {
            for(int i=0;i<i5;i++) opChoose(5,nowclock);
            nowSolution[4]=i5;
            if(nowclock.getSuit()) return true;
            myClock tempcl6(nowclock);
            for(int i6=nowSolution[5];i6<4;i6++)
            {
              for(int i=0;i<i6;i++) opChoose(6,nowclock);
              nowSolution[5]=i6;
              if(nowclock.getSuit()) return true;
              myClock tempcl7(nowclock);
              for(int i7=nowSolution[6];i7<4;i7++)
              {
                for(int i=0;i<i7;i++) opChoose(7,nowclock);
                nowSolution[6]=i7;
                if(nowclock.getSuit()) return true;
                myClock tempcl8(nowclock);
                for(int i8=nowSolution[7];i8<4;i8++)
                {
                  for(int i=0;i<i8;i++) opChoose(8,nowclock);
                  nowSolution[7]=i8;
                  if(nowclock.getSuit()) return true;
                  myClock tempcl9(nowclock);
                  for(int i9=nowSolution[8];i9<4;i9++)
                  {
                    for(int i=0;i<i9;i++) opChoose(9,nowclock);
                    nowSolution[8]=i9;
                    if(nowclock.getSuit()) return true;
                    nowclock=tempcl9;
                  }
                  nowSolution[8]=0;
                  nowclock=tempcl8;
                }
                nowSolution[7]=0;
                nowclock=tempcl7;
              }
              nowSolution[6]=0;
              nowclock=tempcl6;
            }
            nowSolution[5]=0;
            nowclock=tempcl5;
          }
          nowSolution[4]=0;
          nowclock=tempcl4;
        }
        nowSolution[3]=0;
        nowclock=tempcl3;
      }
      nowSolution[2]=0;
      nowclock=tempcl2;
    }
    nowSolution[1]=0;
    nowclock=tempcl1;
  }
  nowSolution[0]=0;
  return false;
}

int solutionLen(int *nowSolution)
{
  int temp=0;
  for(int i=0;i<10;i++) temp+=nowSolution[i];
  return temp;
}

void init(int *nowSolution)
{
  int upper=1;
  int temp;
  for(int i=8;i>=0;i--)
  {
    temp=nowSolution[i]+upper;
    nowSolution[i]=temp%4;
    upper=temp/4;
  }
  if(upper==1) for(int i=0;i<9;i++) nowSolution[i]=4;
}

void compare(int *nowSolution,int *result)
{
  int len1=solutionLen(nowSolution);
  int len2=solutionLen(result);
  if(len2==0) len2=100;
  if(len1<len2) for(int i=0;i<10;i++) result[i]=nowSolution[i];
  else
  {
    if(len1==len2)
    {
      bool flag=false;
      for(int i=0;i<9;i++)
      {
        if(nowSolution[i]>result[i]) {flag=true;break;}
      }
      if(flag) for(int i=0;i<10;i++) result[i]=nowSolution[i];
    }
  }
}


int main()
{
  int temp[3][3];
  for(int i=0;i<3;i++)
  {
    for(int j=0;j<3;j++)
    {
      cin>>temp[i][j];
    }
  }
  myClock cl(temp);
  //myClock tempcl(temp);
  int nowSolution[10]={0};
  int result[10]={0};
  while(true)
  {
    compare(nowSolution,result);
    init(nowSolution);
    if(!baoli(cl,nowSolution)) break;
  }
  for(int i=0;i<9;i++)
  {
    for(int j=0;j<result[i];j++) cout<<i+1<<' ';
  }
  cout<<endl;
  return 0;
}
