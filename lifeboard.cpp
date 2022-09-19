#include "lifeboard.h"

#include <cstdlib>
#include <ctime>

void LifeBoard::init(int width, int height, float dens)
{
    assert(width > 0);
    assert(height > 0);
    assert(dens >= 0.0f && dens <= 1.0f);

    m_width = width;
    m_height = height;
    m_data.reset(new int[width * height]);

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
}
