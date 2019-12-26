#pragma once

#include <utility>

namespace resta_um {

using position_t = std::pair<int, int>;

inline int getX(position_t p) { return p.first; }
inline int getY(position_t p) { return p.second; }

enum class position_state
{
    not_used,
    empty,
    piece
};

} // namespace resta_um
