//
//  main.cpp
//  singleLinkList
//
//  Created by Mingke Wang on 2018/9/30.
//  Copyright © 2018年 Mingke Wang. All rights reserved.
//
#include <iostream>
#include <list>
using namespace std;
template <class elemType>
class sLinkList:public list<elemType>
{
    
    template <class T> friend sLinkList<T> operator+(const sLinkList<T> &a, const sLinkList<T> &b); //把a和b相连成为c
    
private:
    struct node
    {
        elemType data;
        node *next;
        
        node(const elemType &x, node *n=NULL)
        {
            data=x;next=n;;
        }
        node():next(NULL){}
        ~node(){};
    };
    
    node *head; //头指针
    int currentLength;  //表长
    
    node *move(int i) const;//返回第i个节点的地址
    
public:
    sLinkList<elemType>& operator=(const sLinkList<elemType> &obj);
    sLinkList();
    sLinkList(sLinkList<elemType>& obj);
    ~sLinkList()
    {
        clear();
        delete head;
    }
    
    void clear();
    int length() const {return currentLength;}
    void insert(int i, const elemType &x);
    void remove(int i);
    int search(const elemType &x) const;
    elemType visit(int i) const;
    void traverse() const;
    void erase(int x, int y);
    void reverse();
};

template <class elemType>
sLinkList<elemType>& sLinkList<elemType>::operator=(const sLinkList<elemType> &obj)
{
    if (this==&obj) return *this;   //防止自己复制自己
    this->clear();
    for (int i=0; i<obj.currentLength; ++i)
    {
        this->insert(i, obj.visit(i));
    }
    return *this;
}

template <class T>
sLinkList<T> operator+(const sLinkList<T> &a, const sLinkList<T> &b)
{
    sLinkList<T> c;
    for (int i=0; i<a.currentLength; ++i)
        c.insert(i, a.visit(i));
    for (int i=0; i<b.currentLength; ++i)
        c.insert(i + a.currentLength, b.visit(i));
    return c;
}

template <class elemType>
sLinkList<elemType>::sLinkList(sLinkList<elemType> &obj)
{
    head = new node;
    currentLength = 0;
    for (int i=0; i<obj.currentLength; ++i)
    {
        insert(i, obj.visit(i));
    }
}


//单链表私有函数move的实现
template <class elemType>
typename sLinkList<elemType>::node *sLinkList<elemType>::move(int i) const
{
    node *p = head;
    while (i-->=0) p = p->next;
    return p;
}

//单链表的构造函数
template <class elemType>
sLinkList<elemType>::sLinkList()
{
    head = new node;
    currentLength = 0;
}


//单链表类清空函数的实现
template <class elemType>
void sLinkList<elemType>::clear()
{
    node *p = head->next, *q;
    head->next=NULL;
    while (p!=NULL)
    {
        q = p->next;
        delete p;
        p = q;
    }
    currentLength = 0;
}

//节点插入与删除函数的实现
template <class elemType>
void sLinkList<elemType>::insert(int i, const elemType &x)  //首地址不存放data，所以后面的输出是从第二位开始输出
{
    node *pos;
    pos = move(i-1);
    pos->next = new node(x, pos->next);
    ++currentLength;
}

template <class elemType>
void sLinkList<elemType>::remove(int i)
{
    node *pos, *delp;
    
    pos = move(i-1);
    delp = pos->next;
    pos->next = delp->next;
    delete delp;
    --currentLength;
}

//单链表中search， visit和traverse的实现
template <class elemType>
int sLinkList<elemType>::search(const elemType &x) const
{
    node *p = head->next;
    int i = 0;
    
    while (p!=NULL && p->data != x)
    {
        p = p->next;
        ++i;
    }
    if (p==NULL)    return -1;  //不存在该元素
    else return i;
}

template <class elemType>
elemType sLinkList<elemType>::visit(int i) const
{
    return move(i)->data;
}

template <class elemType>
void sLinkList<elemType>::traverse() const
{
    node *p = head->next;
    cout<<endl;
    while (p != NULL)
    {
        cout<<p->data<<"  ";
        p = p->next;
    }
    cout<<endl;
}

template <class elemType>
void sLinkList<elemType>::erase(int x, int y)
{
    node *p=head->next;
    int i=0;
    while (p!=NULL)
    {
        if (p->data>=x && p->data<=y)
            remove(i);
        else i++;
        p = p->next;
    }
}
template <class elemType>
void sLinkList<elemType>::reverse()
{
    elemType *storage = new elemType[currentLength];
    for (int i=0 ; i<currentLength; ++i)
    {
        storage[i] = visit(i);
    }
    for (int i=0; i<currentLength; ++i)
    {
        move(i)->data = storage[currentLength-i-1];
    }
    delete[] storage;
}

int main() {
    std::cout << "Hello, World!" << std::endl;
    sLinkList<int> list;
    for (int i=0; i<10; ++i)
        list.insert(i, i+1);
    list.traverse();
    list.erase(2, 5);
    list.traverse();
    list.reverse();
    list.traverse();
    sLinkList<int> b(list);
    b.traverse();
    b= list + list;
    b.traverse();
    return 0;
}
