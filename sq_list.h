#ifndef _SQ_LIST_H_
#define _SQ_LIST_H_

#include "linear_list.h"
#include <memory.h>
#include <iostream>

template <class T>
class SqList : public ILinearList<T>{
private:
    T* data_;
    uint32_t maxsize_;
    uint32_t length_;
public:
    SqList(uint32_t maxsize){
        data_ = new T[maxsize];
        memset(data_,0,sizeof(data_));
        length_ = 0;
        maxsize_ = maxsize;
    }

    ~SqList(){
        delete data_;
    }

    void ExtendSize(uint32_t offset){
        if(offset <= 0)
            return;

        T* data = new T[maxsize_+offset];
        memset(data, 0, sizeof(0));
        for(int i=0; i<maxsize_; i++){
            data[i] = data_[i];
        }

        delete data_;
        data_ = data;
        maxsize_ = maxsize_ + offset;

    }

    void ListInsert(uint32_t index, const T& elem){
        if(index < 0 || index>maxsize_ || index > length_ || length_+1 > maxsize_)
            throw "out of range";
        
        for(uint32_t i=length_; i>=index+1; i--){
            data_[i+1] = data_[i];
        }
        
        data_[index] = elem;
        ++length_;
    }

    void ListDelete(uint32_t index, T& elem){
        if(index<0 || index>maxsize_ || length_-1 < 0)
            throw "out of range";

        for(uint32_t i=index+1; i<length_; i++){
            data_[i-1] = data_[i];
        }
        --length_;
    }

    bool IsEmpty() const{
        return length_ == 0;
    }

    int LocateElem(const T& elem) const{
        for(uint32_t i=0; i<length_; i++){
            if(elem == data_[i])
                return i;
        }

        return -1;
    }

    void PrintList() const{
        for(uint32_t i=0; i<length_; i++){
            std::cout << data_[i] << " ";    
        }
        std::cout << std::endl;
    }

    T GetElem(uint32_t index) const{
        if(index <0 || index>=length_)
            throw "out of range";
        return data_[index];
    }

    uint32_t Length() const{
        return length_;
    }

    void PushBack(const T& elem){
        if(length_+1 > maxsize_)
            throw "out of range";

        data_[length_++] = elem;
    }

    void PushFront(const T& elem){
        if(length_+1 > maxsize_)
            throw "out of range";
        for(uint32_t i=length_ ; i>=1; i--)
            data_[i+1] = data_[i];
        
        data_[0] = elem;
        ++length_;
    }

    void PopBack(T& elem){
        if(length_-1 <0)
            throw "out of range";

        elem = data_[length_--];
    }

    void PopFront(T& elem){
        if(length_-1<0)
            throw "out of range";
        for(uint32_t i=1; i<length_; i++){
            data_[i-1] = data_[i];
        }

        --length_;
    }
};

#endif

