#pragma once

#include "../model/actions.hpp"
#include "../model/common.hpp"
#include "../model/model.hpp"


#include <lager/context.hpp>

#include <QAbstractListModel>
#include <QObject>
#include <QPoint>

namespace resta_um {

class Board : public QAbstractListModel
{
    Q_OBJECT

public:
    Board(QObject* parent);

    void setModel(board_t board);

    int rowCount(const QModelIndex& = QModelIndex()) const override;
    QVariant data(const QModelIndex& index,
                  int = Qt::DisplayRole) const override;

    Q_INVOKABLE QVariant get(int index) const;

private:
    board_t m_data;
};

class Game : public QObject
{
    Q_OBJECT

public:
    using context_t = lager::context<action_t>;

    Game(context_t context);

    Q_PROPERTY(int width MEMBER m_width CONSTANT)
    Q_PROPERTY(int height MEMBER m_height CONSTANT)

    Q_PROPERTY(Board* board MEMBER m_board CONSTANT)

    Q_INVOKABLE void left(int x, int y);
    Q_INVOKABLE void right(int x, int y);
    Q_INVOKABLE void up(int x, int y);
    Q_INVOKABLE void down(int x, int y);
    // Q_INVOKABLE void reset();

    void setModel(game_model game);

private:
    context_t m_context;

    Board* m_board;

    static constexpr int m_width{game_model::width};
    static constexpr int m_height{game_model::height};
};

} // namespace resta_um

