/******************************************************************
 *
 *		----------------
 *		    Level.cpp
 *		----------------
 *
 *		See level.h for the Stage 2 migration note.
 *
 ******************************************************************/

#include "level.h"

int* Level::AllocNumDecor(int count) {
    num_decor_ = new int[count];
    return num_decor_;
}

bool** Level::AllocMursSanglants(int row_size) {
    murs_sanglants_ = new bool*[60];

    for (int i = 0; i < 60; i++) {
        murs_sanglants_[i] = new bool[row_size];
    }

    return murs_sanglants_;
}

int** Level::AllocYPlat(int row_size) {
    // 8 == NB_MAX_PLAT (globals.h/game.h), matching the original inline
    // `new int*[NB_MAX_PLAT]` in Game::chargeNiveau().
    y_plat_ = new int*[8];

    for (int i = 0; i < 8; i++) {
        y_plat_[i] = new int[row_size];
    }

    return y_plat_;
}

bool** Level::AllocMursOpaques(int row_size) {
    murs_opaques_ = new bool*[60];

    for (int i = 0; i < 60; i++) {
        murs_opaques_[i] = new bool[row_size];
    }

    return murs_opaques_;
}

void Level::Release() {
    if (num_decor_ != nullptr) {
        delete[] num_decor_;
        num_decor_ = nullptr;
    }

    if (y_plat_ != nullptr) {
        for (int i = 0; i < 8; i++) delete[] y_plat_[i];

        delete[] y_plat_;
        y_plat_ = nullptr;
    }

    if (murs_sanglants_ != nullptr) {
        for (int i = 0; i < 60; i++) delete[] murs_sanglants_[i];

        delete[] murs_sanglants_;
        murs_sanglants_ = nullptr;
    }

    if (murs_opaques_ != nullptr) {
        for (int i = 0; i < 60; i++) delete[] murs_opaques_[i];

        delete[] murs_opaques_;
        murs_opaques_ = nullptr;
    }
}
