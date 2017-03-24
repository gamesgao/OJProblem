#ifndef MYLIST
#define MYLIST

template <class T>
class myList
{
  public:
    virtual void clear() = 0;
    virtual bool insert(const T&) = 0;
    virtual bool remove(T&) = 0;
    virtual void setStart() = 0;
    virtual void prev() = 0;
    virtual void next() = 0;
    virtual ~myList(){};
    // no-using function is deleted!
};
#endif // MYLIST
