#pragma once
#include <array>

template <typename T, unsigned pool_size>
class sfba // Simple Fixed Block Allocator
{
public:
    using elem = T;
    sfba() = default;
    unsigned capacity() const;
    unsigned size() const;
    T* malloc(unsigned);
    void free(T* p);
private:
    std::array<bool,pool_size> allocated {};
    std::array<elem,pool_size> pool {};
    std::array<unsigned,pool_size> allocCount {};

    template <unsigned num>
    T* alloc()
    {
        T* rv = nullptr;
        std::array<bool,num> request{}; // set up array for search pattern 
        // see if we can find subgroup in availabe blocks
        auto it = std::search(begin(allocated),end(allocated),begin(request),end(request));
        if(it != end(allocated)) {
            unsigned element = (it - begin(allocated));  // calcualate pos of first free group
            for (unsigned cnt = 0; cnt < num; ++cnt) {
                allocated[element+cnt] = true;  // set each block to allocated
            }
            allocCount[element] = num; // remember how many blocks we allocated
            rv = &pool[element];      // address of block
        }
        return rv;
    }
};


template <typename T, unsigned pool_size>
unsigned sfba<T,pool_size>::capacity() const
{
    return std::count_if(begin(allocated), end(allocated), [](bool b){ return b == false;});
}

template <typename T, unsigned pool_size>
unsigned sfba<T,pool_size>::size() const
{
    return pool_size;
}


template <typename T, unsigned pool_size>
T* sfba<T,pool_size>::malloc(unsigned num)
{
    switch(num) {
        case  1: return sfba<T, pool_size>::alloc<1>();
        case  2: return sfba<T, pool_size>::alloc<2>();
        case  4: return sfba<T, pool_size>::alloc<4>();
        case  8: return sfba<T, pool_size>::alloc<8>();
        case 16: return sfba<T, pool_size>::alloc<16>();
        case 32: return sfba<T, pool_size>::alloc<32>();
        case 64: return sfba<T, pool_size>::alloc<64>();
    }
    return nullptr;
}

template <typename T, unsigned pool_size>
void sfba<T,pool_size>::free(T* p)
{
    unsigned element{};
    for(auto i : pool) {
        if (!(p == &pool[element])) {   // see if ptr address matches a block
             ++element;
        }
        else {
            for(unsigned cnt = 0; cnt < allocCount[element]; ++cnt) {
                allocated[element+cnt] = false;     // make block avaialble 
                pool[element+cnt] = T{};            // clear the contents
            }
            allocCount[element] = 0;
            return;
        }
    }
}
