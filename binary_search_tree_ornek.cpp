#include <iostream>
using namespace std;

template <typename T>
class TreeNode{
public:
    T data;
    TreeNode<T>* left;
    TreeNode<T>* right;
    TreeNode(const T& data):data(data),left(NULL),right(NULL){}
};

enum MOD{PREORDER,INORDER,POSTORDER};

template<typename T>
class BinaryTree{
    TreeNode<T>* root;
    void printPreorder(TreeNode<T> * node)const {
        if (node){
            cout << node->data << " ";
            printPreorder(node->left);
            printPreorder(node->right);
        }
    }
    void printInorder(TreeNode<T> * node)const{
        if (node){
            printInorder(node->left);
            cout << node->data << " ";
            printInorder(node->right);
        }
    }
    void printPostorder(TreeNode<T> * node)const{
        if (node){
            printPostorder(node->left);
            printPostorder(node->right);
            cout << node->data << " ";
        }
    }
    TreeNode<T>* find(TreeNode<T>* node,const T& val) const{
        if (node){
            if (val > node->data) return find(node->right,val);
            else if(val < node->data ) return find(node->left,val);
        }
        return node;
    }
    TreeNode<T>* getMin (TreeNode<T>* node) const {
        TreeNode<T>* ptr = node;
        while(ptr->left){
            ptr = ptr->left;
        }
        return ptr;
    }
    TreeNode<T>* getMax (TreeNode<T>* node) const{
        TreeNode<T>* ptr = node;
        while(ptr->right){
            ptr = ptr->right;
        }
        return ptr;
    }
    TreeNode<T>* mirror(TreeNode<T>* start){
        if (start){
            mirror(start->left);
            mirror(start->right);
            TreeNode<T>* temp = start->left;
            start->left = start->right;
            start->right = temp;
        }
        return start;
    }
public:
    BinaryTree(TreeNode<T>* root = NULL) : root(root) {}
    bool isEmpty() const { return root == NULL; }
    TreeNode<T>* getRoot() const{ return root; }
    int height(TreeNode<T>* node){
        if (node){
            int right = height(node->right);
            int left = height(node->left);
            return 1 + max(right,left);
        }
        else return -1;
    }
    int height(){ return height(root); }
    int depth(TreeNode<T>* first,TreeNode<T>* final){
        if(first){
            if (first == final) return 0;
            int right = depth(first->right,final);
            int left = depth(first->left,final);
            return 1 + max(right,left);
        }
        else return INT_MIN;
    }
    int depth(TreeNode<T>* final){ return depth(root,final); }
    TreeNode<T>* add(TreeNode<T>* node,const T& val){
        if (node){
            if (val > node->data) node->right = add(node->right,val);
            else node->left = add(node->left,val);
            return node;
        }
        else return new TreeNode<T>(val);
    }
    TreeNode<T>* add(const T& val){
        return add(root,val);
    }
    void print(MOD mod)const{
        switch(mod){
        case 0:
            printPreorder(root);
            break;
        case 1:
            printInorder(root);
            break;
        case 2:
            printPostorder(root);
            break;
        }
        cout << endl;
    }
    TreeNode<T>* find(const T& val,bool last = false) const {
        TreeNode<T>* before = find(root,val);
        TreeNode<T>* after = before;
        if (last){
            while(before){
                after = before;
                before = find(before->left,val);
            }
        }
        return after;
    }
    TreeNode<T>* getMin() const{ return getMin(root); }

    TreeNode<T>* getMax() const{ return getMax(root); }

    TreeNode<T>* remove(TreeNode<T>* start,TreeNode<T>* node){
        if (start){
            if (start->data > node->data) start->left = remove(start->left,node);
            else if (start->data < node->data) start->right = remove(start->right,node);
            else if(start == node){
                TreeNode<T>* temp = NULL;
                if (start->right && start->left){
                    temp = getMin(start->right);
                    remove(start->right,temp);
                    temp->right = start->right;
                    temp->left = start->left;
                }
                if (start->right) temp = start->right;
                if (start->left) temp = start->left;
                return temp;
            }
        }
        return start;
    }

    void remove(TreeNode<T>* node){
        if (node){
            remove(root,node);
            delete node;
        }
    }
    void remove(T val,bool last = false){
        remove(find(val,last));
    }
    void mirror(){
        root = mirror(root);
    }
};

int main(){
    TreeNode<int> *n1 = new TreeNode<int>(20);
    BinaryTree<int> tree(n1);
    tree.add(12);
    tree.add(1);
    tree.add(122);
    tree.add(10);
    tree.add(8);
    tree.add(0);
    tree.print(INORDER);
    tree.remove(tree.find(8));
    tree.print(INORDER);
    tree.mirror();
    tree.print(INORDER);
    return 0;
}
