/******************************************************************
 *
 *		----------------
 *		 RpgTrigger.h
 *		----------------
 *
 *		Owns rpg_to_play (globals.h/.cpp before this migration):
 *		which RPG cutscene phase (-1 = none) EventRPG has queued up
 *		for Game::updateRPG() to play.
 *
 *		A single g_rpg_trigger instance is used (rather than a Game
 *		member) because EventRPG::doEvent() has no reachable Game
 *		instance to call through.
 *
 ******************************************************************/

#pragma once

class RpgTrigger {
   public:
    void Set(int num) { num_ = num; }
    void Clear() { num_ = -1; }
    int num() const { return num_; }

   private:
    int num_ = -1;  // -1: none pending, matches the original's initializer
};

extern RpgTrigger g_rpg_trigger;
