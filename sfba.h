#pragma once
#include <cstdint>
#include <array>


template <typename T, std::uint32_t heap_size>
class sfba // Simple Fixed Block Allocator
{
public:
    using elem = T;
    sfba() = default;
    std::uint32_t capacity() const;
    std::uint32_t size() const;
    T* malloc();
    void free(T* p);
private:
    std::array<bool,heap_size> available {};
    std::array<elem,heap_size> heap {};
};


template <typename T, std::uint32_t heap_size>
std::uint32_t sfba<T,heap_size>::capacity() const
{
    return std::count_if(begin(available), end(available), [](bool b){ return b == false;});
}

template <typename T, std::uint32_t heap_size>
std::uint32_t sfba<T,heap_size>::size() const
{
    return heap_size;
}


template <typename T, std::uint32_t heap_size>
T* sfba<T,heap_size>::malloc()
{
    uint32_t element{};
    for(auto i : available) {
        if (i == false) {
            available[element] = true;  // set block to unavaialble
            return &heap[element];      // return address of block
        }
        ++element;
    }
    return nullptr;
}

template <typename T, std::uint32_t heap_size>
void sfba<T,heap_size>::free(T* p)
{
    uint32_t element{};
    for(auto i : heap) {
        if (p == &heap[element]) {   // see if ptr address matches a block
            available[element] = false;     // make block avaialble 
            heap[element] = T{};            // clear the contents
        }
        ++element;
    }
}
