
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

Q_INVOKABLE QVariant Board::at(int index) const
{
    const auto boardHeight = m_data.size();
    const auto boardWidth = m_data.empty() ? 0 : m_data[0].size();
    const auto dataSize = boardHeight * boardWidth;

    if (index >= 0 && index < static_cast<int>(dataSize))
    {
        auto position = indexToPosition(index);
        return fromPositionState(m_data[position.x()][position.y()]);
    }

    return {};
}

QVariant Board::data(const QModelIndex& index, int) const
{
    return at(index.row());
}

Q_INVOKABLE int Board::positionToIndex(int x, int y) const
{
    return (x * m_data[0].size()) + y;
}

Q_INVOKABLE QPoint Board::indexToPosition(int index) const
{
    const int boardWidth = static_cast<int>(m_data.empty() ? 0 : m_data[0].size());

    return QPoint{index / boardWidth, index % boardWidth};
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
