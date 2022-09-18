#include "lifeboard.h"

void LifeBoard::init(int width, int height)
{
    assert(width > 0);
    assert(height > 0);

    m_width = width;
    m_height = height;
    m_data.reset(new int[width * height]);

    const auto sz = width * height;
    for (int i = 0; i < sz; i++)
        m_data[i] = EMPTY_CELL;

    // test
    m_data[index(0, 0)] = 1;
    m_data[index(50, 50)] = 1;
    m_data[index(99, 99)] = 1;
}

void LifeBoard::update()
{
}
