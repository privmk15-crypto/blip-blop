/******************************************************************
 *
 *		----------------
 *		    Level.h
 *		----------------
 *
 *		Owns level geometry data: scr_level_size, level_size,
 *		num_decor, and murs_sanglants (globals.h/.cpp before this
 *		migration).
 *
 *		Stage 2 migration note: deliberately EXCLUDES y_plat and
 *		murs_opaques, which are also level geometry but have a much
 *		wider direct-array-access footprint across entity .cpp files
 *		(not fully reached through plat()/plat2()/mur_opaque() the
 *		way murs_sanglants is fully reached through mur_sanglant()) -
 *		migrating those needs a separate, more careful pass. See the
 *		Stage 2 Phase 1 globals.h inventory.
 *
 *		A single g_level instance is used (rather than a Game member)
 *		because plat()/plat2()/mur_opaque()/mur_sanglant()
 *		(globals.cpp) - callable from ~100+ entity files with no
 *		reachable Game instance - need to read size()/murs_sanglants()
 *		even though Game::chargeNiveau()/releaseNiveau() are the only
 *		writers.
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

    // Frees num_decor/murs_sanglants and nulls both. Mirrors the original
    // Game::releaseNiveau() logic exactly - scr_size()/size() are
    // deliberately left untouched, matching the original, which never
    // reset scr_level_size/level_size on release either.
    void Release();

    int scr_size() const { return scr_size_; }
    int size() const { return size_; }
    int* num_decor() const { return num_decor_; }
    bool** murs_sanglants() const { return murs_sanglants_; }

   private:
    int scr_size_ = 0;
    int size_ = 0;
    int* num_decor_ = nullptr;
    bool** murs_sanglants_ = nullptr;
};

extern Level g_level;
