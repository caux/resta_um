#include "model/common.hpp"
#include "model/actions.hpp"
#include "model/model.hpp"
#include "qt/qmodel.hpp"

#include <lager/store.hpp>
#include <lager/event_loop/qt.hpp>
#include <lager/store.hpp>

#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include <utility>

using namespace resta_um;

int main(int argc, char** argv)
{
    QApplication app{argc, argv};
    QQmlApplicationEngine engine;

    auto initial_state = make_initial();
    auto store         = lager::make_store<action_t>(
        std::move(initial_state), update, lager::with_qt_event_loop{app});

    Game game{store};
    watch(store,
          [&](auto&& /*old*/, auto&& state) { game.setModel(state.game); });
    game.setModel(store.get().game);

    auto* qmlContext = engine.rootContext();
    qmlContext->setContextProperty(QStringLiteral("game"), &game);

    qRegisterMetaType<Board*>("Board*");

    engine.load(LAGER_RESTA_UM_QML_DIR "/main.qml");

    return app.exec();

}
