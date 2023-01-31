//==============================================================================
// The MIT License (MIT)
//
// Copyright (c) 2023 Victor Matia <vmatir@gmail.com>
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the “Software”), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//==============================================================================

#ifndef CELTRE_SOFTWARE_SDL2_CPP_DIRECT_SUBSYSTEMS_HPP
#define CELTRE_SOFTWARE_SDL2_CPP_DIRECT_SUBSYSTEMS_HPP

#include <cstdint>
#include <ostream>
#include <string>
#include <type_traits>

#include <SDL.h>

namespace celtresoft::sdl2cpp_direct {
enum class subsystems {
  none            = 0x00000000U,
  timer           = SDL_INIT_TIMER,
  audio           = SDL_INIT_AUDIO,
  video           = SDL_INIT_VIDEO,
  joystick        = SDL_INIT_JOYSTICK,
  haptic          = SDL_INIT_HAPTIC,
  game_controller = SDL_INIT_GAMECONTROLLER,
  events          = SDL_INIT_EVENTS,

#if SDL_VERSION_ATLEAST(2, 0, 9)
  sensor = SDL_INIT_SENSOR,
#endif // SDLv >= 2.0.9

  no_parachute
#if SDL_VERSION_ATLEAST(2, 0, 4)
  [[deprecated("for compatibility, this flag is ignored")]]
#endif // SDLv >= 2.0.4
  = SDL_INIT_NOPARACHUTE,

  everything = SDL_INIT_EVERYTHING
};

using subsystems_underlying_t = std::underlying_type_t<subsystems>;

auto operator~(subsystems const& obj) -> subsystems {
  return static_cast<subsystems>(~static_cast<subsystems_underlying_t>(obj));
}

auto operator|(subsystems const& lhs, subsystems const& rhs) -> subsystems {
  return static_cast<subsystems>(static_cast<subsystems_underlying_t>(lhs) |
                                 static_cast<subsystems_underlying_t>(rhs));
}

auto operator&(subsystems const& lhs, subsystems const& rhs) -> subsystems {
  return static_cast<subsystems>(static_cast<subsystems_underlying_t>(lhs) &
                                 static_cast<subsystems_underlying_t>(rhs));
}

auto operator^(subsystems const& lhs, subsystems const& rhs) -> subsystems {
  return static_cast<subsystems>(static_cast<subsystems_underlying_t>(lhs) ^
                                 static_cast<subsystems_underlying_t>(rhs));
}

auto operator|=(subsystems& lhs, subsystems const& rhs) -> subsystems& {
  lhs = lhs | rhs;
  return lhs;
}

auto operator&=(subsystems& lhs, subsystems const& rhs) -> subsystems& {
  lhs = lhs & rhs;
  return lhs;
}

auto operator^=(subsystems& lhs, subsystems const& rhs) -> subsystems& {
  lhs = lhs ^ rhs;
  return lhs;
}

auto operator<<(std::ostream& stream, subsystems const& obj) -> std::ostream& {
  using enum celtresoft::sdl2cpp_direct::subsystems;
  std::string final_str{};
  stream << "[";

  auto combine_subsystems = [&const obj, &final_str]() {
    auto concat = [&final_str]() {
      if (!final_str.empty()) {
        final_str += ", ";
      }
    };

    if ((obj & timer) != none) {
      concat();
      final_str = "Timer";
    }

    if ((obj & audio) != none) {
      concat();
      final_str = "Audio";
    }

    if ((obj & video) != none) {
      concat();
      final_str = "Video";
    }

    if ((obj & joystick) != none) {
      concat();
      final_str = "Joystick";
    }

    if ((obj & haptic) != none) {
      concat();
      final_str = "Haptic";
    }

    if ((obj & game_controller) != none) {
      concat();
      final_str = "Game Controller";
    }

    if ((obj & events) != none) {
      concat();
      final_str = "Events";
    }

#if SDL_VERSION_ATLEAST(2, 0, 9)
    if ((obj & sensor) != none) {
      concat();
      final_str = "Sensor";
    }
#endif // SDLv >= 2.0.9

#if !SDL_VERSION_ATLEAST(2, 0, 4)
    if ((obj & subsystems::no_parachute) != subsystems::none) {
      concat();
      final_str = "No Parachute";
    }
#endif // SDLv < 2.0.4
  };

  if (obj == subsystems::none) {
    final_str = "None";
  } else if (obj == subsystems::everything) {
    final_str = "Everything";
  } else {
    combine_subsystems();
  }

  stream << final_str << "]";
  return stream;
}
} // namespace celtresoft::sdl2cpp_direct

#endif // CELTRE_SOFTWARE_SDL2_CPP_DIRECT_SUBSYSTEMS_HPP