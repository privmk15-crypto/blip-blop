/******************************************************************
 *
 *		----------------
 *		 DebugStats.h
 *		----------------
 *
 *		Owns fps_count/fps_current_count/total_debug (globals.h/.cpp
 *		before this migration): the FPS counter pair shown by
 *		Game::drawDebugInfos() (fps_current_count is incremented once
 *		per Game::update() and rolled over into fps_count on each
 *		WM_TIMER tick in WinProc, blip_n_blop_3.cpp), and the
 *		total_debug toggle read by the TRACE macro (trace.h). Never
 *		set to true anywhere in the codebase - TRACE is currently
 *		always a no-op - but preserved with a setter for parity with
 *		the original extern bool.
 *
 *		Owned by GameState (game_state.h) as g_game_state.debug_stats()
 *		as part of the Stage 2 ownership migration.
 *
 ******************************************************************/

#pragma once

class DebugStats {
   public:
    int fps_count() const { return fps_count_; }
    int fps_current_count() const { return fps_current_count_; }
    void IncrementFpsCurrent() { fps_current_count_++; }
    // Matches the original WM_TIMER handler in blip_n_blop_3.cpp:
    // fps_count = fps_current_count; fps_current_count = 0;
    void RolloverFps() {
        fps_count_ = fps_current_count_;
        fps_current_count_ = 0;
    }

    bool total_debug() const { return total_debug_; }
    void set_total_debug(bool v) { total_debug_ = v; }

   private:
    int fps_count_ = 0;
    int fps_current_count_ = 0;
    bool total_debug_ = false;
};

// Owned by GameState (game_state.h) as g_game_state.debug_stats() - no
// standalone global instance here anymore.
