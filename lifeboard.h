#ifndef LIFEBOARD_H
#define LIFEBOARD_H

#include "tiled_array.h"
#include <array>
#include <cstdint>
#include <cassert>

/**
 * @todo write docs
 */
class LifeBoard
{
    tiled_array_2d<int, 4> m_curGen,
                           m_nextGen;
    int m_width = 0,
        m_height = 0;

public:
    static const int EMPTY_CELL = 0;

    // Init with random layout
    void init(int width, int height, float dens = 0.3f);

    int width() const noexcept
    {
        return m_width;
    }

    int height() const noexcept
    {
        return m_height;
    }

    int cell(int r, int c) const noexcept
    {
        assert(c < m_width);
        assert(r < m_height);
        return m_curGen.at(c, r);
    }

    void update();

    std::array<uint8_t, 3> color(int p) const noexcept;
};

#endif // LIFEBOARD_H
