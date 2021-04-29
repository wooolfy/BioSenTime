#include <gui/admincenter_screen/AdminCenterView.hpp>
#include <gui/admincenter_screen/AdminCenterPresenter.hpp>

AdminCenterPresenter::AdminCenterPresenter(AdminCenterView& v)
    : view(v)
{

}

void AdminCenterPresenter::activate()
{

}

void AdminCenterPresenter::deactivate()
{

}


void AdminCenterPresenter::buttonClicked(short int button)
{
	model->AdminCenterScreenButtonClicked(button);
}

void AdminCenterPresenter::showMSG(short int newText)
{
	view.showMSG(newText);
}
