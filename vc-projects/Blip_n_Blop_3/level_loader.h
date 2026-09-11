/******************************************************************
 *
 *		----------------
 *		 LevelLoader.h
 *		----------------
 *
 *		Owns the level-file parsing logic that used to live in
 *		Game::chargeNiveau() (game.cpp before this migration): reads
 *		a .niv-style binary level file, loads its picture/sound
 *		banks, allocates and fills Level's geometry
 *		(g_game_state.level()), attaches the level's RPG cutscene
 *		file, and pushes its Event objects into
 *		g_game_state.entities().list_event_endormis().
 *
 *		The binary file format is completely unchanged - same field
 *		order, same sizes, same fic.read() calls - this is a pure
 *		code-location move, not a format change (per instruction: do
 *		not change the level format unless necessary, and it isn't
 *		here).
 *
 *		Two pieces of data read from the file were Game members
 *		before this migration (xstart1/ystart1/xstart2/ystart2 -
 *		player start coordinates - and vic_x/vic_flag1/vic_val1/
 *		vic_flag2/vic_val2 - victory conditions): LevelLoader doesn't
 *		know about Game, so it fills a Result out-parameter instead;
 *		Game::chargeNiveau() copies those into its own members after
 *		a successful load, exactly preserving their previous values
 *		and meaning.
 *
 *		RPGPlayer& is passed in (rather than reached via GameState)
 *		because it's still a Game-owned member (game.h's `rpg`), not
 *		part of GameState.
 *
 ******************************************************************/

#pragma once

class RPGPlayer;

class LevelLoader {
   public:
    // Player start coordinates and victory conditions read from the
    // level file - previously Game::xstart1/ystart1/xstart2/ystart2 and
    // Game::vic_x/vic_flag1/vic_val1/vic_flag2/vic_val2.
    struct Result {
        int xstart1 = 0;
        int ystart1 = 0;
        int xstart2 = 0;
        int ystart2 = 0;

        int vic_x = 0;
        int vic_flag1 = 0;
        int vic_val1 = 0;
        int vic_flag2 = 0;
        int vic_val2 = 0;
    };

    // Equivalent to the old Game::chargeNiveau(nom_niveau). Returns
    // false (after logging via debug<<, exactly as before) on any
    // I/O or asset-load failure. On success, fills `out`.
    bool Load(const char* nom_niveau, RPGPlayer& rpg, Result& out);
};
