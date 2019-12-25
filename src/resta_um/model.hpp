#pragma once

#include <immer/array.hpp>
#include <boost/variant/variant.hpp>

#include <cstdlib>
#include <utility>
#include <vector>

namespace resta_um {

using position_t = std::pair<int, int>;

inline int getX(position_t p) { return p.first; }
inline int getY(position_t p) { return p.second; }

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

enum class position_state
{
    not_used,
    empty,
    piece
};

using board_t = immer::array<immer::array<position_state>>;

struct game_model
{
    board_t board;
};

struct app_model
{
    game_model game;
};

app_model make_initial();

app_model update(app_model m, action_t action);

} // namespace resta_um
