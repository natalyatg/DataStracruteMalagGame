#include "UnionFindGroup.h"

UnionFindGroup::UnionFindGroup(int k,int scale):
    k(k),
    scale(scale),
    groups_arr(new Group*[k+1])
    {
        groups_arr[0] = nullptr;
        for (int i = 1; i <= k; i++)
        {
            GroupInfo* group_info = new GroupInfo(scale);
            Group* group = new Group(group_info, i);
            groups_arr[i] = group;
        }  
    }

UnionFindGroup::~UnionFindGroup()
{
    for (int i = 1; i <= k; i++)
    {
        if(groups_arr[i] != nullptr)
        {   
            delete groups_arr[i];//to check if needed
        }  
    }
    delete[] groups_arr;
}

UnionFindGroup::UnionFindGroup(const UnionFindGroup& union_find_group):
    k(union_find_group.k),
    scale(union_find_group.scale),
    groups_arr(new Group*[union_find_group.k+1])
    {
        for (int i = 0; i < k+1; i++)
        {
            groups_arr[i]=union_find_group.groups_arr[i];
        }
        
    }

 UnionFindGroup& UnionFindGroup::operator=(const UnionFindGroup& union_find_group)
 {
    if(this == &union_find_group)
    {
        return *this;
    }
    delete[] groups_arr;
    k=union_find_group.k;
    scale=union_find_group.scale;
    groups_arr=new Group*[union_find_group.k+1];
    for (int i = 0; i < k+1; i++)
    {
        groups_arr[i]=union_find_group.groups_arr[i];
    }

    return *this;

 }

 Group* UnionFindGroup::findGroupHelper(Group* group)
 {
    if(group->getFather() == nullptr)
    {
        return group;
    }
    Group* root = findGroupHelper(group->getFather());
    group->updateFather(root);
    return root;
 }

Group* UnionFindGroup::findGroup(int group)
{
    return findGroupHelper(groups_arr[group]);
}

 void UnionFindGroup::UnionGroups(int group1, int group2)
 {
    if(group1 == group2)
    {
        return;
    }

    Group* group1_ptr = findGroup(group1);
    Group* group2_ptr = findGroup(group2);
    if(group1_ptr->getGroupId() == group2_ptr->getGroupId())
    {
        return;
    }
    
    if (group1_ptr->getGroupInfo()->getNumOfGroups() < group2_ptr->getGroupInfo()->getNumOfGroups())
    {
        group2_ptr->getGroupInfo()->mergeGroupInfo(*group1_ptr->getGroupInfo());
        group1_ptr->updateFather(group2_ptr);
        
    }
    else
    {
        group1_ptr->getGroupInfo()->mergeGroupInfo(*group2_ptr->getGroupInfo());
        group2_ptr->updateFather(group1_ptr);
    }
 }

int UnionFindGroup::GetNumOfGroups() const
{
    return this->k;
}

void UnionFindGroup::UpdateScaleZeroArrAddOne(int num_group,int score)
{
    Group* group_ptr = findGroup(num_group);
    group_ptr->getGroupInfo()->UpdateScaleArrAddOne(score);
}

void UnionFindGroup::UpdateScaleZeroArrRemoveOne(int num_group,int score)
{
    Group* group_ptr = findGroup(num_group);
    group_ptr->getGroupInfo()->UpdateScaleArrRemoveOne(score);
}

void UnionFindGroup::UpdateLevelTreeInfo(int num_group, int level,int score)
{
    Group* group_ptr = findGroup(num_group);
    group_ptr->getGroupInfo()->UpdateLevelTree(level,score);
}

void UnionFindGroup::UpdateNewScoreInfo(int num_group,int old_score,int new_score)
{
    Group* group_ptr = findGroup(num_group);
    group_ptr->getGroupInfo()->UpdateNewScore(old_score,new_score);
}
void UnionFindGroup::UpdateIncreaseLevelInfo(int num_group,int player_score,int old_level, int new_level, int scale)
{
    Group* group_ptr = findGroup(num_group);
    group_ptr->getGroupInfo()->UpdateLevelIncreaseLevelInfo(player_score,old_level,new_level,scale);
}

void UnionFindGroup::UpdateNewScoreLevelTreeInfo(int num_group,int level,int old_score,int new_score)
{
    Group* group_ptr = findGroup(num_group);
    group_ptr->getGroupInfo()->UpdateNewScoreLevelInfo(level, old_score,new_score);
}

double UnionFindGroup::getPrecentGroup(int num_group, int score, int lowerLevel, int higherLevel) 
{
    Group* group_ptr = findGroup(num_group);
    double precent = group_ptr->getGroupInfo()->GetPercentOfPlayer(score, lowerLevel,higherLevel);
    return precent;
}

double UnionFindGroup::AverageHighestPlayerLevel(int GroupID, int m)
{
    Group* group_ptr = findGroup(GroupID);
    double avg = group_ptr->getGroupInfo()->AverageHighestPlayerLevel(m);
    return avg;
}