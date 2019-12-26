#pragma once

#include "common.hpp"

#include <boost/variant/variant.hpp>

namespace resta_um {

struct move_left
{
    position_t position;
};

struct move_right
{
    position_t position;
};

struct move_up
{
    position_t position;
};

struct move_down
{
    position_t position;
};

struct reset
{};
using action_t = boost::variant<move_left, move_right, move_up, move_down, reset>;

} // namespace resta_um
