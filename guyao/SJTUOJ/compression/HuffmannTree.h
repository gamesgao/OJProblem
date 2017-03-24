#ifndef HUFFMANNTREE_H_INCLUDED
#define HUFFMANNTREE_H_INCLUDED
#include <iostream>
#include "MQ.h"

using namespace std;

template <class T>
class huffNode
{
  public:
    virtual bool isLeaf()=0;
    virtual int getWeight()=0;
    virtual void setWeight(int w)=0;
    virtual huffNode<T> *left()=0;
    virtual huffNode<T> *right()=0;
    virtual void setLeft(huffNode<T> *lc)=0;
    virtual void setRight(huffNode<T> *rc)=0;
    virtual T &getData()=0;
    virtual void setData(T &newData)=0;
    virtual ~huffNode() {};

};


template <class T>
class leafNode:public huffNode<T>
{
  private:
    T data;
    int weight;

  public:
    leafNode(T &newdata,int newweight)
    {
      data=newdata;
      weight=newweight;
    };
    leafNode()
    {
    };

    T &val() {return data;};
    bool isLeaf() {return true;};
    int getWeight() {return weight;};
    void setWeight(int w) {weight=w;};
    T &getData() {return data;};
    void setData(T &newData) {data=newData;};

    huffNode<T> *left() {return NULL;};
    huffNode<T> *right() {return NULL;};
    void setLeft(huffNode<T> *lc) {};
    void setRight(huffNode<T> *rc) {};


};

template <class T>
class intlNode:public huffNode<T>
{
  private:
    int weight;
    huffNode<T> *lchild;
    huffNode<T> *rchild;
    T data;

  public:
    intlNode(huffNode<T> *lc,huffNode<T> *rc)
    {
      lchild=lc;
      rchild=rc;
      weight=lc->getWeight()+rc->getWeight();
    };

    intlNode()
    {
      lchild=NULL;
      rchild=NULL;
    };

    int getWeight() {return weight;};
    void setWeight(int w) {weight=w;};
    bool isLeaf() {return false;};
    huffNode<T> *left() {return lchild;};
    huffNode<T> *right() {return rchild;};
    void setLeft(huffNode<T> *lc) {lchild=lc;};
    void setRight(huffNode<T> *rc) {rchild=rc;};
    T &getData() {return data;};
    void setData(T &newData) {data=newData;};
};

template <class T>
class comp
{
  public:
    bool operator()(huffNode<T> *n1,huffNode<T> *n2)
    {
      if(n1->getWeight()>n2->getWeight()) return true;
      else return false;
    };
};

template <class T>
class huffTree
{
  private:
    huffNode<T> *root;
    huffNode<T> *DPointer;
    int TNum;
    int **encodeTable;

    void clear(huffNode<T> *rt)
    {
      if(rt->left()) clear(rt->left());
      if(rt->right()) clear(rt->right());
      delete rt;
     };

     void EncodePrint(int *tempCode,huffNode<T> *node)
     {
       int posi=0;
       if(node->left())
       {
         posi=0;
         while(tempCode[posi]!=-1) posi++;
         tempCode[posi]=0;
         if(node->left()->isLeaf())
         {
           int temp=0;
           cout<<node->left()->getData()<<": ";
           while(tempCode[temp]!=-1) cout<<tempCode[temp++];
           cout<<endl;
           tempCode[posi]=-1;
         }
         else
         {
           EncodePrint(tempCode,node->left());
           tempCode[posi]=-1;
         }
       }
       if(node->right())
       {
         posi=0;
         while(tempCode[posi]!=-1) posi++;
         tempCode[posi]=1;
         if(node->right()->isLeaf())
         {
           int temp=0;
           cout<<node->right()->getData()<<": ";
           while(tempCode[temp]!=-1) cout<<tempCode[temp++];
           cout<<endl;
           tempCode[posi]=-1;
         }
         else
         {
           EncodePrint(tempCode,node->right());
           tempCode[posi]=-1;
         }
       }
     };

     void Encode(int *tempCode,huffNode<T> *node)
     {
       int posi;
       if(node->left())
       {
         posi=0;
         while(tempCode[posi]!=-1) posi++;
         tempCode[posi]=0;
         if(node->left()->isLeaf())
         {
           T &tempData=node->left()->getData();
           int temp=0;
           while(tempCode[temp]!=-1) {encodeTable[(int)tempData][temp]=tempCode[temp];temp++;}
           encodeTable[(int)tempData][temp]=-1;
           tempCode[posi]=-1;
         }
         else
         {
           Encode(tempCode,node->left());
           tempCode[posi]=-1;
         }
       }
       if(node->right())
       {
         posi=0;
         while(tempCode[posi]!=-1) posi++;
         tempCode[posi]=1;
         if(node->right()->isLeaf())
         {
           T &tempData=node->right()->getData();
           int temp=0;
           while(tempCode[temp]!=-1) {encodeTable[(int)tempData][temp]=tempCode[temp];temp++;}
           encodeTable[(int)tempData][temp]=-1;
           tempCode[posi]=-1;
         }
         else
         {
           Encode(tempCode,node->right());
           tempCode[posi]=-1;
         }
       }
     };

