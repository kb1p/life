#include "lifeboard.h"

#include <cstdlib>
#include <ctime>
#include <cstring>

void LifeBoard::init(int width, int height, float dens)
{
    assert(width > 0);
    assert(height > 0);
    assert(dens >= 0.0f && dens <= 1.0f);

    m_width = width;
    m_height = height;
    m_data.reset(new int[width * height * 2]);

    std::srand(std::time(nullptr));

    const auto sz = width * height;
    for (int i = 0; i < sz; i++)
    {
        if (static_cast<float>(std::rand()) / RAND_MAX <= dens)
            m_data[i] = 1;
        else
            m_data[i] = EMPTY_CELL;
    }
}

void LifeBoard::update()
{
    // Offset to the next generation data
    const auto off = m_width * m_height;

    // Calculate next generation
    for (int x = 0; x < m_width; x++)
        for (int y = 0; y < m_height; y++)
        {
            const int xm1 = (x + m_width - 1) % m_width,
                      ym1 = (y + m_height - 1) % m_height,
                      xp1 = (x + 1) % m_width,
                      yp1 = (y + 1) % m_height;
            const int c = cell(x, y);
            const int n[8] = {
                cell(xm1, ym1),
                cell(xm1, y),
                cell(xm1, yp1),
                cell(x, ym1),
                cell(x, yp1),
                cell(xp1, ym1),
                cell(xp1, y),
                cell(xp1, yp1)
            };

            int nn = 0;
            for (int i = 0; i < 8; i++)
                if (n[i] != EMPTY_CELL)
                    nn++;

            auto &out = m_data[off + index(x, y)];
            if (nn == 3)
                out = 1;
            else if (nn != 2 || c == EMPTY_CELL)
                out = EMPTY_CELL;
        }

    // Copy next to the field
    std::memcpy(m_data.get(), m_data.get() + off, off * sizeof(int));
}

std::array<uint8_t, 3> LifeBoard::color(int p) const noexcept
{
    (void)p;

    // For now we support only 1 player
    return { 0xFFu, 0u, 0u };
}
