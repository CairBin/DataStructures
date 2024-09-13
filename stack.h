#ifndef _STACK_H_
#define _STACK_H_

#include <cstring>
#include <stdint.h>
#include "linked_list.h"

template<class T>
class IStack{
public:
    virtual uint32_t Length() const = 0;
    virtual bool IsEmpty() const = 0;
    virtual void Push(const T& elem) = 0;
    virtual void Pop(T& elem) = 0;
    virtual T Top() const = 0;
};


template <class T>
class SqStack:public IStack<T>{
private:
    T* data_;
    uint32_t length_;
    uint32_t maxsize_;

public:
    SqStack(uint32_t maxsize){
        maxsize_ = maxsize;
        data_ = new T[maxsize];
        length_ = 0;
    }

    ~SqStack(){
        delete data_;
    }

    bool IsFull() const{
        return maxsize_ == length_;
    }

    bool IsEmpty() const{
        return 0 == length_;
    }

    void Push(const T& elem){
        if(length_+1>maxsize_)
            throw "stack overflow";

        data_[length_++] = elem;
    }

    void Pop(T& elem){
        if(length_-1<0)
            throw "stack underflow";
        elem = data_[--length_];
    }

    T Top() const{
        if(IsEmpty())
            throw "stack is empty";
        return data_[length_-1];
    }


    uint32_t Length() const{
        return length_;
    }

    void ExtendSize(uint32_t offset){
        if(offset <= 0)
            return;
        
        T* data = new T[maxsize_+offset];
        memcpy(data, data_, sizeof(data_));
        delete data_;
        data_ = data;

        maxsize_ += offset;
    }

    uint32_t GetMaxsize() const{
        return maxsize_;
    }
};

template<class T>
class LinkedStack:public IStack<T>{
private:
    LinkedList<T>* lst_;
public:
    LinkedStack(){
        lst_ = new LinkedList<T>();
    }
    ~LinkedStack(){
        delete lst_;
    }

    uint32_t Length() const{
        return lst_->Length();
    }

    bool IsEmpty() const{
        return 0 == Length();
    }

    void Push(const T& elem){
        lst_->PushFront(elem);
    }

    void Pop(T& elem){
        if(IsEmpty())
            throw "stack underflow";
        lst_->PopFront(elem);
    }

    T Top() const{
        if(IsEmpty())
            throw "stack is empty";
        return lst_->GetElem(0);
    }

};

#endif
