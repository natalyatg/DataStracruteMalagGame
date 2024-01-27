#include "library2.h"
#include "PlayersManager.h"

void *Init(int k, int scale) {
    PlayersManager *DS = new PlayersManager(k,scale);
    return (void*)DS;
}

StatusType MergeGroups(void *DS, int GroupID1, int GroupID2)
{
    if (DS == NULL || GroupID1 <= 0 || GroupID2<=0)
    {
        return INVALID_INPUT;
    }
    return((PlayersManager*)DS)-> MergeGroups(GroupID1, GroupID2);
}

StatusType AddPlayer(void *DS, int PlayerID, int GroupID, int score)
{
    if (DS == NULL || GroupID <= 0 || PlayerID<=0 || score <= 0)
    {
        return INVALID_INPUT;
    }
    return((PlayersManager*)DS)-> AddPlayer(PlayerID, GroupID, score);
}

StatusType RemovePlayer(void *DS, int PlayerID)
{
    if (DS == NULL || PlayerID<=0)
    {
        return INVALID_INPUT;
    }
    return((PlayersManager*)DS)-> RemovePlayer(PlayerID);
}


StatusType IncreasePlayerIDLevel(void *DS, int PlayerID, int LevelIncrease)
{
    if (DS==NULL || PlayerID <=0 || LevelIncrease <=0)
    {
        return INVALID_INPUT;
    }
    return((PlayersManager*)DS)-> IncreasePlayerIDLevel(PlayerID, LevelIncrease);
}

StatusType ChangePlayerIDScore(void *DS, int PlayerID, int NewScore)
{
    if (DS==NULL || PlayerID <= 0 || NewScore <= 0)
    {
        return INVALID_INPUT;
    }
    return((PlayersManager*)DS)-> ChangePlayerIDScore(PlayerID, NewScore);
}

StatusType GetPlayersBound(void *DS, int GroupID, int score, int m,
                                         int * LowerBoundPlayers, int * HigherBoundPlayers)
{
    return SUCCESS;
}


StatusType GetPercentOfPlayersWithScoreInBounds(void *DS, int GroupID, int score, int lowerLevel, int higherLevel,
                                            double * players)
{
    if(DS == NULL || GroupID < 0 || players == NULL)
    {
        return INVALID_INPUT;
    }
    return((PlayersManager*)DS)-> GetPercentOfPlayersWithScoreInBounds(GroupID, score, lowerLevel, higherLevel, players);
}

StatusType AverageHighestPlayerLevelByGroup(void *DS, int GroupID, int m, double * level)
{
     if(DS == NULL || GroupID < 0 || m <= 0 || level == NULL)
     {
         return INVALID_INPUT;
     }
    return((PlayersManager*)DS)-> AverageHighestPlayerLevelByGroup(GroupID, m, level);
}


void Quit(void** DS)
{
    PlayersManager* pm = (PlayersManager*)*DS;
    (pm)->Quit();
    delete pm;
    *DS = NULL;
}


