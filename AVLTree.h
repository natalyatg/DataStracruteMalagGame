#ifndef AVLTree_H
#define AVLTree_H
using namespace std;
#include <iostream>

#include "exceptions.h"

/*
    updated functions:
    remove
    insert
    findData
*/

template <class T>
class AVLTree {
    
    private:
    struct Node
    {
        T data;
        Node* left;
        Node* right;
        int height;  
    };
    Node* root;
    Node* max;
    int tree_size;
    
    Node* createNode(const T &data);
    Node* findNode(Node* node ,const T &data) const;
    Node* insertNode(Node* node, const T& value);
    Node* removeNode(Node* node, const T& value);
    int getHeight(Node* node); 
    int getMaxHeight(int num1, int num2); 

    // ----------- Roll Functions -----------
    Node* RightRight(Node* node);
    Node* RightLeft(Node* node);
    Node* LeftRight(Node* node);
    Node* LeftLeft(Node* node);

    public:
    AVLTree();
    AVLTree(const AVLTree& tree);
    ~AVLTree();
    AVLTree<T>& operator=(const AVLTree& tree);
    Node* copyTree(Node* node);
    void delete_all(Node* node);
    void delete_tree();
    T& findData(const T &data) const;
    int treeBalence(Node* node);
    void insert(const T &value);
    void remove(const T &value);
    Node* getMax(Node* node) const;
    int getTreeSize() const;
    bool isDestroyed() const;
    void printInorder() const;
    void printNode(Node* node) const;
    T* mergeArrays(T arr1[] , T arr2[], int m , int n);
    void treeToArray(Node* node, T inorder[], int* index_ptr) const;
    void treeToArrayInorder(T inorder[]) const;
    Node* arrayToTree(T arr[], int start, int end);
    bool IsExists(const T &data) const;
    Node* mergeTreesNode(Node* root_tree1, Node* root_tree2, int size1, int size2);
    T* getDataPtr(const T &value);
    T& getMaxData() const;
    void mergeTrees(const AVLTree& tree);
    void updateHeight() const;
     
    


};
// ----------- Node -----------

template <class T>
typename AVLTree<T>::Node* AVLTree<T>::createNode(const T &data)
{
    Node* node = new Node;
    node->data = data;
    node->right = nullptr;
    node->left = nullptr;
    node->height = 0;
    return node;
}

template <class T>
int AVLTree<T>::getHeight(AVLTree<T>::Node* node)
{
    if (node == nullptr)
    {
        return -1;
    }
    else return node->height;
}

template <class T>
 typename AVLTree<T>::Node* AVLTree<T>::findNode(AVLTree<T>::Node* node ,const T &data) const
 {
     if (node == nullptr)
    {
        return nullptr;
    }
    else if(data < node->data)
    {
        return findNode(node->left, data);
    }
    else if(node->data < data)
    {
        return findNode(node->right, data);
    }
    else
    {
        return node;
    }
 }

template <class T>
 int AVLTree<T>::getMaxHeight(int num1, int num2)
{
    if (num1 > num2)
    {
        return num1;
    }
    return num2;
}

 // ----------- Roll Functions -----------
 template <class T>
 typename AVLTree<T>::Node* AVLTree<T>::RightRight(AVLTree<T>::Node* node)
 {
    Node* new_node= node->right;
    Node* temp_son = new_node->left;
    new_node->left = node;
    node->right = temp_son;
    node->height = getMaxHeight(getHeight(node->left), getHeight(node->right))+1;
    new_node->height = getMaxHeight(getHeight(new_node->left), getHeight(new_node->right))+1;
    return new_node; 
 }

 template <class T>
 typename AVLTree<T>::Node* AVLTree<T>::LeftLeft(AVLTree<T>::Node* node)
 {
    Node* new_node=node->left;
    Node* temp_son = new_node->right;
    new_node->right = node;
    node->left = temp_son;
    node->height = getMaxHeight(getHeight(node->left), getHeight(node->right))+1;
    new_node->height = getMaxHeight(getHeight(new_node->left), getHeight(new_node->right))+1;
    return new_node; 
 }

 template <class T>
 typename AVLTree<T>::Node* AVLTree<T>::RightLeft(AVLTree<T>::Node* node)
 {
    node->right=LeftLeft(node->right);
    return RightRight(node); 
 }

template <class T>
 typename AVLTree<T>::Node* AVLTree<T>::LeftRight(AVLTree<T>::Node* node)
 {
    node->left=RightRight(node->left);
    return LeftLeft(node); 
 }


