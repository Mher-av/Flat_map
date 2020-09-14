#pragma once

#include <algorithm>
#include <functional>
#include <vector>

namespace detail
{
    void throw_out_of_range(const char* message);
}

    /**
     * @brief A flat_map is a kind of associative container that supports unique keys and provides for fast retrieval of values of another type T based on the keys.
     * The flat_map class supports random-access iterators.
     *
     * @tparam K is the key_type of the map.
     * @tparam V is the value_type of the map.
     * @tparam std::less<K> the ordering function for Keys.
     * @tparam std::allocator<std::pair<K, V>> the allocator to allocate the value_types.
     */
    template <typename K
        , typename V
        , typename Comp = std::less<K>
        , typename Allocator = std::allocator<std::pair<K, V>>
    >
        struct flat_map
    {
        using key_type = K;
        using mapped_type = V;
        using value_type = std::pair<K, V>;
        using key_compare = Comp;

        struct value_compare
        {
            bool operator() (const value_type& lhs, const value_type& rhs) const
            {
                return key_compare()(lhs.first, rhs.first);
            }
        };

        using allocator_type = Allocator;
        using reference = V&;
        using const_reference = const V&;
        using pointer = typename std::allocator_traits<allocator_type>::pointer;
        using const_pointer = typename std::allocator_traits<allocator_type>::const_pointer;
        using container_type = std::vector<value_type, allocator_type>;
        using iterator = typename container_type::iterator;
        using const_iterator = typename container_type::const_iterator;
        using reverse_iterator = typename container_type::reverse_iterator;
        using const_reverse_iterator = typename container_type::const_reverse_iterator;
        using difference_type = typename container_type::difference_type;
        using size_type = typename container_type::size_type;

        flat_map() = default;
        ~flat_map() = default;
        flat_map(flat_map&&) = default;
        flat_map(const flat_map&) = default;
        flat_map& operator=(flat_map&&) = default;
        flat_map& operator=(const flat_map&) = default;

        /**
         * @brief Constructs an empty flat_map and inserts elements from the range [begin ,end ).
         *
         * @param begin range of elements to insert.
         * @param end range of elements to insert.
         */
        template <typename It>
        flat_map(It begin, It end)
        {
            insert(begin, end);
        }

        /**
         * @brief Constructs an empty flat_map and inserts elements from the range [il.begin() ,il.end()).
         *
         * @param init An initializer_list.
         */
        flat_map(std::initializer_list<value_type> init)
            : flat_map(std::begin(init), std::end(init))
        {
        }
        /**
         * @brief Returns an iterator to the first element contained in the container.
         *
         * @return An iterator to the first element.
         */
        [[nodiscard]] iterator begin() noexcept
        {
            return std::begin(m_data);
        }

        /**
         * @brief Returns an iterator to the end of the container.
         *
         * @return An iterator to the end of the container.
         */
        [[nodiscard]] iterator end() noexcept
        {
            return std::end(m_data);
        }

        /**
         * @brief Returns a const_iterator to the first element contained in the container.
         *
         * @return const_iterator to the first element.
         */
        [[nodiscard]] const_iterator begin() const noexcept
        {
            return std::begin(m_data);
        }

        /**
         * @brief Returns a const_iterator to the end of the container.
         *
         * @return const_iterator to the end of the container.
         */
        [[nodiscard]] const_iterator end() const noexcept
        {
            return std::end(m_data);
        }

        /**
         * @brief Returns a const_iterator to the first element contained in the container.
         *
         * @return const_iterator to the first element.
         */
        [[nodiscard]] const_iterator cbegin() const noexcept
        {
            return std::cbegin(m_data);
        }

        /**
         * @brief Returns a const_iterator to the end of the container.
         *
         * @return const_iterator to the end of the container.
         */
        [[nodiscard]] const_iterator cend() const noexcept
        {
            return std::cend(m_data);
        }

        /**
         * @brief Returns a reverse_iterator pointing to the beginning of the reversed container.
         *
         * @return reverse_iterator to the beginning of the reversed container.
         */
        [[nodiscard]] reverse_iterator rbegin() noexcept
        {
            return std::rbegin(m_data);
        }

        /**
         * @brief  Returns a reverse_iterator pointing to the end of the reversed container.
         *
         * @return reverse_iterator to the end of the reversed container.
         */
        [[nodiscard]] reverse_iterator rend() noexcept
        {
            return std::rend(m_data);
        }

        /**
         * @brief Returns a const_reverse_iterator pointing to the beginning of the reversed container.
         *
         * @return const_reverse_iterator to the beginning of the reversed container.
         */
        [[nodiscard]] const_reverse_iterator rbegin() const noexcept
        {
            return std::rbegin(m_data);
        }

        /**
         * @brief Returns a const_reverse_iterator pointing to the end of the reversed container.
         *
         * @return const_reverse_iterator to the end of the reversed container.
         */
        [[nodiscard]] const_reverse_iterator rend() const noexcept
        {
            return std::rbegin(m_data);
        }

        /**
         * @brief Returns a const_reverse_iterator pointing to the beginning of the reversed container.
         *
         * @return const_reverse_iterator to the beginning of the reversed container.
         */
        [[nodiscard]] const_reverse_iterator crbegin() const noexcept
        {
            return std::crbegin(m_data);
        }

        /**
         * @brief Returns a const_reverse_iterator pointing to the end of the reversed container.
         *
         * @return const_reverse_iterator to the end of the reversed container.
         */
        [[nodiscard]] const_reverse_iterator crend() const noexcept
        {
            return std::crend(m_data);
        }

        /**
         * @brief Checks the empyiness of the container
         *
         * @return true if the container contains no elemets, false otherwise.
         */
        [[nodiscard]] bool empty() const noexcept
        {
            return m_data.empty();
        }

        /**
         * @brief  Returns the number of the elements contained in the container.
         *
         * @return The number of the elements of container.
         */
        [[nodiscard]] size_type size() const noexcept
        {
            return std::size(m_data);
        }

        /**
         * @brief Returns the largest possible size of the container.
         *
         * @return The largest possible size.
         */
        [[nodiscard]] size_type max_size() const noexcept
        {
            return m_data.max_size();
        }

        /**
         * @brief Number of elements for which memory has been allocated. capacity() is always greater than or equal to size().
         *
         * @return Number of elements for which memory has been allocated.
         */
        [[nodiscard]] size_type capacity() const noexcept
        {
            return m_data.capacity();
        }

        /**
         * @brief If n is less than or equal to capacity(), this call has no effect. Otherwise, it is a request for allocation of additional memory.
         *        If the request is successful, then capacity() is greater than or equal to n; otherwise, capacity() is unchanged.
         *        In either case, size() is unchanged.
         *
         * @param size Requested size for allocation of additional memory.
         */
        void reserve(size_type size)
        {
            m_data.reserve(size);
        }

        /**
         * @brief Attempts to deallocate the excess of memory created.
         *
         */
        void shrink_to_fit()
        {
            m_data.shrink_to_fit();
        }

        /**
         * @brief If there is no key equivalent to @key in the flat_map, inserts value_type(@key, T()) into the flat_map.
         *
         * @param key The key of the element to find.
         * @return mapped_type& A reference to the mapped_type corresponding to @key in *this.
         */
        mapped_type& operator[] (const key_type& key)
        {
            KeyOrValueCompare comp;
            auto lower = lower_bound(key);
            if ((lower == end()) || comp(key, *lower)) {
                return m_data.emplace(lower, key, mapped_type())->second;
            }
            return lower->second;
        }

        /**
         * @brief If there is no key equivalent to @key in the flat_map, inserts value_type(move(@key), T()) into the flat_map (the key is move-constructed).
         *
         * @param key The key of the element to find.
         * @return mapped_type& A reference to the mapped_type corresponding to @key in *this.
         */
        mapped_type& operator[] (key_type&& key)
        {
            KeyOrValueCompare comp;
            auto lower = lower_bound(key);
            if ((lower == end()) || comp(key, *lower)) {
                return m_data.emplace(lower, std::move(key), mapped_type())->second;
            }
            return lower->second;
        }

        /**
         * @brief Returns a reference to the element whose key is equivalent to @key.
         *        Throws an exception object of type out_of_range if no such element is present.
         *
         * @param key The key of the element to find.
         * @return mapped_type& A reference to the element whose key is equivalent to @key.
         */
        mapped_type& at(const key_type& key)
        {
            auto found = binary_find(begin(), end(), key, KeyOrValueCompare());
            if (found == end()) {
                detail::throw_out_of_range("key passed to 'at' doesn't exist in this map");
            }
            return found->second;
        }

        /**
         * @brief Returns a reference to the element whose key is equivalent to @key.
         *        Throws an exception object of type out_of_range if no such element is present.
         *
         * @param key The key of the element to find.
         * @return const mapped_type& A const reference to the element whose key is equivalent to @key.
         */
        const mapped_type& at(const key_type& key) const
        {
            auto found = binary_find(begin(), end(), key, KeyOrValueCompare());
            if (found == end()) {
                detail::throw_out_of_range("key passed to 'at' doesn't exist in this map");
            }
            return found->second;
        }

        /**
         * @brief Inserts a new value_type move constructed from the pair if and only if there is no element in the container with key equivalent to the key of value.
         *
         * @param value std::pair<Key,T> for insertion.
         * @return std::pair<iterator, bool> The bool component of the returned pair is true if and only if the insertion takes place,
         *               and the iterator component of the pair points to the element with key equivalent to the key of @key.
         */
        std::pair<iterator, bool> insert(value_type&& value)
        {
            return emplace(std::move(value));
        }

        /**
         * @brief  Inserts value if and only if there is no element in the container with key equivalent to the key of value.
         *
         * @param value std::pair<Key,T> for insertion.
         * @return std::pair<iterator, bool> The bool component of the returned pair is true if and only if the insertion takes place,
         *         and the iterator component of the pair points to the element with key equivalent to the key of @key.
         */
        std::pair<iterator, bool> insert(const value_type& value)
        {
            return emplace(value);
        }

        /**
         * @brief  Inserts an element move constructed from "value" in the container.
         *
         * @param hint Hint pointing to where the insert should start to search.
         * @param value std::pair<Key,T> for insertion.
         * @return iterator An iterator pointing to the element with key equivalent to the key of @key.
         */
        iterator insert(const_iterator hint, value_type&& value)
        {
            return emplace_hint(hint, std::move(value));
        }

        /**
         * @brief Inserts a copy of "value" in the container if and only if there is no element in the container with key equivalent to the key of "value".
         *
         * @param hint Hint pointing to where the insert should start to search.
         * @param value std::pair<Key,T> for insertion.
         * @return iterator An iterator pointing to the element with key equivalent to the key of "value".
         */
        iterator insert(const_iterator hint, const value_type& value)
        {
            return emplace_hint(hint, value);
        }

        /**
         * @brief Inserts each element from the range [first,last) if and only if there is no element with key equivalent to the key of that element.
         *
         * @param begin range of elements to insert.
         * @param end range of elements to insert.
         */
        template <typename It>
        void insert(It begin, It end)
        {
            for (; begin != end && size() == capacity(); ++begin) {
                emplace(*begin);
            }
            if (begin == end) {
                return;
            }

            size_type size_before = m_data.size();
            try
            {
                for (size_t i = capacity(); i > size_before && begin != end; --i, ++begin) {
                    m_data.emplace_back(*begin);
                }
            }
            catch (...)
            {
                for (size_t i = m_data.size(); i > size_before; --i) {
                    m_data.pop_back();
                }
                throw;
            }
            value_compare comp;
            auto mid = std::begin(m_data) + size_before;
            std::stable_sort(mid, std::end(m_data), comp);
            std::inplace_merge(std::begin(m_data), mid, std::end(m_data), comp);
            m_data.erase(std::unique(std::begin(m_data), std::end(m_data)
                , std::not2(comp)), std::end(m_data));
            if (m_data.size() == size_before) {
                for (; begin != end; ++begin) {
                    if (emplace(*begin).second) {
                        ++begin;
                        break;
                    }
                }
            }
            return insert(begin, end);
        }

        /**
         * @brief Inserts each element from the range [il.begin(), il.end()) if and only if there is no element with key equivalent to the key of that element.
         *
         * @param il An initializer_list.
         */
        void insert(std::initializer_list<value_type> il)
        {
            insert(std::begin(il), std::end(il));
        }

        /**
         * @brief Erases the element pointed to by it.
         *
         * @param it Iterator pointing to the element to be erased.
         * @return iterator An iterator pointing to the element immediately following q prior to the element being erased. If no such element exists, returns end().
         */
        iterator erase(iterator it)
        {
            return m_data.erase(it);
        }

        /**
         * @brief Erases the element pointed to by it
         *
         * @param it Iterator pointing to the element to be erased.
         * @return iterator an iterator pointing to the element immediately following q prior to the element being erased. If no such element exists, returns end().
         */
        iterator erase(const_iterator it)
        {
            return erase(iterator_const_cast(it));
        }

        /**
         * @brief Erases element in the container with key equivalent to @key.
         *
         * @param key Key value of the element to remove.
         * @return  0 if @key not found in container, 1 otherwise.
         */
        size_type erase(const key_type& key)
        {
            auto found = find(key);
            if (found == end()) {
                return 0;
            }
            erase(found);
            return 1;
        }

        /**
         * @brief Erases all the elements in the range [first, last).
         *
         * @param first range of elements to remove.
         * @param last range of elements to remove.
         * @return iterator to the next of the last deleted element.
         */
        iterator erase(const_iterator first, const_iterator last)
        {
            return m_data.erase(iterator_const_cast(first), iterator_const_cast(last));
        }

        /**
         * @brief Swaps the contents of *this and other.
         *
         * @param other flat_map with which must be swapped.
         */
        void swap(flat_map& other) noexcept
        {
            m_data.swap(other.m_data);
        }

        /**
         * @brief Erases all elements in container.
         *
         */
        void clear()
        {
            m_data.clear();
        }

        /**
         * @brief Constructs a pair<key_type, value_type> object t constructed with std::forward<Args>(args)....
                  If the map already contains an element whose key is equivalent to the key of t,
         *
         * @param first
         * @param args
         * @return std::pair<iterator, bool> The bool component of the returned pair is true if and only if the insertion took place, and
                   the iterator component of the pair points to the element with key equivalent to the key of t
         */
        template <typename First, typename ... Args>
        std::pair<iterator, bool> emplace(First&& first, Args&& ... args)
        {
            KeyOrValueCompare comp;
            auto lower_bound = std::lower_bound(std::begin(m_data), std::end(m_data), first, comp);
            if ((lower_bound == std::end(m_data)) || comp(first, *lower_bound)) {
                return { m_data.emplace(lower_bound, std::forward<First>(first)
                         , std::forward<Args>(args) ...)
                         , true };
            }
            return { lower_bound, false };
        }

        /**
         * @brief Constructs a pair<key_type, value_type> object t constructed with std::forward<Args>(args)....
                  If the map already contains an element whose key is equivalent to the key of t,
         *
         * @return std::pair<iterator, bool> The bool component of the returned pair is true if and only if the insertion took place, and
                   the iterator component of the pair points to the element with key equivalent to the key of t
         */
        std::pair<iterator, bool> emplace()
        {
            return emplace(value_type());
        }

        /**
         * @brief Inserts an object of type T constructed with std::forward<Args>(args)... in the container if
         *        and only if there is no element in the container with key equivalent to the key of x.
         *
         * @param hint Hint pointing to where the insert should start to search.
         * @param first
         * @param args
         * @return iterator pointing to the element with key equivalent to the key of x.
         */
        template <typename First, typename ... Args>
        iterator emplace_hint(const_iterator hint, First&& first, Args&& ... args)
        {
            KeyOrValueCompare comp;
            if ((hint == cend()) || comp(first, *hint)) {
                if ((hint == cbegin()) || comp(*(hint - 1), first)) {
                    return m_data.emplace(
                        iterator_const_cast(hint), std::forward<First>(first), std::forward<Args>(args) ...);
                }
                return emplace(std::forward<First>(first), std::forward<Args>(args) ...).first;
            }
            if (!comp(*hint, first)) {
                return begin() + (hint - cbegin());
            }
            return emplace(std::forward<First>(first), std::forward<Args>(args) ...).first;
        }

        iterator emplace_hint(const_iterator hint)
        {
            return emplace_hint(hint, value_type());
        }

        /**
         * @brief Returns the comparison object out of which a was constructed.
         *
         * @return key_compare The comparison object
         */
        key_compare key_comp() const
        {
            return key_compare();
        }

        /**
         * @brief Returns an object of value_compare constructed out of the comparison object.
         *
         * @return value_compare An object of value_compare.
         */
        value_compare value_comp() const
        {
            return value_compare();
        }

        /**
         * @brief Attempts to find an element with key equivalent to @key.
         *
         * @param key Key value of the element to search for.
         * @return iterator An iterator pointing to an element with the key equivalent to key, or end() if such an element is not found.
         */
        template <typename T>
        iterator find(const T& key)
        {
            return binary_find(begin(), end(), key, KeyOrValueCompare());
        }

        /**
         * @brief Attempts to find an element with key equivalent to @key.
         *
         * @param key Key value of the element to search for.
         * @return const_iterator A const_iterator pointing to an element with the key equivalent to @key, or end() if such an element is not found.
         */
        template <typename T>
        const_iterator find(const T& key) const
        {
            return binary_find(begin(), end(), key, KeyOrValueCompare());
        }

        /**
         * @brief Finds the first element with key not less than @key, or end() if such an element is not found.
         *
         * @param key Key value to compare the elements to.
         * @return iterator An iterator pointing to the first element with key not less than k, or end() if such an element is not found.
         */
        template <typename T>
        iterator lower_bound(const T& key)
        {
            return std::lower_bound(begin(), end(), key, KeyOrValueCompare());
        }

        /**
         * @brief Finds the first element with key not less than @key, or end() if such an element is not found.
         *
         * @param key Key value to compare the elements to.
         * @return const_iterator An const iterator pointing to the first element with key not less than k, or end() if such an element is not found.
         */
        template <typename T>
        const_iterator lower_bound(const T& key) const
        {
            return std::lower_bound(begin(), end(), key, KeyOrValueCompare());
        }

        /**
         * @brief Finds the first element with key greater than @key, or end() if such an element is not found.
         *
         * @param key Key value to compare the elements to.
         * @return iterator An iterator pointing to the first element with key greater than @key, or end() if such an element is not found.
         */
        template <typename T>
        iterator upper_bound(const T& key)
        {
            return std::upper_bound(begin(), end(), key, KeyOrValueCompare());
        }

        /**
         * @brief Finds the first element with key greater than @key, or end() if such an element is not found.
         *
         * @param key Key value to compare the elements to.
         * @return const_iterator An const iterator pointing to the first element with key greater than @key, or end() if such an element is not found.
         */
        template <typename T>
        const_iterator upper_bound(const T& key) const
        {
            return std::upper_bound(begin(), end(), key, KeyOrValueCompare());
        }

        /**
         * @brief  Returns a range containing all elements equivalent to value in the range [first, last).
         *
         * @param key Key value to compare the elements to.
         * @return std::pair<iterator, iterator> std::pair containing a pair of iterators defining the wanted range,
         *         the first pointing to the first element that is not less than value and the second pointing to the first element greater than value.
         */
        template <typename T>
        std::pair<iterator, iterator> equal_range(const T& key)
        {
            return std::equal_range(begin(), end(), key, KeyOrValueCompare());
        }

        /**
         * @brief  Returns a range containing all elements equivalent to value in the range [first, last).
         *
         * @param key Key value to compare the elements to.
         * @return std::pair<const_iterator, const_iterator> std::pair<iterator, iterator> std::pair containing a pair of iterators defining the wanted range,
         *         the first pointing to the first element that is not less than value and the second pointing to the first element greater than value.
         */
        template <typename T>
        std::pair<const_iterator, const_iterator> equal_range(const T& key) const
        {
            return std::equal_range(begin(), end(), key, KeyOrValueCompare());
        }

        /**
         * @brief Returns a copy of the allocator that was passed to the object's constructor.
         *
         * @return allocator_type Copy of the allocator.
         */
        allocator_type get_allocator() const
        {
            return m_data.get_allocator();
        }

        /**
         * @brief Compares two flat_maps.
         *
         * @param other A flat_map with which need to compare.
         * @return true if they are equal,false otherwise.
         */
        bool operator== (const flat_map& other) const
        {
            return m_data == other.m_data;
        }

        /**
         * @brief Compares two flat_maps.
         *
         * @param other A flat_map with which need to compare.
         * @return true if they are unequal,false otherwise.
         */
        bool operator!= (const flat_map& other) const
        {
            return !(*this == other);
        }

        /**
         * @brief Compares two flat_maps.
         *
         * @param other A flat_map with which need to compare.
         * @return true if current flat_map is less than other.
         */
        bool operator< (const flat_map& other) const
        {
            return m_data < other.m_data;
        }

        /**
         * @brief Compares two flat_maps.
         *
         * @param other A flat_map with which need to compare.
         * @return true if current flat_map is greater than other, false otherwise.
         */
        bool operator> (const flat_map& other) const
        {
            return other < *this;
        }

        /**
         * @brief Compares two flat_maps.
         *
         * @param other A flat_map with which need to compare.
         * @return true if current flat_map is equal or less than other, false otherwise.
         */
        bool operator<= (const flat_map& other) const
        {
            return !(other < *this);
        }

        /**
         * @brief Compares two flat_maps.
         *
         * @param other A flat_map with which need to compare.
         * @return true if current flat_map is equal or greater thanother, false otherwise.
         */
        bool operator>= (const flat_map& other) const
        {
            return !(*this < other);
        }

    private:
        container_type m_data;

        iterator iterator_const_cast(const_iterator it)
        {
            return begin() + (it - cbegin());
        }

        struct KeyOrValueCompare
        {
            bool operator() (const key_type& lhs, const key_type& rhs) const
            {
                return key_compare()(lhs, rhs);
            }

            bool operator() (const key_type& lhs, const value_type& rhs) const
            {
                return key_compare()(lhs, rhs.first);
            }

            template <typename T>
            bool operator() (const key_type& lhs, const T& rhs) const
            {
                return key_compare()(lhs, rhs);
            }

            template <typename T>
            bool operator() (const T& lhs, const key_type& rhs) const
            {
                return key_compare()(lhs, rhs);
            }

            bool operator() (const value_type& lhs, const key_type& rhs) const
            {
                return key_compare()(lhs.first, rhs);
            }

            bool operator() (const value_type& lhs, const value_type& rhs) const
            {
                return key_compare()(lhs.first, rhs.first);
            }

            template <typename T>
            bool operator() (const value_type& lhs, const T& rhs) const
            {
                return key_compare()(lhs.first, rhs);
            }

            template <typename T>
            bool operator() (const T& lhs, const value_type& rhs) const
            {
                return key_compare()(lhs, rhs.first);
            }
        };

        /**
         * @brief Checks if an element equivalent to value appears within the range [first, last).
         *
         * @param begin the range of elements to examine.
         * @param end the range of elements to examine.
         * @param value value to compare the elements to.
         * @param cmp binary predicate which returns ​true if the first argument is less than (i.e. is ordered before) the second.
         * @return It True if an element equal to value is found, false otherwise.
         */
        template <typename It, typename T, typename Compare>
        static It binary_find(It begin, It end, const T& value, const Compare& cmp)
        {
            auto lower_bound = std::lower_bound(begin, end, value, cmp);
            if ((lower_bound == end) || cmp(value, *lower_bound)) {
                return end;
            }
            return lower_bound;
        }
    };

    template <typename K, typename V, typename C, typename A>
    void swap(flat_map<K, V, C, A>& lhs, flat_map<K, V, C, A>& rhs) noexcept
    {
        lhs.swap(rhs);
    }

