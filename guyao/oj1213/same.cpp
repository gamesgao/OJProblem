#include<iostream>

using namespace std;

class myNode
{
  private:
    myNode *lchild;
    myNode *rchild;
    int data;

  public:
    myNode(){lchild=NULL;rchild=NULL;};

    void setLeft(myNode *newLeft) {lchild=newLeft;};
    void setRight(myNode *newRight) {rchild=newRight;};
    void setData(int newData) {data=newData;};

    myNode *left() {return lchild;};
    myNode *right() {return rchild;};
    int getData() {return data;};
};

template<class T>
class myQueue
{
  private:
    T data[100001];
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

    bool enQueue(T newData)
    {
      if((rear+2)%maxSize==head) return false;
      rear=(rear+1)%maxSize;
      data[rear]=newData;
      return true;
    };

    T deQueue()
    {
      if((rear+1)%maxSize==head) return NULL;  //may not be right
      T &temp=data[head];
      head=(head+1)%maxSize;
      return temp;
    };

    bool isEmpty() const {return (rear+1)%maxSize==head;};

};

template<class T>
class myStack
{
  private:
    T data[100000];
    int top;
    int maxSize;

  public:
    myStack()
    {
      top=-1;
      maxSize=100000;
    };

    bool push(T newData)
    {
      if(top==100000) return false;
      top++;
      data[top]=newData;
    };

    T pop()
    {
      if(top==-1) return NULL;
      T &temp=data[top];
      top--;
      return temp;
    };

    bool isEmpty() const {return top==-1;};
};

class myTree
{
  private:
    myNode *root;
    void clear(myNode *root)
    {
      if(root->left()) clear(root->left());
      if(root->right()) clear(root->right());
      delete root;
    };

  public:
    myTree() {root=NULL;};
    myTree(myNode *newRoot) {root=newRoot;};

    bool isSame(myTree &other)
    {
      myQueue<myNode *> TDTQ1;
      myQueue<myNode *> TDTQ2;
      TDTQ1.enQueue(root);
      TDTQ2.enQueue(other.root);
      myNode *temp1;
      myNode *temp2;
      while(!TDTQ1.isEmpty()&&!TDTQ2.isEmpty())
      {
        temp1=TDTQ1.deQueue();
        temp2=TDTQ2.deQueue();
        if(temp1->left()&&temp2->left())
        {
          TDTQ1.enQueue(temp1->left());
          TDTQ2.enQueue(temp2->left());
        }
        else
        {
          if(temp1->left()||temp2->left()) return false;
        }
        if(temp1->right()&&temp2->right())
        {
          TDTQ1.enQueue(temp1->right());
          TDTQ2.enQueue(temp2->right());
        }
        else
        {
          if(temp1->right()||temp2->right()) return false;
        }
        if(temp1->getData()!=temp2->getData()) return false;

      }
      if(!TDTQ1.isEmpty()||!TDTQ2.isEmpty()) return false;
      return true;

    };





    ~myTree() {clear(root);};
};




int main()
{
  int nodeNum1,nodeNum2;
  cin>>nodeNum1;
  myNode **tempdata=new myNode *[nodeNum1];
  int *findRoot=new int [nodeNum1];
  for(int i=0;i<nodeNum1;i++) findRoot[i]=0;
  for(int i=0;i<nodeNum1;i++)
  {
    tempdata[i]=new myNode;
  }
  int lNum=0,rNum=0;
  int weight=0;
  myNode *lc=NULL,*rc=NULL;
  for(int i=0;i<nodeNum1;i++)
  {
    cin>>lNum>>rNum>>weight;
    if(lNum==0) lc=NULL;
    else {lc=tempdata[lNum-1];findRoot[lNum-1]++;}
    if(rNum==0) rc=NULL;
    else {rc=tempdata[rNum-1];findRoot[rNum-1]++;}
    tempdata[i]->setLeft(lc);
    tempdata[i]->setRight(rc);
    tempdata[i]->setData(weight);
  }
  int tempRoot=0;
  for(int i=0;i<nodeNum1;i++)
  {
    if(findRoot[i]==0) tempRoot=i;
  }
  myTree tree1(tempdata[tempRoot]);



  cin>>nodeNum2;
  if(nodeNum1!=nodeNum2) {cout<<'N';return 0;}


  //myNode **tempdata=new myNode *[nodeNum1];
  //int *findRoot=new int [nodeNum1];
  for(int i=0;i<nodeNum2;i++) findRoot[i]=0;
  for(int i=0;i<nodeNum2;i++)
  {
    tempdata[i]=new myNode;
  }
  lNum=0;
  rNum=0;
  weight=0;
  lc=NULL;
  rc=NULL;
  for(int i=0;i<nodeNum2;i++)
  {
    cin>>lNum>>rNum>>weight;
    if(lNum==0) lc=NULL;
    else {lc=tempdata[lNum-1];findRoot[lNum-1]++;}
    if(rNum==0) rc=NULL;
    else {rc=tempdata[rNum-1];findRoot[rNum-1]++;}
    tempdata[i]->setLeft(lc);
    tempdata[i]->setRight(rc);
    tempdata[i]->setData(weight);
  }
  tempRoot=0;
  for(int i=0;i<nodeNum2;i++)
  {
    if(findRoot[i]==0) tempRoot=i;
  }
  myTree tree2(tempdata[tempRoot]);


  if(tree1.isSame(tree2)) cout<<'Y'<<endl;
  else cout<<'N'<<endl;


  return 0;
}
