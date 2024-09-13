#ifndef _LINKED_LIST_H_
#define _LINKED_LIST_H_

#include "linear_list.h"
#include <iostream>

template<class T>
class SingleLinkedList : public ILinearList<T>{
private:
    typedef struct LNode{
        T data_;
        LNode* next_;
    }LNode;

private:
    LNode* head_;   // 头节点不存放元素
    uint32_t length_;

public:
    SingleLinkedList(){
        head_ = new LNode;
        length_ = 0;
        head_->next_ = nullptr;
    }
    
    ~SingleLinkedList(){
        while(head_){
            LNode* temp = head_;
            head_ = head_->next_;
            delete temp;
        }
    }

    void ListInsert(uint32_t index, const T& elem){
        if(index <0 || index>length_)
            throw "out of range";
    
        LNode* t = head_;
        for(uint32_t i=0; i<index; i++)
            t = t->next_;

        LNode* n = new LNode;
        n->data_ = elem;
        n->next_ = t->next_;

        t->next_ = n;
        ++length_;
    }

    void ListDelete(uint32_t index, T& elem){
        if(index<0 || index>= length_)
            throw "out of range";

        LNode* t = head_;
        for(uint32_t i=0; i<index; i++)
            t = t->next_;

        LNode* del_n = t->next_;
        t->next_ = t->next_->next_;
        delete del_n;
        --length_;
    }

    bool IsEmpty() const{
        return 0 == length_;
    }

    uint32_t Length() const{
        return length_;
    }

    void PrintList() const{
        LNode* t = head_->next_;
        while(t){
            std::cout << t->data_ << " ";    
            t = t->next_;
        }
        std::cout << std::endl;
    }
    
    void PushBack(const T& elem){
        LNode* t = head_;
        while(t->next_)
            t = t->next_;

        LNode* n = new LNode;
        n->data_ = elem;
        n->next_ = nullptr;

        t->next_ = n;
        ++length_;
    }

    void PushFront(const T& elem){
        LNode* n = new LNode;
        n->data_ = elem;
        n->next_ = head_->next_;

        head_->next_ = n;
        ++length_;
    }

    void PopBack(T& elem){
        if(length_-1 < 0)
            throw "out of range";

        LNode* t = head_;
        while(t->next_->next_){
            t = t->next_;
        }
        
        elem = t->next_->data_;
        delete t->next_;
        t->next_ = nullptr;
        --length_;
    }

    void PopFront(T& elem){
        if(length_-1 < 0)
            throw "out of range";

        elem = head_->next_->data_;
        LNode* t = head_->next_;
        head_->next_ = head_->next_->next_;
        delete t;

        --length_;
    }

    T GetElem(uint32_t index) const{
        if(index<0 || index>= length_)
            throw "out of range";

        LNode* t = head_;
        for(uint32_t i=0;i<index;i++)
            t = t->next_;

        return t->data_;
    }

    int LocateElem(const T& elem) const{
        LNode* t = head_->next_;
        uint32_t i = 0;
        while(t){
            if(t->data_ == elem){
                return i;
            }
            ++i;
            t = t->next_;
        }

        return -1;
    }


};

template<class T>
class LinkedList : public ILinearList<T>{
private:
    typedef struct LNode{
        T data_;
        struct LNode* prev_;
        struct LNode* next_;
    }LNode;

private:
    LNode* head_;
    uint32_t length_;

public:
    LinkedList(){
        head_ = new LNode;
        head_->next_ = nullptr;
        head_->prev_ = nullptr;
        length_ = 0;
    }
    ~LinkedList(){
        while(head_){
            LNode* temp = head_;
            head_ = head_->next_;
            delete temp;
        }
    }
    void ListInsert(uint32_t index, const T& elem){
        if(index<0 || index>length_)
            throw "out of range";
            
        LNode* temp = head_;
        for(uint32_t i=0; i<index; i++){
            temp = temp->next_;
        }

        LNode* n = new LNode;
        n->data_ = elem;
        n->next_ = temp->next_;
        n->prev_ = temp;
        
        if(temp->next_)
            temp->next_->prev_ = n;
        temp->next_ = n;
        

        ++length_;
    }

    void ListDelete(uint32_t index, T& elem){
        if(index<0 || index>=length_)
            throw "out of range";

        LNode* t = head_;
        for(uint32_t i=0; i<index; i++){
            t = t->next_;    
        }

        LNode* n = new LNode;
        elem = t->next_->data_;
        
        LNode* del_n = t->next_;
        if(del_n->next_)
            del_n->next_->prev_ = t;
        
        t->next_ = del_n->next_;
        delete del_n;
        
        --length_;
    }

    bool IsEmpty() const{
        return 0 == length_;
    }

    uint32_t Length() const{
        return length_;
    }

    void PrintList() const{
        LNode* t = head_->next_;
        while(t){
            std::cout << t->data_ << " ";
            t = t->next_;
        }
        std::cout << std::endl;
    }

    int LocateElem(const T& elem) const{
        LNode* t = head_->next_;
        int i = 0;
        while(t){
            if(t->data_ == elem)
                return i;
            ++i;
            t = t->next_;
        }

        return -1;
    }

    T GetElem(uint32_t index) const {
        if(index<0 || index>=length_)
            throw "out of range";
        
        LNode* t = head_;
        for(uint32_t i=0; i<index; i++)
            t = t->next_;
        
        return t->next_->data_;
    }

    void PushBack(const T& elem){
        LNode* t = head_;
        while(t->next_)
            t = t->next_;

        LNode* n = new LNode;
        n->data_ = elem;
        n->prev_ = t;
        n->next_ = nullptr;

        t->next_ = n;
        ++length_;
    }

    void PushFront(const T& elem){

        LNode* n = new LNode;
        n->next_ = head_->next_;
        n->prev_ = head_;
        n->data_ = elem;

        if(head_->next_)
            head_->next_->prev_ = n;
        head_->next_ = n;

        ++length_;
    }

    void PopBack(T& elem){
        if(length_-1 < 0)
            throw "out of range";
        LNode* t = head_;
        while(t->next_)
            t = t->next_;

        elem = t->data_;
        t = t->prev_;
    
        delete t->next_;
        t->next_ = nullptr;
        
        --length_;
    }

    void PopFront(T& elem){
        if(length_-1 < 0)
            throw "out of range";

        LNode* del_n = head_->next_;
        elem = del_n->data_;
        if(del_n->next_)
            del_n->next_->prev_ = head_;
        head_->next_ = del_n->next_;

        delete del_n;
        --length_;
    }
};


#endif

