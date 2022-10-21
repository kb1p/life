#include "lifeboard.h"

#include <cstdlib>
#include <ctime>

void LifeBoard::init(int width, int height, float dens)
{
    assert(width > 0);
    assert(height > 0);
    assert(dens >= 0.0f && dens <= 1.0f);

    // Size of the board
    m_width = width;
    m_height = height;

    m_curGen.resize(width, height);
    m_nextGen.resize(width, height);

    std::srand(std::time(nullptr));

    for (int x = 0; x < width; x++)
        for (int y = 0; y < height; y++)
        {
            auto &v = m_curGen.at(x, y);
            if (static_cast<float>(std::rand()) / RAND_MAX <= dens)
                v = 1;
            else
                v = EMPTY_CELL;
        }
}

void LifeBoard::update()
{
    // Calculate next generation
    for (int x = 0; x < m_width; x++)
        for (int y = 0; y < m_height; y++)
        {
            const int xm1 = (x + m_width - 1) % m_width,
                      ym1 = (y + m_height - 1) % m_height,
                      xp1 = (x + 1) % m_width,
                      yp1 = (y + 1) % m_height;
            const int c = cell(y, x);
            const int n[8] = {
                cell(ym1, xm1),
                cell(ym1, x),
                cell(ym1, xp1),
                cell(y, xm1),
                cell(y, xp1),
                cell(yp1, xm1),
                cell(yp1, x),
                cell(yp1, xp1)
            };

            int nn = 0;
            for (int i = 0; i < 8; i++)
                if (n[i] != EMPTY_CELL)
                    nn++;

            auto &out = m_nextGen.at(x, y);
            if (nn == 3)
                out = 1;
            else if (nn != 2 || c == EMPTY_CELL)
                out = EMPTY_CELL;
        }

    // Copy next to the field
    m_curGen.copyFrom(m_nextGen);
}

std::array<uint8_t, 3> LifeBoard::color(int p) const noexcept
{
    (void)p;

    // For now we support only 1 player
    return { 0xFFu, 0u, 0u };
}
