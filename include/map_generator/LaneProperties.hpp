#ifndef LANE_PROPERTIES_HPP
#define LANE_PROPERTIES_HPP

#include "GameActivity.hpp"
#include "Lane.hpp"

namespace LaneUtils
{
unsigned int random_range(int l, int r);
}

class LaneProperties
{
public:
    LaneProperties(int map_width, GameActivity::GameLevel level);

    virtual void generate() = 0;
    virtual Lane::Type getType() const = 0;
    virtual void setExternalStatic() const = 0;

protected:
    int m_width;
    GameActivity::GameLevel m_level;
};

#endif
