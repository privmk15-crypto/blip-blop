#pragma once

#include "ben_maths.h"
#include "globals.h"
#include "game_state.h"

class GoArrow {
    enum class Phase { Coming, Bouncing, Leaving, No };
    static const int kNbSprites = 5;
    static const int kSpriteDuration = 4;

   public:
    GoArrow() { Reset(); }

    void Reset() {
        x_ = -10;
        phase_ = Phase::No;
        delay_ = 0;
        anim_step_ = 1;
    }

    void Update() {
        switch (phase_) {
            case Phase::No:
                update_no();
                return;
            case Phase::Coming:
                update_coming();
                return;
            case Phase::Bouncing:
                update_bouncing();
                return;
            case Phase::Leaving:
                update_leaving();
                return;
        }
    }

    void Leave() {
        if (phase_ != Phase::No) {
            phase_ = Phase::Leaving;
        } else {
            delay_ = 0;
        }
    }

    void Come() {
        if (phase_ == Phase::No) {
            phase_ = Phase::Coming;
        }
    }

    void Draw() {
        if (phase_ != Phase::No) {
            g_game_state.picture_banks().misc()[81 + anim_step_ / kSpriteDuration]->BlitTo(
                backSurface, x_, 150);
        }
    }

   private:
    void update_no() {
        // Fix: this used to tick delay_ unconditionally, so the "been
        // idle a while, here's a hint arrow" timeout could (and did)
        // fire while an active scroll lock's real release condition
        // still hadn't been met - showing the arrow well before the
        // screen could actually move, only for the real scroll to
        // start later once the lock genuinely released. Reported as
        // the GO arrow appearing, then the screen only advancing
        // "po chwili" (after a moment). While a lock is active, hold
        // this timer at 0 instead - Come() (called from
        // Game::updateLock() the instant the lock's real condition is
        // met) is the only thing that should ever show the arrow in
        // that case; the idle-nudge timeout is only meaningful when
        // there's no lock gating progress at all.
        if (g_game_state.scroll_lock().active()) {
            delay_ = 0;
            return;
        }

        delay_ += 1;
        if (delay_ >= 300) {
            phase_ = Phase::Coming;
        }
    }

    void update_coming() {
        update_anim();
        x_ += 10;
        // Etap 4 (Full HD prep, step 3): >= rather than == SCREEN_W -
        // x_ steps by 10 from -10, which lands exactly on 640 but
        // would overshoot the new SCREEN_W (854) and never satisfy an
        // exact equality, leaving the arrow stuck in Coming forever.
        if (x_ >= SCREEN_W) {
            phase_ = Phase::Bouncing;
            theta_ = 0;
        }
    }

    void update_bouncing() {
        update_anim();

        theta_ = (theta_ + 3) % 360;
        int x = sini(100, theta_);

        if (x < 0) {
            x = -x;
        }

        x_ = SCREEN_W - x;
    }

    void update_leaving() {
        update_anim();
        x_ += 10;
        // Etap 4 (Full HD prep, step 3): was a bare 800 (640 + 160
        // margin) - kept the same margin past the new SCREEN_W so the
        // arrow still fully leaves the visible area before resetting.
        if (x_ > SCREEN_W + 160) {
            Reset();
        }
    }

    void update_anim() {
        anim_step_ = (anim_step_ + 1) % (kNbSprites * kSpriteDuration);
    }

    Phase phase_;
    int theta_;
    int delay_;
    int x_;
    int anim_step_;
};
