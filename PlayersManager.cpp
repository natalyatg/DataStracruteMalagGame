#include "PlayersManager.h"
#include "exceptions.h"

PlayersManager::PlayersManager(int k, int scale):
    PlayersTable(), AVL_all_levels(), UF_groups(k,scale+1), num_of_players(0), scale(scale), scale_level_0(new int[scale+1])
    {
        for (int i = 0; i < scale + 1; i++)
        {
            scale_level_0[i] = 0;
        } 
    }

PlayersManager::PlayersManager(const PlayersManager& PlayersManager): 
PlayersTable(PlayersManager.PlayersTable), AVL_all_levels(PlayersManager.AVL_all_levels),
    UF_groups(PlayersManager.UF_groups), num_of_players(PlayersManager.num_of_players), scale(PlayersManager.scale), scale_level_0(new int[PlayersManager.scale])
{
    for (int i = 0; i < PlayersManager.scale; i++)
        {
            scale_level_0[i] = PlayersManager.scale_level_0[i];
        } 
}


PlayersManager& PlayersManager::operator=(const PlayersManager& PlayersManager)
{
    if(this == &PlayersManager)
    {
        return *this;
    }
    this->PlayersTable = PlayersManager.PlayersTable;
    this->AVL_all_levels = PlayersManager.AVL_all_levels;
    this->UF_groups = PlayersManager.UF_groups;
    this->num_of_players = PlayersManager.num_of_players;
    this->scale = PlayersManager.scale;
    delete[] this->scale_level_0;
    this->scale_level_0 = new int[PlayersManager.scale];
    for (int i = 0; i < PlayersManager.scale; i++)
    {
        scale_level_0[i] = PlayersManager.scale_level_0[i];
    } 
    return *this;
}

StatusType PlayersManager::MergeGroups(int GroupID1, int GroupID2)
{
    if (GroupID1 > this->UF_groups.GetNumOfGroups() || GroupID2 > this->UF_groups.GetNumOfGroups())
    {
        return INVALID_INPUT;
    }
    try
    {
        this->UF_groups.UnionGroups(GroupID1,GroupID2);
    }
    catch(const std::bad_alloc& e)
    {
        return ALLOCATION_ERROR;
    }
    return SUCCESS;

}

StatusType PlayersManager::AddPlayer(int PlayerID, int GroupID, int score)
{
    if (GroupID > this->UF_groups.GetNumOfGroups() || score > scale)
    {
        return INVALID_INPUT;
    }
    PlayerInfo new_player = PlayerInfo(PlayerID,GroupID,0,score);
    try
    {
        PlayersTable.insert(new_player);
    }
    catch(DataAlreadyExists &e)
    {
        return FAILURE;
    }
    catch (std::bad_alloc &e) 
    {
        return ALLOCATION_ERROR;
    }
    //if it was successful to this operations:
    this->scale_level_0[score]++;

    //add to the uf here:
    this->UF_groups.UpdateScaleZeroArrAddOne(GroupID,score);
    num_of_players++;
    return SUCCESS;
}

StatusType PlayersManager::RemovePlayer(int PlayerID)
{
    PlayerInfo to_remove_player = PlayerInfo(PlayerID,0,0,0);
    PlayerInfo tmp_player;
    try
    {
        tmp_player = PlayersTable.findData(to_remove_player);
    }
    catch(DataNotExists &e)
    {
        return FAILURE;
    }
    int remove_level = tmp_player.getLevel();
    int remove_scale = tmp_player.getScale();
    int remove_group_id = tmp_player.getGroupId();
    PlayersTable.remove(to_remove_player);
    num_of_players--;

    if (remove_level == 0)
    {
        scale_level_0[remove_scale]--;
        this->UF_groups.UpdateScaleZeroArrRemoveOne(remove_group_id,remove_scale);
    }
    else
    {
        AVL_all_levels.updatePlayerRemove(remove_level,remove_scale);
        this->UF_groups.UpdateLevelTreeInfo(remove_group_id,remove_level,remove_scale);
    }
    return SUCCESS;
}

StatusType PlayersManager::IncreasePlayerIDLevel(int PlayerID, int LevelIncrease)
{
    PlayerInfo to_update_player = PlayerInfo(PlayerID,0,0,0);
    PlayerInfo tmp_player;
    try
    {
        tmp_player = PlayersTable.findData(to_update_player);
    }
    catch(DataNotExists &e)
    {
        return FAILURE;
    }
    //update in the hash
    int old_level = tmp_player.getLevel();
    int player_score = tmp_player.getScale();
    PlayerInfo* playerInfoPtr = PlayersTable.getDataPtr(to_update_player);
    playerInfoPtr->updateLevel(LevelIncrease);

    //now update in the whole system
    //if the old level is 0:
    if (old_level == 0)
    {
        scale_level_0[player_score]--;
        this->UF_groups.UpdateScaleZeroArrRemoveOne(tmp_player.getGroupId(),tmp_player.getScale());
    }
    AVL_all_levels.updatePlayerNewLevel(player_score,old_level,old_level+LevelIncrease,scale+1);
    this->UF_groups.UpdateIncreaseLevelInfo(tmp_player.getGroupId(),player_score,old_level,old_level+LevelIncrease,scale+1);  
    return SUCCESS;
}

