/*
 * PollingRoutine.c
 *
 *  Created on: Apr 1, 2021
 *      Author: AndreRother
 */
#include "main.h"
#include "PollingRoutine.h"
#include "string.h"
#include "cmsis_os.h"
#include "stdio.h"

#ifdef __GNUC__
  /* With GCC/RAISONANCE, small printf (option LD Linker->Libraries->Small printf
     set to 'Yes') calls __io_putchar() */
  #define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
  #define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */

extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart6;
extern osMessageQId queueAdminScreenHandle;
extern osMessageQId queueAdmin2Handle;
extern osMessageQId queueStandartScreenHandle;
extern osSemaphoreId binarySemTextHandle;

uint8_t UserID;
uint8_t rx1data[5];
uint8_t rx6data[8];
uint8_t TxBuf[8];
uint8_t SetLevel;
uint8_t MsgRdyFlag=0;
uint8_t Finger_SleepFlag=1;
uint8_t CMD_Flag = 1;
uint8_t delID;
uint8_t item2;
uint16_t item4;
char newText[20];



uint8_t GetUserCount(void);
uint8_t GetcompareLevel(void);
uint8_t SetcompareLevel(void);
uint8_t VerifyUser(void);
uint8_t AddUser(void);
uint8_t DeleteUser(void);
uint8_t Stromsparmodus(void);
uint8_t ClearAllUser(void);
uint8_t IsMasterUser(uint8_t UserID);
uint8_t TxAndRxCmd(uint8_t Scnt,  uint16_t Delay_ms);
HAL_StatusTypeDef  TxByte(uint8_t temp);
void Auto_Vergleich(void);
void Analysiere_Pc_Kommandos(void);
void DeleteRx6(void);
void DeleteRx1(void);
void ablauf(void);
void wake(void);
void sleep(void);
void showGUI();
void adminshowGUI();
uint8_t GAM();
void Auto_Check(void);
void Analysiere_TouchGFX(void);
uint8_t CheckID(void);
uint8_t zahl(uint8_t item);
uint8_t DeleteUserTouchGFX(void);
void setAddingMode(void);




void PollingInit()
{
	  wake();
	  HAL_UART_Receive_DMA(&huart1, rx1data, 5);
	  HAL_UART_Receive_DMA(&huart6, rx6data, 8);
	  DeleteRx6();
	  HAL_Delay(1000);
	  printf("__________________________________________________________________________\r\n");
	  printf("                                                                          \r\n");
	  printf("                               TITEL                                      \r\n");
	  printf("__________________________________________________________________________\r\n");
	  printf("                                                                          \r\n");
	  printf("              akt. eingestellte Sensibilitaet:  %d                        \r\n", GetcompareLevel());
	  printf("              akt. gespeicherte Fingerabdruecke:  %d                      \r\n", GetUserCount());
	  setAddingMode();
	  printf("              akt. FingerAdd-Modus:  %d                                   \r\n", GAM());
	  printf("__________________________________________________________________________\r\n");
	  printf("                                                                          \r\n");
	  printf("  CMDA(1-9) : Sensibilitaet 1-9 sind die Werte. CMDA6 = Sensibilitaet 6   \r\n");
	  printf("                                                                          \r\n");
	  printf("  CMD10     : Die Anzahl der gespeicherten Fingerabdruecke                \r\n");
	  printf("  CMD20     : Der Wert der Sensibilitaet                                  \r\n");
	  printf("  CMD30     : Einen Fingerabdruck Hinzufuegen                             \r\n");
	  printf("  CMD40     : Loesche einen bestimmten Fingerabdruck ( ID notwenidg )     \r\n");
	  printf("  CMD50     : Loesche alle Fingerabdruecke                                \r\n");
	  printf("  CMD60     : Vergleich Fingerabdruck                                     \r\n");
	  printf("  CMD70     : Aktiviere den Auto_Verify_Modus  (nur CMD80/CMD90 moeglich) \r\n");
	  printf("  CMD80     : Dektiviere den Auto_Verify_Modus (alle CMD moeglich)        \r\n");
	  printf("  CMD90     : README                                                      \r\n");
	  printf("__________________________________________________________________________\r\n");
	  printf("                                                                          \r\n");
	  printf("Bitte benutzten Sie jetzt die oben stehende Befehle:                      \r\n");
	  printf("                                                                          \r\n");
	  sleep();
	  DeleteRx6();
	  DeleteRx1();
}

