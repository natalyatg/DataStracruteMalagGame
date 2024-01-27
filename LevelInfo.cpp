#include "LevelInfo.h"

//constructor
LevelInfo::LevelInfo(int num_level,int arr_size):
    num_level(num_level),
    this_num_players(0),
    scale_arr(new int[arr_size]),
    arr_size(arr_size){
        for (int i = 0; i < arr_size; i++)
        {
            scale_arr[i] = 0;
        } 
    }

    LevelInfo::LevelInfo(int num_level):
    num_level(num_level),
    this_num_players(0),
    scale_arr(nullptr),
    arr_size(0){}

// I added the constructor without the parameters because there was a problem when creating the node on the avl tree
LevelInfo::LevelInfo():
    num_level(0),
    this_num_players(0),
    scale_arr(nullptr),
    arr_size(0)
    {}

//destructor 
LevelInfo::~LevelInfo()
{
    if (scale_arr != nullptr)
    {
        delete[] scale_arr;
    }
}

//copy constructor
LevelInfo::LevelInfo(const LevelInfo& LevelInfo):
    num_level(LevelInfo.num_level),
    this_num_players(LevelInfo.this_num_players),
    scale_arr(new int[LevelInfo.arr_size]),
    arr_size(LevelInfo.arr_size)
    {
        for (int i = 0; i < arr_size; i++)
        {
            scale_arr[i] = LevelInfo.scale_arr[i];
        } 
    }
#include<stdio.h>

void d_print(int* d, int size){
    printf("\n------------/E----------\n");
    for(int i=0;i<size;i++)
        printf("%d", d[i]);
    printf("\n------------/E----------\n");
}

//operator= 
LevelInfo& LevelInfo::operator=(const LevelInfo& LevelInfo)
{
    if(this == &LevelInfo)
    {
        return *this;
    }
    if (scale_arr != nullptr)
    {
        delete[] scale_arr;
    }

    num_level = LevelInfo.num_level;
    this_num_players = LevelInfo.this_num_players;
    scale_arr = new int[LevelInfo.arr_size];
    arr_size = LevelInfo.arr_size;
    for (int i = 0; i < arr_size; i++)
    {
        scale_arr[i] = LevelInfo.scale_arr[i];
    }

    return *this;
}

bool LevelInfo::operator<(const LevelInfo& LevelInfo) const
{
     return this->num_level < LevelInfo.num_level;
}


bool LevelInfo::operator==(const LevelInfo& LevelInfo) const
{
    if(this->num_level == LevelInfo.num_level)
    {
        return true;
    }
    else
    {
        return false;
    }
}

int LevelInfo::getArr_size() const
{
    return this->arr_size;
}

int LevelInfo::getThisNumPlayers() const
{
    return this->this_num_players;
}

//check if the right way - nataly change - delete const in the end
int* LevelInfo::getScaleArr()
{
    return this->scale_arr;
}

void LevelInfo::mergeTwoLevelInfo(const LevelInfo& LevelInfo)
{
    for (int i = 0; i < this->arr_size; i++)
    {
        this->scale_arr[i]=this->scale_arr[i]+LevelInfo.scale_arr[i];
    }
    this->this_num_players = this->this_num_players+LevelInfo.this_num_players;
    //delete[] LevelInfo.scale_arr;
}

void LevelInfo::updateNumPlayers(int num)
{
    this->this_num_players = this->this_num_players + num;
}

void LevelInfo::updateScaleArrRemoval(int score)
{
    this->scale_arr[score]--;
}

void LevelInfo::updateScaleArrNewScore(int old_score, int new_score)
{
    if (old_score != 0)
    {
        this->scale_arr[old_score] = this->scale_arr[old_score] -1;
    }
    this->scale_arr[new_score] = this->scale_arr[new_score] +1;
}

void LevelInfo::updateScaleArrNewLevel(int num_to_add, int score)
{
    this->scale_arr[score] =  this->scale_arr[score] + num_to_add;
}

int LevelInfo::getNumLevel() const
{
    return this->num_level;
}

int LevelInfo::getPlayersInScore(int score) const
{
    return this->scale_arr[score];
}