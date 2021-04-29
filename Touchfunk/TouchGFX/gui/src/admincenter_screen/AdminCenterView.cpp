#include <gui/admincenter_screen/AdminCenterView.hpp>
#include <gui/model/Model.hpp>
#include "string.h"
#include "PollingRoutine.h"
#include <cstdio>


AdminCenterView::AdminCenterView()
{

}

void AdminCenterView::setupScreen()
{
    AdminCenterViewBase::setupScreen();
}

void AdminCenterView::tearDownScreen()
{
    AdminCenterViewBase::tearDownScreen();
}

void AdminCenterView::uscerCountButtonClicked()
{
	presenter->buttonClicked(3);
}

void AdminCenterView::deleteAllUserButtonClicked()
{
	presenter->buttonClicked(5);
}

void AdminCenterView::deleteUserButtonClicked()
{
	uint16_t test = 0;uint8_t test100;uint8_t test10;uint8_t test1;uint16_t test4000 = 4000;
	test100 = slider1.getValue() * 100;
	test10 = slider2.getValue() * 10;
	test1 = slider3.getValue();
	test = test100+test10+test1+test4000;
	presenter->buttonClicked(test);
}

void AdminCenterView::verifyUserButtonClicked()
{
	presenter->buttonClicked(2);
}

void AdminCenterView::addUserButtonClicked()
{
    presenter->buttonClicked(1);
}

void AdminCenterView::deactivateAutoVerify()
{
	presenter->buttonClicked(6);
}

void AdminCenterView::activateAutoVerify()
{
	presenter->buttonClicked(7);
}

void AdminCenterView::showMSG(short int newText)
{
	if(newText=='\0') return;

	char str[4];
	char str2[11];
	if(newText>=0 && newText<=500)
	{
		//Reaktion ID: %d
		sprintf(str,"%d",newText);
		strncpy(str2,"ID: ",sizeof(str2));
		strncat(str2,str,4);
	}
	if(newText == 501)
	{
		strncpy(str2,"Done",sizeof(str2));
	}
	if(newText == 502)
	{
		strncpy(str2,"Fail",sizeof(str2));
	}
	if(newText>=3000 && newText<=3500)
	{
		sprintf(str,"%d",newText);
		strncpy(str2,"Count: ",sizeof(str2));
		strncat(str2,str,4);
	}
	memset(&textArea1Buffer, 0, 12);
	Unicode::strncpy(textArea1Buffer, str2, 11);
	textArea1Buffer[12]='\0';
	textArea1.invalidate();
}