void PollingRoutine()
{

	if(Finger_SleepFlag==1) // Nur Aktiv im Standart-Modus und wenn keine Befehle über den Computer kommen soll.
	{
		 Auto_Vergleich();
	}

	if(CMD_Flag = 1)
	{
		if(rx1data[0]!='\0' && rx1data[1]!='\0' && rx1data[2]!='\0' && rx1data[3]!='\0' && rx1data[4]!='\0') // Fertig
			{
				Analysiere_Pc_Kommandos();
				DeleteRx1();
				DeleteRx6();
			}
	}
	Analysiere_TouchGFX();
}

uint8_t GAM(void)
	{
	uint8_t m;

	TxBuf[0] = 0x2D;
	TxBuf[1] = 0;
	TxBuf[2] = 0;
	TxBuf[3] = 1;
	TxBuf[4] = 0;

	m = TxAndRxCmd(5, 100);

	if (m == 0x00 && rx6data[4] == 0x00)
	{

		if(rx6data[3]==0)
		{
			m = 0;
		}
		else
		{
			m = 1;
		}
		return m;
	}
	else
	{
		printf("Fail.");
	}
	DeleteRx6();
}

void setAddingMode(void)
	{
	uint8_t m;

	TxBuf[0] = 0x2D;
	TxBuf[1] = 0;
	TxBuf[2] = 0;
	TxBuf[3] = 0;
	TxBuf[4] = 0;

	m = TxAndRxCmd(5, 100);

	if (m == 0x00 && rx6data[4] == 0x00)
	{
		DeleteRx6();
	}
	else
	{
		printf("Fail.");
	}
}

uint8_t TxAndRxCmd(uint8_t Scnt,  uint16_t Delay_ms)
{
	uint8_t  i,j, CheckSum;
    uint32_t before_tick;
    uint32_t after_tick;
    uint8_t   overflow_Flag = 0;

	TxByte(0xF5);
	CheckSum = 0;
	for (i = 0; i < Scnt; i++)
	{
		TxByte(TxBuf[i]);
		CheckSum ^= TxBuf[i];
	}
	TxByte(CheckSum);
	TxByte(0xF5);


  // Receive time out: Delay_ms
  before_tick = HAL_GetTick();
  do
  {
    overflow_Flag = 0;
    after_tick = HAL_GetTick();
    if(before_tick > after_tick)   	  //if overflow (go back to zero)
    {
      before_tick = HAL_GetTick();	  // get time_before again
      overflow_Flag = 1;
    }

  } while (( (after_tick - before_tick < Delay_ms)) || (overflow_Flag == 1));


  while(rx6data[0]=='\0' && rx6data[1]=='\0' && rx6data[2]=='\0' && rx6data[3]=='\0' && rx6data[4]=='\0' && rx6data[5]=='\0' && rx6data[6]=='\0' && rx6data[7]=='\0' || j>=50)
  {
	  j++;
	  HAL_Delay(100);
  }



	if (rx6data[0] != 0xF5) 	   return 0x01;
	if (rx6data[8 - 1] != 0xF5)    return 0x01;
	if (rx6data[1] != (TxBuf[0]))  return 0x01;

	return  0x00;
}

HAL_StatusTypeDef  TxByte(uint8_t temp)
{
	return   HAL_UART_Transmit(&huart6, &temp, 1 , 100);
}

PUTCHAR_PROTOTYPE // __________________Für Printf über Usart1
{
  /* Place your implementation of fputc here */
  /* e.g. write a character to the EVAL_COM1 and Loop until the end of transmission */
  HAL_UART_Transmit(&huart1, (uint8_t *)&ch, 1, 0xFFFF);

  return ch;
}

uint8_t GetUserCount(void)	// Fertig
{
	uint8_t m;

	TxBuf[0] = 0x09;
	TxBuf[1] = 0;
	TxBuf[2] = 0;
	TxBuf[3] = 0;
	TxBuf[4] = 0;

	m = TxAndRxCmd(5, 100);


	if (m == 0x00 && rx6data[4] == 0x00)
	{
		uint8_t LSB = rx6data[3];
		uint8_t MSB = rx6data[2]*256;
		uint16_t temp = LSB+MSB;
		DeleteRx6();
		return temp;
	}
	else
	{
	 	return 0xFF;
	}
}

