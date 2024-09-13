#ifndef _HUFFMAN_TREE_H_
#define _HUFFMAN_TREE_H_

#include <vector>
#include <map>
#include <queue> 

class HuffmanTree{
private:
    typedef struct Node{
        int weight_;
        Node* l_;
        Node* r_;
    }HNode,Node,HTree;

private:
    std::vector<Node*> forest_;
    HTree* root_;


public:
    ~HuffmanTree(){
       for(int i=0; i<forest_.size(); i++){
            delete forest_[i];
            forest_[i] = nullptr;
        } 
    }
    HuffmanTree(int arr[], int n){
        root_ = nullptr;
        for(int i=0; i<n; i++){
            HTree* temp;
            temp = new HTree;
            temp->weight_ = arr[i];
            temp->l_ = nullptr;
            temp->r_ = nullptr;
            forest_.emplace_back(temp);
        }

        for(int i=1; i<n; i++){
            int minn = -1;
            int minn_sub;

            for(int j = 0; j < n; j++){
                if(forest_[j] && !(~(minn))){
                    minn = j;
                    continue;
                }

                if(forest_[j]){
                    minn_sub = j;
                    break;
                }
            }

            for(int j=minn_sub; j<n; j++){
            if(!forest_[j]) continue;
            if(forest_[j]->weight_ < forest_[minn]->weight_) minn_sub = minn, minn = j;
            else if(forest_[j]->weight_ < forest_[minn_sub]->weight_) minn_sub = j;
            }
            

             // build a new tree
            root_ = new HNode;
            root_->weight_ = forest_[minn]->weight_
                + forest_[minn_sub]->weight_;
            root_->l_ = forest_[minn];
            root_->r_ = forest_[minn_sub];

            forest_[minn] = root_;
            forest_[minn_sub] = nullptr;

        }

        
    }

    int GetWpl(){
        return GetWpl(root_, 0);
    }

    void GetCoding(std::map<int, std::vector<std::vector<bool> > >& res){
        std::vector<bool> arr(forest_.size(), false);
        GetCoding(res, root_, 0, arr);
    }

private:
    int GetWpl(Node* root, int len){
        if(!root) return 0;

        if(root->l_ == nullptr && root->r_ == nullptr){
            // leaf node
            return root->weight_*len;
        }

        return GetWpl(root->l_, len+1) + GetWpl(root->r_, len+1);
    }

    void GetCoding(std::map<int, std::vector<std::vector<bool> > >& res, Node* root, int len, std::vector<bool>& arr){
        if(!root) return;

        if(!(root->l_) && !(root->r_)){
            res[root->weight_].emplace_back(std::vector<bool>(arr.begin(), arr.begin()+len));
            return;
        }

        arr[len] = false;
        GetCoding(res, root->l_, len+1, arr);
        arr[len] = true;
        GetCoding(res, root->r_, len+1, arr);
    }

public:
    static int GetWpl(int arr[], int n){
        std::priority_queue<int, std::vector<int>, std::greater<int> > huffman;
        for(int i=0; i<n; i++) huffman.emplace(arr[i]);

        int res = 0;
        for(int i=0; i<n-1; i++){
            int x = huffman.top();  // min node
            huffman.pop();

            int y = huffman.top();    // min sub node
            huffman.pop();

            int temp = x+y; //parent weight
            res+=temp;
            huffman.emplace(temp);
        }


        return res;
    }

};




#endif

