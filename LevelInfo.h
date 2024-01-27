#ifndef LevelInfo_H
#define LevelInfo_H

class LevelInfo{
    
    int num_level;
    int this_num_players;
    int* scale_arr;
    int arr_size;

    public:
    LevelInfo(int num_level, int arr_size);
    LevelInfo(int num_level);
    LevelInfo();
    ~LevelInfo();
    LevelInfo(const LevelInfo& LevelInfo);
    LevelInfo& operator=(const LevelInfo& LevelInfo);
    bool operator<(const LevelInfo& LevelInfo) const;
    bool operator==(const LevelInfo& LevelInfo) const;
    int getArr_size() const;
    int getThisNumPlayers() const;
    int* getScaleArr();
    void mergeTwoLevelInfo(const LevelInfo& LevelInfo);
    void updateScaleArrRemoval(int score);
    void updateScaleArrNewScore(int old_score, int new_score);
    void updateScaleArrNewLevel(int num_to_add, int score);
    void updateNumPlayers(int num);
    int getNumLevel() const;
    int getPlayersInScore(int score)const;
};

#endif