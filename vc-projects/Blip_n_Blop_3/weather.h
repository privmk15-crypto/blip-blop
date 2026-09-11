/******************************************************************
 *
 *		----------------
 *		   Weather.h
 *		----------------
 *
 *		Owns the current weather effect knobs (intensite_meteo/
 *		type_meteo, globals.h/.cpp before this migration) that drive
 *		Game's updateMeteo()/drawDeformation() and the rain/snow
 *		particle spawner.
 *
 *		Owned by GameState (game_state.h) as g_game_state.weather()
 *		because EventMeteo::doEvent() - like the other Stage 2
 *		Event-triggered state - has no reachable Game/GameState
 *		instance to call through.
 *
 ******************************************************************/

#pragma once

class Weather {
   public:
    void Set(int intensite, int type);

    // Matches the original level-reset block, which only zeroed
    // intensite_meteo - type_meteo was deliberately left untouched there
    // too.
    void ResetIntensite();

    int intensite() const { return intensite_; }
    int type() const { return type_; }

   private:
    int intensite_ = 0;
    int type_ = 0;
};

// Owned by GameState (game_state.h) as g_game_state.weather() - no
// standalone global instance here anymore.
