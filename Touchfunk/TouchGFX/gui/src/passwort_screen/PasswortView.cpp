#include <gui/passwort_screen/PasswortView.hpp>



uint8_t Button1=0;
uint8_t Button2=0;
uint8_t Button3=0;
uint8_t Count=0;

PasswortView::PasswortView()
{

}

void PasswortView::setupScreen()
{
    PasswortViewBase::setupScreen();
}

void PasswortView::tearDownScreen()
{
    PasswortViewBase::tearDownScreen();
}


void PasswortView::ButtonClicked1()
{
    Button1=1;
    Button2=0;
    Button3=0;
    Count++;
    if(Count==4)
    {
    	application().gotoStandartScreenScreenNoTransition();
    	Count=0;
    }
}

void PasswortView::Button2clicked()
{
	Button2=0;
	if(Button1==1 && Count==1)
	{
		Button2=1;
	}
	Button1=0;
	Button3=0;
	Count++;
    if(Count==4)
    {
    	application().gotoStandartScreenScreenNoTransition();
    	Count=0;
    }
}

void PasswortView::Button3Clicked()
{

	Button3=0;
	if(Button2==1 && Count==2)
		{
			Button3=1;
		}
	Button1=0;
	Button2=0;
	Count++;
    if(Count==4)
    {
    	application().gotoStandartScreenScreenNoTransition();
    	Count=0;
    }
}

void PasswortView::Button4cklicked()
{
	if(Button3==1 && Count==3)
		{
		Count=0;
		application().gotoAdminCenterScreenNoTransition();
		}
	Button1=0;
	Button2=0;
	Button3=0;
	Count++;
    if(Count==4)
    {
    	application().gotoStandartScreenScreenNoTransition();
    	Count=0;
    }
}

void PasswortView::Button5Clicked()
{
	Button1=0;
	Button2=0;
	Button3=0;
	Count++;
	if(Count==4)
	    {
	    	application().gotoStandartScreenScreenNoTransition();
	    	Count=0;
	    }

}

void PasswortView::Button6Clicked()
{
	Button1=0;
	Button2=0;
	Button3=0;
	Count++;
	    if(Count==4)
	    {
	    	application().gotoStandartScreenScreenNoTransition();
	    	Count=0;
	    }
}

void PasswortView::Button7Clicked()
{
	Button1=0;
	Button2=0;
	Button3=0;
	Count++;
	    if(Count==4)
	    {
	    	application().gotoStandartScreenScreenNoTransition();
	    	Count=0;
	    }
}

void PasswortView::Button8Clicked()
{
	Button1=0;
	Button2=0;
	Button3=0;
	Count++;
	    if(Count==4)
	    {
	    	application().gotoStandartScreenScreenNoTransition();
	    	Count=0;
	    }
}

void PasswortView::Button9Clicked()
{
	Button1=0;
	Button2=0;
	Button3=0;
	Count++;
	    if(Count==4)
	    {
	    	application().gotoStandartScreenScreenNoTransition();
	    	Count=0;
	    }
}

void PasswortView::Button0Clicked()
{
	Button1=0;
	Button2=0;
	Button3=0;
	Count++;
	    if(Count==4)
	    {
	    	application().gotoStandartScreenScreenNoTransition();
	    	Count=0;
	    }
}
