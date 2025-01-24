#pragma once

#include <cstddef>
#include <initializer_list>
#include <iterator>
#include <algorithm>
#include <stdexcept>

namespace ppp
{
    template <typename T>
    class BoxArray;

    template <typename T>
    class BoxArray
    {
    protected:
        size_t _size;
        T *_data;

    public:
        BoxArray(const size_t &size = 0);
        BoxArray(const size_t &size, const T &t);
        BoxArray(std::initializer_list<T> init);
        BoxArray(const BoxArray &) = default;
        BoxArray(BoxArray &&) noexcept = default;
        BoxArray &operator=(const BoxArray &) = default;
        BoxArray &operator=(BoxArray &&) noexcept = default;
        ~BoxArray();

        virtual T *begin() noexcept;
        virtual const T *begin() const noexcept;
        virtual T *end() noexcept;
        virtual const T *end() const noexcept;
        std::reverse_iterator<T *> rbegin() noexcept;
        std::reverse_iterator<const T *> rbegin() const noexcept;
        std::reverse_iterator<T *> rend() noexcept;
        std::reverse_iterator<const T *> rend() const noexcept;
        const T *cbegin() const noexcept;
        const T *cend() const noexcept;
        std::reverse_iterator<const T *> crbegin() const noexcept;
        std::reverse_iterator<const T *> crend() const noexcept;

        size_t size() const noexcept;
        void resize(size_t new_size = SIZE_MAX);

        virtual T &operator[](const size_t &index) noexcept;
        virtual const T &operator[](const size_t &index) const noexcept;
        virtual T &at(const size_t &index);
        virtual const T &at(const size_t &index) const;
        virtual T &front();
        virtual const T &front() const;
        virtual T &back();
        virtual const T &back() const;
        T *data() noexcept;
        const T *data() const noexcept;

        void fill(const T &t) noexcept;
    };

    template <typename T>
    BoxArray<T>::BoxArray(const size_t &size)
        : _size(size), _data(new T[size]) {}

    template <typename T>
    BoxArray<T>::BoxArray(const size_t &size, const T &t)
        : _size(size), _data(new T[size])
    {
        std::fill(_data, _data + _size, t);
    }

    template <typename T>
    BoxArray<T>::BoxArray(std::initializer_list<T> init)
        : _size(init.size()), _data(new T[init.size()])
    {
        std::copy(init.begin(), init.end(), _data);
    }

    template <typename T>
    BoxArray<T>::BoxArray::~BoxArray()
    {
        delete[] _data;
    }

    template <typename T>
    T *BoxArray<T>::begin() noexcept
    {
        return _data;
    }

    template <typename T>
    const T *BoxArray<T>::begin() const noexcept
    {
        return _data;
    }

    template <typename T>
    T *BoxArray<T>::end() noexcept
    {
        return _data + _size;
    }

    template <typename T>
    const T *BoxArray<T>::end() const noexcept
    {
        return _data + _size;
    }

    template <typename T>
    std::reverse_iterator<T *> BoxArray<T>::rbegin() noexcept
    {
        return std::reverse_iterator<T *>(end());
    }

    template <typename T>
    std::reverse_iterator<const T *> BoxArray<T>::rbegin() const noexcept
    {
        return std::reverse_iterator<const T *>(end());
    }

    template <typename T>
    std::reverse_iterator<T *> BoxArray<T>::rend() noexcept
    {
        return std::reverse_iterator<T *>(begin());
    }

    template <typename T>
    std::reverse_iterator<const T *> BoxArray<T>::rend() const noexcept
    {
        return std::reverse_iterator<const T *>(begin());
    }

    template <typename T>
    const T *BoxArray<T>::cbegin() const noexcept
    {
        return begin();
    }

    template <typename T>
    const T *BoxArray<T>::cend() const noexcept
    {
        return end();
    }

    template <typename T>
    std::reverse_iterator<const T *> BoxArray<T>::crbegin() const noexcept
    {
        return rbegin();
    }

    template <typename T>
    std::reverse_iterator<const T *> BoxArray<T>::crend() const noexcept
    {
        return rend();
    }

    template <typename T>
    size_t BoxArray<T>::size() const noexcept
    {
        return _size;
    }

    template <typename T>
    void BoxArray<T>::resize(size_t new_size)
    {
        if (new_size == SIZE_MAX)
        {
            T *new_data = new T[++this->_size];
            for (size_t i = 0; i < this->_size - 1; ++i)
                new_data[i] = std::move(_data[i]);
            delete[] this->_data;
            this->_data = new_data;
        }
        else
        {
            T *new_data = new T[new_size];
            for (size_t i = 0; i < _size; ++i)
                new_data[i] = std::move(_data[i]);
            delete[] _data;
            _size = new_size;
            _data = new_data;
        }
    }

    template <typename T>
    T &BoxArray<T>::operator[](const size_t &index) noexcept
    {
        return _data[index];
    }

    template <typename T>
    const T &BoxArray<T>::operator[](const size_t &index) const noexcept
    {
        return _data[index];
    }

    template <typename T>
    T &BoxArray<T>::at(const size_t &index)
    {
        if (index >= _size)
            throw std::out_of_range("at out of range");
        return _data[index];
    }

    template <typename T>
    const T &BoxArray<T>::at(const size_t &index) const
    {
        if (index >= _size)
            throw std::out_of_range("at out of range");
        return _data[index];
    }

    template <typename T>
    T &BoxArray<T>::front()
    {
        if (_size == 0)
            throw std::underflow_error("front underflow");
        return _data[0];
    }

    template <typename T>
    const T &BoxArray<T>::front() const
    {
        if (_size == 0)
            throw std::underflow_error("front underflow");
        return _data[0];
    }

    template <typename T>
    T &BoxArray<T>::back()
    {
        if (_size == 0)
            throw std::underflow_error("BoxArray: back underflow");
        return _data[_size - 1];
    }

    template <typename T>
    const T &BoxArray<T>::back() const
    {
        if (_size == 0)
            throw std::underflow_error("BoxArray: back underflow");
        return _data[_size - 1];
    }

    template <typename T>
    T *BoxArray<T>::data() noexcept
    {
        return _data;
    }

    template <typename T>
    const T *BoxArray<T>::data() const noexcept
    {
        return _data;
    }

    template <typename T>
    void BoxArray<T>::fill(const T &t) noexcept
    {
        std::fill(_data, _data + _size, t);
    }
}
