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
#include <mwutils/helpers.hpp>
#include <random>
#include <chrono>

namespace mwutils {
namespace random {
static std::mt19937 rng;

void seed_rng(void)
{
    rng.seed(std::chrono::high_resolution_clock::now().time_since_epoch().count());
}

s32 get_random(s32 min, s32 max)
{
    min < INT32_MIN ? min = INT32_MIN : min;
    max > INT32_MAX ? max = INT32_MAX : max;

    std::uniform_int_distribution<s32>  uniform(min, max);

    return (uniform(rng));
}

bool get_random(void)
{
    return random::get_random(0, 1);
}
}; /* namespace random */
}; /* namespace utils */
