/******************************************************************
 *
 *		----------------
 *		    Level.h
 *		----------------
 *
 *		Owns level geometry data: scr_level_size, level_size,
 *		num_decor, murs_sanglants, y_plat, and murs_opaques
 *		(globals.h/.cpp before this migration).
 *
 *		y_plat/murs_opaques follow-up note: these two were originally
 *		excluded from the first Level migration pass because ~26
 *		entity .cpp files read/write them directly (y_plat[i][x],
 *		murs_opaques[i][j]) rather than only through
 *		plat()/plat2()/mur_opaque() - unlike murs_sanglants, which
 *		was and remains fully reached through mur_sanglant() alone.
 *		Also unlike the first pass, game.cpp is NOT the only writer:
 *		fond_monolite.cpp mutates y_plat directly, and
 *		fond_snork_sas.cpp/ennemi_pic.cpp mutate murs_opaques
 *		directly, at runtime (e.g. a platform moving updates the
 *		collision grid). This migration keeps those exact direct
 *		read/write sites working unchanged in shape - they now go
 *		through g_game_state.level().y_plat()/.murs_opaques()
 *		(returning the raw int** or bool** pointer, same as before)
 *		instead of a bare global name; still direct pointer/array
 *		access after that, not hidden behind new accessor methods,
 *		to keep this a mechanical rename rather than a behavior
 *		change.
 *
 *		Owned by GameState (game_state.h) as g_game_state.level()
 *		because plat()/plat2()/mur_opaque()/mur_sanglant()
 *		(globals.cpp) - callable from ~100+ entity files with no
 *		reachable Game/GameState instance - need to read
 *		size()/murs_sanglants() even though Game::chargeNiveau()/
 *		releaseNiveau() are the only writers.
 *
 *		Allocation/loading logic (reading the level file) stays in
 *		Game::chargeNiveau() as before; this class only owns the
 *		storage and the alloc/free of num_decor/murs_sanglants,
 *		matching pre-migration ownership exactly (properly delete[]'d
 *		in Game::releaseNiveau(), not leaked).
 *
 ******************************************************************/

#pragma once

class Level {
   public:
    void set_scr_size(int v) { scr_size_ = v; }
    void set_size(int v) { size_ = v; }

    // Allocates num_decor as `new int[count]` and returns it so the caller
    // can fill it in - mirrors the original inline `new` + read loop in
    // Game::chargeNiveau().
    int* AllocNumDecor(int count);

    // Allocates murs_sanglants as 60 rows of `new bool[row_size]` each and
    // returns it - same reasoning as above.
    bool** AllocMursSanglants(int row_size);

    // Allocates y_plat as NB_MAX_PLAT (8) rows of `new int[row_size]` each
    // and returns it - same reasoning as above.
    int** AllocYPlat(int row_size);

    // Allocates murs_opaques as 60 rows of `new bool[row_size]` each and
    // returns it - same reasoning as above.
    bool** AllocMursOpaques(int row_size);

    // Frees num_decor/murs_sanglants/y_plat/murs_opaques and nulls all
    // four. Mirrors the original Game::releaseNiveau() logic exactly -
    // scr_size()/size() are deliberately left untouched, matching the
    // original, which never reset scr_level_size/level_size on release
    // either.
    void Release();

    int scr_size() const { return scr_size_; }
    int size() const { return size_; }
    int* num_decor() const { return num_decor_; }
    bool** murs_sanglants() const { return murs_sanglants_; }
    // Raw pointers, same as before this migration - callers index them
    // directly (y_plat()[i][x], murs_opaques()[i][j]), not hidden behind
    // further accessors. See the class-level comment for why.
    int** y_plat() const { return y_plat_; }
    bool** murs_opaques() const { return murs_opaques_; }

   private:
    int scr_size_ = 0;
    int size_ = 0;
    int* num_decor_ = nullptr;
    bool** murs_sanglants_ = nullptr;
    int** y_plat_ = nullptr;
    bool** murs_opaques_ = nullptr;
};

// Owned by GameState (game_state.h) as g_game_state.level() - no
// standalone global instance here anymore.
