#include <gui/standartscreen_screen/StandartScreenView.hpp>
#include <gui/standartscreen_screen/StandartScreenPresenter.hpp>

StandartScreenPresenter::StandartScreenPresenter(StandartScreenView& v)
    : view(v)
{

}

void StandartScreenPresenter::activate()
{

}

void StandartScreenPresenter::deactivate()
{

}

void StandartScreenPresenter::show(uint8_t number)
{
	view.show(number);
}

void StandartScreenPresenter::buttonClicked( int button)
{
	model->StandartScreenButtonClicked(button);
}