StatusType PlayersManager::ChangePlayerIDScore(int PlayerID, int NewScore)
{
    if (NewScore > scale)
    {
        return INVALID_INPUT;
    }
    PlayerInfo to_update_player = PlayerInfo(PlayerID,0,0,0);
    PlayerInfo tmp_player;
    try
    {
        tmp_player = PlayersTable.findData(to_update_player);
    }
    catch(DataNotExists &e)
    {
        return FAILURE;
    }
    int old_score = tmp_player.getScale();
    //update in the hash table the new score
    PlayerInfo* playerInfoPtr = PlayersTable.getDataPtr(to_update_player);
    playerInfoPtr->updateScore(NewScore);
    
    if (tmp_player.getLevel() == 0)
    {
        scale_level_0[old_score]--;
        scale_level_0[NewScore]++;
        this->UF_groups.UpdateNewScoreInfo(tmp_player.getGroupId(),old_score,NewScore);
    }
    else
    {
        AVL_all_levels.updatePlayerNewScore(tmp_player.getLevel(),old_score, NewScore);
        this->UF_groups.UpdateNewScoreLevelTreeInfo(tmp_player.getGroupId(),tmp_player.getLevel(),old_score, NewScore);
    }
    return SUCCESS;
}

StatusType PlayersManager::GetPercentOfPlayersWithScoreInBounds(int GroupID, int score, int lowerLevel, int higherLevel,double * players)
{
    if (GroupID > this->UF_groups.GetNumOfGroups())
    {
    return INVALID_INPUT;
    }    
    //delete after. now for almog test!!!!!
    if (higherLevel < lowerLevel)
    {
        return FAILURE;
    }
    if(GroupID == 0)
    {
        if(lowerLevel == 0)
        {
            int players_in_level_0 = 0;
            int players_equal_score_level_0=0;
            for (int i = 0; i < scale+1; i++)
            {
                players_in_level_0 = players_in_level_0+scale_level_0[i];
            }
            players_equal_score_level_0 = this->scale_level_0[score];
            int players_higher_level=players_in_level_0 +this->AVL_all_levels.getSumofPlayersInLevelRange(higherLevel);
            if (players_higher_level == 0)
            {
                return FAILURE;
            }
            int players_equal_score_higher =players_equal_score_level_0 +this->AVL_all_levels.getSumofPlayersEqualToScore(higherLevel,score);
            double percent = (double)(players_equal_score_higher)/(double)players_higher_level;
            percent = percent*100;
            *players = percent;
            return SUCCESS;
        }
        else
        {
            int players_in_range = this->AVL_all_levels.getSumofPlayersInLevelRange(higherLevel)- this->AVL_all_levels.getSumofPlayersInLevelRange(lowerLevel-1);
            if(players_in_range <= 0)
            {
                return FAILURE;
            }

            int players_equal_score = this->AVL_all_levels.getSumofPlayersEqualToScore(higherLevel,score)-this->AVL_all_levels.getSumofPlayersEqualToScore(lowerLevel-1,score);
            double percent = (double)(players_equal_score)/(double)players_in_range;
            percent = percent*100;
            *players = percent;
            return SUCCESS;
        }
    }
    else
    {
        double percent =  this->UF_groups.getPrecentGroup(GroupID,score, lowerLevel,higherLevel);
        if((int)percent == -1)
        {
            return FAILURE;
        }
        *players = percent;
        return SUCCESS;
    }
}

StatusType PlayersManager::AverageHighestPlayerLevelByGroup(int GroupID, int m, double * level)
{
    if (GroupID > this->UF_groups.GetNumOfGroups())
    {
        return INVALID_INPUT;
    }
    if (GroupID == 0)
    {
        if (m > this->num_of_players)
        {
            return FAILURE;
        }
        
        if (m > this->AVL_all_levels.getNumOfPlayersInTree())
        {
            *level = AVL_all_levels.getLevelSumPlayersInTree();
            *level = (*level)/m;
            return SUCCESS;
        }
        AVL_all_levels.averageHighestLevel(m,level);
        *level = (*level)/m;
        return SUCCESS;
    }
    else
    {
        double avg =  this->UF_groups.AverageHighestPlayerLevel(GroupID,m);
        if((int)avg == -1)
        {
            return FAILURE;
        }
        *level = avg/m;
        return SUCCESS;
    }
}

void PlayersManager::Quit()
{
    this->AVL_all_levels.delete_tree(); 
    delete[]  this->scale_level_0;
}
