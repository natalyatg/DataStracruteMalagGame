#include "Group.h"

Group::Group(GroupInfo* group_info,int group_id):
    father(nullptr),
    group_info(group_info),
    group_id(group_id)
    {}

Group::Group():
    father(nullptr),
    group_info(nullptr),
    group_id(0)
    {}


Group::Group(const Group& group):
    father(group.father),
    group_info(group.group_info),
    group_id(group.group_id)
    {}

Group::~Group()
{
    if(this->group_info != nullptr)
    {
        delete this->group_info;
    }
}

Group& Group::operator=(const Group& group)
{
    if(this == &group)
    {
        return *this;
    }
    father = group.father;
    group_info = group.group_info;
    group_id = group.group_id;

    return *this;
}



GroupInfo* Group::getGroupInfo() const
{
    return this->group_info;
}

void Group::updateFather(Group* new_father)
{
    this->father=new_father;
}

Group* Group::getFather() const
{
    return this->father;
}

int Group::getGroupId() const
{
    return this->group_id;
}

void Group::UpdateGroupInfo()
{
    this->group_info=nullptr;
}