uint8_t GetcompareLevel(void) // Fertig
{
	uint8_t m;

	TxBuf[0] = 0x28;
	TxBuf[1] = 0;
	TxBuf[2] = 0;
	TxBuf[3] = 1;
	TxBuf[4] = 0;

	m = TxAndRxCmd(5, 100);

	if (m == 0x00 && rx6data[4] == 0x00)
	{
		uint8_t temp = rx6data[3];
		DeleteRx6();
	    return temp;
	}
	else
	{
	 	return 0xFF;
	}
}

uint8_t SetcompareLevel(void)	 // Fertig
	{
	uint8_t m;

	TxBuf[0] = 0x28;
	TxBuf[1] = 0;
	TxBuf[2] = SetLevel;
	TxBuf[3] = 0;
	TxBuf[4] = 0;

	m = TxAndRxCmd(5, 100);

	if (m == 0x00 && rx6data[4] == 0x00)
	{
		uint8_t temp = rx6data[3];
		DeleteRx6();
	    return temp;
	}
	else
	{
	 	return 0xFF;
	}
}

uint8_t VerifyUser(void)
{
	uint8_t m;

	TxBuf[0] = 0x0C;
	TxBuf[1] = 0;
	TxBuf[2] = 0;
	TxBuf[3] = 0;
	TxBuf[4] = 0;

	m = TxAndRxCmd(5, 500);

	if ((m == 0x00) && (IsMasterUser(rx6data[4]) == 1))
	{
		 return 0x00;
	}
	else if(rx6data[4] == 0x05)
	{
		return 0x05;
	}
	else if(rx6data[4] == 0x08)
	{
		return 0x08;
	}
	else{
		return 0x01;
	}
}

uint8_t IsMasterUser(uint8_t UserID) // Fertig
{
    if ((UserID == 1) || (UserID == 2) || (UserID == 3)) return 1;
		else  return 0;
}

uint8_t AddUser(void)
{
	uint8_t m;

	m = GetUserCount();
	if (m >= 500)
		return 0x04;

	TxBuf[0] = 0x01;
	TxBuf[1] = 0;
	TxBuf[2] = m +1;
	TxBuf[3] = 1;
	TxBuf[4] = 0;

	DeleteRx6();
	m = TxAndRxCmd(5, 500);
	HAL_Delay(300);

	if (m == 0x00 && rx6data[4] == 0x00)
	{
		TxBuf[0] = 0x03;
		DeleteRx6();
		m = TxAndRxCmd(5, 500);
		HAL_Delay(300);
		if (m == 0x00 && rx6data[4] == 0x00)
		{
			return 0x00;
		}
		else
		  return 0x01;
	}
	else
		return 0x0F;
}

uint8_t ClearAllUser(void)
{
 	uint8_t m;

	TxBuf[0] = 0x05;
	TxBuf[1] = 0;
	TxBuf[2] = 0;
	TxBuf[3] = 0;
	TxBuf[4] = 0;

	m = TxAndRxCmd(5, 500);

	if (m == 0x00 && rx6data[4] == 0x00)
	{
		return 0x00;
	}
	else
	{
		return 0x01;
	}
}

uint8_t DeleteUser(void)
{
 	uint8_t m;

 	m = CheckID();

	TxBuf[0] = 0x04;
	TxBuf[1] = 0;
	TxBuf[2] = m;
	TxBuf[3] = 0;
	TxBuf[4] = 0;
	HAL_Delay(200);
	m = TxAndRxCmd(5, 500);

	if (m == 0x00 && rx6data[4] == 0x00)
	{
		return 0x00;
	}
	else
	{
		return 0x01;
	}
}

uint8_t DeleteUserTouchGFX(void)
{

	uint8_t m;

	TxBuf[0] = 0x04;
	TxBuf[1] = 0;
	TxBuf[2] = delID;
	TxBuf[3] = 0;
	TxBuf[4] = 0;

	HAL_Delay(200);
	m = TxAndRxCmd(5, 500);

	if (m == 0x00 && rx6data[4] == 0x00)
	{
		item2=1;
		return 0x00;
	}
	else
	{
		item2=0;
		return 0x01;
	}
}

