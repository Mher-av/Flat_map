# Flat_map
A flat_map is a kind of associative container that supports unique keys (contains at most one of each key value) and provides for fast retrieval of values of another type T based on the keys. The flat_map class supports random-access iterators.

A flat_map satisfies all of the requirements of a container and of a reversible container and of an associative container. A flat_map also provides most operations described for unique keys. For a flat_map<Key,T> the key_type is Key and the value_type is std::pair<Key,T> (unlike std::map<Key, T> which value_type is std::pair<const Key, T>).

Compare is the ordering function for Keys (e.g. std::less<Key>).

Allocator is the allocator to allocate the value_types (e.g. allocator< std::pair<Key, T> >).

flat_map is similar to std::map but it's implemented like an ordered vector. This means that inserting a new element into a flat_map invalidates previous iterators and references

Erasing an element invalidates iterators and references pointing to elements that come after (their keys are bigger) the erased element.

This container provides random-access iterators.
