/******************************************************************
 *
 *		----------------
 *		 ScreenShake.cpp
 *		----------------
 *
 *		See screen_shake.h for the Stage 2 migration note. Logic in
 *		this file is copied verbatim from the pre-migration
 *		free function tremblement() and Game::updateTremblements() /
 *		Game::drawTremblements() (globals.cpp / game.cpp) - only the
 *		storage (four globals -> one object's private fields) and the
 *		hardcoded backSurface (-> an explicit Draw() parameter)
 *		changed.
 *
 ******************************************************************/

#include "screen_shake.h"

#include <cstring>

#include "globals.h"  // for tremblement()'s declaration
#include "graphics.h"

ScreenShake g_screen_shake;

void tremblement(int amp) { g_screen_shake.Start(amp); }

void ScreenShake::Start(int amp) {
    amplitude_ = amp;
    ddy_ = (amp >> 1) + 1;
    dy_ = -amp;
    etape_ = 0;
}

void ScreenShake::Update() {
    if (amplitude_ == 0) return;

    if (etape_ == 0) {
        dy_ += ddy_;

        if (dy_ <= -amplitude_) {
            amplitude_ -= 1;
            ddy_ = (amplitude_ >> 1) + 1;
            dy_ += 1;
        } else if (dy_ >= amplitude_) {
            amplitude_ -= 1;
            ddy_ = -(amplitude_ >> 1) - 1;
            dy_ -= 1;
        }
    }
}

void ScreenShake::Draw(SDL::Surface* surf) {
    if (amplitude_ == 0 || dy_ == 0) return;

    int y;
    Rect r;
    Rect r2;

    r2.left = r.left = 0;
    r2.right = r.right = 640;

    if (dy_ < 0) {
        r.top = -dy_;
        r.bottom = 480;

        r2.top = 480 + dy_;
        r2.bottom = 480;

        y = 0;
    } else if (dy_ > 0) {
        r.top = 0;
        r.bottom = 480 - dy_;

        r2.top = 0;
        r2.bottom = dy_;

        y = dy_;
    }

    surf->BltFast(0, y, surf, &r, DDBLTFAST_WAIT | DDBLTFAST_NOCOLORKEY);

    DDBLTFX ddfx;

    memset(&ddfx, 0, sizeof(ddfx));
    ddfx.dwSize = sizeof(ddfx);
    ddfx.dwFillColor = 0;

    surf->Blt(&r2, NULL, NULL, DDBLT_COLORFILL | DDBLT_WAIT, &ddfx);
}

void ScreenShake::Reset() {
    dy_ = 0;
    etape_ = 0;
    amplitude_ = 0;
    // ddy_ deliberately not reset - matches pre-migration behavior.
}
