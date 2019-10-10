#ifndef HEAP_HPP
#define HEAP_HPP

#include <iostream>
#include <istream>
#include <iterator>
#include <ostream>
#include <vector>

template<class T, template<class... TArgs> class ContainerTemplate = std::vector>
class heap
{
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

    template<class TF>
    friend std::istream& operator>>(std::istream& in, heap<TF>& hp);
    template<class TF>
    friend std::ostream& operator<<(std::ostream& out, heap<TF> const& hp);

private:
    void max_heapify(typename Cnt::iterator b, typename Cnt::iterator e,
                     typename Cnt::iterator::difference_type cur_head);

    typename Cnt::iterator::difference_type parent_pos(typename Cnt::iterator::difference_type child_pos)
    {
        return (child_pos + child_pos % 2) / 2 - 1;
    }
};

template<class T, template<class... TArgs> class ContainerTemplate>
heap<T, ContainerTemplate>::heap(heap<T, ContainerTemplate> const& other)
    : m_container(other.m_container)
{
}

template<class T, template<class... TArgs> class ContainerTemplate>
T heap<T, ContainerTemplate>::get_max()
{
    return m_container.front();
}

template<class T, template<class... TArgs> class ContainerTemplate>
void heap<T, ContainerTemplate>::insert(T item)
{
    m_container.push_back(item);
    if (m_container.size() != 1)
    {
        max_heapify(m_container.begin(), m_container.end(),
                    parent_pos(m_container.size() - 1));
    }
}

template<class T, template<class... TArgs> class ContainerTemplate>
template<class... TS>
void heap<T, ContainerTemplate>::insert(T item, TS... rest)
{
    insert(item);
    insert(rest...);
}

template<class T, template<class... TArgs> class ContainerTemplate>
void heap<T, ContainerTemplate>::max_heapify(typename Cnt::iterator b,
                                          typename Cnt::iterator e,
                                          typename Cnt::iterator::difference_type cur_head)
{
    using iter_diff = typename Cnt::iterator::difference_type;
    iter_diff max_diff = std::distance(b, e);
    auto max_pos_helper = [b, max_diff]
                          (iter_diff l, iter_diff r)
                          {
                              if (r >= max_diff)
                              {
                                  return l;
                              }
                              else if (b[l] < b[r])
                              {
                                  return r;
                              }
                              else
                              {
                                  return l;
                              }
                          };
    iter_diff max_pos = max_pos_helper(cur_head, 2 * cur_head + 1);
    max_pos = max_pos_helper(max_pos, 2 * cur_head + 2);

    if (max_pos != cur_head)
    {
        std::iter_swap(b + cur_head, b + max_pos);
        if (cur_head != 0)
        {
            max_heapify(b, e, parent_pos(cur_head));
        }
    }
}

template<class TF>
std::istream& operator>>(std::istream& in, heap<TF>& hp)
{
    TF temp;
    in >> temp;
    hp.insert(temp);

    return in;
}

template<class TF>
std::ostream& operator<<(std::ostream& out, heap<TF> const& hp)
{
    for (auto const& e : hp.m_container)
    {
        out << e << " ";
    }
    out << std::endl;

    return out;
}

#endif