uint8_t Stromsparmodus(void)
{
 	uint8_t m;

	TxBuf[0] = 0x2C;
	TxBuf[1] = 0;
	TxBuf[2] = 0;
	TxBuf[3] = 0;
	TxBuf[4] = 0;

	m = TxAndRxCmd(5, 500);

	if (m == 0x00 && rx6data[1] == 0x2C && rx6data[2] == 0x00 && rx6data[3] == 0x00 && rx6data[4] == 0x00 && rx6data[5] == 0x00)
	{
		return 0x00;
	}
	else
	{
		return 0x01;
	}
}

void Auto_Vergleich(void)
{
	if(HAL_GPIO_ReadPin(FINGER_WAKE_GPIO_Port, FINGER_WAKE_Pin) == GPIO_PIN_SET)
	{
	  while(HAL_GPIO_ReadPin(FINGER_WAKE_GPIO_Port, FINGER_WAKE_Pin) != GPIO_PIN_RESET)
	  {
		wake();
		DeleteRx6();
		switch(VerifyUser())
			{
				case 0x00:
					printf("Fingerabdruck erkannt! UserID: %d\r\n",rx6data[3]);
					item2=1;
					break;
				case 0x05:
					printf("FEHLER : Fingerabdruck ist nicht in der Datenbank gespeichert !\r\n");
					item2=10;
					break;
				case 0x08:
					item2=10;
					printf("FEHLER : Time out !\r\n");
					break;
				case 0x07:
					item2=10;
					printf("FEHLER : nocheinmal versuchen.. Finger neu positionieren !\r\n");
					break;
				default:
					break;
			}
	  }
	  sleep();
	  HAL_Delay(200);
	  DeleteRx6();
	  showGUI();
	  while(HAL_GPIO_ReadPin(FINGER_WAKE_GPIO_Port, FINGER_WAKE_Pin) == GPIO_PIN_SET)
	  {
	  	  HAL_Delay(10);
	  }
	  uint8_t LogButton=0;
	  uint8_t time=0;
	  while(LogButton==0)
	  {
		  uint8_t item4=0;
		  if(xQueueReceive(queueStandartScreenHandle, &item4, ( TickType_t ) 10 ) == pdPASS)
		  {
			  switch(item4)
			  {
			  case 1: //Login
				  printf("Login..\r\n");
				  item2=2;
				  break;
			  case 2: //Logout
				  printf("Logout..\r\n");
				  item2=3;
				  break;
			  default: break;
			  }
			  showGUI();
			  LogButton=1;
		  }
		  else
		  {
			  HAL_Delay(10);
			  time++;
			  if(time>=200)
			  {
				  LogButton=1;
				  printf("Keine taste erkannt. Buchung nicht erfolgreich!\r\n");
				  item2=4;
				  showGUI();
			  }
		  }
	  }
	  return;
	}
}

void showGUI()
{
	xQueueSend(queueStandartScreenHandle, &item2, ( TickType_t ) 10);
}

void adminshowGUI()
{
	xQueueSend(queueAdmin2Handle, &item4, ( TickType_t ) 10);
}

