#ifndef PLAYERSMANAGER_H
#define PLAYERSMANAGER_H

#include "PlayerInfo.h"
#include "hashTable.h"
#include "AVLLevelTree.h"
#include "library2.h"
#include "UnionFindGroup.h"
#include <memory>

class PlayersManager{
private:
    HashTable <PlayerInfo> PlayersTable;
    AVLLevelTree AVL_all_levels;
    UnionFindGroup UF_groups;
    int num_of_players;    
    int scale;
    int *scale_level_0;

public:
    PlayersManager(int k, int scale);
    ~PlayersManager() = default;
    PlayersManager(const PlayersManager& PlayersManager);
    PlayersManager& operator=(const PlayersManager& PlayersManager);

    //given functions
    StatusType MergeGroups(int GroupID1, int GroupID2);
    StatusType AddPlayer(int PlayerID, int GroupID, int score);
    StatusType RemovePlayer(int PlayerID);
    StatusType IncreasePlayerIDLevel(int PlayerID, int LevelIncrease);
    StatusType ChangePlayerIDScore(int PlayerID, int NewScore);
    StatusType GetPercentOfPlayersWithScoreInBounds(int GroupID, int score, int lowerLevel, int higherLevel, 
        double * players);
    StatusType AverageHighestPlayerLevelByGroup(int GroupID, int m, double * level);
    StatusType GetPlayersBound(int GroupID, int score, int m, int * LowerBoundPlayers, int * HigherBoundPlayers);
    void Quit();
};

#endif



