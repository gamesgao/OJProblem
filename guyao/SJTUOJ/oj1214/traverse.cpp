#include<iostream>

using namespace std;

class myNode
{
  private:
    myNode * lchild;
    myNode *rsibling;
    int weight;
  public:
    myNode()
    {
      lchild=rsibling=NULL;
    };

    void setLeft(myNode *newLeft)
    {
      lchild=newLeft;
    };

    myNode *left()
    {
      return lchild;
    };

    void setRight(myNode *newRight)
    {
      rsibling=newRight;
    };
    myNode *right()
    {
      return rsibling;
    };

    void setWeight(int newWeight)
    {
      weight=newWeight;
    };

    int getWeight()
    {
      return weight;
    };

};

class myQueue
{
  private:
    myNode *data[100001];
    int rear;
    int head;
    int maxSize;
  public:
    myQueue()
    {
      rear=0;
      head=1;
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

    void PREOT(myNode *node)
    {
      cout<<node->getWeight()<<' ';
      for(myNode *temp=node->left();temp!=NULL;temp=temp->right()) PREOT(temp);
    };

    void POSTOT(myNode *node)
    {
      for(myNode *temp=node->left();temp!=NULL;temp=temp->right()) POSTOT(temp);
      cout<<node->getWeight()<<' ';
    };

  public:
    myTree()
    {
      root=NULL;
    };

    void preOrderTraversal()
    {
      PREOT(root);
    };

    void postOrderTraversal()
    {
      POSTOT(root);
    };

    void levelOrderTraversal()
    {
      myQueue saveNode;
      cout<<root->getWeight()<<' ';
      saveNode.enqueue(root);
      myNode *node;
      while(!saveNode.isEmpty())
      {
        node=saveNode.dequeue();
        for(myNode *temp=node->left();temp!=NULL;temp=temp->right())
        {
          cout<<temp->getWeight()<<' ';
          saveNode.enqueue(temp);
        }
      }
    };




    myTree(myNode *newRoot)
    {
      root=newRoot;
    };

    ~myTree()
    {
      clear(root);
    };
};

int main()
{
  int nodeNum;
  int lc,rs;
  int weight;
  cin>>nodeNum;
  myNode *lcNode;
  myNode *rsNode;
  myNode **tempNodeList=new myNode *[nodeNum];
  int *findRoot=new int [nodeNum];
  for(int i=0;i<nodeNum;i++) {tempNodeList[i]=new myNode;findRoot[i]=0;}
  for(int i=0;i<nodeNum;i++)
  {
    cin>>lc>>rs>>weight;
    if(lc==0) lcNode=NULL;
    else {lcNode=tempNodeList[lc-1];findRoot[lc-1]++;}
    if(rs==0) rsNode=NULL;
    else {rsNode=tempNodeList[rs-1];findRoot[rs-1]++;}
    tempNodeList[i]->setLeft(lcNode);
    tempNodeList[i]->setRight(rsNode);
    tempNodeList[i]->setWeight(weight);
  }
  int rootNum=0;
  for(int i=0;i<nodeNum;i++)
  {
    if(findRoot[i]==0) {rootNum=i;break;}
  }
  myTree tree(tempNodeList[rootNum]);
  tree.preOrderTraversal();
  cout<<endl;
  tree.postOrderTraversal();
  cout<<endl;
  tree.levelOrderTraversal();
  cout<<endl;

  delete [] tempNodeList;
  delete [] findRoot;
  return 0;
}