void Analysiere_Pc_Kommandos(void)
{
	if(rx1data[0] == 'C' && rx1data[1] == 'M' && rx1data[2] == 'D' )
		{
		switch(rx1data[3])
			  {
//______________________________________________________________________________________________________________________ FERTIG
			  case '1':
				  if(Finger_SleepFlag == 1)  break;
			  			printf("Gespeicherte Fingerabdruecke:  %d\r\n\n",GetUserCount());
			  		break;
//______________________________________________________________________________________________________________________ FERTIG
			  case '2':
				  if(Finger_SleepFlag == 1)  break;
			  			printf("Sensibilitaet:  %d\r\n\n", GetcompareLevel());
			  		break;
//______________________________________________________________________________________________________________________
			  case '3':
				  if(Finger_SleepFlag == 1)  break;
			  			printf("Legen Sie jetzt den Finger drauf, bevor die Zeit Abgelaufen ist...\r\n\n");
			  			setAddingMode();
			  			DeleteRx6();
			  			if(GAM()==0)
			  			{
			  			DeleteRx6();
			  			ablauf();
			  			switch(AddUser())
			  				{
			  				case 0x00:
			  						printf("Fingerabdruck Gespeichert unter der ID: %d !\r\n\n",TxBuf[2]);
			  					break;
			  				case 0x01:
			  						printf("FEHLER: Fingerabdruck nicht gespeichert !\r\n\n");
			  					break;
			  				case 0x0F:
			  						printf("FEHLER: Neu Positionieren !\r\n\n");

			  					break;
			  				default:
			  					break;
			  				}
			  			}
			  		break;
//______________________________________________________________________________________________________________________ NOCH NICHT BENUTZTEN
			  case '4':
				  if(Finger_SleepFlag == 1)  break;
			  			DeleteUser();
			  			printf("Loesche bestimmten Fingerabdruck ID: %d\r\n\n",UserID);
			  		break;
//______________________________________________________________________________________________________________________ NOCH NICHT BENUTZTEN
			  case '5':
				  if(Finger_SleepFlag == 1)  break;
				  switch(ClearAllUser())
				  	  {
				  	  case 0x00:printf("Loesche alle Fingerabdruecke\r\n\n");
				  	  	  break;
				  	  case 0x01:printf("FEHLER!\r\n\n");
					  	  break;
				  	  }


			  		break;
//______________________________________________________________________________________________________________________ FERTIG
			  case '6': // Verify
				  if(Finger_SleepFlag == 1)  break;
			  			printf("Legen Sie jetzt den Finger drauf, bevor die Zeit Abgelaufen ist...\r\n\n");
			  			ablauf();
			  			switch(VerifyUser())
			  			{
			  			case 0x00:
			  				printf("Fingerabdruck erkannt! ID: %d !\r\n\n",rx6data[3]);
			  				break;
			  			case 0x05:
			  				printf("FEHLER : Der Fingerabdruck ist nicht in der Datenbank!\r\n\n");
			  				break;
			  			case 0x08:
			  				printf("FEHLER : Time OUT\r\n\n");
			  				break;
			  			case 0x0F:
			  				printf("FEHLER : Neuer Versuch\r\n\n");
			  				break;
			  			}
			  		break;
//______________________________________________________________________________________________________________________
			  	case '7': // SleepMode
			  		if(Finger_SleepFlag == 1)  break;
			  				sleep();
			  				printf("Auto_Verify_Modus aktiviert!\r\n\n");
			  				printf("Alle Befehle (außer CMD80) nicht verfügbar!\r\n\n");
			  		break;
//______________________________________________________________________________________________________________________
			  	case '8': // deactivate SleepMode
			  				wake();
			  				printf("Auto_Verify_Modus deaktiviert!\r\n\n");
			  				printf("Jetzt können Sie wieder Befehle senden!\r\n\n");
			  		break;
//______________________________________________________________________________________________________________________ FERTIG
			  case 'A':
				  if(Finger_SleepFlag == 1)  break;
			  			switch(rx1data[4])	// Umwandlung von Ascii zu Dezimal
			  				{
			  				case 49: SetLevel = 1; break;
			  				case 50: SetLevel = 2; break;
			  				case 51: SetLevel = 3; break;
			  				case 52: SetLevel = 4; break;
			  				case 53: SetLevel = 5; break;
			  				case 54: SetLevel = 6; break;
			  				case 55: SetLevel = 7; break;
			  				case 56: SetLevel = 8; break;
			  				case 57: SetLevel = 9; break;
			  				}
			  			SetcompareLevel();
			  			if(rx6data[4]==0x00)
			  				{
			  					printf("Sensibilitaet ist jetzt auf %c gesetzt.\r\n", rx1data[4]);
			  				}
			  				else
			  				{
			  					printf("FEHLER : Sensibilitaet ist nicht auf %c gesetzt.\r\n", rx1data[4]);
			  				}
			  		break;
//______________________________________________________________________________________________________________________
			  case '9':
				 printf("Die Programmierung soll mit Hilfe eines Fingerabdrucksensor von CQROBOT, den Fingerabdruck einer Person einer eindeutigen ID zuordnen.\r\n");
				 printf("Diese ID wird anschließend mit einen Zeitstempel zusammen an ein Enterprise-Ressourcen-Planungs-System gesendet.\r\n");
				 printf("Die Programmierung sieht folgende Bedienung vor: 1. durch den Auto_Verify_Modus 2. durch den Admin_Modus am Touch-Display 3. über die ST-Link Verbindung zum Computer\r\n");
				 printf("Der Auto_Verify_Modus ist automatisch im Standartbildschirm an, während der Auto_Verify-Modus an ist, kann ein Finger jederzeit auf den Sensor gelegt werden. \r\n");
				 printf("Die Programmierung prüft dann den Abdruck und vergleicht diesen automatisch und gibt Meldung über den Erfolg am Display und am Computer über den ST-Link\r\n");
				 printf("Admin_Modus am Touch-Display, wird nur benutzt wenn man veränderungen am Sensor oder am STM32F746G-Disco vornehmen möchte.(z.B. Benutzter Hinzufügen, Hellikeit oder Uhrzeit einstellen)\r\n");
				 printf("Ein USB-Kabel am Anschluss CN14 und mit dem Computer verbinden. Anschließend ein Terminalprogramm wie HTERM starten und mit den Einstellungen 115200-8-1-None Verbinden. Danach sind die untenstehenden Kommandos(CMD) zu senden.");
				 printf("!!!Am 19.01.2038 ist der Speicher nicht mehr ausreichend für die Zeitrechnung- ZeitStempel!!!");
			  		break;
//______________________________________________________________________________________________________________________
			  }
		printf("                           \r\n");
		printf("                           \r\n");

		}
}

