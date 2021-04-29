#ifndef ADMINCENTERVIEW_HPP
#define ADMINCENTERVIEW_HPP

#include <gui_generated/admincenter_screen/AdminCenterViewBase.hpp>
#include <gui/admincenter_screen/AdminCenterPresenter.hpp>

class AdminCenterView : public AdminCenterViewBase
{
public:
    AdminCenterView();
    virtual ~AdminCenterView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
    virtual void uscerCountButtonClicked();
    virtual void deleteAllUserButtonClicked();
    virtual void deleteUserButtonClicked();
    virtual void verifyUserButtonClicked();
    virtual void addUserButtonClicked();
    virtual void deactivateAutoVerify();
    virtual void activateAutoVerify();
    virtual void showMSG(short int newText);
protected:
};

#endif // ADMINCENTERVIEW_HPP
