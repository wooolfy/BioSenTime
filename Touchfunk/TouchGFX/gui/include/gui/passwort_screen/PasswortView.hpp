#ifndef PASSWORTVIEW_HPP
#define PASSWORTVIEW_HPP

#include <gui_generated/passwort_screen/PasswortViewBase.hpp>
#include <gui/passwort_screen/PasswortPresenter.hpp>

class PasswortView : public PasswortViewBase
{
public:
    PasswortView();
    virtual ~PasswortView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
    virtual void ButtonClicked1();
    virtual void Button2clicked();
    virtual void Button3Clicked();
    virtual void Button4cklicked();
    virtual void Button5Clicked();
    virtual void Button6Clicked();
    virtual void Button7Clicked();
    virtual void Button8Clicked();
    virtual void Button9Clicked();
    virtual void Button0Clicked();

protected:
};

#endif // PASSWORTVIEW_HPP
