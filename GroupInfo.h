#ifndef GROUPOINFO_H
#define GROUPOINFO_H
#include "AVLLevelTree.h"

class GroupInfo{

    int num_of_groups;
    int arr_size;
    int* scale_level_0;
    AVLLevelTree level_tree;
    
    public:
    GroupInfo(int arr_size);
    ~GroupInfo();
    GroupInfo(const GroupInfo& group_info);
    GroupInfo& operator=(const GroupInfo& group_info);
    void mergeGroupInfo(const GroupInfo& group_info);
    int getNumOfGroups();
    void UpdateScaleArrAddOne(int score);
    void UpdateScaleArrRemoveOne(int score);
    void UpdateLevelTree(int level, int score);
    void UpdateNewScore(int old_score, int new_score);
    void UpdateNewScoreLevelInfo(int level,int old_score, int new_score);
    void UpdateLevelIncreaseLevelInfo(int player_score,int old_level, int new_level, int scale);
    double GetPercentOfPlayer(int score, int lowerLevel, int higherLevel) const;
    double AverageHighestPlayerLevel(int m);
    


};

#endif