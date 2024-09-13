#ifndef _QUEUE_H_
#define _QUEUE_H_

#include "linked_list.h"
#include "sq_list.h"
#include <cstring>

template<class T>
class IQueue{
public:
    virtual uint32_t Length() const = 0;
    virtual void Push(const T& elem) =0;
    virtual T Top() const = 0;
    virtual void Pop(T& elem) = 0;
    virtual bool IsEmpty() const = 0;
};

template<class T>
class SqQueue : public IQueue<T>{
private:
    SqList<T>* container_;
    uint32_t maxsize_;
public:
    SqQueue(uint32_t maxsize){
        container_ = new SqList<T>(maxsize);
        maxsize_ = maxsize;
    }
    ~SqQueue(){
        delete container_;
    }

    void Push(const T& elem){
        container_->PushBack(elem);
    }

    T Top() const{
        return container_->GetElem(container_->Length()-1);
    }

    uint32_t Length() const{
        return container_ -> Length();
    }

    void Pop(T& elem){
        container_->PopFront(elem);
    }

    uint32_t GetMaxsize() const{
        return maxsize_;
    }

    void ExtendSize(uint32_t offset){
        if(offset <= 0)
            return;
        container_->ExtendSize(offset);
        maxsize_ += offset;
    }

    bool IsEmpty() const{
        return container_->IsEmpty();
    }
};

template<class T>
class LinkedQueue:IQueue<T>{
private:
    typedef struct LNode{
        T data_;
        LNode* next_;
    }LNode;

private:
    LNode* head_;
    uint32_t length_;
    LNode* back_;
public:
    LinkedQueue(){
        head_ = new LNode();
        head_->next_ = nullptr;
        length_ = 0;
        back_ = head_;
    }

    ~LinkedQueue(){
        while(head_){
            LNode* t = head_;
            head_ = head_->next_;
            delete t;
        }
    }

    uint32_t Length() const{
        return length_;
    }

    bool IsEmpty() const{
        return 0 == length_;
    }

    void Push(const T& elem){
        LNode* n = new LNode;
        n->data_ = elem;
        n->next_ = nullptr;
        
        back_->next_ = n;
        back_ = n;
        ++length_;
    }

    void Pop(T& elem){
        if(IsEmpty())
            throw "queue underflow";

        LNode* del_n = head_->next_;
        if(back_ == del_n)
            back_ = head_;

        head_->next_ = del_n->next_;
        elem = del_n->data_;
        delete del_n;
        
        --length_;
    }

    T Top() const{
        if(IsEmpty())
            throw "queue is empty";

        return head_->next_->data_;
    }

};

template <class T>
class CircularQueue : public IQueue<T>{
private:
    T* data_;
    uint32_t front_;
    uint32_t rear_;
    uint32_t maxsize_;
    uint32_t length_;
public:
    CircularQueue(uint32_t maxsize){
        maxsize_ = maxsize+1;
        data_ = new T[maxsize+1];
        rear_ = 0;
        front_ = 0;
        length_ = 0;
    }

    ~CircularQueue(){
        delete data_;
    }

    bool IsEmpty() const{
        return front_ == rear_;
    }

    bool IsFull() const {
        return (rear_+1)%maxsize_ == front_;
    }

    void Push(const T& elem){
        if(IsFull())
            throw "queue overflow";

        data_[rear_] = elem;
        rear_ = (rear_+1)%maxsize_;

        ++length_;
    }

    void Pop(T& elem){
        if(IsEmpty())
            throw "queue underflow";
        elem = data_[front_];
        front_ = (front_+1) % maxsize_;

        --length_;
    }

    uint32_t GetMaxsize() const{
        return maxsize_-1;
    }


    T Top()const{
        if(IsEmpty())
            throw "queue is empty";
        return data_[front_];
    }

    void ExtendSize(uint32_t offset){
        if(offset <= 0)
            return;
        //std::cout << front_ << "-----" << std::endl;
        //std::cout << rear_ << "-------" << std::endl;
        T* data = new T[maxsize_+offset];
        memcpy(data, data_, sizeof(data_));
        delete data_;
        data_ = data;
        maxsize_ += offset;
    }
    
    uint32_t Length()const{
        return length_;
    }
};

#endif
