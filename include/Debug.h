#pragma once
#include <iostream>

// LOG_DEBUG: stream-style debug logging.
// Usage:  LOG_DEBUG << "x=" << x << "\n";
//
// In debug builds (default), writes to stdout.
// In release builds (-DNDEBUG), the entire expression is dead code — the
// compiler eliminates it completely. The if(false) form keeps type-checking
// intact while guaranteeing zero runtime overhead.

#ifndef NDEBUG
#define LOG_DEBUG std::cout
#else
#define LOG_DEBUG if (false) std::cout
#endif
