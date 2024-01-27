#ifndef AVLLevelTree_H
#define AVLLevelTree_H
#include <iostream>
#include "LevelInfo.h"
#include "exceptions.h"

using namespace std;

class AVLLevelTree{
    
    private:
    struct Node
    {
        LevelInfo data;
        Node* left;
        Node* right;
        int height;  
        //new variables
        int sum_num_players;
        int* sum_scale;
        int level_sum_players;//new variable
    };
    Node* root;
    Node* max;
    int tree_size;
    
    Node* createNode(const LevelInfo& data);
    Node* findNode(Node* node ,const LevelInfo& data) const;
    Node* insertNode(Node* node, const LevelInfo& value);
    Node* removeNode(Node* node, const LevelInfo& value);
    int getHeight(Node* node); 
    int getMaxHeight(int num1, int num2); 
    int getSumNumPlayers(Node* node) const;//new added function
    int* getSumScale(Node* node) const;//new added function
    void updateScaleArr(Node* current_node, Node* left_node, Node* right_node);//new added function

    // ----------- Roll Functions -----------
    Node* RightRight(Node* node);
    Node* RightLeft(Node* node);
    Node* LeftRight(Node* node);
    Node* LeftLeft(Node* node);

    public:
    AVLLevelTree();
    AVLLevelTree(const AVLLevelTree& tree);
    ~AVLLevelTree();
    AVLLevelTree& operator=(const AVLLevelTree& tree);
    Node* copyTree(Node* node);
    void delete_all(Node* node);
    void delete_tree();
    LevelInfo& findData(const LevelInfo& data) const;
    int treeBalence(Node* node);
    void insert(const LevelInfo& value);
    void remove(const LevelInfo& value);
    Node* getMax(Node* node) const;
    int getTreeSize() const;
    bool isDestroyed() const;
    void printInorder() const;
    void printNode(Node* node) const;
    LevelInfo* mergeArrays(LevelInfo arr1[] ,LevelInfo arr2[], int m , int n, int* true_size);
    void treeToArray(Node* node,LevelInfo inorder[], int* index_ptr) const;
    void treeToArrayInorder(LevelInfo inorder[]) const;
    Node* arrayToTree(LevelInfo arr[], int start, int end);
    bool IsExists(const LevelInfo& data) const;
    Node* mergeTreesNode(Node* root_tree1, Node* root_tree2, int size1, int size2, int* new_size);
    LevelInfo* getDataPtr(const LevelInfo& value);
    LevelInfo& getMaxData() const;
    void mergeTrees(const AVLLevelTree& tree);
    void updateSumInTree(Node* node);//new function
    void updateScore(Node* node, const LevelInfo& data);//new function,changePlayerIDScore helper
    void updatePlayerRemove(int level, int score);
    void updatePlayerNewScore(int level, int old_score, int new_score);
    void updatePlayerNewLevel(int score, int old_level, int new_level, int arr_size);
    void updateTreeAfterRemove(Node* node, LevelInfo& data, int score);
    void updateTreeAfteNewScore(Node* node, LevelInfo& data, int old_score, int new_score);
    void updateTreeAfteNewLevel(Node* node, LevelInfo& data, int score, int num);
    int getSumofPlayersInLevelRangeTree(Node* node,int level) const;
    int getSumofPlayersInLevelRange(int level) const;
    int getSumofPlayersEqualToScoreTree(Node* node,int level,int score) const;
    int getSumofPlayersEqualToScore(int level,int score) const;
    void averageHighestLevel(int m, double * level);
    int getNumOfPlayersInTree() const;
    int getLevelSumPlayersInTree() const;
    int getLevelSumPlayers(Node* node) const;
    void RecurAverageHighestLevel(Node* node, int* counter, double * level);
    Node* getRoot() const;
    
    
};


#endif