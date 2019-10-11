#ifndef HEAP_HPP
#define HEAP_HPP

#include <iostream>
#include <istream>
#include <iterator>
#include <ostream>
#include <vector>

template<class T, template<class...> class ContainerTemplate = std::vector>
class heap
{
public:
    using value_type = T;

private:
    using Cnt = ContainerTemplate<T>;

private:
    Cnt m_container;

public:
    heap() = default;
    heap(heap<T, ContainerTemplate> const& other);

    T get_max();

    void insert(T item);
    template<class... TS>
    void insert(T item, TS... rest);

    void clear();

    template<class TF, template<class...> class ContainerTemplateF>
    friend std::istream& operator>>(std::istream& in, heap<TF, ContainerTemplateF>& hp);
    template<class TF, template<class...> class ContainerTemplateF>
    friend std::ostream& operator<<(std::ostream& out, heap<TF, ContainerTemplateF> const& hp);

private:
    void max_heapify(typename Cnt::iterator::difference_type child_pos);

    typename Cnt::iterator::difference_type parent_pos(typename Cnt::iterator::difference_type child_pos)
    {
        return (child_pos + child_pos % 2) / 2 - 1;
    }
};

template<class T, template<class...> class ContainerTemplate>
heap<T, ContainerTemplate>::heap(heap<T, ContainerTemplate> const& other)
    : m_container(other.m_container)
{
}

template<class T, template<class...> class ContainerTemplate>
T heap<T, ContainerTemplate>::get_max()
{
    return m_container.front();
}

template<class T, template<class...> class ContainerTemplate>
void heap<T, ContainerTemplate>::insert(T item)
{
    m_container.push_back(item);
    max_heapify(m_container.size() - 1);
}

template<class T, template<class...> class ContainerTemplate>
template<class... TS>
void heap<T, ContainerTemplate>::insert(T item, TS... rest)
{
    insert(item);
    insert(rest...);
}

template<class T, template <class...> class ContainerTemplate>
void heap<T, ContainerTemplate>::clear()
{
    m_container.clear();
}

template<class T, template<class...> class ContainerTemplate>
void heap<T, ContainerTemplate>::max_heapify(typename Cnt::iterator::difference_type child_pos)
{
    if (child_pos == 0)
    {
        return;
    }

    auto ps = parent_pos(child_pos);

    if (m_container[ps] < m_container[child_pos])
    {
        iter_swap(m_container.begin() + ps, m_container.begin() + child_pos);
        max_heapify(ps);
    }
}

template<class TF, template<class...> class ContainerTemplateF>
std::istream& operator>>(std::istream& in, heap<TF, ContainerTemplateF>& hp)
{
    TF temp;
    in >> temp;
    hp.insert(temp);

    return in;
}

template<class TF, template<class...> class ContainerTemplateF>
std::ostream& operator<<(std::ostream& out, heap<TF, ContainerTemplateF> const& hp)
{
    for (auto const& e : hp.m_container)
    {
        out << e << " ";
    }
    out << std::endl;

    return out;
}

#endif
