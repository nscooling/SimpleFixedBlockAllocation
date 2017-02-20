#pragma once

#include "sfba.h"

template<typename T>
class SFBAllocator {
public : 
    //    typedefs
    typedef T value_type;
    typedef value_type* pointer;
    typedef const value_type* const_pointer;
    typedef value_type& reference;
    typedef const value_type& const_reference;
    typedef std::size_t size_type;
    typedef std::ptrdiff_t difference_type;

public : 
    //    convert an allocator<T> to allocator<U>
    template<typename U>
    struct rebind {
        typedef SFBAllocator<U> other;
    };

public : 
    SFBAllocator() = default;
    ~SFBAllocator() = default;
    SFBAllocator(SFBAllocator const&) = default;
    template<typename U>
    SFBAllocator(SFBAllocator<U> const&) {}

    //    address
    pointer address(reference r) { return &r; }
    const_pointer address(const_reference r) { return &r; }

    //    memory allocation
    pointer allocate(size_type num) 
    { 
#ifdef DEBUG
        std::cout << "alloc =================> " << num << std::endl;
#endif
        void* mem = pool.malloc(num);
        if(mem == nullptr) {
            throw std::bad_alloc{};
        }
        return static_cast<pointer>(mem); 
    }

    void deallocate(pointer p, size_type num) 
    { 
#ifdef DEBUG
        std::cout << "dealloc =================> " << num << std::endl;
#endif
        pool.free(p); 
    }

    //    size
    size_type max_size() const 
    { 
        return std::numeric_limits<size_type>::max() / sizeof(T);
    }

    //    construction/destruction
    void construct(pointer p, const T& t) 
    { 
        new(p) T(t); 
    }
    void destroy(pointer p) 
    { 
        p->~T(); 
    }

    bool operator==(SFBAllocator const&) { return true; }
    bool operator!=(SFBAllocator const& a) { return !operator==(a); }


    sfba<T, 32> pool;
};    //    end of class SFBAllocator
