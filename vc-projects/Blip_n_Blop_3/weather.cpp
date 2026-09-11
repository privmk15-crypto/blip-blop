/******************************************************************
 *
 *		----------------
 *		   Weather.cpp
 *		----------------
 *
 *		See weather.h for the Stage 2 migration note.
 *
 ******************************************************************/

#include "weather.h"

Weather g_weather;

void Weather::Set(int intensite, int type) {
    intensite_ = intensite;
    type_ = type;
}

void Weather::ResetIntensite() { intensite_ = 0; }
