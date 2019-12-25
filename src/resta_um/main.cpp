#include "model/model.hpp"

#include <lager/store.hpp>
#include <lager/event_loop/manual.hpp>

#include <iostream>
#include <utility>

using namespace resta_um;

void draw(app_model prev, app_model curr)
{
    for(auto row : curr.game.board)
    {
        for(auto pos : row)
        {
            switch(pos)
            {
                case position_state::not_used:
                    std::cout << " ";
                    break;
                case position_state::empty:
                    std::cout << "O";
                    break;
                case position_state::piece:
                    std::cout << "*";
                    break;
            }
        }
        std::cout << std::endl;
    }
}

int main(int argc, char** argv)
{
    auto initial_state = make_initial();
    auto store         = lager::make_store<action_t>(
        std::move(initial_state), update, lager::with_manual_event_loop{});

    watch(store, draw);
    auto event = char{};
    while (std::cin >> event) {
    }
}
