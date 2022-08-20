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
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <climits>
#include <sstream>
#include <iomanip>
/// The maximum value of a u64.
#define U64_MAX	UINT64_MAX

/// would be nice if newlib had this already
#ifndef SSIZE_MAX
#ifdef SIZE_MAX
#define SSIZE_MAX ((SIZE_MAX) >> 1)
#endif
#endif

typedef char16_t utf16;

typedef uint8_t  u8;  ///<  8-bit unsigned integer
typedef uint16_t u16; ///< 16-bit unsigned integer
typedef uint32_t u32; ///< 32-bit unsigned integer
typedef uint64_t u64; ///< 64-bit unsigned integer

typedef int8_t  s8;  ///<  8-bit signed integer
typedef int16_t s16; ///< 16-bit signed integer
typedef int32_t s32; ///< 32-bit signed integer
typedef int64_t s64; ///< 64-bit signed integer

typedef volatile u8 vu8;   ///<  8-bit volatile unsigned integer.
typedef volatile u16 vu16; ///< 16-bit volatile unsigned integer.
typedef volatile u32 vu32; ///< 32-bit volatile unsigned integer.
typedef volatile u64 vu64; ///< 64-bit volatile unsigned integer.

typedef volatile s8 vs8;   ///<  8-bit volatile signed integer.
typedef volatile s16 vs16; ///< 16-bit volatile signed integer.
typedef volatile s32 vs32; ///< 32-bit volatile signed integer.
typedef volatile s64 vs64; ///< 64-bit volatile signed integer.

/// Aligns a struct (and other types?) to m, making sure that the size of the struct is a multiple of m.
#define ALIGN(m)        __attribute__((aligned(m)))
/// Packs a struct (and other types?) so it won't include padding bytes.
#define PACKED          __attribute__((packed))

#define USED            __attribute__((used))
#define UNUSED          __attribute__((unused))
#define DEPRECATED      __attribute__((deprecated))
#define NAKED           __attribute__((naked))
#define NORETURN        __attribute__((noreturn))
#define ALWAYS_INLINE   __attribute__((always_inline))
#define WEAK            __attribute__((weak))


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

    const mask& mask = reinterpret_cast<const union mask&>(&u);

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
