#ifndef HASHTABLE_H
#define HASHTABLE_H
#include <iostream>
#include "exceptions.h"
#include "AVLTree.h"

using namespace std;


template <class T>
class HashTable
{
    private:
    AVLTree<T>* arr;
    int arr_size;
    int curr_taken; 

    void moveToBiggerArr(AVLTree<T>* new_arr)
    {
        curr_taken = 0;
        for (int i = 0; i < arr_size; i++)
        {
            //first, we will move the tree in arr[i] to an array if it is not empty
            if (arr[i].getTreeSize() != 0)
            {
                int i_tree_size = arr[i].getTreeSize();
                T* arr_data = new T[i_tree_size];
                arr[i].treeToArrayInorder(arr_data);
                //now insert to the new arr
                for (int j = 0; j < i_tree_size ; j++)
                {
                    int new_modulu = arr_data[j]%(arr_size*2);
                    new_arr[new_modulu].insert(arr_data[j]);
                    //if it is the first one
                    if (new_arr[new_modulu].getTreeSize()==1)
                    {
                        curr_taken++;
                    }
                }
                //finished, so delete this arr and move to the next tree
                delete[] arr_data;
            }
        }
        //finished to move all
    }

    void moveToSmallerArr(AVLTree<T>* new_arr)
    {
        curr_taken = 0;
        for (int i = 0; i < arr_size; i++)
        {
            //first, we will move the tree in arr[i] to an array if it is not empty
            if (arr[i].getTreeSize() != 0)
            {
                int i_tree_size = arr[i].getTreeSize();
                T* arr_data = new T[i_tree_size];
                arr[i].treeToArrayInorder(arr_data);
                //now insert to the new arr
                for (int j = 0; j < i_tree_size ; j++)
                {
                    int new_modulu = arr_data[j]%(arr_size/2);
                    new_arr[new_modulu].insert(arr_data[j]);
                    //if it is the first one
                    if (new_arr[new_modulu].getTreeSize()==1)
                    {
                        curr_taken++;
                    }
                }
                //finished, so delete this arr and move to the next tree
                delete[] arr_data;
            }
        }
        //finished to move all
    }

    public:
    HashTable();
    HashTable(const HashTable& hash);
    HashTable<T>& operator=(const HashTable& hash);
    ~HashTable();
    void insert(const T &data);
    void remove(const T &data);
    bool IsExists(const T &data) const;
    T& findData(const T &data) const;
    T* getDataPtr(const T &value);
    
    

};

template <class T>
HashTable<T>::HashTable(): arr(nullptr), arr_size(10), curr_taken(0) 
{
    this->arr = new AVLTree<T>[10];
}

template <class T>
HashTable<T>::~HashTable()
{
    delete[] this->arr;
}

template <class T>
HashTable<T>::HashTable(const HashTable& hash)
{
    this->arr = hash.arr;
    this->arr_size = hash.arr_size;
    this->curr_taken =  hash.curr_taken;
}

template <class T>
HashTable<T>& HashTable<T>::operator=(const HashTable& hash)
{
   if (this == &hash)
    {
        return *this;
    }
    delete[] this->arr;
    this->arr = hash.arr;
    this->arr_size = hash.arr_size;
    this->curr_taken = hash.curr_taken;
    return *this;
}

template <class T>
void HashTable<T>::insert(const T &data)
{
    if (IsExists(data))
    {
        throw DataAlreadyExists();
    }

    if (curr_taken == arr_size)
    {
        //make the array bigger
        AVLTree<T>* new_arr = new AVLTree<T>[arr_size*2];
        //go over the old arr and put in the new arr
        moveToBiggerArr(new_arr);
        this->arr_size = arr_size*2;
        delete[] this->arr;
        this->arr = new AVLTree<T>[arr_size];
        for (int k = 0; k < arr_size; k++)
        {
            arr[k]=new_arr[k];
        }
        delete[] new_arr;
    }
    int i = data%arr_size;
    arr[i].insert(data);
    //if it is the first one
    if (arr[i].getTreeSize()==1)
    {
        curr_taken++;
    }
}

template <class T>
void HashTable<T>::remove(const T &data)
{
    //if the data not exists
    if (!IsExists(data))
    {
        throw DataNotExists();
    }
    //if it is exists
    int i = data%arr_size;
    arr[i].remove(data);
    if (arr[i].getTreeSize()==0)
    {
        curr_taken--;
    } 

    //make it smaller if needed
    if (arr_size > 10)
    {
        if (curr_taken <= arr_size/4)
        {
            //make the array smaller
            AVLTree<T>* new_arr = new AVLTree<T>[arr_size/2];
            //go over the old arr and put in the new arr
            moveToSmallerArr(new_arr);
            this->arr_size = arr_size/2;
            delete[] this->arr;
            this->arr = new AVLTree<T>[arr_size];
            for (int k = 0; k < arr_size; k++)
            {
                arr[k]=new_arr[k];
            }
            delete[] new_arr;
            }
        } 
}


template <class T>
bool HashTable<T>::IsExists(const T &data) const
{
    int i = data%arr_size;
    if (arr[i].getTreeSize()==0)
    {
        return false;
    }
    if (arr[i].IsExists(data))
    {
        return true;
    }  
    return false;
}

template <class T>
T& HashTable<T>::findData(const T &data) const
{
    int i = data%arr_size;

    try
    {
        return arr[i].findData(data);
    }
    catch(const DataNotExists& e)
    {
        throw DataNotExists();
    }
}

template <class T>
T* HashTable<T>::getDataPtr(const T &value)
{
    T new_data;
    try
    {
        new_data = findData(value);
    }
    catch(const DataNotExists& e)
    {
        throw DataNotExists();
    }
    int i = value%arr_size;
    T *t_ptr = this->arr[i].getDataPtr(value);
    return t_ptr;
}

#endif