void DeleteRx1(void)	// Fertig
{
	for(uint8_t b=0; b<5; b++)	// Lösche den Buffer von rx1data
			{
				rx1data[b]='\0';
			}
	 HAL_UART_Receive_DMA(&huart1, rx1data, 5);
}

void DeleteRx6(void)	// Fertig
{
	for(uint8_t a = 0; a<8; a++)
	{
		rx6data[a]='\0';
	}
	HAL_UART_Receive_DMA(&huart6, rx6data, 8);
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(huart);

  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_UART_RxCpltCallback can be implemented in the user file.
   */
}

void ablauf(void)
{
	HAL_Delay(1000);
	printf("Noch 5 Sekunden..\r\n");
	HAL_Delay(1000);
	printf("Noch 4 Sekunden..\r\n");
	HAL_Delay(1000);
	printf("Noch 3 Sekunden..\r\n");
	HAL_Delay(1000);
	printf("Noch 2 Sekunden..\r\n");
	HAL_Delay(1000);
	printf("Noch 1 Sekunden..\r\n");
	HAL_Delay(1000);
	printf("Finger wird jetzt eingelesen...\r\n");
}

uint8_t CheckID(void)
{
	for(uint8_t i=0; i<5; i++)
	{
		rx1data[i]='\0';
	}

	HAL_UART_Receive_DMA(&huart1, rx1data, 3);
	HAL_Delay(200);
	printf("Bitte jetzt die UserID angeben... Beispiel: 007 fuer ID: 7\r\n\n");

	uint8_t Timeout=0;

	printf("Warte auf ID:          ( 5 Sekunden) \r\n");

	while(rx1data[1]=='\0' && rx1data[2]=='\0' || Timeout>=50)
	{
		Timeout++;
		HAL_Delay(100);
	}

	uint8_t hundert = zahl(rx1data[0])*100;
	uint8_t zehner = zahl(rx1data[1])*10;
	uint8_t einser = zahl(rx1data[2]);

	UserID = hundert+zehner+einser;

	if(Timeout>=50)
	{
		HAL_Delay(200);
		printf("5 Sekunden Timeout...\r\n\n");
	}
	else
	{
		HAL_Delay(200);
		printf("ID: %d erhalten.\r\n\n",UserID);
	}

	return UserID;

}

uint8_t zahl(uint8_t item)
{
	switch(item)
		{
			case 48:return 0;break;
			case 49:return 1;break;
			case 50:return 2;break;
			case 51:return 3;break;
			case 52:return 4;break;
			case 53:return 5;break;
			case 54:return 6;break;
			case 55:return 7;break;
			case 56:return 8;break;
			case 57:return 9;break;
		}
}

void sleep(void)
{
	HAL_GPIO_WritePin(FINGER_RST_GPIO_Port, FINGER_RST_Pin, RESET);
	Finger_SleepFlag = 1;
}

void wake(void)
{
	HAL_GPIO_WritePin(FINGER_RST_GPIO_Port, FINGER_RST_Pin, SET);
	HAL_Delay(1000);
	Finger_SleepFlag = 0;
}

