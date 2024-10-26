#ifndef _B_TREE_H_
#define _B_TREE_H_

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdint>

template<typename T>
class BTree{
private:
    typedef struct Node{
        bool is_leaf_;
        std::vector<T> keys_;
        std::vector<Node*> children_;

        Node(bool is_leaf) : is_leaf_(is_leaf) {}
    }Node;
private:
    std::size_t order_;
    std::size_t size_;
    Node* root_;

public:
    BTree(std::size_t order) 
        : order_(order), root_(nullptr), size_(0) {}


private:
    void SplitChild(Node* parent, std::size_t index, Node* child){
        std::size_t mid_index = order_ / 2;
        Node* new_node = new Node(child->is_leaf_);

        new_node->keys_.assign(
            child->keys_.begin() + mid_index + 1,
            child->keys_.end()
        );
        if(!child->is_leaf_)
            new_node->children_.assign(
                child->children_.begin() + mid_index + 1,
                child->children_.end()
            );
        T mid_key = child->keys_[mid_index];
        child->keys_.resize(mid_index);
        child->children_.resize(mid_index + 1);

        parent->children_.insert(
            parent->children_.begin() + index + 1,
            new_node
        );
        parent->keys_.insert(
            parent->keys_.begin() + index,
            mid_key
        );
    }

    // 插入到非满节点
    void InsertNonFull(Node* node, const T& key){
        std::size_t i = node->keys_.size() - 1;
        if(node->is_leaf_){
            // 插入到末尾
            node->keys_.push_back(key);
            while(i >= 0 && key < node->keys_[i]){
                node->keys_[i+1] = node->keys_[i];
                --i;
            }
            node->keys_[i+1] = key;
            ++size_;
            return;
        }

        while(i >= 0 && key < node->keys_[i]) i--;
        i++;
        if(node->children_[i]->keys_.size() == order_ - 1){
            SplitChild(node, i, node->children_[i]);
            if(key > node->keys_[i]) ++i;
        }
        InsertNonFull(node->children_[i], key);
    }

    bool FindKey(const Node* node, const T& key) const{
        std::size_t i = 0;
        while(i < node->keys_.size() && key > node->keys_[i]) i++;
        if(i < node->keys_.size() && node->keys_[i] == key) return true;
        if(node->is_leaf_) return false;

        return FindKey(node->children_[i], key);
    }

    T GetPredecessor(Node* node){
        while(!node->is_leaf_) node = node->children_.back();
        return node->keys_.back();
    }

    T GetSuccessor(Node* node){
        while(!node->is_leaf_) node = node->children_.front();
        return node->keys_.front();
    }

    // 向兄弟借一个键
    void BorrowFromPrev(Node* node, std::size_t idx){
        Node* child = node->children_[idx];
        Node* sibling = node->children_[idx - 1];
        child->keys_.insert(child->keys_.begin(), node->keys_[idx - 1]);

        if(!child->is_leaf_){
            child->children_.insert(
                child->children_.begin(),
                sibling->children_.back()
            );
        }
        node->keys_[idx - 1] = sibling->keys_.back();
        sibling->keys_.pop_back();
    }

    // 从下一个兄弟借点借
    void BorrowFromNext(Node* node, std::size_t idx){
        Node* child = node->children_[idx];
        Node* sibling = node->children_[idx + 1];
        if(!child->is_leaf_){
            child->children_.push_back(sibling->children_.front());
            sibling->children_.erase(sibling->children_.begin());
        }

        node->keys_[idx] = sibling->keys_.front();
        sibling->keys_.erase(sibling->keys_.begin());
    }

    // 合并子节点
    void MergeChildren(Node* node, std::size_t idx){
        Node* left = node->children_[idx];
        Node* right = node->children_[idx + 1];

        left->keys_.push_back(node->keys_[idx]);
        left->keys_.insert(
            left->keys_.end(),
            right->keys_.begin(),
            right->keys_.end()
        );

        node->keys_.erase(node->keys_.begin() + idx);
        node->children_.erase(node->children_.begin() + idx + 1);
        delete right;
    }

    void RemoveKey(Node* node, const T& key){
        std::size_t idx = std::lower_bound(node->keys_.begin(), node->keys_.end(), key)
            - node->keys_.begin();
        if(idx < node->keys_.size() && node->keys_[idx] == key){
            if(node->is_leaf_){
                node->keys_.erase(node->keys_.begin() + idx);
                --size_;
                return;
            }
            Node* left = node->children_[idx];
            if(left->keys_.size() >= order_ / 2){
                // 左孩子有足够的键
                T pred = GetPredecessor(left);
                node->keys_[idx] = pred;
                RemoveKey(left, pred);
            }else if(node->children_[idx + 1]->keys_.size() >= order_ / 2){
                // 有孩子有足够的键
                Node* right = node->children_[idx + 1];
                T succ = GetSuccessor(right);
                node->keys_[idx] = succ;
                RemoveKey(right, succ);
            }else{
                // 左右孩子均不足，将左右孩子合并
                MergeChildren(node, idx);
                RemoveKey(left, key);
            }
            return;
        }

        if(!node->is_leaf_){
            // 键不在当前节点
            Node* child = node->children_[idx];
            if(child->keys_.size() >= order_ / 2){
                // 保证子节点至少有 t 个键
                if(idx > 0 && node->children_[idx - 1]->keys_.size() >= order_ / 2)
                    BorrowFromPrev(node, idx);
                else if(idx < node->keys_.size() && node->children_[idx + 1]->keys_.size() >= order_ / 2)
                    BorrowFromNext(node, idx);
                else{
                    if(idx < node->keys_.size())    MergeChildren(node, idx);
                    else{
                        MergeChildren(node, idx - 1);
                        child = node->children_[idx - 1];
                    }
                }
            }
            RemoveKey(child, key);
        }
    }
public:
    void Insert(const T& key){
        if(!root_){
            root_ = new Node(true);
            root_->keys_.push_back(key);
            ++size_;
            return;
        }

        if(root_->keys_.size() == order_ - 1){
            Node* new_root = new Node(false);
            new_root->children_.push_back(root_);
            SplitChild(new_root, 0, root_);
            root_ = new_root;
        }
        InsertNonFull(root_, key);
    }

    bool Find(const T& key) const {
        return FindKey(root_, key);
    }

    void Remove(const T& key){
        if(!root_) return;
        RemoveKey(root_, key);
        if(root_->keys_.empty() && !root_->is_leaf_){
            Node* old_root = root_;
            root_ = root_->children_[0];
            delete old_root;
        }
    }

    std::size_t Size() const{
        return size_;
    }

    bool Empty() const {
        return size_ == 0;
    }

/**************** TEST ********************/

private:
    void PrintTree(const Node* node, std::size_t level) const{
        for(int i=0; i<node->keys_.size(); i++){
            if(!node->is_leaf_) PrintTree(node->children_[i], level+1);
            std::cout << "Level " << level << " Key: " << node->keys_[i] << std::endl;
        }
        if(!node->is_leaf_) PrintTree(node->children_[node->keys_.size()], level+1);
    }

public:
    void Print() const {
        if(root_) PrintTree(root_, 0);
    }

};

#endif