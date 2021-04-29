#include <gui/standartscreen_screen/StandartScreenView.hpp>
#include <gui/model/Model.hpp>




StandartScreenView::StandartScreenView()
{

}

void StandartScreenView::setupScreen()
{
    StandartScreenViewBase::setupScreen();
}

void StandartScreenView::tearDownScreen()
{
    StandartScreenViewBase::tearDownScreen();
}

void StandartScreenView::loginbuttonClicked()
{
	presenter->buttonClicked(1);
	loginButton.setVisible(false);
	loginButton.invalidate();
	logoutButton.setVisible(false);
	logoutButton.invalidate();
}

void StandartScreenView::logoutButtonClicked()
{
	presenter->buttonClicked(2);
	loginButton.setVisible(false);
	loginButton.invalidate();
	logoutButton.setVisible(false);
	logoutButton.invalidate();
}

void StandartScreenView::show(uint8_t number)
{
	if(number == 10) // Zeige Fail
	{
		fail.setVisible(true);
		fail.invalidate();
		SettingsButton.setVisible(false);
		SettingsButton.invalidate();
		tickCounter=0;
		number=0;

	}
	else if(number == 1) // Zeige Buttons und Check
	{
		check.setVisible(true);
		check.invalidate();
		SettingsButton.setVisible(false);
		SettingsButton.invalidate();
		loginButton.setVisible(true);
		loginButton.invalidate();
		logoutButton.setVisible(true);
		logoutButton.invalidate();
		tickCounter=0;
		number=0;
	}

	else if(number == 2) // Zeige Login
	{
		textlogin.setVisible(true);
		textlogin.invalidate();
		tickCounter=0;
		number=0;
	}
	else if(number == 3) // Zeige LogOut
	{
		textlogout.setVisible(true);
		textlogout.invalidate();
		tickCounter=0;
		number=0;
	}
	else if(number == 4) // lösche Logs
	{
		loginButton.setVisible(false);
		loginButton.invalidate();
		logoutButton.setVisible(false);
		logoutButton.invalidate();
		texttimeout.setVisible(true);
		texttimeout.invalidate();
		tickCounter=0;
		number=0;
	}
	else
	{
		Cover.invalidate();
	}

}

void StandartScreenView::handleTickEvent()
{
	tickCounter++;
	if(tickCounter >= 150)
	{
		fail.setVisible(false);
		fail.invalidate();
		check.setVisible(false);
		check.invalidate();
		SettingsButton.setVisible(true);
		SettingsButton.invalidate();
		textlogout.setVisible(false);
		textlogout.invalidate();
		textlogin.setVisible(false);
		textlogin.invalidate();
		texttimeout.setVisible(false);
		texttimeout.invalidate();
		tickCounter=0;
	}
}
