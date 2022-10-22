#ifndef TILED_ARRAY_H
#define TILED_ARRAY_H

#include <memory>
#include <cstring>
#include <cassert>

template <typename T, size_t TILE_SIZE>
class tiled_array_2d
{
public:
    using value_type = T;
    using size_type = size_t;

    class accessor final
    {
        tiled_array_2d &m_arr;
        const size_type m_x;

    public:
        accessor(tiled_array_2d &arr, const size_type x) noexcept:
            m_arr { arr },
            m_x { x }
        {
        }

        value_type &operator[](const size_type r) noexcept
        {
            return m_arr.m_data[m_arr.index(m_x, r)];
        }
    };

    class const_accessor final
    {
        const tiled_array_2d &m_arr;
        const size_type m_x;

    public:
        const_accessor(const tiled_array_2d &arr, const size_type x) noexcept:
            m_arr { arr },
            m_x { x }
        {
        }

        const value_type &operator[](const size_type r) const noexcept
        {
            return m_arr.m_data[m_arr.index(m_x, r)];
        }
    };

    tiled_array_2d() = default;

    tiled_array_2d(size_type reqWidth, size_type reqHeight)
    {
        resize(reqWidth, reqHeight);
    }

    void resize(size_type reqWidth, size_type reqHeight)
    {
        // Padding may change the final width / height values
        m_width = (reqWidth / TILE_SIZE + (reqWidth % TILE_SIZE > 0u ? 1u : 0u)) * TILE_SIZE;
        m_height = (reqHeight / TILE_SIZE + (reqHeight % TILE_SIZE > 0u ? 1u : 0u)) * TILE_SIZE;

        m_data.reset(new value_type[m_width * m_height]);
        m_indX.reset(new size_type[m_width]);
        m_indY.reset(new size_type[m_height]);

        constexpr int TS2 = TILE_SIZE * TILE_SIZE;
        for (int x = 0; x < m_width; x++)
            m_indX[x] = TS2 * (x / TILE_SIZE) + x % TILE_SIZE;
        for (int y = 0; y < m_height; y++)
            m_indY[y] = TS2 * (m_width / TILE_SIZE) * (y / TILE_SIZE) + (y % TILE_SIZE) * TILE_SIZE;
    }

    size_type width() const noexcept
    {
        return m_width;
    }

    size_type height() const noexcept
    {
        return m_height;
    }

    value_type &at(const size_type x, const size_type y) noexcept
    {
        return m_data[index(x, y)];
    }

    accessor operator[](const size_type x) noexcept
    {
        return { *this, x };
    }

    const_accessor operator[](const size_type x) const noexcept
    {
        return { *this, x };
    }

    const value_type &at(const size_type x, const size_type y) const noexcept
    {
        return m_data[index(x, y)];
    }

    void swap(tiled_array_2d &other)
    {
        std::swap(m_data, other.m_data);
        std::swap(m_indX, other.m_indX);
        std::swap(m_indY, other.m_indY);
        std::swap(m_width, other.m_width);
        std::swap(m_height, other.m_height);
    }

    void copyFrom(const tiled_array_2d &other)
    {
        if (m_width != other.m_width || m_height != other.m_height)
            resize(other.m_width, other.m_height);

        std::memcpy(m_data.get(), other.m_data.get(), m_width * m_height * sizeof(value_type));
    }

protected:
    size_type index(const size_type x, const size_type y) const noexcept
    {
        assert(!!m_indX && !!m_indY);
        assert(y >= 0u && y < m_height);
        assert(x >= 0u && x < m_width);

        return m_indX[x] + m_indY[y];
    }

private:
    size_type m_width = 0,
              m_height = 0;
    std::unique_ptr<value_type[]> m_data;
    std::unique_ptr<size_type[]> m_indX,
                                 m_indY;
};

#endif
