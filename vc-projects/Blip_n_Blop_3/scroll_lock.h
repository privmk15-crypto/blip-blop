/******************************************************************
 *
 *		----------------
 *		 ScrollLock.h
 *		----------------
 *
 *		Owns the scroll-lock state used by EventLock to pin the
 *		camera at a given x until a level-scripted condition is met
 *		(list_ennemis/list_gen_ennemis/game_flag - see
 *		Game::updateLock()).
 *
 *		Stage 2 migration: replaces five independent globals
 *		(scroll_locked, x_lock, cond_end_lock, flag_end_lock,
 *		val_end_lock; globals.h/.cpp) with one object, owned by
 *		GameState (game_state.h) as g_game_state.scroll_lock() -
 *		because EventLock::doEvent() - like tremblement()'s callers
 *		in the screen-shake migration - has no reachable Game/
 *		GameState instance to call through.
 *
 *		This class only stores what was locked and whether it's
 *		active; the condition check itself (list_ennemis.empty(),
 *		game_flag[...], etc.) stays in Game::updateLock(), which
 *		already owns those other globals - ScrollLock isn't the
 *		right owner for logic that reads entity lists and game_flag.
 *
 ******************************************************************/

#pragma once

class ScrollLock {
   public:
    // Engages the lock. Equivalent to the field assignments that used to
    // be in EventLock::doEvent().
    void Engage(int x, int cond, int flag, int val);

    // Releases the lock. Equivalent to the old `scroll_locked = false;`.
    void Release();

    bool active() const { return active_; }
    int x() const { return x_; }
    int cond() const { return cond_; }
    int flag() const { return flag_; }
    int val() const { return val_; }

   private:
    bool active_ = false;
    int x_ = 0;
    int cond_ = 0;
    int flag_ = 0;
    int val_ = 0;
};

// Owned by GameState (game_state.h) as g_game_state.scroll_lock() - no
// standalone global instance here anymore.
