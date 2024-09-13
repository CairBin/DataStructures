#ifndef _STRING_ALGO_H_
#define _STRING_ALGO_H_

#include <string>
#include <stdint.h>
#include <vector>

using String = std::string;

// 对于string许多方法在标准库里有
// 此实现仅仅为了学习原理

bool Compare(const String& s1, const String& s2){
    if(s1.size() != s2.size())
        return false;

    for(uint32_t i = 0; i<s1.size(); i++)
        if(s1[i] != s2[i]) return false;

    return true;
}

String 
SubString(const String& s, uint32_t pos, uint32_t len){
    uint32_t l = s.size();
    if(pos >= l || pos+len > l) throw "out of range";

    String res = "";
    for(uint32_t i=0; i<len; i++){
        res += s[pos+i];
    }

    return res;
}

// 暴力匹配
int FindString(const String& src, const String& dest){
    uint32_t l1 = src.size();
    uint32_t l2 = dest.size();
    
    if(l1 < l2) return -1;

    for(uint32_t i=0; i<l1; i++){
        if(i+l2 > l1) return -1;
        
        bool flag = true;
        for(uint32_t j=0; j<l2; j++){
            if(src[i+j] != dest[j]){
                flag = false;
                break;
            }
        }

        if(flag) return i;
    }

    return -1;
}

int FindStringOptimizing(const String& src, const String& dest){
    uint32_t src_size = src.size();
    uint32_t dest_size = dest.size();

    if(src_size < dest_size) return -1;

    for(uint32_t i=0; i<src_size; i++){
        if(i+dest_size > src_size) return -1;
        uint32_t j = 0;
        
        bool flag = true;
        for(; j<dest_size; j++){
            if(src[i+j] != dest[j]){
                flag = false;
                break;
            }
        }

        if(flag) return i;
        else i=i+j;

    }
    
    return -1;
}


// 获取next数组
std::vector<int> PrefixFunction(const String& s){
    uint32_t n = (uint32_t)s.length();
    std::vector<int> pi(n);
    for(int i=1;i<n;i++){
        int j = pi[i-1];
        while(j>0 && s[i]!=s[j]) j=pi[j-1];
        if(s[i]==s[j]) ++j;
        pi[i] = j;
    }
    return pi;
}

int Kmp(const String& src, const String& desc){
    String cur = desc + '#' + src;
    int l1 = src.size();
    int l2 = desc.size();
    std::vector<int> next = PrefixFunction(cur);
    for(int i=l2+1; i<=l1+l2; i++){
        if(next[i] == l2) return i-2*l2;
    }

    return -1;
}


#endif 
