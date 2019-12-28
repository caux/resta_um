#pragma once

#include "actions.hpp"
#include "common.hpp"

#include <immer/array.hpp>

namespace resta_um {

// Row major
using board_t = immer::array<immer::array<position_state>>;

struct game_model
{
    static constexpr int height{7};
    static constexpr int width{7};

    board_t board;
};

struct app_model
{
    game_model game;
};

app_model make_initial();

app_model update(app_model m, action_t action);

} // namespace resta_um
