/******************************************************************
 *
 *		----------------
 *		 EnemyStats.h
 *		----------------
 *
 *		Owns nb_ennemis_created (globals.h/.cpp before this
 *		migration): a running count of enemies spawned this level,
 *		incremented from several EnnemiXxx::update()/EventEnnemi::
 *		doEvent() spawn sites and reset to 0 on level (re)load
 *		(Game::chargeNiveau()). Used by Game::drawKillPercent() to
 *		compute each player's kill percentage.
 *
 *		Owned by GameState (game_state.h) as g_game_state.enemy_stats()
 *		as part of the Stage 2 ownership migration.
 *
 ******************************************************************/

#pragma once

class EnemyStats {
   public:
    int created() const { return created_; }
    void Add(int n = 1) { created_ += n; }
    void Reset() { created_ = 0; }

   private:
    int created_ = 0;
};

// Owned by GameState (game_state.h) as g_game_state.enemy_stats() - no
// standalone global instance here anymore.
