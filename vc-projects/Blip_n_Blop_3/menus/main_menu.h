#pragma once

#include "abstract_menu.h"
#include "menu_list.h"

class MainMenu : public AbstractMenu {
   public:
    MainMenu();
    void Draw(SDL::Surface* surf) const override;
    int ProcessEvent();

   private:
    MenuList items_;
};
