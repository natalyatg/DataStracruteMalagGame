#include "AVLLevelTree.h"

// ----------- Node -----------

//added the other variables to the the create node
typename AVLLevelTree::Node* AVLLevelTree::createNode(const LevelInfo& data)
{
    Node* node = new Node;
    node->data = data;
    node->right = nullptr;
    node->left = nullptr;
    node->height = 0;
    node->sum_num_players=0;
    node->sum_scale= new int[data.getArr_size()];
    for (int i = 0; i < data.getArr_size(); i++)
    {
        node->sum_scale[i] = 0;
    }
    node->level_sum_players=0;
    return node;
}

int AVLLevelTree::getHeight(AVLLevelTree::Node* node)
{
    if (node == nullptr)
    {
        return -1;
    }
    else return node->height;
}

void AVLLevelTree::updateScore(AVLLevelTree::Node* node, const LevelInfo& data)
{
    if(node == nullptr)
    {
        return;
    }
    else if(data < node->data)
    {
        updateScore(node->left, data);
        updateScaleArr(node,node->left,node->right);
    }
    else if(node->data < data)
    {
        updateScore(node->right, data);
        updateScaleArr(node,node->left,node->right);
    }
    else
    {
        updateScaleArr(node,node->left,node->right);
    }
}

 typename AVLLevelTree::Node* AVLLevelTree::findNode(AVLLevelTree::Node* node ,const LevelInfo& data) const
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

 int AVLLevelTree::getMaxHeight(int num1, int num2)
{
    if (num1 > num2)
    {
        return num1;
    }
    return num2;
}

int AVLLevelTree::getSumNumPlayers(AVLLevelTree::Node* node) const//new function
{
    if (node == nullptr)
    {
        return 0;
    } 
    else
    {
        return node->sum_num_players;
    }
}

int AVLLevelTree::getLevelSumPlayers(AVLLevelTree::Node* node) const
{
    if (node == nullptr)
    {
        return 0;
    } 
    else
    {
        return node->level_sum_players;
    }
}

int* AVLLevelTree::getSumScale(AVLLevelTree::Node* node) const
{
    if (node == nullptr)
    {
        return nullptr;
    } 
    else
    {
        return node->sum_scale;
    }
}


void AVLLevelTree::updateScaleArr(AVLLevelTree::Node* current_node, AVLLevelTree::Node* left_node, AVLLevelTree::Node* right_node)
{
    int* left_arr = getSumScale(left_node);
    int* right_arr = getSumScale(right_node);
    int* node_arr = current_node->data.getScaleArr();
    //only right son
    if(left_arr == nullptr && right_arr != nullptr)
    {
        for (int i = 0; i < current_node->data.getArr_size(); i++)
        {   
           
            current_node->sum_scale[i] =right_arr[i]+ node_arr[i];
        }
    }
    //only left son
    else if(left_arr != nullptr && right_arr == nullptr)
    {
        for (int i = 0; i < current_node->data.getArr_size(); i++)
        {
            current_node->sum_scale[i] = left_arr[i]+node_arr[i];
        }
    }
    //left and right son
    else if(left_arr != nullptr && right_arr != nullptr)
    {
        for (int i = 0; i < current_node->data.getArr_size(); i++)
        {
            current_node->sum_scale[i] = left_arr[i]+right_arr[i]+ node_arr[i];
        }
    }
    //no sons
    else
    {
        for (int i = 0; i < current_node->data.getArr_size(); i++)
        {
            current_node->sum_scale[i] = node_arr[i];
        }
    }
    
}

 // ----------- Roll Functions -----------
 //Updated the rightright and leftleft roll function according to the new variables

 typename AVLLevelTree::Node* AVLLevelTree::RightRight(AVLLevelTree::Node* node)
 {
    Node* new_node=node->right;
    Node* temp_son = new_node->left;
    new_node->left = node;
    node->right = temp_son;
    node->height = getMaxHeight(getHeight(node->left), getHeight(node->right))+1;
    node->sum_num_players = getSumNumPlayers(node->left)+getSumNumPlayers(node->right) + node->data.getThisNumPlayers();
    updateScaleArr(node,node->left,node->right);
    node->level_sum_players=(node->data.getNumLevel())*(node->data.getThisNumPlayers())+getLevelSumPlayers(node->right)+getLevelSumPlayers(node->left);
    new_node->height = getMaxHeight(getHeight(new_node->left), getHeight(new_node->right))+1;
    new_node->sum_num_players = getSumNumPlayers(new_node->left)+getSumNumPlayers(new_node->right)+ new_node->data.getThisNumPlayers();
    updateScaleArr(new_node,new_node->left,new_node->right);
    new_node->level_sum_players=(new_node->data.getNumLevel())*(new_node->data.getThisNumPlayers())+getLevelSumPlayers(new_node->right)+getLevelSumPlayers(new_node->left);
    return new_node; 
 }

 typename AVLLevelTree::Node* AVLLevelTree::LeftLeft(AVLLevelTree::Node* node)
 {
    Node* new_node=node->left;
    Node* temp_son = new_node->right;
    new_node->right = node;
    node->left = temp_son;
    node->height = getMaxHeight(getHeight(node->left), getHeight(node->right))+1;
    node->sum_num_players = getSumNumPlayers(node->left)+getSumNumPlayers(node->right) + node->data.getThisNumPlayers();
    updateScaleArr(node,node->left,node->right);
    node->level_sum_players=(node->data.getNumLevel())*(node->data.getThisNumPlayers())+getLevelSumPlayers(node->right)+getLevelSumPlayers(node->left);
    new_node->height = getMaxHeight(getHeight(new_node->left), getHeight(new_node->right))+1;
    new_node->sum_num_players = getSumNumPlayers(new_node->left)+getSumNumPlayers(new_node->right)+ new_node->data.getThisNumPlayers();
    updateScaleArr(new_node,new_node->left,new_node->right);
    new_node->level_sum_players=(new_node->data.getNumLevel())*(new_node->data.getThisNumPlayers())+getLevelSumPlayers(new_node->right)+getLevelSumPlayers(new_node->left);
    return new_node; 
 }

 typename AVLLevelTree::Node* AVLLevelTree::RightLeft(AVLLevelTree::Node* node)
 {
    node->right=LeftLeft(node->right);
    return RightRight(node); 
 }

 typename AVLLevelTree::Node* AVLLevelTree::LeftRight(AVLLevelTree::Node* node)
 {
    node->left=RightRight(node->left);
    return LeftLeft(node); 
 }

