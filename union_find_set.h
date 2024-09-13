#ifndef _UNION_FIND_SET_
#define _UNION_FIND_SET_

#include <cstring>
#include <numeric>
#include <vector>
#include <iostream>

class Dsu{
private:
    std::vector<size_t> pa_;
    bool is_zip_;
public:
    explicit Dsu(size_t n, bool is_zip) : pa_(n), is_zip_(is_zip){
        iota(pa_.begin(), pa_.end(), 0);
    }

    
    size_t Find(size_t x){
        // 非路径压缩方式
        if(!is_zip_)
            return pa_[x] == x ? x:Find(pa_[x]);
        else // 路径压缩查询
            return pa_[x] == x ? x:pa_[x] = Find(pa_[x]);
    }

    // 将x链接到y，注意有方向性
    void Unite(size_t x, size_t y){
        pa_[Find(x)] = Find(y);
    }

    void Print(){
        for(int i=0; i<pa_.size(); i++){
            std::cout << i << ":" << pa_[i] << std::endl;
        }
    }
};

#endif
