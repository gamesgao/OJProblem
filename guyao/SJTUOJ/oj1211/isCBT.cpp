#include <iostream>

using namespace std;


class myNode
{
  private:
    myNode *lchild;
    myNode *rchild;

  public:
    myNode(myNode *newlchild,myNode *newrchild)
    {
      lchild=newlchild;
      rchild=newrchild;
    };

    myNode()
    {
      lchild=NULL;
      rchild=NULL;
    };

    void setleft(myNode *newlchild) {lchild=newlchild;};
    void setright(myNode *newrchild) {rchild=newrchild;};

    myNode *left() {return lchild;};
    myNode *right() {return rchild;};


};

class myQueue
{
  private:
    myNode* data[100001];
    int head;
    int rear;
    int maxSize;

  public:
    myQueue()
    {
      head=1;
      rear=0;
      maxSize=100000;
    };

    bool enqueue(myNode *newdata)
    {
      if((rear+2)%maxSize==head) return false;
      rear=(rear+1)%maxSize;
      data[rear]=newdata;
      return true;
    };

    myNode *dequeue()
    {
      if((rear+1)%maxSize==head) return NULL;
      myNode *temp=data[head];
      head=(head+1)%maxSize;
      return temp;
    };

    bool isEmpty() const
    {
      return (rear+1)%maxSize==head;
    };


};



class myTree
{
  private:
    myNode *root;
    void clear(myNode *rt)
    {
      if(rt->left()) clear(rt->left());
      if(rt->right()) clear(rt->right());
      delete rt;
    };

  public:
    myTree() {root=NULL;};
    myTree(myNode *newroot) {root=newroot;};

    bool levelOrderTraversal()
    {
      myQueue temp;
      myNode *tempnode;
      temp.enqueue(root);
      bool end=false;
      while(!temp.isEmpty())
      {
        tempnode=temp.dequeue();
        if(tempnode->left()&&!end) temp.enqueue(tempnode->left());
        else
        {
          if(end&&tempnode->left()) return false;
          else end=true;
        }
        if(tempnode->right()&&!end) temp.enqueue(tempnode->right());
        else
        {
          if(end&&tempnode->right()) return false;
          else end=true;
        }
      }
      return true;
    };

    ~myTree()
    {
      clear(root);
    };
};



















int main()
{
  int lc,rc;
  int nodeNum;
  cin>>nodeNum;
  myNode *templ;
  myNode *tempr;
  myNode **temp=new myNode *[nodeNum];
  int *judgeRoot=new int [nodeNum];
  for(int i=0;i<nodeNum;i++)
  {
    judgeRoot[i]=0;
  }
  for(int i=0;i<nodeNum;i++)
  {
    temp[i]=new myNode;
  }
  for(int i=0;i<nodeNum;i++)
  {
    cin>>lc>>rc;
    if(lc==0) templ=NULL;
    else {templ=temp[lc-1];judgeRoot[lc-1]++;}
    if(rc==0) tempr=NULL;
    else {tempr=temp[rc-1];judgeRoot[rc-1]++;}
    temp[i]->setleft(templ);
    temp[i]->setright(tempr);
  }
  int rootNum;
  for(int i=0;i<nodeNum;i++)
  {
    if(judgeRoot[i]==0) {rootNum=i;break;}
  }
  myTree datatree(temp[rootNum]);
  if(datatree.levelOrderTraversal()) cout<<'Y';
  else cout<<'N';
  delete [] judgeRoot;
  delete [] temp;




  return 0;

}
