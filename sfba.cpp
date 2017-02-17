// #include "sfba.h"
// using namespace std;

// template <std::uint32_t heap_size>
// std::uint32_t sfba<heap_size>::capacity() const
// {
//     return count_if(begin(available), end(available), [](bool b){ return b == false;});
// }

// template <std::uint32_t heap_size>
// std::uint32_t sfba<heap_size>::size() const
// {
//     return heap_size;
// }


// template <std::uint32_t heap_size>
// void* sfba<heap_size>::malloc()
// {
//     uint32_t element{};
//     for(auto i : available) {
//         if (i == false) {
//             available[element] = true;
//             return (void*)(&heap[element]);
//         }
//         ++element;
//     }
//     return nullptr;
// }