//update the function according to the new variables
typename AVLLevelTree::Node* AVLLevelTree::insertNode(AVLLevelTree::Node* node, const LevelInfo& value) 
{
    if (node == nullptr)
    {
        node = createNode(value);
        node->sum_num_players = value.getThisNumPlayers();
        node->level_sum_players=value.getNumLevel()*value.getThisNumPlayers();
        updateScaleArr(node,node->left,node->right);
        return  node;
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
    //if the left is bigger then the right - LR or LL
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
    
    //update new height, sum_num_players and sumScale
    node->height = getMaxHeight(getHeight(node->left), getHeight(node->right))+1;
    node->sum_num_players = getSumNumPlayers(node->left)+getSumNumPlayers(node->right) + node->data.getThisNumPlayers();
    updateScaleArr(node,node->left,node->right);
    node->level_sum_players=(node->data.getNumLevel())*(node->data.getThisNumPlayers())+getLevelSumPlayers(node->right)+getLevelSumPlayers(node->left);
    
    return node;
}

//update the function according to the new variables
typename AVLLevelTree::Node* AVLLevelTree::removeNode(AVLLevelTree::Node* node, const LevelInfo& value) 
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
            delete[] node->sum_scale; 
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
    node->sum_num_players = getSumNumPlayers(node->left)+getSumNumPlayers(node->right) + node->data.getThisNumPlayers();
    updateScaleArr(node,node->left,node->right);
    node->level_sum_players=(node->data.getNumLevel())*(node->data.getThisNumPlayers())+getLevelSumPlayers(node->right)+getLevelSumPlayers(node->left);


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


// ----------- AVLLevelTree -----------
AVLLevelTree::AVLLevelTree(): root(nullptr),max(nullptr), tree_size(0) {}

//copy constructor helper
//updated according to the new variables
typename AVLLevelTree::Node* AVLLevelTree::copyTree(AVLLevelTree::Node* node)
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
    new_node->sum_num_players = node->sum_num_players;
    delete[] new_node->sum_scale;
    new_node->sum_scale = new int[node->data.getArr_size()];
    for (int i = 0; i < node->data.getArr_size(); i++)
    {
        new_node->sum_scale[i] = node->sum_scale[i];
    }
    new_node->level_sum_players=node->level_sum_players;
    return new_node;
}   
  
  
//copy constructor
AVLLevelTree::AVLLevelTree(const AVLLevelTree& tree): root(nullptr),max(nullptr)
{
    this->root = copyTree(tree.root);
    this->tree_size = tree.tree_size;
    this->max =  getMax(this->root);
}

