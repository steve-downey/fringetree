include_guard(GLOBAL)

set(CMAKE_C_COMPILER gcc-14)
set(CMAKE_CXX_COMPILER g++-14)

set(CMAKE_CXX_STANDARD 23)

set(CMAKE_CXX_FLAGS
  "-Wall -Wextra "
CACHE STRING "CXX_FLAGS" FORCE)

set(CMAKE_CXX_FLAGS_DEBUG "-O0 -fno-inline -g3" CACHE STRING "C++ DEBUG Flags" FORCE)
set(CMAKE_CXX_FLAGS_RELEASE "-Ofast -g0 " CACHE STRING "C++ Release Flags" FORCE)
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-O3 -g " CACHE STRING "C++ RelWithDebInfo Flags" FORCE)
set(CMAKE_CXX_FLAGS_TSAN "-O3 -g -fsanitize=thread" CACHE STRING "C++ TSAN Flags" FORCE)
set(CMAKE_CXX_FLAGS_ASAN "-O3 -g -fsanitize=address,undefined,leak" CACHE STRING "C++ ASAN Flags" FORCE)
