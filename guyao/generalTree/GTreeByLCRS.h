#ifndef GTREEBYLCRS_H_INCLUDED
#define GTREEBYLCRS_H_INCLUDED
#include <iostream>
#include <fstream>

using namespace std;

template <class T>
class myNode
{
  private:
    myNode<T> * lchild;
    myNode<T> *rsibling;
    T weight;
    int level;
  public:
    myNode()
    {
      lchild=rsibling=NULL;
    };

    void setLeft(myNode<T> *newLeft)
    {
      lchild=newLeft;
    };

    myNode<T> *left()
    {
      return lchild;
    };

    void setRight(myNode<T> *newRight)
    {
      rsibling=newRight;
    };
    myNode<T> *right()
    {
      return rsibling;
    };

    void setWeight(T &newWeight)
    {
      weight=newWeight;
    };

    T &getWeight()
    {
      return weight;
    };

    void setLevel(int newlevel) {level=newlevel;};

    int getLevel() {return level;};

};

class myTree
{
  private:
    myNode<char> *root;
    int maxLevel;
    void clear(myNode<char> *rt)
    {
      if(rt->left()) clear(rt->left());
      if(rt->right()) clear(rt->right());
      delete rt;
    };

    void PREOT(myNode<char> *node)
    {
      cout<<node->getWeight();
      for(int i=node->getLevel();i<=maxLevel;i++) cout<<'-';
      cout<<endl;
      for(myNode<char> *temp=node->left();temp!=NULL;temp=temp->right()) PREOT(temp);
    };

    void levelPlusOne(myNode<char> *node)
    {
      node->setLevel(node->getLevel()+1);
      for(myNode<char> *temp=node->left();temp!=NULL;temp=temp->right()) levelPlusOne(temp);
    };

    void createTree(ifstream &fin,myNode<char> *node,int nowlevel,int &maxlevel)
    {
      char tempdata;
      if(nowlevel>maxlevel) maxlevel=nowlevel;
      tempdata=fin.get();
      while(true)
      {
        if(tempdata!=')')
        {
          if(!node->left())
          {
            node->setLeft(new myNode<char>);
            node->left()->setWeight(tempdata);
            node->left()->setLevel(nowlevel);
            createTree(fin,node->left(),nowlevel+1,maxlevel);
          }
          else
          {
            myNode<char> *temp=node->left();
            while(temp->right()) temp=temp->right();
            temp->setRight(new myNode<char>);
            temp->right()->setWeight(tempdata);
            temp->right()->setLevel(nowlevel);
            createTree(fin,temp->right(),nowlevel+1,maxlevel);
          }
        }
        else
        {
          return;
        }
        tempdata=fin.get();
      }

    };


  public:
    myTree()
    {
      root=NULL;
      maxLevel=0;
    };
    myTree(const char *fileAddr)
    {
      ifstream fin(fileAddr);
      char tempdata;
      int nowlevel=0;
      root=new myNode<char>;
      tempdata=fin.get();
      root->setWeight(tempdata);
      root->setLevel(0);
      int maxl=0;
      createTree(fin,root,nowlevel+1,maxl);
      maxLevel=maxl;
      fin.close();
    };

    void preOrderTraversal()
    {
      PREOT(root);
    };

    void UNION(myTree &other)
    {
      if(root->left())
      {
        myNode<char> *temp=root->left();
        while(temp->right()) temp=temp->right();
        temp->setRight(other.root);
        maxLevel=(maxLevel>other.maxLevel+1)?maxLevel:other.maxLevel+1;
        levelPlusOne(other.root);
      }
      else
      {
        root->setLeft(other.root);
        maxLevel=(maxLevel>other.maxLevel+1)?maxLevel:other.maxLevel+1;
      }
      other.root=NULL;
    };

    ~myTree()
    {
      if(root) clear(root);
    };

    void print() {preOrderTraversal();};
};




#endif // GTREEBYLCRS_H_INCLUDED
