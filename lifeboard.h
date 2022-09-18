#ifndef LIFEBOARD_H
#define LIFEBOARD_H

#include <memory>
#include <cassert>

/**
 * @todo write docs
 */
class LifeBoard
{
    std::unique_ptr<int[]> m_data;
    int m_width = 0,
        m_height = 0;

public:
    static const int EMPTY_CELL = 0;

    void init(int width, int height);

    int width() const noexcept
    {
        return m_width;
    }

    int height() const noexcept
    {
        return m_height;
    }

    int index(int r, int c) const noexcept
    {
        return r * m_width + c;
    }

    int cell(int r, int c) const noexcept
    {
        assert(c < m_width);
        assert(r < m_height);
        return m_data[index(r, c)];
    }

    void update();
};

#endif // LIFEBOARD_H
