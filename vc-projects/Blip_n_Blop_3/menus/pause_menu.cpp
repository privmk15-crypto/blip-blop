#include "pause_menu.h"

#include "../control_alias.h"
#include "../input.h"
#include "../txt_data.h"
#include "txt_defines.h"

PauseMenu::PauseMenu() {
    items_.AddEntry(txt_data[TXT_RESUME]);
    items_.AddEntry(txt_data[TXT_OPTIONS]);
    items_.AddEntry(txt_data[TXT_EXIT]);
}
int PauseMenu::ProcessEvent() {
    if (in.scanKey(DIK_UP) || in.scanAlias(ALIAS_P1_UP)) {
        items_.MoveUp();
    } else if (in.scanKey(DIK_DOWN) || in.scanAlias(ALIAS_P1_DOWN)) {
        items_.MoveDown();
    }
    if (in.scanKey(DIK_RETURN) || in.scanAlias(ALIAS_P1_FIRE)) {
        switch (items_.focused()) {
            case 0:
                return MenuType::Game_1;
            case 1:
                return MenuType::Options;
            case 2:
                return MenuType::Exit;
        }
        return MenuType::Main;
    }
    // Fix: fell off the end here when neither key was pressed, returning
    // whatever garbage happened to be on the stack (-Wreturn-type),
    // which MenuGame::Update() then fed into a switch on MenuType.
    // MenuType::Main is what MenuGame::Update() already treats as "stay
    // in the pause menu" (case MenuType::Main: active_ = &pause_menu_;),
    // matching the same fallback-to-self pattern every sibling menu
    // (StartMenu/MainMenu/KeysMenu) already uses.
    return MenuType::Main;
}
