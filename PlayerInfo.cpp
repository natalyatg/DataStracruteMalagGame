#include "PlayerInfo.h"

//constructor
PlayerInfo::PlayerInfo(int player_id, int group_id, int level, int scale):
    player_id(player_id),
    group_id(group_id),
    level(0),
    scale(scale){}

// I added the constructor without the parameters because there was a problem when creating the node on the avl tree
PlayerInfo::PlayerInfo():
    player_id(0),
    group_id(0),
    level(0),
    scale(0)
    {}


bool PlayerInfo::operator<(const PlayerInfo& playerInfo) const
{
     return this->player_id < playerInfo.player_id;
}


bool PlayerInfo::operator==(const PlayerInfo& playerInfo) const
{
    if(this->player_id == playerInfo.player_id)
    {
        return true;
    }
    else
    {
        return false;
    }
}

int PlayerInfo::operator%(const int num) const
{
    return this->player_id%num;
}

int PlayerInfo::getLevel() const
{
    return this->level;
}

int PlayerInfo::getScale() const
{
    return this->scale;
}

//check if the right way
int PlayerInfo::getGroupId() const
{
    return this->group_id;
}

void PlayerInfo::updateScore(int new_score)
{
    this->scale = new_score;
}

void PlayerInfo::updateLevel(int new_level)
{
    this->level = this->level + new_level;
}