#ifndef _LINEAR_LIST_H_
#define _LINEAR_LIST_H_

#include <stdint.h>

// 元素类型请重载等于号
template<class T>
class ILinearList{
public:
    virtual void ListInsert(uint32_t index, const T& elem) = 0;
    virtual void ListDelete(uint32_t index, T& data) = 0;
    virtual int32_t LocateElem(const T& elem) const = 0;
    virtual T GetElem(uint32_t index) const = 0;
    virtual uint32_t Length() const = 0;
    virtual bool IsEmpty() const = 0;
    virtual void PrintList() const = 0;
    virtual void PushBack(const T& elem) = 0;
    virtual void PushFront(const T& elem) = 0;
    virtual void PopBack(T& elem) = 0;
    virtual void PopFront(T& elem) = 0;
};

#endif