template <class T>
typename AVLTree<T>::Node* AVLTree<T>::insertNode(AVLTree<T>::Node* node, const T& value) 
{
    if (node == nullptr)
    {
        return createNode(value);
    }
    if (value < node->data)
    {
        node->left = insertNode(node->left, value);
    }
    else if (node->data < value)
    {
        node->right = insertNode(node->right, value);  
    }

    //recursion finished, now balancing the tree
    int balanced_factor = treeBalence(node);
    //if the right is bigger then the left - RL or RR
    if (balanced_factor > 1 )
    {
        //if it is LL
        if (treeBalence(node->left) >= 0)
        {
            return LeftLeft(node);
        }
        //if it is LR
        else 
        {
            return LeftRight(node);
        }   
    }
    //if the right is bigger then the left - RL or RR
    else if (balanced_factor < -1 )
    {
        //if it is RL
        if (treeBalence(node->right) == 1)
        {
            return RightLeft(node);
        }
        //if it is RR
        else 
        {
            return RightRight(node);
        }    
    }
    //update new hight
    node->height = getMaxHeight(getHeight(node->left), getHeight(node->right))+1;
    
    return node;
}

template <class T>
typename AVLTree<T>::Node* AVLTree<T>::removeNode(AVLTree<T>::Node* node, const T& value) 
{
    if (node == nullptr)
    {
        return nullptr;
    }
    if (node->data == value)
    {
        //if leaf
        if (node->right == nullptr && node->left == nullptr)
        {
            delete node;
            return nullptr;
        }
        //if only left son
        else if (node->right == nullptr && node->left != nullptr) 
        {
            node->data = node->left->data;
            node->left->data = value;
            node->left = removeNode(node->left, value);
        }
        //if only right son
        else if ( node->right != nullptr && node->left == nullptr)
        {
            node->data = node->right->data;
            node->right->data = value;
            node->right = removeNode(node->right, value);
        }
        else
        {
            //get the next value after the removal value
            Node* temp = node->right;
            while (temp->left != nullptr)
            {
                temp = temp->left;
            }  
            node->data = temp->data;
            temp->data = value;
            node->right = removeNode(node->right,value);
        }    
    }
    else if (value < node->data)
    {
        node->left = removeNode(node->left, value);
    }
    else
    {
        node->right = removeNode(node->right, value);
    }
    
    node->height = getMaxHeight(getHeight(node->left), getHeight(node->right))+1;
    
    //recursion finished, now balancing the tree
    int balanced_factor = treeBalence(node);
    //if the right is bigger then the left - RL or RR
    if (balanced_factor > 1 )
    {
        //if it is LL
        if (treeBalence(node->left) >= 0)
        {
            return LeftLeft(node);
        }
        //if it is LR
        else 
        {
            return LeftRight(node);
        }   
    }
    //if the right is bigger then the left - RL or RR
    else if (balanced_factor < -1 )
    {
        //if it is RL
        if (treeBalence(node->right) == 1)
        {
            return RightLeft(node);
        }
        //if it is RR
        else 
        {
            return RightRight(node);
        }    
    }
    return node;
}


// ----------- AVLTree -----------
template <class T>
AVLTree<T>::AVLTree(): root(nullptr),max(nullptr), tree_size(0) {}

//copy constructor helper
template <class T>
typename AVLTree<T>::Node* AVLTree<T>::copyTree(AVLTree<T>::Node* node)
{ 
    if(node == nullptr)
    {
        return nullptr;
    }
    Node* left = copyTree(node->left);
    Node* right = copyTree(node->right);
    Node* new_node = createNode(node->data);
    new_node->left = left;
    new_node->right = right;
    new_node->height = node->height;
    return new_node;
}   
  
  
//copy constructor
template <class T>
AVLTree<T>::AVLTree(const AVLTree& tree): root(nullptr),max(nullptr)
{
    this->root = copyTree(tree.root);
    this->tree_size = tree.tree_size;
    this->max =  getMax(this->root);
}

//operator =
template <class T>
AVLTree<T>& AVLTree<T>::operator=(const AVLTree<T>& tree)
{
    if (this == &tree)
    {
        return *this;
    }
    this->delete_all(this->root);
    this->root = copyTree(tree.root);
    this->tree_size = tree.tree_size;
    this->max =  getMax(this->root);
    return *this;
}

//destructor helper
template <class T>
void AVLTree<T>::delete_all(AVLTree<T>::Node* node)
{
    if(node == nullptr)
    {
        return;
    }
    
    if(node->left != nullptr)
    {   
        delete_all(node->left);
    }
    
    if(node->right != nullptr)
    {
        delete_all(node->right);
    }
    delete node;
}

template <class T>
void AVLTree<T>::delete_tree()
{
    this->delete_all(this->root);
    this->root= nullptr;
    this->max=nullptr;
    this->tree_size=0;
}

//destructor
template <class T>
AVLTree<T>::~AVLTree()
{
    this->delete_tree();
}

//find data
template <class T>
T& AVLTree<T>::findData(const T &data) const
{
    Node* new_node = findNode(this->root, data);
    if (new_node == nullptr)
    {
        throw DataNotExists();
    }
    return new_node->data;
}

template <class T>
bool AVLTree<T>::IsExists(const T &data) const
{
    try
    {
       findData(data);
    }
    catch (DataNotExists &e) {
        return false;
    }
    return true;
}

template <class T>
 int AVLTree<T>::treeBalence(AVLTree<T>::Node* node)
{
    if (node == nullptr)
        return 0;
    return getHeight(node->left) - getHeight(node->right);
}   

