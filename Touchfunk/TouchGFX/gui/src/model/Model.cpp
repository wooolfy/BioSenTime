#include <gui/model/Model.hpp>
#include <gui/model/ModelListener.hpp>

#include "main.h"
#include "cmsis_os.h"

extern osMessageQId queueAdminScreenHandle;
extern osMessageQId queueAdmin2Handle;
extern osMessageQId queueStandartScreenHandle;
extern osSemaphoreId binarySemTextHandle;
int item2;
short int item4;
short int newText;

Model::Model() : modelListener(0)
{

}

void Model::tick()
{
	if(xQueueReceive(queueStandartScreenHandle, &item2, ( TickType_t ) 10) == pdPASS)
	{
		uint8_t number;
		number = item2;
		show(number);
	}
	if(xQueueReceive(queueAdmin2Handle, &item4, ( TickType_t ) 10) == pdPASS)
	{
		short int number;
		number = item4;
		showMSG(number);
	}
	//https://www.freertos.org/FreeRTOS_Support_Forum_Archive/December_2015/freertos_How_to_send_string_through_queue_9b0e9d02j.html
}

void Model::showMSG(short int newText)
{
	modelListener->showMSG(newText);
}

void Model::AdminCenterScreenButtonClicked(short int button)
{
	uint16_t item;
	item = button;
	xQueueSend(queueAdminScreenHandle, &item, ( TickType_t ) 10);
}

void Model::show(uint8_t number)
{
	modelListener->show(number);
}

void Model::StandartScreenButtonClicked(int button)
{
	uint8_t item3;
	item3 = button;
	xQueueSend(queueStandartScreenHandle, &item3, ( TickType_t ) 10);
}
