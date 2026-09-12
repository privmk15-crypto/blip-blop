#include "main_menu.h"

#include "../control_alias.h"
#include "../game_state.h"
#include "../globals.h"
#include "../input.h"
#include "../txt_data.h"
#include "txt_defines.h"

MainMenu::MainMenu() {
    items_.AddEntry(txt_data[TXT_START_GAME]);
    items_.AddEntry("OPTIONS");
    items_.AddEntry(txt_data[TXT_EXIT]);
}

void MainMenu::Draw(SDL::Surface* surf) const {
    items_.Draw(surf);

    // Small edition watermark, bottom-left corner - only on the main
    // menu screen itself, not carried into Options/Start/etc.
    //
    // Fix: y=462 clipped most of the glyphs off the bottom edge of the
    // 480-tall surface (only their very top sliver was visible -
    // looked like garbled fragments instead of readable text). Moved
    // up so the whole line fits with real margin below it.
    g_game_state.font_bank().menu().print(
        surf, 10, 440, "Blip&Blop: Rearmed Edition");
}

int MainMenu::ProcessEvent() {
    if (in.scanKey(DIK_UP) || in.scanAlias(ALIAS_P1_UP)) {
        items_.MoveUp();
    } else if (in.scanKey(DIK_DOWN) || in.scanAlias(ALIAS_P1_DOWN)) {
        items_.MoveDown();
    }
    if (in.scanKey(DIK_RETURN) || in.scanAlias(ALIAS_P1_FIRE)) {
        switch (items_.focused()) {
            case 0:
                return MenuType::Start;
            case 1:
                return MenuType::Options;
            case 2:
                return MenuType::Exit;
        }
    }
    return MenuType::Main;
}
