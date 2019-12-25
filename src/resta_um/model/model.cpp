#include "model.hpp"

#include <zug/util.hpp>

#include <lager/util.hpp>

#include <boost/config.hpp>
#include <boost/variant.hpp>

#include <algorithm>

namespace resta_um {

constexpr int width{7};
constexpr int height{7};
const app_model initialApp   {{{{position_state::not_used, position_state::not_used, position_state::piece, position_state::piece, position_state::piece, position_state::not_used, position_state::not_used},
                                {position_state::not_used, position_state::not_used, position_state::piece, position_state::piece, position_state::piece, position_state::not_used, position_state::not_used},
                                {position_state::piece,    position_state::piece   , position_state::piece, position_state::piece, position_state::piece, position_state::piece   , position_state::piece   },
                                {position_state::piece,    position_state::piece   , position_state::piece, position_state::empty, position_state::piece, position_state::piece   , position_state::piece   },
                                {position_state::piece,    position_state::piece   , position_state::piece, position_state::piece, position_state::piece, position_state::piece   , position_state::piece   },
                                {position_state::not_used, position_state::not_used, position_state::piece, position_state::piece, position_state::piece, position_state::not_used, position_state::not_used},
                                {position_state::not_used, position_state::not_used, position_state::piece, position_state::piece, position_state::piece, position_state::not_used, position_state::not_used}}}};

namespace {

app_model setBoard(app_model b, int x, int y, position_state s)
{
    b.game.board = std::move(b.game.board.set(x, b.game.board[x].set(y, s)));
    return b;
}


app_model movePieceLeft(app_model m, position_t p)
{
    const auto x = getX(p);
    const auto y = getY(p);

    if(x >= width || y >= height)
        return m;

    if(m.game.board[x][y] != position_state::piece)
        return m;

    if(x < 2 || m.game.board[x - 1][y] != position_state::piece || m.game.board[x - 2][y] != position_state::empty)
        return m;

    return setBoard(setBoard(m, x - 2, y, position_state::piece), x, y, position_state::empty);
}

app_model movePieceRight(app_model m, position_t p)
{
    const auto x = getX(p);
    const auto y = getY(p);

    if(x >= width || y >= height)
        return m;

    if(m.game.board[x][y] != position_state::piece)
        return m;

    if(x >= width - 2 || m.game.board[x + 1][y] != position_state::piece || m.game.board[x + 2][y] != position_state::empty)
        return m;

    return setBoard(setBoard(m, x + 2, y, position_state::piece), x, y, position_state::empty);
}

app_model movePieceUp(app_model m, position_t p)
{
    const auto x = getX(p);
    const auto y = getY(p);

    if(x >= width || y >= height)
        return m;

    if(m.game.board[x][y] != position_state::piece)
        return m;

    if(y < 2 || m.game.board[x][y - 1] != position_state::piece || m.game.board[x][y - 2] != position_state::empty)
        return m;

    return setBoard(setBoard(m, x, y - 2, position_state::piece), x, y, position_state::empty);
}

app_model movePieceDown(app_model m, position_t p)
{
    const auto x = getX(p);
    const auto y = getY(p);

    if(x >= width || y >= height)
        return m;

    if(m.game.board[x][y] != position_state::piece)
        return m;

    if(y >= height - 2 || m.game.board[x][y + 1] != position_state::piece || m.game.board[x][y + 2] != position_state::empty)
        return m;

    return setBoard(setBoard(m, x, y + 2, position_state::piece), x, y, position_state::empty);
}

}

app_model make_initial()
{
    return initialApp;
}

app_model update(app_model m, action_t action)
{
    return boost::apply_visitor(
        lager::visitor{
            [&](move_left a) {
                return movePieceLeft(m, a.position);
            },
            [&](move_right a) {
                return movePieceRight(m, a.position);
            },
            [&](move_up a) {
                return movePieceUp(m, a.position);
            },
            [&](move_down a) {
                return movePieceDown(m, a.position);
            },
            [&](reset) {
                return m;
            }},
        action);
}

} // namespace sn