      void PREOT(huffNode<T> *node,ofstream &fout)
      {
        int temp=node->getWeight();
        char tempC;
        fout.write((char*)&temp,sizeof(temp));
        if(node->isLeaf())
        {
          temp=-2;
          fout.write((char*)&temp,sizeof(temp));
          tempC=node->getData();
          fout.write((char*)&tempC,sizeof(tempC));
        }
        else
        {
          PREOT(node->left(),fout);
          PREOT(node->right(),fout);
          temp=-1;
          fout.write((char*)&temp,sizeof(temp));
        }
      };

      bool createTreeByfile(ifstream &fin,huffNode<T> *node)
      {
        int tempdata;
        fin.read((char*)&tempdata,sizeof(tempdata));
        while(true)
        {
          if(tempdata!=-1&&tempdata!=-2)
          {
            if(!node->left())
            {
              node->setLeft(new intlNode<char>);
              node->left()->setWeight(tempdata);
              if(createTreeByfile(fin,node->left()))
              {
                huffNode<char> *temp=node->left();
                node->setLeft(new leafNode<char>);
                node->left()->setWeight(temp->getWeight());
                node->left()->setData(temp->getData());
                delete temp;
              }
            }
            else
            {
              node->setRight(new intlNode<char>);
              node->right()->setWeight(tempdata);
              if(createTreeByfile(fin,node->right()))
              {
                huffNode<char> *temp=node->right();
                node->setRight(new leafNode<char>);
                node->right()->setWeight(temp->getWeight());
                node->right()->setData(temp->getData());
                delete temp;
              }
            }
          }
          else
          {
            if(tempdata==-2)
            {
              T newdata;
              fin.read((char*)&newdata,sizeof(newdata));
              node->setData(newdata);
              return true;
            }
            else return false;
          }
          fin.read((char*)&tempdata,sizeof(tempdata));
        }
      };


  public:
    huffTree(huffNode<T> **nodeArray,int leafNum)
    {
      myQueue<huffNode<T> *,comp<T> > nodeQueue;
      TNum=leafNum;
      encodeTable=new int *[256];
      for(int i=0;i<256;i++)
      {
        encodeTable[i]=new int [256];
      }
      for(int i=0;i<leafNum;i++)
      {
        nodeQueue.enqueue(nodeArray[i]);
      }
      while(nodeQueue.getSize()>1)
      {
        nodeQueue.enqueue(new intlNode<T>(nodeQueue.dequeue(),nodeQueue.dequeue()));
      }
      root=nodeQueue.dequeue();
      DPointer=root;
    };

    huffTree()
    {
      root=NULL;
      DPointer=NULL;
      TNum=0;
    };

    huffNode<T>* getRoot() {return root;};

    void outputCode()
    {
      cout<<"Code:"<<endl;
      int *tempCode=new int [TNum];
      for(int i=0;i<TNum;i++) tempCode[i]=-1;
      if(root->isLeaf()) cout<<'0'<<endl;
      else EncodePrint(tempCode,root);
      delete [] tempCode;
    };

    void outputTree(ofstream &fout)
    {
      PREOT(root,fout);
    };

    void createCodeTable()
    {
      int *tempCode=new int [TNum];
      for(int i=0;i<TNum;i++) tempCode[i]=-1;
      if(root->isLeaf())
      {
        T &tempIndex=root->getData();
        encodeTable[(int)tempIndex][0]=0;
        encodeTable[(int)tempIndex][1]=-1;
      }
      else Encode(tempCode,root);
      delete [] tempCode;
    };

    void inputTree(ifstream &fin)
    {
      int tempdata;
      fin.read((char*)&tempdata,sizeof(tempdata));
      root=new intlNode<char>;
      root->setWeight(tempdata);
      if(createTreeByfile(fin,root))
      {
        huffNode<char> *temp=root;
        root=new leafNode<char>;
        root->setWeight(temp->getWeight());
        root->setData(temp->getData());
        delete temp;
      }
    };

    int **getCodeTable()
    {
      return encodeTable;
    };

    void setDpointerRoot() {DPointer=root;};

    bool isDpointerLeaf() const {return DPointer->isLeaf();};

    void goLeft() {DPointer=DPointer->left();};

    void goRight() {DPointer=DPointer->right();};

    T &getDpointerData() {return DPointer->getData();};

    ~huffTree()
    {
      clear(root);
    };
};


#endif // HUFFMANNTREE_H_INCLUDED
