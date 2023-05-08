#pragma once

#include "Shaddock/Core/PlatformDetection.h"

#ifdef SD_PLATFORM_WINDOWS
	#ifndef NOMINMAX
	// See github.com/skypjack/entt/wiki/Frequently-Asked-Questions#warning-c4003-the-min-the-max-and-the-macro
		#define NOMINMAX
	#endif
#endif

#include <iostream>
#include <memory>
#include <utility>
#include <algorithm>
#include <functional>
#include <array>

#include <string>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <unordered_set>

#include "Shaddock/Core/Base.h"
#include "Shaddock/Core/Log.h"
#include "Shaddock/Debug/Instrumentor.h"

#ifdef SD_PLATFORM_WINDOWS
	#include <Windows.h>
#endif