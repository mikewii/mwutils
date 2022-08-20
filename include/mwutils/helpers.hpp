/*
 * This file is part of mwutils
 *
 * Copyright (c) 2022 - present, mikewii
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 * --- Optional exception to the license ---
 *
 * As an exception, if, as a result of your compiling your source code, portions
 * of this Software are embedded into a machine-executable object form of such
 * source code, you may redistribute such embedded portions in such object form
 * without including the above copyright and permission notices.
*/

#pragma once
#include <mwutils/types.hpp>
#include <sstream>
#include <iomanip>
#include <climits>

namespace mwutils {
    void init(void);

namespace random {
    void    seed_rng(void);

    s32     get_random(s32 min, s32 max);
    bool    get_random(void);
}; /* namespace random */

namespace print {
    void    as_hex(const void* const data, const int data_size);
}; /* namespace print */

namespace convert {
template <typename T>
std::string to_string(const T& u, const bool uppercase = false)
{
    std::stringstream ss;

    union mask {
        T u;
        unsigned char u8[sizeof(T)];
    };

    const mask& mask = reinterpret_cast<const union mask&>(u);

    for (size_t i = 0; i < sizeof(T); i++) {
        if (uppercase)
            ss << std::uppercase << std::hex << std::setfill('0') << std::setw(2) << static_cast<u32>(mask.u8[i]);
        else
            ss << std::hex << std::setfill('0') << std::setw(2) << static_cast<u32>(mask.u8[i]);
    }

    return ss.str();
}
}; /* namespace convert */

namespace endianess {
template <typename T>
static T swap(const T u)
{
    static_assert (CHAR_BIT == 8, "CHAR_BIT != 8");

    union {
        T u;
        unsigned char u8[sizeof(T)];
    } source, dest;

    source.u = u;

    for (std::size_t k = 0; k < sizeof(T); k++)
        dest.u8[k] = source.u8[sizeof(T) - k - 1];

    return dest.u;
}
}; /* namespace endianess */

///
/// \brief alignment safe copy
///
void* copy_bytes(void* dest, const void* src, const size_t size);

}; /* namespace utils */

