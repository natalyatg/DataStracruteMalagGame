#ifndef PLAYERINFO_H
#define PLAYERINFO_H

class PlayerInfo{
    
    int player_id;
    int group_id;
    int level;
    int scale;

    public:
    PlayerInfo(int player_id, int group_id, int level, int scale);
    PlayerInfo();
    ~PlayerInfo()=default;
    PlayerInfo(const PlayerInfo& playerInfo)=default;
    PlayerInfo& operator=(const PlayerInfo& playerInfo)=default;
    bool operator<(const PlayerInfo& playerInfo) const;
    bool operator==(const PlayerInfo& playerInfo) const;
    int operator%(const int num) const;
    int getLevel() const;
    int getScale() const;
    int getGroupId() const;
    void updateScore(int new_score);
    void updateLevel(int new_level);
};

#endif