/******************************************************************
 *
 *		----------------
 *		  HoldFire.h
 *		----------------
 *
 *		Owns the "hold fire" state (hold_fire/flag_hold_fire/
 *		val_hold_fire, globals.h/.cpp before this migration): when
 *		active, Couille::fire logic won't let a player shoot until
 *		game_flag[flag()] == val() (checked in
 *		Game::updateHoldFire()), which then releases it.
 *
 *		A single g_hold_fire instance is used (rather than a Game
 *		member) because EventHoldFire::doEvent() has no reachable
 *		Game instance to call through.
 *
 *		Two distinct activation call sites existed before this
 *		migration and are preserved as two distinct methods, not
 *		merged: EventHoldFire::doEvent() sets the flag/val release
 *		condition together with activating (Engage());
 *		Game::updateVictoryAndDefeat() only ever set the bool
 *		directly, without touching flag_hold_fire/val_hold_fire
 *		(Activate()) - preserved exactly, including whatever stale
 *		flag()/val() that leaves in place.
 *
 ******************************************************************/

#pragma once

class HoldFire {
   public:
    void Engage(int flag, int val);
    void Activate();
    void Release();

    bool active() const { return active_; }
    int flag() const { return flag_; }
    int val() const { return val_; }

   private:
    bool active_ = false;
    int flag_ = 0;
    int val_ = 0;
};

extern HoldFire g_hold_fire;
