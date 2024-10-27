// c++ 17
#ifndef _HASH_TABLE_H_
#define _HASH_TABLE_H_

#include <functional>
#include <vector>
#include <list>


template<typename Key, typename Value>
class HashTable{
private:
    std::vector<std::list<std::pair<Key, Value> > > buckets_;
    std::size_t size_ = 0;

    std::list<std::pair<Key, Value> >& GetBucket(const Key& key){
        std::size_t index = std::hash<Key>{}(key) % buckets_.size();
        return buckets_[index];
    }

    const std::list<std::pair<Key, Value> >& GetBucket(const Key& key) const {
        std::size_t index = std::hash<Key>{}(key) % buckets_.size();
        return buckets_[index];
    }

public:
    explicit HashTable(std::size_t bucket_cnt = 10) : buckets_(bucket_cnt) {}

    void Insert(const Key& key, const Value& value){
        auto& bucket = GetBucket(key);
        for(auto& [k, v] : bucket){
            if(k != key) continue;
            // 键已经存在则更新值
            v = value;
            return;
        }
        bucket.emplace_back(key, value);
        ++size_;
    }

    bool Find(const Key& key, Value& value) const {
        const auto& bucket = GetBucket(key);
        for (const auto& [k, v] : bucket){
            if(k != key) continue;
            value = v;
            return true;
        }
        return false;
    }

    bool Remove(const Key& key){
        auto& bucket = GetBucket(key);
        for(auto it = bucket.begin(); it!=bucket.end(); ++it){
            if(it->first!=key) continue;
            bucket.erase(it);
            --size_;
            return true;
        }
        return false;
    }

    std::size_t Size() const {
        return size_;
    }

    bool Empty() const{
        return size_ == 0;
    }
};

#endif