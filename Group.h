#ifndef GROUP_H
#define GROUP_H
#include "GroupInfo.h"

class Group{
       
    Group* father;
    GroupInfo* group_info;
    int group_id;

    public:
    Group(GroupInfo* group_info,int group_id);
    Group();
    ~Group();
    Group(const Group& group);
    Group& operator=(const Group& group);
    GroupInfo* getGroupInfo()const;
    void updateFather(Group* father);
    Group* getFather() const;
    int getGroupId() const;
    void UpdateGroupInfo();
};

#endif