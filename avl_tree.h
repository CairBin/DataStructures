// std c++ 14
#ifndef _AVL_TREE_H_
#define _AVL_TREE_H_

#include <iostream>
#include <memory>
#include <cstdint>
#include <tuple>

template<typename Key, typename Value>
class AvlMap{
private:
    typedef struct Node{
        Key key_;
        Value value_;
        int64_t height_;
        std::unique_ptr<struct Node> left_, right_;
        Node(const Key& key, const Value& value) : 
            key_(key), value_(value), height_(1) {}
    }Node;

    std::unique_ptr<Node> root_ = nullptr;

    int Height(const std::unique_ptr<Node>& node) const {
        return node ? node->height_ : 0;
    }

    int GetBalance(const std::unique_ptr<Node>& node) const {
        return node ? Height(node->left_) - Height(node->right_) : 0;
    }

    std::unique_ptr<Node> RightRotate(std::unique_ptr<Node> y){
        std::unique_ptr<Node> x = std::move(y->left_);
        std::unique_ptr<Node> T2 = std::move(x->right_);

        x->right_ = std::move(y);
        x->right_->left_ = std::move(T2);

        x->right_->height_ = std::max(
            Height(x->right_->left_),
            Height(x->right_->right_)
        ) + 1;

        x->height_ = std::max(Height(x->left_), Height(x->right_)) + 1;

        return x;
    }

    std::unique_ptr<Node> LeftRotate(std::unique_ptr<Node> x){
        std::unique_ptr<Node> y = std::move(x->right_);
        std::unique_ptr<Node> T2 = std::move(y->left_);

        y->left_ = std::move(x);
        y->left_->right_ = std::move(T2);

        y->left_->height_ = std::max(
            Height(y->left_->left_),
            Height(y->left_->right_)
        ) + 1;
    
        return y;
    }


    std::unique_ptr<Node> InsertNode(std::unique_ptr<Node> node, const Key& key, const Value& value, bool& is_new_node){
        if(!node){
            is_new_node = true;
            return std::make_unique<Node>(key, value);
        }

        if(key < node->key_) node->left_ = InsertNode(std::move(node->left_), key, value, is_new_node);
        else if(key > node->key_) node->right_ = InsertNode(std::move(node->right_), key, value, is_new_node);
        else{
            node->value_ = value;
            return node;
        }

        node->height_ = std::max(Height(node->left_), Height(node->right_)) + 1;
        int balance = GetBalance(node);

        // LL
        if(balance>1 && key<node->left_->key_) return RightRotate(std::move(node));
        // RR
        if(balance<-1 && key>node->right_->key_) return LeftRotate(std::move(node));
        // LR
        if(balance>1 && key>node->left_->key_){
            node->left_ = LeftRotate(std::move(node->left_));
            return RightRotate(std::move(node));
        }
        // RL
        if(balance<-1 && key<node->right_->key_){
            node->left_ = LeftRotate(std::move(node->left_));
            return LeftRotate(std::move(node));
        }

        return node;
    }

    Node* FindNode(const std::unique_ptr<Node>& node, const Key& key) const{
        if(!node) return nullptr;

        if(key < node->key_) return FindNode(node->left_, key);
        else if(key > node->key_) return FindNode(node->right_, key);
        else return node.get();
    }

    std::unique_ptr<Node> DeleteNode(std::unique_ptr<Node> root, const Key& key, bool& is_deleted){
        if(!root) return nullptr;

        if(key < root->key_) root->left_ = DeleteNode(std::move(root->left_), key, is_deleted);
        else if(key > root->key_) root->right_ = DeleteNode(std::move(root->right_), key, is_deleted);
        else{
            is_deleted = true; // 找到了节点并删除
            if(!root->left_ || !root->right_) return std::move(root->left_ ? root->left_ : root->right_);
            Node* temp = MinValueNode(root->right_.get());
            root->key_ = temp->key_;
            root->value_ = temp->value_;
            root->right_ = DeleteNode(std::move(root->right_), temp->key_, is_deleted);

        }

        root->height_ = std::max(Height(root->left_), Height(root->right_)) + 1;
        int balance = GetBalance(root);

        if(balance>1 && GetBalance(root->left_)>=0) return RightRotate(std::move(root));
        if(balance>1 && GetBalance(root->left_)<0){
            root->left_ = LeftRotate(std::move(root->left_));
            return RightRotate(std::move(root));
        }
        if(balance<-1 && GetBalance(root->right_)<=0) return LeftRotate(std::move(root));
        if(balance<-1 && GetBalance(root->right_)>0){
            root->right_ = RightRotate(std::move(root->right_));
            return LeftRotate(std::move(root));
        }

        return root;
    }

    Node* MinValueNode(Node* node){
        Node* current = node;
        while(current->left_) current = current->left_.get();
        return current;
    }


public:
    void Insert(const Key& key, const Value& value){
        bool is_new_node = false;
        root_ = InsertNode(std::move(root_), key, value, is_new_node);
        if(is_new_node) ++size_;
    }

    bool Get(const Key& key, Value& value) const {
        Node* node = FindNode(root_, key);
        if(node) {
            value = node->value_;
            return true;
        }
        return false;
    }

    void Remove(const Key& key){
        bool is_deleted = false;
        root_ = DeleteNode(std::move(root_), key, is_deleted);
        if(is_deleted) --size_;
    }

    std::size_t Size() const{
        return size_;
    }

private:
    size_t size_;
public:
    AvlMap() : size_(0){}
};

#endif