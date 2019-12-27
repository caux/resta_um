
#include "qmodel.hpp"

namespace resta_um {

namespace {
int fromPositionState(position_state p)
{
    switch(p)
    {
        case position_state::not_used:
            return 0;
        case position_state::empty:
            return 1;
        case position_state::piece:
            return 2;
    }
}
}

Board::Board(QObject* parent)
    : QAbstractListModel(parent)
{}

void Board::setModel(board_t body)
{
    if (m_data != body) {
        beginResetModel();
        m_data = body;
        endResetModel();
    }
}

int Board::rowCount(const QModelIndex&) const
{
    return m_data.empty() ? 0 : m_data.size() * m_data[0].size();
}

QVariant Board::data(const QModelIndex& index, int) const
{
    return get(index.row());
}

Q_INVOKABLE QVariant Board::get(int index) const
{
    const auto boardWidth = m_data.size();
    const auto boardHeight = m_data.empty() ? 0 : m_data[0].size();
    const auto dataSize = boardWidth * boardHeight;

    if (index >= 0 && index < static_cast<int>(dataSize))
        return fromPositionState(m_data[index % boardWidth][index / boardWidth]);

    return {};
}

Game::Game(context_t context)
    : m_context{std::move(context)}, m_board{new Board(this)}
{}

void Game::setModel(game_model game)
{
    m_board->setModel(game.board);
}

Q_INVOKABLE void Game::left(int x, int y)
{
    m_context.dispatch(move_left{{x, y}});
}

Q_INVOKABLE void Game::right(int x, int y)
{
    m_context.dispatch(move_right{{x, y}});
}

Q_INVOKABLE void Game::up(int x, int y)
{
    m_context.dispatch(move_up{{x, y}});
}

Q_INVOKABLE void Game::down(int x, int y)
{
    m_context.dispatch(move_down{{x, y}});
}

// Q_INVOKABLE void Game::reset() { m_context.dispatch(sn::reset{}); }

} // namespace sn
