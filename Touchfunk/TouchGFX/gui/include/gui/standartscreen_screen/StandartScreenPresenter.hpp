#ifndef STANDARTSCREENPRESENTER_HPP
#define STANDARTSCREENPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class StandartScreenView;

class StandartScreenPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    StandartScreenPresenter(StandartScreenView& v);

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

    virtual ~StandartScreenPresenter() {};
    virtual void show(uint8_t number);
    virtual void buttonClicked(int button);

private:
    StandartScreenPresenter();

    StandartScreenView& view;
};

#endif // STANDARTSCREENPRESENTER_HPP
