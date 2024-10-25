#ifndef _HEAP_H_
#define _HEAP_H_

#include <utility>
#include <functional>
#include <vector>
#include <cstdint>

template<typename T, typename _Compare = std::less<T> >
class Heap{
private:
    std::vector<T> heap_;
    _Compare Compare = _Compare();
private:
    // 上浮操作
    void SiftUp(int64_t index){
        while(index > 0){
            int64_t parent = (index-1) / 2;
            if(Compare(heap_[parent], heap_[index])) break;
            std::swap(heap_[index], heap_[parent]);
            index = parent; 
        }
    }

    // 下沉操作
    void SiftDown(int64_t index){
        int64_t size = heap_.size();
        while(index < size){
            int64_t left_child = 2*index+1;
            int64_t right_child = 2*index+2;
            int64_t mark = index;

            if(left_child < size && Compare(heap_[left_child], heap_[mark]))
                mark = left_child;
            
            if(right_child < size && Compare(heap_[right_child], heap_[mark]))
                mark = right_child;
            
            if(mark == index) break;

            std::swap(heap_[index], heap_[mark]);
            index = mark;
        }
    }

public:
    Heap(){}
    
    void Insert(const T& value){
        heap_.emplace_back(value);
        SiftUp(heap_.size() - 1);
    }

    const T& Peek() const{
        if(heap_.empty()) throw std::runtime_error("Heap is empty.");
        return heap_[0];
    }

    T& Peek() {
        if(heap_.empty()) throw std::runtime_error("Heap is empty.");
        return heap_[0];
    }

    // 弹出堆顶元素
    void Pop(){
        if(heap_.empty()) throw std::runtime_error("Heap is empty.");
        heap_[0] = heap_.back();
        heap_.pop_back();
        if(!heap_.empty()) SiftDown(0);
    }

    bool Empty() const {
        return heap_.empty();
    }

    int64_t size() const{
        return heap_.size();
    }

};

#endif