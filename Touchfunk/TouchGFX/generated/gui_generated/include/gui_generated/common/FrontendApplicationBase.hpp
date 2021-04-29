/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#ifndef FRONTENDAPPLICATIONBASE_HPP
#define FRONTENDAPPLICATIONBASE_HPP

#include <mvp/MVPApplication.hpp>
#include <gui/model/Model.hpp>

class FrontendHeap;

class FrontendApplicationBase : public touchgfx::MVPApplication
{
public:
    FrontendApplicationBase(Model& m, FrontendHeap& heap);
    virtual ~FrontendApplicationBase() { }

    // StartScreen
    void gotoStartScreenScreenNoTransition();

    // StandartScreen
    void gotoStandartScreenScreenNoTransition();

    // AdminCenter
    void gotoAdminCenterScreenNoTransition();

    // Passwort
    void gotoPasswortScreenNoTransition();

protected:
    touchgfx::Callback<FrontendApplicationBase> transitionCallback;
    FrontendHeap& frontendHeap;
    Model& model;

    // StartScreen
    void gotoStartScreenScreenNoTransitionImpl();

    // StandartScreen
    void gotoStandartScreenScreenNoTransitionImpl();

    // AdminCenter
    void gotoAdminCenterScreenNoTransitionImpl();

    // Passwort
    void gotoPasswortScreenNoTransitionImpl();
};

#endif // FRONTENDAPPLICATIONBASE_HPP