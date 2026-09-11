#include "options_menu.h"

#include "../input.h"

int OptionsMenu::ProcessEvent() {
    // Fix: this used to call in.update() and in.waitClean() itself, on
    // top of what TitleScreen::update() (its only caller) already does
    // immediately before and after calling active_menu_->ProcessEvent()
    // (see menu_main.cpp). Every other menu (MainMenu/StartMenu/
    // OptionsPanel/KeysMenu) relies solely on the caller's single
    // update()+waitClean() pair and never touches `in` directly outside
    // scanKey()/scanAlias() - OptionsMenu was the only one duplicating
    // that work, which only matters when this is the active top-level
    // menu (i.e. inside Options and its Keys_1/Keys_2 sub-menus, not
    // Main/Start) - matching the reported "sometimes picks something
    // other than what's highlighted" happening intermittently rather
    // than everywhere. Now just dispatches to the active sub-menu and
    // interprets its result, like TitleScreen does for its own
    // top-level menus.
    MenuType next = MenuType(active_menu_->ProcessEvent());
    switch (next) {
        case MenuType::Main:
            return MenuType::Main;
        case MenuType::Options:
            active_menu_ = &options_menu_;
            break;
        case MenuType::Keys_1:
            active_menu_ = &p1_menu_;
            break;
        case MenuType::Keys_2:
            active_menu_ = &p2_menu_;
            break;
    }
    return MenuType::Options;
}
