#pragma once

#include "actions.hpp"
#include "common.hpp"

#include <immer/array.hpp>

namespace resta_um {

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
