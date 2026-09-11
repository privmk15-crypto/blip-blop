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
 *		A single g_weather instance is used (rather than a Game
 *		member) because EventMeteo::doEvent() - like the other Stage
 *		2 Event-triggered globals - has no reachable Game instance to
 *		call through.
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

extern Weather g_weather;
