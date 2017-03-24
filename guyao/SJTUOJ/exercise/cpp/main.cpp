#include <iostream>
#include <fstream>
#include "HuffmannTree.h"



using namespace std;

/// Count the characters in a file
void countFile(int *totalChar,char *fileAddr)
{
  ifstream fin;
  fin.open(fileAddr);
  char temp;
  while((temp=fin.get())!=-1)
  {
    totalChar[(int)temp]++;
  }
  fin.close();
}

int power(int bn,int exp)
{
  int result=1;
  for(int i=0;i<exp;i++)
  {
    result*=bn;
  }
  return result;
}

char bit2char(int *bitArray)
{
  char result='\0';
  for(int i=0;i<8;i++)
  {
    result+=bitArray[i]*power(2,7-i);
  }
  return result;
}

void char2bit(char ch,int *bitArray)
{
  int temp=(ch-'\0'+256)%256;
  for(int i=0;i<8;i++)
  {
    bitArray[7-i]=temp%2;
    temp/=2;
  }
}

///save compression File
void saveCompressionFile(huffTree<char> &tree,char *fileAddr)
{
  ifstream fin(fileAddr);
  ofstream fout("compression.dat",ofstream::binary);
  tree.outputTree(fout);
  int **Code=tree.getCodeTable();
  int buffer[8]={0};
  int bufferPosi=1;
  int codePosi=0;
  char compChar='\0';
  char tempChar;
  while(true)
  {
    compChar=fin.get();
    while(compChar<-1) compChar=fin.get();
    if(compChar!=EOF)
    {
      codePosi=0;
      compChar=(compChar+256)%256;
      while(Code[(int)compChar][codePosi]!=-1)
      {
        buffer[bufferPosi]=Code[(int)compChar][codePosi];
        if(bufferPosi==7)
        {
          tempChar=bit2char(buffer);
          fout.write(&tempChar,1);
        }
        bufferPosi=bufferPosi%7+1;
        codePosi++;
      }
    }
    else
    {
      if(bufferPosi==1) break;
      for(int i=bufferPosi;i<8;i++)
      {
        buffer[i]=0;
      }
      tempChar=bit2char(buffer);
      fout.write(&tempChar,1);
      break;
    }
  }
  fout<<(char)-1;
  fin.close();
  fout.close();
}

///decode compression File
bool reCompressionFile(const char *fileAddr)
{
  ifstream fin(fileAddr,ifstream::binary);
  ofstream fout("recompression.txt");
  huffTree<char> codeTree;
  codeTree.inputTree(fin);
  char *tempData=new char;
  int bitArray[8];
  codeTree.setDpointerRoot();
  while(true)
  {
    fin.read(tempData,1);
    if(*tempData==-1) break;
    char2bit(*tempData,bitArray);
    for(int i=1;i<8;i++)
    {
      if(bitArray[i]==0)
      {
        codeTree.goLeft();
        if(codeTree.isDpointerLeaf())
        {
          fout<<codeTree.getDpointerData();
          codeTree.setDpointerRoot();
        }
      }
      else if(bitArray[i]==1)
      {
        codeTree.goRight();
        if(codeTree.isDpointerLeaf())
        {
          fout<<codeTree.getDpointerData();
          codeTree.setDpointerRoot();
        }
      }
    }
  }


  delete tempData;
  fin.close();
  fout.close();
  return 0;
}

void compression(char *fileAddr)
{
  int num=0;
  char data;
  huffNode<char> **nodeArray;
  int totalChar[256]={0};

  ///count file character frequency
  countFile(totalChar,fileAddr);

  ///count total character types
  for(int i=0;i<256;i++) if(totalChar[i]!=0) num++;

  ///create huffTree
  nodeArray=new huffNode<char>* [num];
  int tempCount=0;
  for(int i=0;i<256;i++)
  {
    if(totalChar[i]!=0)
    {
      data='\0'+i;
      nodeArray[tempCount]=new leafNode<char>(data,totalChar[i]);
      tempCount++;
    }
  }
  huffTree<char> codeTree(nodeArray,num);
  delete [] nodeArray;

  ///create huffCode
  //codeTree.outputCode();
  codeTree.createCodeTable();

  ///save compression File
  saveCompressionFile(codeTree,fileAddr);
}

///xx.exe 0(compression)/1(recompression) fileAddr
int main(int argc,char **argv)
{
  if(argc==3)
  {
    if(argv[1][0]-'0'==0) compression(argv[2]);
    if(argv[1][0]-'0'==1) reCompressionFile(argv[2]);
  }
  return 0;
}
