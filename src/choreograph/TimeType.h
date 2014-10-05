/*
 * Copyright (c) 2014 David Wicks, sansumbrella.com
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or
 * without modification, are permitted provided that the following
 * conditions are met:
 *
 * Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 * Redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#pragma once

#include <cmath>

namespace choreograph
{

///
/// Choreograph uses float to measure Time by default.
/// We use an alias so it's easier to change out if needed.
/// Float loses precision pretty quickly, but is fast and doesn't take up much space.
/// Double works nicely when adding together lots of little bits or if you need long sequences (over 8 hours).
/// To use double for time instead, #define CHOREOGRAPH_USE_DOUBLE_TIME before any inclusion of Choreograph.
///
#if defined( CHOREOGRAPH_USE_DOUBLE_TIME )
  using Time = double;
#else
  using Time = float;
#endif

/// Wrap \a time past \a duration around \a inflectionPoint.
inline Time wrapTime( Time time, Time duration, Time inflectionPoint=0.0f )
{
  if( time > duration ) {
    return inflectionPoint + std::fmod( time, duration - inflectionPoint );
  }
  else {
    return time;
  }
}

} // namespace choreograph