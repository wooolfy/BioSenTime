/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#ifndef STANDARTSCREENVIEWBASE_HPP
#define STANDARTSCREENVIEWBASE_HPP

#include <gui/common/FrontendApplication.hpp>
#include <mvp/View.hpp>
#include <gui/standartscreen_screen/StandartScreenPresenter.hpp>
#include <touchgfx/widgets/Box.hpp>
#include <touchgfx/widgets/Image.hpp>
#include <touchgfx/widgets/Button.hpp>
#include <touchgfx/widgets/TextArea.hpp>
#include <touchgfx/EasingEquations.hpp>
#include <touchgfx/mixins/FadeAnimator.hpp>

class StandartScreenViewBase : public touchgfx::View<StandartScreenPresenter>
{
public:
    StandartScreenViewBase();
    virtual ~StandartScreenViewBase() {}
    virtual void setupScreen();

    /*
     * Virtual Action Handlers
     */
    virtual void loginbuttonClicked()
    {
        // Override and implement this function in StandartScreen
    }

    virtual void logoutButtonClicked()
    {
        // Override and implement this function in StandartScreen
    }

protected:
    FrontendApplication& application() {
        return *static_cast<FrontendApplication*>(touchgfx::Application::getInstance());
    }

    /*
     * Member Declarations
     */
    touchgfx::Box __background;
    touchgfx::Image Cover;
    touchgfx::FadeAnimator< touchgfx::Button > SettingsButton;
    touchgfx::Image fail;
    touchgfx::Image check;
    touchgfx::Button loginButton;
    touchgfx::Button logoutButton;
    touchgfx::TextArea textlogin;
    touchgfx::TextArea textlogout;
    touchgfx::TextArea texttimeout;

private:

    /*
     * Callback Declarations
     */
    touchgfx::Callback<StandartScreenViewBase, const touchgfx::AbstractButton&> buttonCallback;

    /*
     * Callback Handler Declarations
     */
    void buttonCallbackHandler(const touchgfx::AbstractButton& src);

};

#endif // STANDARTSCREENVIEWBASE_HPP
