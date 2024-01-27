#ifndef UNIONFINDGROUP_H
#define UNIONFINDGROUP_H
#include "Group.h"


class UnionFindGroup{
    

    int k;
    int scale;
    Group** groups_arr;
    
    public:
    UnionFindGroup(int k,int scale);
    ~UnionFindGroup();
    UnionFindGroup(const UnionFindGroup& union_find_group);
    UnionFindGroup& operator=(const UnionFindGroup& union_find_group);
    Group* findGroupHelper(Group* group);
    Group* findGroup(int group);
    void UnionGroups(int group1, int group2);
    int GetNumOfGroups() const;
    void UpdateScaleZeroArrAddOne(int num_group,int score);
    void UpdateScaleZeroArrRemoveOne(int num_group,int score);
    void UpdateLevelTreeInfo(int num_group,int level,int score);
    void UpdateNewScoreInfo(int num_group,int old_score,int new_score);
    void UpdateIncreaseLevelInfo(int num_group,int player_score,int old_level, int new_level, int scale);
    void UpdateNewScoreLevelTreeInfo(int num_group,int level,int old_score,int new_score);
    double getPrecentGroup(int GroupID, int score, int lowerLevel, int higherLevel);
    double AverageHighestPlayerLevel(int GroupID, int m); 
};

#endif