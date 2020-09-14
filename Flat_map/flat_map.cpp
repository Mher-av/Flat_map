#include <stdexcept>
#include "flat_map.h"

namespace detail
{
    void throw_out_of_range(const char* message)
    {
        throw std::out_of_range(message);
    }
}