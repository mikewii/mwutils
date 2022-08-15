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
#include "mwutils/mwutils.hpp"
#include <iostream>
#include <iomanip>
#include <cstring>

namespace mwutils {
void init(void)
{
    random::seed_rng();
}

namespace print {
void as_hex(const void* const data, const int data_size)
{
    const u8* const as_char = reinterpret_cast<const u8* const>(data);

    for (int i = 1; i < data_size + 1; i++) {
        u32 value = static_cast<u32>(as_char[i - 1]);

        std::cout << std::uppercase << std::hex << std::setfill('0') << std::setw(2) << value << " ";

        if (i % 8 == 0) {
            std::cout << std::endl;
        } else if (i % 4 == 0) {
            std::cout << "  ";
        }
    }

    std::cout << std::endl;
}
}; /* namespace print */

void* copy_bytes(void* dest, const void* src, const size_t size)
{
    if ((reinterpret_cast<u64>(dest) % sizeof(dest)) == 0)
        return memcpy(dest, src, size);

    return memmove(dest, src, size);
}
}; /* namespace utils */
