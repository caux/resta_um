#include "actions.hpp"
#include "model.hpp"
#include "common.hpp"

#include <zug/util.hpp>

#include <lager/util.hpp>

#include <boost/config.hpp>
#include <boost/variant.hpp>

#include <algorithm>

namespace resta_um {

const app_model initialApp   {{{{position_state::not_used, position_state::not_used, position_state::piece, position_state::piece, position_state::piece, position_state::not_used, position_state::not_used},
                                {position_state::not_used, position_state::not_used, position_state::piece, position_state::piece, position_state::piece, position_state::not_used, position_state::not_used},
                                {position_state::piece,    position_state::piece   , position_state::piece, position_state::piece, position_state::piece, position_state::piece   , position_state::piece   },
                                {position_state::piece,    position_state::piece   , position_state::piece, position_state::empty, position_state::piece, position_state::piece   , position_state::piece   },
                                {position_state::piece,    position_state::piece   , position_state::piece, position_state::piece, position_state::piece, position_state::piece   , position_state::piece   },
                                {position_state::not_used, position_state::not_used, position_state::piece, position_state::piece, position_state::piece, position_state::not_used, position_state::not_used},
                                {position_state::not_used, position_state::not_used, position_state::piece, position_state::piece, position_state::piece, position_state::not_used, position_state::not_used}}}};

namespace {

board_t setBoard(board_t b, int x, int y, position_state s)
{
    return std::move(b).set(x, std::move(b[x]).set(y, s));
}


app_model movePieceLeft(app_model m, position_t p)
{
    const auto x = getX(p);
    const auto y = getY(p);

    if(x >= m.game.width || y >= m.game.height)
        return m;

    if(m.game.board[x][y] != position_state::piece)
        return m;

    if(x < 2 || m.game.board[x - 1][y] != position_state::piece || m.game.board[x - 2][y] != position_state::empty)
        return m;

    m.game.board = setBoard(std::move(m.game.board), x - 2, y, position_state::piece);
    m.game.board = setBoard(std::move(m.game.board), x - 1, y, position_state::empty);
    m.game.board = setBoard(std::move(m.game.board), x, y, position_state::empty);
    return m;
}

app_model movePieceRight(app_model m, position_t p)
{
    const auto x = getX(p);
    const auto y = getY(p);

    if(x >= m.game.width || y >= m.game.height)
        return m;

    if(m.game.board[x][y] != position_state::piece)
        return m;

    if(x >= m.game.width - 2 || m.game.board[x + 1][y] != position_state::piece || m.game.board[x + 2][y] != position_state::empty)
        return m;

    m.game.board = setBoard(std::move(m.game.board), x + 2, y, position_state::piece);
    m.game.board = setBoard(std::move(m.game.board), x + 1, y, position_state::empty);
    m.game.board = setBoard(std::move(m.game.board), x, y, position_state::empty);
    return m;
}

app_model movePieceUp(app_model m, position_t p)
{
    const auto x = getX(p);
    const auto y = getY(p);

    if(x >= m.game.width || y >= m.game.height)
        return m;

    if(m.game.board[x][y] != position_state::piece)
        return m;

    if(y < 2 || m.game.board[x][y - 1] != position_state::piece || m.game.board[x][y - 2] != position_state::empty)
        return m;

    m.game.board = setBoard(std::move(m.game.board), x, y - 2, position_state::piece);
    m.game.board = setBoard(std::move(m.game.board), x, y - 1, position_state::empty);
    m.game.board = setBoard(std::move(m.game.board), x, y, position_state::empty);
    return m;
}

app_model movePieceDown(app_model m, position_t p)
{
    const auto x = getX(p);
    const auto y = getY(p);

    if(x >= m.game.width || y >= m.game.height)
        return m;

    if(m.game.board[x][y] != position_state::piece)
        return m;

    if(y >= m.game.height - 2 || m.game.board[x][y + 1] != position_state::piece || m.game.board[x][y + 2] != position_state::empty)
        return m;

    m.game.board = setBoard(std::move(m.game.board), x, y + 2, position_state::piece);
    m.game.board = setBoard(std::move(m.game.board), x, y + 1, position_state::empty);
    m.game.board = setBoard(std::move(m.game.board), x, y, position_state::empty);
    return m;
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
                return make_initial();
            }},
        action);
}

} // namespace sn