/*
 * Copyright (c) 2015 David Wicks, sansumbrella.com
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

#include "TimelineItem.h"
#include "Sequence.hpp"

namespace choreograph
{

/// Adds knowledge of the current time to a Sequence, making it steppable.
/// I think this will be useful for things like entity systems where we are avoiding pointer chasing.
/// Can then describe animations in terms of components without pointing into other components (making easily serializable).
template<typename T>
class SimpleMotion
{
  SimpleMotion() = default;

  explicit SimpleMotion( const T &value )
  : _value( value ),
    _source( value )
  {}

  /// Create a SimpleMotion from a Sequence.
  explicit SimpleMotion( const Sequence<T> &source )
  : _value( source.getStartValue() ),
    _source( source )
  {}

  void step( Time t ) { _time += t; update(); }
  void jumpTo( Time t ) { _time = t; update(); }

  void update() { _value = _source.getValue( time() ); }

  Time duration() const { return _source.getDuration(); }

  bool finished() const { return time() > duration(); }

  Time time() const { return _time; }

  const T&      value() const { return _value; }
  Sequence<T>&  sequence() { return _source; }

private:
  T           _value;
  Time        _time = 0;
  Sequence<T> _source = Sequence<T>( _value );
};

}