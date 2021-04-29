#ifndef STANDARTSCREENVIEW_HPP
#define STANDARTSCREENVIEW_HPP

#include <gui_generated/standartscreen_screen/StandartScreenViewBase.hpp>
#include <gui/standartscreen_screen/StandartScreenPresenter.hpp>

class StandartScreenView : public StandartScreenViewBase
{
public:
    StandartScreenView();
    virtual ~StandartScreenView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
    virtual void show(uint8_t number);
    virtual void handleTickEvent();
    virtual void loginbuttonClicked();
    virtual void logoutButtonClicked();
    int tickCounter=0;
protected:
};

#endif // STANDARTSCREENVIEW_HPP
