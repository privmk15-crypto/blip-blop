/******************************************************************
 *
 *		----------------
 *		 PhaseClock.h
 *		----------------
 *
 *		Owns phase/slow_phase (globals.h/.cpp before this migration):
 *		a blink timer many sprites poll to synchronize flashing/
 *		blinking animations (Couille invincibility flicker, several
 *		FondXxx decor classes, EnnemiToad, EnnemiBisouZombi, ...).
 *		Advanced once per Game::update() frame via Tick(); reset to
 *		false/false on restore via Reset().
 *
 *		Owned by GameState (game_state.h) as g_game_state.phase_clock()
 *		as part of the Stage 2 ownership migration.
 *
 ******************************************************************/

#pragma once

class PhaseClock {
   public:
    bool phase() const { return phase_; }
    bool slow_phase() const { return slow_phase_; }

    // Matches the original Game::update():
    // phase = !phase; if (phase) slow_phase = !slow_phase;
    void Tick() {
        phase_ = !phase_;
        if (phase_) slow_phase_ = !slow_phase_;
    }

    void Reset() {
        phase_ = false;
        slow_phase_ = false;
    }

   private:
    bool phase_ = false;
    bool slow_phase_ = false;
};

// Owned by GameState (game_state.h) as g_game_state.phase_clock() - no
// standalone global instance here anymore.