//operator =
AVLLevelTree& AVLLevelTree::operator=(const AVLLevelTree& tree)
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
//added deteted arr
void AVLLevelTree::delete_all(AVLLevelTree::Node* node)
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
    delete[] node->sum_scale;
    delete node;
}

void AVLLevelTree::delete_tree()
{
    this->delete_all(this->root);
    this->root= nullptr;
    this->max=nullptr;
    this->tree_size=0;
}

//destructor
AVLLevelTree::~AVLLevelTree()
{
    this->delete_tree();
}

//find data
LevelInfo& AVLLevelTree::findData(const LevelInfo& data) const
{
    Node* new_node = findNode(this->root, data);
    if (new_node == nullptr)
    {
        throw DataNotExists();
    }
    return new_node->data;
}

bool AVLLevelTree::IsExists(const LevelInfo& data) const
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


 int AVLLevelTree::treeBalence(AVLLevelTree::Node* node)
{
    if (node == nullptr)
        return 0;
    return getHeight(node->left) - getHeight(node->right);
}   

void AVLLevelTree::insert(const LevelInfo& value) {
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

void AVLLevelTree::remove(const LevelInfo& value) 
{
        this->root = removeNode(this->root, value);
        this->tree_size = this->tree_size-1;
        this->max = getMax(this->root); 
}

typename AVLLevelTree::Node* AVLLevelTree::getMax(AVLLevelTree::Node* node) const
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

int AVLLevelTree::getTreeSize() const
{
    return this->tree_size;
}

bool AVLLevelTree::isDestroyed() const
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

//function that merge two sorted arrays to one sorted array
LevelInfo* AVLLevelTree::mergeArrays(LevelInfo arr1[] ,LevelInfo arr2[], int m , int n, int* true_size) //need to delete the two arrays?
{
   
    LevelInfo* merge_arr = new LevelInfo[m+n];
    int i = 0, j=0,k=0;
    while (i < m && j < n)
    {
        // Pick the smaller element and put it in merge_arr
        if (arr1[i] < arr2[j])
        {
           merge_arr[k] = arr1[i];
            i++;
        }
        else if (arr2[j] < arr1[i])
        {
           merge_arr[k] = arr2[j];
            j++;
        }
        //Added in case the two levels are equal
        else
        {
            arr1[i].mergeTwoLevelInfo(arr2[j]);
            merge_arr[k]=arr1[i];
            i++;
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

    if (k < m+n)
    {
        LevelInfo* new_merge_arr = new LevelInfo[k];
        for (int i = 0; i < k; i++)
        {
            new_merge_arr[i]= merge_arr[i];
        }
        delete[] merge_arr;
        *true_size = k;
        return new_merge_arr;
    }
    *true_size = m+n;
     return merge_arr;
}

//function that transfers AvlTree to sorted array
void AVLLevelTree::treeToArray(AVLLevelTree::Node* node,LevelInfo inorder[], int* index_ptr) const
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

void AVLLevelTree::treeToArrayInorder(LevelInfo inorder[]) const
{
    int i = 0;
    treeToArray(this->root,inorder,&i);
}

//function that create AVLLevelTree from sorted array
typename AVLLevelTree::Node* AVLLevelTree::arrayToTree(LevelInfo arr[], int start, int end) 
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

typename AVLLevelTree::Node* AVLLevelTree::mergeTreesNode(AVLLevelTree::Node* root_tree1, AVLLevelTree::Node* root_tree2,
    int size1, int size2, int *new_size)
{
    //transfers first tree to array
   LevelInfo* arr1 = new LevelInfo[size1];
    int i = 0;
    treeToArray(root_tree1, arr1, &i);
    //transfers second tree to array
   LevelInfo* arr2 = new LevelInfo[size2];
    int j = 0;
    treeToArray(root_tree2, arr2, &j);
    //merge the two arrays
    int true_size = 0;
   LevelInfo*mergedArr = mergeArrays(arr1, arr2,size1, size2, &true_size);
    //create AVLLevelTree from the merged araay
    delete []arr1;
    delete []arr2;
    Node* temp=arrayToTree(mergedArr, 0, true_size - 1);
    delete []mergedArr;
    delete_all(root_tree1);
    *new_size = true_size;
    return temp;
}

LevelInfo* AVLLevelTree::getDataPtr(const LevelInfo& value)
{
    Node* new_node = findNode(this->root, value);
    if (new_node == nullptr)
    {
        throw DataNotExists();
    }
   LevelInfo*t_ptr = &(new_node->data);
    return t_ptr;
}

LevelInfo& AVLLevelTree::getMaxData() const
{
    Node* tmp_node = this->max;
    return tmp_node->data;
}


//update the nodes array and the sum of all tree
void AVLLevelTree::updateSumInTree(AVLLevelTree::Node* node)
{
    if(node == nullptr)
    {
        return;
    }
    updateSumInTree(node->left);
    updateSumInTree(node->right);
    node->sum_num_players=getSumNumPlayers(node->left)+getSumNumPlayers(node->right)+node->data.getThisNumPlayers();
    updateScaleArr(node,node->left,node->right);
    node->level_sum_players=(node->data.getNumLevel())*(node->data.getThisNumPlayers())+getLevelSumPlayers(node->right)+getLevelSumPlayers(node->left);
}


void AVLLevelTree::mergeTrees(const AVLLevelTree& tree)
{
    int size1 = this->tree_size;
    int size2 = tree.tree_size;
    int new_size=0;
    this->root=mergeTreesNode(this->root, tree.root, size1, size2, &new_size);
    this->max = getMax(this->root);
    this->tree_size = new_size;
    updateSumInTree(this->root); 
}

void AVLLevelTree::updatePlayerRemove(int level, int score)
{
    LevelInfo tmp_lvl_info(level);
    LevelInfo lvl_data = findData(tmp_lvl_info);
    //if there is more then one player, so i dont need to delete the node.
    if (lvl_data.getThisNumPlayers()>1)
    {
        updateTreeAfterRemove(root,lvl_data,score);
    }
    else
    {
        //we need to delete all the node.
        this->remove(tmp_lvl_info);
    }
}


void AVLLevelTree::updateTreeAfterRemove(AVLLevelTree::Node* node, LevelInfo& data, int score)
{
    if(node == nullptr)
    {
        return;
    }
    else if(data < node->data)
    {
        updateTreeAfterRemove(node->left, data, score);
    }
    else if(node->data < data)
    {
        updateTreeAfterRemove(node->right, data, score);
    }
    else
    {
        //if we are here it means it is equal
        node->data.updateScaleArrRemoval(score);
        node->data.updateNumPlayers(-1);
    }
    node->sum_scale[score] = node->sum_scale[score] -1;
    node->sum_num_players = node->sum_num_players -1;
    node->level_sum_players = node->level_sum_players-data.getNumLevel();
}

void AVLLevelTree::updatePlayerNewScore(int level, int old_score, int new_score)
{
    LevelInfo tmp_lvl_info(level);
    LevelInfo lvl_data = findData(tmp_lvl_info);
    updateTreeAfteNewScore(root,lvl_data, old_score, new_score);
}

void AVLLevelTree::updateTreeAfteNewScore(AVLLevelTree::Node* node, LevelInfo& data, int old_score, int new_score)
{
    if(node == nullptr)
    {
        return;
    }
    else if(data < node->data)
    {
        updateTreeAfteNewScore(node->left, data, old_score, new_score);
    }
    else if(node->data < data)
    {
        updateTreeAfteNewScore(node->right, data, old_score, new_score);
    }
    //if we are here it means it is equal
    else
    {
        node->data.updateScaleArrNewScore(old_score,new_score);
    }
    node->sum_scale[old_score] = node->sum_scale[old_score] -1;
    node->sum_scale[new_score] = node->sum_scale[new_score] +1;
}

void AVLLevelTree::updatePlayerNewLevel(int score, int old_level, int new_level, int arr_size)
{
    if (old_level != 0)
    {
        LevelInfo tmp_old_lvl_info(old_level);
        LevelInfo tmp_data = findData(tmp_old_lvl_info);
        //if there is one player, so we need to delete the node.
        if (tmp_data.getThisNumPlayers()==1)
        {
            this->remove(tmp_old_lvl_info);
        }
        else
        {
            //update all the levels
            updateTreeAfteNewLevel(root,tmp_old_lvl_info,score,-1);
        }
    }

    //now update the new level
    LevelInfo tmp_new_lvl_info(new_level);
    //if the new level node exists
    if (IsExists(tmp_new_lvl_info))
    {
        updateTreeAfteNewLevel(root,tmp_new_lvl_info,score,1);
    }
    else
    {
        //if we need to create new level node
        LevelInfo tmp_new_lvl_info_2(new_level,arr_size);
        tmp_new_lvl_info_2.updateScaleArrNewScore(0,score);
        tmp_new_lvl_info_2.updateNumPlayers(1);
        insert(tmp_new_lvl_info_2);   
    }
}

void AVLLevelTree::updateTreeAfteNewLevel(Node* node, LevelInfo& data, int score, int num)
{
    if(node == nullptr)
    {
        return;
    }
    else if(data < node->data)
    {
        updateTreeAfteNewLevel(node->left, data, score, num);
    }
    else if(node->data < data)
    {
        updateTreeAfteNewLevel(node->right, data, score, num);
    }
    //if we are here it means it is equal
    else
    {
        node->data.updateScaleArrNewLevel(num,score);
        node->data.updateNumPlayers(num);
    }
    node->sum_scale[score] = node->sum_scale[score] + num;
    node->sum_num_players = node->sum_num_players + num;
    node->level_sum_players = node->level_sum_players + num*(data.getNumLevel());
}

int AVLLevelTree::getSumofPlayersInLevelRangeTree(Node* node,int level) const
{
    if(node == nullptr)
    {
        return 0;
    }
    int sum_of_players = 0;
    if(level < node->data.getNumLevel())
    {
        sum_of_players = sum_of_players + getSumofPlayersInLevelRangeTree(node->left,level);
        return sum_of_players;
    }
    else
    {
        sum_of_players=sum_of_players+node->data.getThisNumPlayers();
        if(node->left != nullptr)
        {
            sum_of_players=sum_of_players+node->left->sum_num_players;
        }
        sum_of_players = sum_of_players + getSumofPlayersInLevelRangeTree(node->right,level);
        return sum_of_players;
    } 
}

int AVLLevelTree::getSumofPlayersInLevelRange(int level) const
{
    return getSumofPlayersInLevelRangeTree(this->root,level);
}

int AVLLevelTree::getSumofPlayersEqualToScoreTree(Node* node,int level,int score)const
{
    if(node == nullptr)
    {
        return 0;
    }
    int players_equal_score = 0;
    if(level < node->data.getNumLevel())
    {
        players_equal_score = players_equal_score + getSumofPlayersEqualToScoreTree(node->left,level,score);
        return players_equal_score;
    }
    else
    {
        players_equal_score = players_equal_score+node->data.getPlayersInScore(score);
        if(node->left != nullptr)
        {
            players_equal_score=players_equal_score+node->left->sum_scale[score];
        }
        players_equal_score=players_equal_score+getSumofPlayersEqualToScoreTree(node->right,level,score);
        return players_equal_score;
    }
}

 int AVLLevelTree::getSumofPlayersEqualToScore(int level,int score) const
 {
     return getSumofPlayersEqualToScoreTree(this->root,level,score);
 }

void AVLLevelTree::averageHighestLevel(int m, double * level)
{
    *level = 0;
    int tmp =m;
    RecurAverageHighestLevel(root,&tmp,level);
}

int AVLLevelTree::getNumOfPlayersInTree() const
{
    return getSumNumPlayers(root);
}

int AVLLevelTree::getLevelSumPlayersInTree() const
{
    return getLevelSumPlayers(root);
}

//new function


void AVLLevelTree::RecurAverageHighestLevel(Node* node, int* counter, double * level)
{
    if(*counter == 0 || node == nullptr)
    {
        return;
    }
    if(node->right != nullptr)
    {
            if (*counter >= getSumNumPlayers(node->right) && *counter <= (getSumNumPlayers(node->right)+node->data.getThisNumPlayers()))
            {
                *level = *level + getLevelSumPlayers(node->right);
                *counter = *counter - node->right->sum_num_players;
                *level = *level + (*counter)*(node->data.getNumLevel());
                *counter = 0;
            }
            else if (*counter < getSumNumPlayers(node->right))
            {
                RecurAverageHighestLevel(node->right,counter,level);
            }
            else
            {
                *level = *level + getLevelSumPlayers(node->right);
                *level = *level + node->data.getThisNumPlayers()*(node->data.getNumLevel());
                *counter = *counter - node->data.getThisNumPlayers() - node->right->sum_num_players;
                RecurAverageHighestLevel(node->left,counter,level);
            }
    } 
    else
    {
        if (node->data.getThisNumPlayers() >= *counter)
        {
            *level = *level + (*counter)*(node->data.getNumLevel());
            *counter = 0;
        }
        else
        {
            *level = *level + node->data.getThisNumPlayers()*(node->data.getNumLevel());
            *counter = *counter - node->data.getThisNumPlayers();
            RecurAverageHighestLevel(node->left,counter,level);
        } 
    }
}

typename AVLLevelTree::Node* AVLLevelTree::getRoot() const
{
    if(this->root == nullptr)
    {
        return nullptr;
    }
    return this->root;
}
