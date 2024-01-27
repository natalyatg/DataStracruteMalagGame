#include "GroupInfo.h"

//constructor
GroupInfo::GroupInfo(int arr_size):  
    num_of_groups(1),
    arr_size(arr_size),
    scale_level_0(new int[arr_size]),
    level_tree()
    {
        for (int i = 0; i < arr_size; i++)
        {
            scale_level_0[i]=0;
        }  
    }

GroupInfo::~GroupInfo()
{
    delete[] this->scale_level_0;

}

//copy constructor
GroupInfo::GroupInfo(const GroupInfo& group_info):
    num_of_groups(group_info.num_of_groups),
    arr_size(group_info.arr_size),
    scale_level_0(new int[group_info.arr_size]),
    level_tree(group_info.level_tree)
    {
        for (int i = 0; i < arr_size; i++)
        {
            scale_level_0[i]=group_info.scale_level_0[i];
        }  
    }

GroupInfo& GroupInfo::operator=(const GroupInfo& group_info)
{
    if(this == &group_info)
    {
        return *this;
    }
    delete[] scale_level_0;
    num_of_groups = group_info.num_of_groups;
    arr_size = group_info.arr_size;
    scale_level_0 = new int[group_info.arr_size];
    level_tree = group_info.level_tree;
    for (int i = 0; i < group_info.arr_size; i++)
    {
        scale_level_0[i] = group_info.scale_level_0[i];
    } 
    
    return *this;
}

void GroupInfo::mergeGroupInfo(const GroupInfo& group_info)
{
    this->num_of_groups=this->num_of_groups+group_info.num_of_groups;
    for (int i = 1; i < this->arr_size; i++)
    {
        this->scale_level_0[i]=this->scale_level_0[i]+group_info.scale_level_0[i];
    }
    this->level_tree.mergeTrees(group_info.level_tree);
}

int GroupInfo::getNumOfGroups()
{
    return this->num_of_groups;
}

void GroupInfo::UpdateScaleArrAddOne(int score)
{
    this->scale_level_0[score]=this->scale_level_0[score]+1;
}

void GroupInfo::UpdateScaleArrRemoveOne(int score)
{
    this->scale_level_0[score]= this->scale_level_0[score]-1;
}

void GroupInfo::UpdateLevelTree(int level, int score)
{
    this->level_tree.updatePlayerRemove(level,score);
}

void GroupInfo::UpdateNewScore(int old_score, int new_score)
{
    this->scale_level_0[old_score]=this->scale_level_0[old_score]-1;
    this->scale_level_0[new_score]=this->scale_level_0[new_score]+1;
}

void GroupInfo::UpdateNewScoreLevelInfo(int level,int old_score, int new_score)
{
    this->level_tree.updatePlayerNewScore(level,old_score,new_score);
}

void GroupInfo::UpdateLevelIncreaseLevelInfo(int player_score,int old_level, int new_level, int scale)
{
    this->level_tree.updatePlayerNewLevel(player_score,old_level,new_level,scale);
}

double GroupInfo::GetPercentOfPlayer(int score, int lowerLevel, int higherLevel) const
{
    if(lowerLevel == 0)
    {
        int players_in_level_0 = 0;
        int players_equal_score_level_0=0;
        for (int i = 0; i < arr_size; i++)
        {
            players_in_level_0 = players_in_level_0+scale_level_0[i];
        }
        players_equal_score_level_0 = this->scale_level_0[score];
        int players_higher_level=players_in_level_0 +this->level_tree.getSumofPlayersInLevelRange(higherLevel);
        if (players_higher_level == 0)
        {
            return -1;
        }
        int players_equal_score_higher =players_equal_score_level_0 +this->level_tree.getSumofPlayersEqualToScore(higherLevel,score);
        double percent = (double)(players_equal_score_higher)/(double)players_higher_level;
        percent = percent*100;
        return percent;
    }
    else
    {
        int players_in_range = this->level_tree.getSumofPlayersInLevelRange(higherLevel)- this->level_tree.getSumofPlayersInLevelRange(lowerLevel-1);
        if(players_in_range <= 0)
        {
            return -1;
        }

        int players_equal_score = this->level_tree.getSumofPlayersEqualToScore(higherLevel,score)-this->level_tree.getSumofPlayersEqualToScore(lowerLevel-1,score);
        double percent = (double)(players_equal_score)/(double)players_in_range;
        percent = percent*100;
        return percent;
    }

}

double GroupInfo::AverageHighestPlayerLevel(int m)
{
    int num_players = level_tree.getNumOfPlayersInTree();
    for (int i = 0; i < arr_size; i++)
    {
        num_players = num_players+scale_level_0[i];
    }
    if (m > num_players)
    {
        return -1;
    }
        
    if (m > this->level_tree.getNumOfPlayersInTree())
    {
        double tmp = level_tree.getLevelSumPlayersInTree();
        return tmp;
    }
    double tmp;
    level_tree.averageHighestLevel(m,&tmp);
    return tmp;
}

