
#ifndef TRACE

#include "globals.h"
#include "ben_debug.h"
#include "game_state.h"

#ifdef _DEBUG

#define TRACE if ( g_game_state.debug_stats().total_debug()) debug<<(__FILE__)<<" : "<<(__LINE__)<<"\n";

#else

#define TRACE ;

#endif

#endif
