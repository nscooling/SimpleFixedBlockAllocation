
template<typename T>
class Allocator {
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
        typedef Allocator<U> other;
    };

public : 
    Allocator() = default;
    ~Allocator() = default;
    Allocator(Allocator const&) = default;
    template<typename U>
    Allocator(Allocator<U> const&) {}

    //    address
    pointer address(reference r) { return &r; }
    const_pointer address(const_reference r) { return &r; }

    //    memory allocation
    pointer allocate(size_type num) 
    { 
        void* mem = malloc(num * sizeof (T));
        if(mem == nullptr) {
            throw std::bad_alloc{};
        }
        return static_cast<pointer>(mem); 
    }

    void deallocate(pointer p, size_type) 
    { 
        free(p); 
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

    bool operator==(Allocator const&) { return true; }
    bool operator!=(Allocator const& a) { return !operator==(a); }
};    //    end of class Allocator