//add errors later
template <class T>
void AVLTree<T>::insert(const T& value) {
    if (findNode(this->root, value) != nullptr)
    {
        throw DataAlreadyExists();
    }
    else
    {
        this->root = insertNode(this->root, value);
        this->tree_size = this->tree_size + 1;
        this->max = getMax(this->root);
    }   
}

template <class T>
void AVLTree<T>::remove(const T& value) 
{
        this->root = removeNode(this->root, value);
        this->tree_size = this->tree_size-1;
        this->max = getMax(this->root); 
}

template <class T>
typename AVLTree<T>::Node* AVLTree<T>::getMax(AVLTree<T>::Node* node) const
{
    if (node == nullptr)
    {
        return nullptr;
    }
    if(node->right== nullptr)
    {
        return node;
    }
    while(node->right != nullptr)
    {
        node=node->right;
    }
    return node;
}

template <class T>
int AVLTree<T>::getTreeSize() const
{
    return this->tree_size;
}

template <class T>
bool AVLTree<T>::isDestroyed() const
{
    if(this->root==nullptr)
    {
        return true;
    }
    else
    {
        return false;
    }
}

template <class T>
void AVLTree<T>::printNode(AVLTree<T>::Node* node) const
{
    if(node == NULL)
    {
        return;
    }      
    printNode(node->left);
    cout << node->data <<  " " ;
    printNode(node->right);

}

template <class T>
void AVLTree<T>::printInorder() const
{
    printNode(this->root);
}

//function that merge two sorted arrays to one sorted array
template <class T>
T* AVLTree<T>::mergeArrays(T arr1[] , T arr2[], int m , int n)
{
   
    T *merge_arr = new T[m+n];
    int i = 0, j=0,k=0;
    while (i < m && j < n)
    {
        // Pick the smaller element and put it in merge_arr
        if (arr1[i] < arr2[j])
        {
           merge_arr[k] = arr1[i];
            i++;
        }
        else
        {
           merge_arr[k] = arr2[j];
            j++;
        }
        k++;
    }

    // If there are more elements in first array
    while (i < m)
    {
        merge_arr[k] = arr1[i];
        i++; k++;
    }

    // If there are more elements in second array
    while (j < n)
    {
        merge_arr[k] = arr2[j];
        j++; k++;
    }

     return merge_arr;
}

//function that transfers AvlTree to sorted array
template <class T>
void AVLTree<T>::treeToArray(AVLTree<T>::Node* node, T inorder[], int* index_ptr) const
{
    if (node == nullptr)
    {
        return;
    }
    treeToArray(node->left, inorder, index_ptr);
    inorder[*index_ptr] = node->data;
    (*index_ptr)++;
    treeToArray(node->right, inorder, index_ptr);
}

template <class T>
void AVLTree<T>::treeToArrayInorder(T inorder[]) const
{
    int i = 0;
    treeToArray(this->root,inorder,&i);
}

//function that create AVLTree from sorted array
template <class T>
typename AVLTree<T>::Node* AVLTree<T>::arrayToTree(T arr[], int start, int end) 
{
    if (start > end)
    {
        return nullptr;
    }
    int mid = (start + end)/2;
    Node* new_root = createNode(arr[mid]);
    new_root->left = arrayToTree(arr, start, mid-1);
    new_root->right = arrayToTree(arr, mid+1, end);
    new_root->height = getMaxHeight(getHeight(new_root->left), getHeight(new_root->right))+1;
    return new_root;
}

template <class T>
typename AVLTree<T>::Node* AVLTree<T>::mergeTreesNode(AVLTree<T>::Node* root_tree1, AVLTree<T>::Node* root_tree2, int size1, int size2)
{
    //transfers first tree to array
    T *arr1 = new T[size1];
    int i = 0;
    treeToArray(root_tree1, arr1, &i);
    //transfers second tree to array
    T *arr2 = new T[size2];
    int j = 0;
    treeToArray(root_tree2, arr2, &j);
    //merge the two arrays
    T *mergedArr = mergeArrays(arr1, arr2,size1, size2);
    //create AVLTree from the merged araay
    delete []arr1;
    delete []arr2;
    Node* temp=arrayToTree(mergedArr, 0, size1 + size2 - 1);
    delete []mergedArr;
    delete_all(root_tree1);
    return temp;
}

template <class T>
T* AVLTree<T>::getDataPtr(const T &value)
{
    Node* new_node = findNode(this->root, value);
    if (new_node == nullptr)
    {
        throw DataNotExists();
    }
    T *t_ptr = &(new_node->data);
    return t_ptr;
}

template <class T>
T& AVLTree<T>::getMaxData() const
{
    Node* tmp_node = this->max;
    return tmp_node->data;
}

template <class T>
void AVLTree<T>::mergeTrees(const AVLTree& tree)
{
    int size1 = this->tree_size;
    int size2 = tree.tree_size;
    this->root=mergeTreesNode(this->root, tree.root, size1, size2);
    this->max = getMax(this->root);
    this->tree_size = size1+size2;
}

template <class T>
void AVLTree<T>::updateHeight() const
{
    
}

#endif