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

Level g_level;

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

void Level::Release() {
    if (num_decor_ != nullptr) {
        delete[] num_decor_;
        num_decor_ = nullptr;
    }

    if (murs_sanglants_ != nullptr) {
        for (int i = 0; i < 60; i++) delete[] murs_sanglants_[i];

        delete[] murs_sanglants_;
        murs_sanglants_ = nullptr;
    }
}