void Auto_Check(void)
{
	switch(VerifyUser())
			  			{
			  				case 0x00:
			  					printf("Fingerabdruck erkannt! User-ID: %d\r\n",rx6data[3]);
			  					printf("                                                                          \r\n");
			  					break;
			  				case 0x05:
			  					printf("Fehler: Fingerabdruck ist nicht in der Datenbank gespeichert !\r\n");
			  					printf("                                                                          \r\n");
			  					break;
			  				case 0x08:
			  					printf("Fehler: Time out !\r\n");
			  					printf("                                                                          \r\n");
			  					break;
			  				case 0x07:
			  					printf("Fehler: nocheinmal versuchen.. Finger neu positionieren !\r\n");
			  					printf("                                                                          \r\n");
			  					break;
			  				default:
			  					break;
			  			}
		DeleteRx6();
}

void Analysiere_TouchGFX(void)
{
	uint16_t item;
	if(xQueueReceive(queueAdminScreenHandle, &item, ( TickType_t ) 10 ) == pdPASS)
	{
		char str[20];
		if(item == 1 || item == 2 || item == 3 || item == 5 )
		{
		switch(item)
		{
		case 1: //AddUser
			setAddingMode();
			DeleteRx6();
			if(GAM()==0)
			{
			DeleteRx6();
			switch (AddUser())
				{
			case 0x00:
				printf("Fingerabdruck Gespeichert unter der ID: %d !\r\n",TxBuf[2]);
				sprintf(str,"%d",TxBuf[2]);
				strcat(newText,"New ID: ");
				strcat(newText,str);
				item4=TxBuf[2];
				break;
			case 0x01:
				printf("FEHLER: Fingerabdruck nicht gespeichert !\r\n");
				sprintf(str,"Not saved!");
				strcat(newText,"Fail: ");
				strcat(newText,str);
				item4=502;
				break;
			case 0x0F:
				sprintf(str,"Check ID!");
				strcat(newText,"Fail: ");
				strcat(newText,str);
				item4=502;
				break;
			default:
				break;
				}
			}
			else
			{
				HAL_Delay(1);
			}
		break;

		case 2: //VerifyUser
			printf("Legen Sie jetzt den Finger drauf, bevor die Zeit Abgelaufen ist...\r\n");
			switch (VerifyUser())
			{
			case 0x00:
				printf("Fingerabdruck erkannt! ID: %d !\r\n", rx6data[3]);
				sprintf(str,"%d", rx6data[3]);
				strcat(newText,"ID: ");
				strcat(newText,str);
				break;
			case 0x05:
				sprintf(str,"Not Found!");
				strcat(newText,"Fail: ");
				strcat(newText,str);
				break;
			case 0x08:
				sprintf(str,"Time Out!");
				strcat(newText,"Fail: ");
				strcat(newText,str);
				break;
			case 0x0F:
				sprintf(str,"Try Again!");
				strcat(newText,"Fail: ");
				strcat(newText,str);
				break;
			}
			break;

		case 3: //UserCount
			sprintf(str,"%d", GetUserCount());
			strcat(newText,"Count: ");
			strcat(newText,str);
			break;

		case 5: //DeleteAll
			switch (ClearAllUser())
				{
				case 0x00:
					strcpy(newText,"All Users Deleted!");
					break;
				case 0x01:
					printf("Fail!\r\n");
					strcpy(newText,"Fail!");
					break;
				}
			break;
			}
		printf("%s \r\n",newText);
		}
		else if(item == 6 || item == 7)
		{
			switch(item)
			{
			case 6: //deactivate Auto_Verify_Modus
				wake();
				DeleteRx6();
				CMD_Flag = 0;
				printf("Betrete Adminmodus - Auto_Verify_Modus OFF\r\n");
				break;

			case 7: //activate Auto_Verify_Modus
				sleep();
				CMD_Flag = 1;
				DeleteRx6();
				printf("Verlassen des Adminmodus - Auto_Verify_Modus ON \r\n");
				break;
			}

		}
		else if(item >= 4000 && item < 4501)
				{
					delID = item - 4000;
					DeleteUserTouchGFX();
					sprintf(str,"ID: %d",delID);
					strcat(newText,"Delete ");
					strcat(newText,str);
					printf("%s\r\n",newText); //SEND newText to GUI
				}
		else
		{
			HAL_Delay(1);
		}

		adminshowGUI();
	}
	else
	{
		HAL_Delay(1);
	}
	HAL_Delay(500);
	item = '\0';
	DeleteRx6();
	item2='\0';
	item4='\0';
}


