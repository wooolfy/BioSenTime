#ifndef ADMINCENTERPRESENTER_HPP
#define ADMINCENTERPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class AdminCenterView;

class AdminCenterPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    AdminCenterPresenter(AdminCenterView& v);

    /**
     * The activate function is called automatically when this screen is "switched in"
     * (ie. made active). Initialization logic can be placed here.
     */
    virtual void activate();

    /**
     * The deactivate function is called automatically when this screen is "switched out"
     * (ie. made inactive). Teardown functionality can be placed here.
     */
    virtual void deactivate();

    virtual ~AdminCenterPresenter() {};


    virtual void buttonClicked(short int button);
    virtual void showMSG(short int newText);

private:
    AdminCenterPresenter();

    AdminCenterView& view;
};

#endif // ADMINCENTERPRESENTER_HPP
