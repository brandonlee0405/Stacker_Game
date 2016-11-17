#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <avr/eeprom.h>
#include "C:\Users\User\Desktop\header\io.c"
#include "C:\Users\User\Desktop\header\io.h"
#include "C:\Users\User\Desktop\header\timer.h"

unsigned char iteration = 0;
unsigned char Winner_Winner = 0;

// Normal/Hard Level comparator
unsigned char two_dot_check = 0;
unsigned char two_dot_check2 = 0;
unsigned char one_dot_check = 0;
unsigned char one_dot_check2 = 0;

unsigned char ggg = 0;
unsigned char ggg2 = 0;
unsigned char ggg3 = 0;
unsigned char ggg4 = 0;
// Normal/Hard Level ggg
unsigned char ggg5 = 0;//
unsigned char ggg6 = 0;//
unsigned char ggg7 = 0;//
unsigned char ggg8 = 0;//
//-----------------------
unsigned char ccc = 0;
unsigned char comparing = 0;
unsigned char comparing2 = 0;
unsigned char comparing3 = 0;
unsigned char comparing4 = 0;
// Normal/Hard Level comparing
unsigned char comparing5 = 0;//
unsigned char comparing6 = 0;//
unsigned char comparing7 = 0;//
unsigned char comparing8 = 0;//
//-----------------------------

//unsigned char rob = 1;
unsigned char cou = 0;
unsigned char cou2 = 0;
unsigned char cou3 = 0;


unsigned char row_counter = 0;
unsigned char row_counter2 = 0;
unsigned char row_counter3 = 0;
// Normal/Hard Level row_counter
unsigned char row_counter4 = 0;//
unsigned char row_counter5 = 0;//
unsigned char row_counter6 = 0;//
unsigned char row_counter7 = 0;//
//-------------------------------
unsigned char win_check = 0;

unsigned char light_fail = 0;

unsigned char light_fail2 = 0;

unsigned long int findGCD (unsigned long int a, unsigned long int b)
{
	unsigned long int c;
	while(1)
	{
		c = a % b;
		if(c==0){return b;}
		a = b;
		b = c;
	}
	return 0;
}

typedef struct _task
{
	signed char state;
	unsigned long int period;
	unsigned long int elapsedTime;
	int (*TickFct)(int);
} task;

void A2D_init()
{
	ADCSRA |= (1 << ADEN) | (1 << ADSC) | (1 << ADATE);
	// ADEN: Enables analog-to-digital conversion
	// ADSC: Starts analog-to-digital conversion
	// ADATE: Enables auto-triggering, allowing for constant
	//	    analog to digital conversions.
}

/*
void transmit_data(unsigned char data) {
	int i;
	for (i = 7; i >= 0; --i)
	{
		// Sets SRCLR to 1 allowing data to be set
		// Also clears SRCLK in preparation of sending data
		PORTA = 0x08;
		// set SER = next bit of data to be sent.
		PORTA |= ((data >> i) & 0x01);
		// set SRCLK = 1. Rising edge shifts next bit of data into the shift register
		PORTA |= 0x04;
	}
	
	// set RCLK = 1. Rising edge copies data from the “Shift” register to the
	// “Storage” register
	PORTA |= 0x02;
	// clears all lines in preparation of a new transmission
	PORTA = 0x00;
}
*/
void transmit_data2(unsigned char data) {
	int i;
	for (i = 7; i >= 0; --i)
	{
		// Sets SRCLR to 1 allowing data to be set
		// Also clears SRCLK in preparation of sending data
		PORTB = 0x08;
		// set SER = next bit of data to be sent.
		PORTB |= ((data >> i) & 0x01);
		// set SRCLK = 1. Rising edge shifts next bit of data into the shift register
		PORTB |= 0x04;
	}
	
	// set RCLK = 1. Rising edge copies data from the “Shift” register to the
	// “Storage” register
	PORTB |= 0x02;
	// clears all lines in preparation of a new transmission
	PORTB = 0x00;
}

unsigned char *menu_string = "1. One Player   2. Two Player   ";
unsigned char *one_menu_string = "1. Start        2. Choose Level ";
unsigned char *two_menu_string = "1. Start        2. Back         ";

// Fix this string maybe?
unsigned char *level_menu_string = "1.Easy 2. Normal3. Hard         ";
unsigned char *game_start_string = "  BEGIN GAME!   ";

// Win or Lose String
unsigned char *win_string = "You Win!        Congratulations!";
unsigned char *lose_string = "You Lose!       Try Again!      ";

// Variables for the level
unsigned char start_easy = 0;
unsigned char start_normal = 0;
unsigned char start_hard = 0;

unsigned char end_level = 0;
//unsigned char end_normal = 0;
//unsigned char end_hard = 0;

unsigned char fail = 0;
unsigned char winner = 0;
unsigned char stop_variable = 0;


unsigned char level = 1;

// Buttons
unsigned char button = 0;
unsigned char button2 = 0;
unsigned char button3 = 0;
unsigned char back_button = 0;

// Score Variable Counter
unsigned char score_total = 0;
unsigned char numBlocks = 3;

unsigned char out = 0;
unsigned char out2 = 0;

// Line Counter
unsigned char column_count = 1;
unsigned char row_count = 1;
unsigned char row_decrement_count = 1;
 

unsigned char arr[10] = {0x1F, 0x8F, 0xC7, 0xE3, 0xF1, 0xF8, 0xF1, 0xE3, 0xC7, 0x8F};
unsigned char arr2[12] = {0x3F, 0x9F, 0xCF, 0xE7, 0xF3, 0xF9, 0xFC, 0xF9, 0xF3, 0xE7, 0xCF, 0x9F};
unsigned char arr3[14] = {0x7F, 0xBF, 0xDF, 0xEF, 0xF7, 0xFB, 0xFD, 0xFE, 0xFD, 0xFB, 0xF7, 0xEF, 0xDF, 0xBF};


enum menu_sms {init, menu, menu_start, temp, one_player, two_player, c_level} menu_sm;
int menu_sm_tick()
{
	
	button = ~PINC & 0x04;
	button2 = ~PINC & 0x08;
	//button3 = ~PIND & 0x10;
	back_button = ~PINC & 0x10;
	switch (menu_sm)
	{
		case init:
			menu_sm = menu_start;
			break;
			
		case menu_start:
		
			LCD_ClearScreen();
			LCD_Cursor(1);
			LCD_DisplayString(1, menu_string);
			menu_sm = menu;
			break;
		
		case menu:
			if (back_button)
			{
				menu_sm = menu_start;
			}
			if (button)
			{
				LCD_ClearScreen();
				LCD_Cursor(1);
				LCD_DisplayString(1, one_menu_string);
				menu_sm = one_player;
			}
			if (button2)
			{
			
				LCD_ClearScreen();
				LCD_Cursor(1);
				LCD_DisplayString(1, two_menu_string);
				menu_sm = two_player;
			}
			break;
		case temp:
			
			break;

		case one_player:
			if (back_button) // FIXME with JoyStick Select
			{
				menu_sm = menu_start;
			}
			else if (button)
			{
				LCD_ClearScreen();
				LCD_Cursor(1);
				LCD_DisplayString(1, game_start_string);
				menu_sm = temp;
			}
			else if (button2)
			{
				LCD_ClearScreen();
				LCD_Cursor(1);
				LCD_DisplayString(1, level_menu_string);
				menu_sm = c_level;
			}
			break;

		case two_player:
			if (button2)
			{
				menu_sm = menu_start;
			}
			if (button)
			{
				menu_sm = temp;
			}
		break;

		case c_level:
			if (back_button)
			{
				menu_sm = menu_start;
			}
			if (button)
			{
				level = 1;
				LCD_ClearScreen();
				LCD_Cursor(1);
				LCD_DisplayString(1, one_menu_string);
				menu_sm = one_player;
			}
			if (button2)
			{
				level = 2;
				LCD_ClearScreen();
				LCD_Cursor(1);
				LCD_DisplayString(1, one_menu_string);
				menu_sm = one_player;
			}
			if (button3)
			{
				level = 3;
				LCD_ClearScreen();
				LCD_Cursor(1);
				LCD_DisplayString(1, one_menu_string);
				menu_sm = one_player;
			}
			break;

		default:
			menu_sm = menu_start;
			break;
	}
	// ACTION
	switch (menu_sm)
	{
		case init:
			break;
		
		case menu_start:
			break;
		
		case menu:
			break;

		case temp:
			if (level == 1)
			{
				start_easy = 1;
			}
			else if (level == 2)
			{
				start_normal = 1;
			}
			else if (level == 3)
			{
				start_hard = 1;
			}
			break;

		case one_player:
			break;

		case two_player:
			break;

		case c_level:
			break;

		default:
			break;

	}
}

// ONE PLAYER GAME
enum level1s {l1_init, blink1, blink2, blink3, blink4, final_win_lose, win_lose, display, stop} level1;
	unsigned char y = 0;
int level1_tick()
{
	button = ~PINC & 0x04;
	switch(level1)
	{
		// TRANSITIONS
		case l1_init:
			end_level = 0;
			if (!start_easy)
			{
				level1 = l1_init;
			}
			else if (start_easy)
			{
				LCD_ClearScreen();
				LCD_Cursor(1);
				LCD_DisplayString(1, game_start_string);
				level1 = display;
				end_level = 1;
			}
			break;
		
		case display:
			level1 = blink1;
			break;
		
		case blink1:
			if (button)
			{
				ggg = 1;
				level1 = stop;
			}
		break;
		
		case blink2:
			if (button)
			{
				ggg2 = 1;
				level1 = win_lose;
			}
			break;
			
		case blink3:
			if (button)
			{
				ggg3 = 1;
				level1 = win_lose;
			}
			break;
		
		case blink4:
			if (button)
			{
				ggg4 = 1;
				level1 = win_lose;
			}
			break;
		
		case win_lose:
			if (ggg2)
			{
				ggg2 = 0;
				if (comparing != comparing2)
				{
					fail = 1;
					light_fail = 1;
					light_fail2 = 1;
					cou = 1;
				}
				else
				{
					row_counter = 0;
					level1 = stop;

				}
			}
			if (ggg3)
			{
				ggg3 = 0;
				if (comparing3 != comparing2)
				{
					light_fail = 1;
					light_fail2 = 1;
					fail = 1;
					cou2 = 1;
				}
				else
				{
					row_counter2 = 0;
					level1 = stop;
				}
			}
			if (ggg4)
			{
				ggg4 = 0;
				
				if (comparing4 != comparing3)
				{
					
					light_fail = 1;
					light_fail2 = 1;
					fail = 1;
					cou3 = 1;
				}
				
				else
				{
					level1 = final_win_lose;
				}
				
			}
			break;
			
		case final_win_lose:
				winner = 1;
				break;
			
		//FIXME
		case stop:
		
			if (row_counter)
			{
				level1 = blink2;
			}
			if (row_counter2)
			{
				level1 = blink3;
			}
			if (row_counter3)
			{
				level1 = blink4;
			}
			
			break;
		
		
		default:
			break;
	}
	// ACTIONS
	switch(level1)
	{
		
		case l1_init:
			break;
		
		case display:
		
			break;
		
		case blink1:
			if (iteration > 2)
			{
				transmit_data2(0x03);
				PORTA = arr[y];
				comparing = arr[y];
				y++;
				if (y == 10)
				{
					y = 0;
				}
				iteration = 0;
			}
			iteration++;
			break;
		
		case blink2:
			if (iteration > 2)
			{
				transmit_data2(0x0C);
				PORTA = arr[y];
				comparing2 = arr[y];
				y++;
				if (y == 10)
				{
					y = 0;
				}
				iteration = 0;
			}
			iteration++;
			break;
		
		case stop:
			break;
			
		case blink3:
			if (iteration > 2)
			{
				transmit_data2(0x30);
				PORTA = arr[y];
				comparing3 = arr[y];
				y++;
				if (y == 10)
				{
					y = 0;
				}
				iteration = 0;
			}
			iteration++;
			break;
			
		case blink4:
			if (iteration > 2)
			{
				transmit_data2(0xC0);
				PORTA = arr[y];
				comparing4 = arr[y];
				y++;
				if (y == 10)
				{
					y = 0;
				}
				iteration = 0;
			}
			iteration++;
			break;
		
		default:
			break;
	}
}

enum level1_stops {l1_stop} level1_stop;
int level1_stop_tick()
{
	switch(level1_stop)
	{
		case l1_stop:
			break;
						
		default:
			break;
	}
	
	switch(level1_stop)
	{
		case l1_stop:
			if(start_easy)
			{
				if(ggg)
				{
					if (!light_fail && !light_fail2)
					{
						ggg = 0;
						transmit_data2(0x03);
						PORTA = comparing;
						row_counter++;
						ccc++;
						y =0;
					}
				
				}
				else if (ggg4)
				{
					if (!light_fail && !light_fail2)
					{
						transmit_data2(0xC0);
						PORTA = comparing4;
						//row_counter4++;
						ccc++;
					}
				}
				else if (ggg3)
				{
					if (!light_fail && !light_fail2)
					{
						transmit_data2(0x30);
						PORTA = comparing3;
						ccc = ccc + 1;
						row_counter3++;
						y = 0;
					}
				}
				else if (ggg2)
				{
					if (!light_fail && !light_fail2)
					{
						transmit_data2(0x0C);
						PORTA = comparing2;
						ccc = ccc + 1;
						row_counter2++;
						y = 0;
					}
				}
			}
			break;
	}
}

enum fail_lights {fl_init, fl_init2, fl_init3, fl_init4, fl_init5} fail_light;
int fail_light_tick()
{
	switch(fail_light)
	{
		case fl_init:
			
			if (cou) 
			{
				fail_light = fl_init2;
			}
			if (cou2)
			{
				fail_light = fl_init4;
			}
			if (cou3)
			{
				fail_light = fl_init5;
			}
			break;
			
		case fl_init2:
			fail_light = fl_init3;
			break;
		
		case fl_init3:
			
				if (!cou2)
				{
					fail_light = fl_init2;
				}
				if (cou2 && !cou3)
				{
					fail_light = fl_init4;
				}
				if (cou3)
				{
					fail_light = fl_init5;
				}
			
			break;
			
		case fl_init4:
			if (!cou3)
			{
				fail_light = fl_init2;
			}
			if (cou3)
			{
				fail_light = fl_init2;
			}
			break;
			
		case fl_init5:
			fail_light = fl_init4;
			break;
	}
	switch(fail_light)
	{
		case fl_init:
			break;
			
		case fl_init2:
			transmit_data2(0x0C);
			PORTA = comparing2;
			break;
			
		case fl_init3:
			transmit_data2(0x03);
			PORTA = comparing;
			break;
			
		case fl_init4:
			transmit_data2(0x30);
			PORTA = comparing3;
			break;
			
		case fl_init5:
			transmit_data2(0xC0);
			PORTA = comparing4;
			break;
	}
}


enum level2s {l2_init, l2_display, l2_blink1, l2_blink2, l2_blink3, l2_blink4, l2_blink5, l2_blink6, l2_blink7, l2_blink8, l2_win_lose, l2_final_win_lose, l2_stop} level2;
int level2_tick()
{
	button = ~PINC & 0x04;
	
	//------------TRANSITIONS------------
	switch(level2)
	{
		case l2_init:
			end_level = 1;
			if (!start_normal)
			{
				level2 = l2_init;
			}
			else if (start_normal)
			{
				LCD_ClearScreen();
				LCD_DisplayString(1, game_start_string);
				level2 = l2_display;
			}
			break;
			
		case l2_display:
			level2 = l2_blink1;
			break;
			
		case l2_blink1:
			if (button)
			{
				ggg = 1;
				level2 = l2_stop;
			}
			break;
			
		case l2_blink2:
			if (button)
			{
				ggg2 = 1;
				level2 = l2_win_lose;
			}
			break;
			
		case l2_blink3:
			if (button)
			{
				ggg3 = 1;
				level2 = l2_win_lose;
			}
			break;
			
		case l2_blink4:
			if (button)
			{
				ggg4 = 1;
				level2 = l2_win_lose;			
			}
			break;
			
		case l2_blink5:
			if (button)
			{
				ggg5 = 1;
				level2 = l2_win_lose;
			}
			break;
			
		case l2_blink6:
			if (button)
			{
				ggg6 = 1;
				level2 = l2_win_lose;
			}
			break;
			
		case l2_blink7:
			if (button)
			{
				ggg7 = 1;
				level2 = l2_win_lose;
			}
			break;
			
		case l2_blink8:
			if (button)
			{
				ggg8 = 1;
				level2 = l2_win_lose;
			}
			
		case l2_win_lose:
			if (ggg2)
			{
				ggg2 = 0;
				if (comparing != comparing2)
				{
					fail = 1;
					light_fail = 1;
					light_fail2 = 1;
				}
				else
				{
					row_counter = 0;
					level2 = l2_stop;
				}
			}
			if (ggg3)
			{
				ggg3 = 0;
				if (comparing3 != comparing2)
				{
					fail = 1;
					light_fail = 1;
					light_fail2 = 1;
				}
				else
				{
					row_counter2 = 0;
					level2 = l2_stop;
				}
			}
			if (ggg4)
			{
				ggg4 = 0;
				if ((comparing4 != two_dot_check) && (comparing4 != two_dot_check2))
				{
					fail = 1;
					light_fail = 1;
					light_fail2 = 1;
				}
				else
				{
					row_counter3 = 0;
					level2 = l2_stop;
				}
			}
			if (ggg5)
			{
				ggg5 = 0;
				if (comparing5 != comparing4)
				{
					fail = 1;
					light_fail = 1;
					light_fail2 = 1;
				}
				else
				{
					row_counter4 = 0;
					level2 = l2_stop;
				}
			}
			if (ggg6)
			{
				ggg6 = 0;
				if (comparing6 != comparing5)
				{
					fail = 1;
					light_fail = 1;
					light_fail2 = 1;
				}
				else
				{
					row_counter5 = 0;
					level2 = l2_stop;
				}
			}
			if (ggg7)
			{
				ggg7 = 0;
				if ((comparing7 != one_dot_check) && (comparing7 != one_dot_check2))
				{
					fail = 1;
					light_fail = 1;
					light_fail2 = 1;
				}
				else
				{
					row_counter6 = 0;
					level2 = l2_stop;
				}
			}
			if (ggg8)
			{
				ggg8 = 0;
				if (comparing8 != comparing7)
				{
					fail = 1;
					light_fail = 1;
					light_fail2 = 1;
				}
				else
				{
					level2 = l2_final_win_lose;
				}
			}
			break;
			
		case l2_final_win_lose:
			Winner_Winner = 1;
			break;
			
		case l2_stop:
			if (row_counter)
			{
				level2 = l2_blink2;
			}
			if (row_counter2)
			{
				level2 = l2_blink3;
			}
			if (row_counter3)
			{
				level2 = l2_blink4;
			}
			if (row_counter4)
			{
				level2 = l2_blink5;
			}
			if (row_counter5)
			{
				level2 = l2_blink6;
			}
			if (row_counter6)
			{
				level2 = l2_blink7;
			}
			if (row_counter7)
			{
				level2 = l2_blink8;
			}
			break;
		
		default:
		break;
	}
	
	//------------ACTIONS------------
	switch(level2)
	{
		case l2_init:
			break;
			
		case l2_display:
			break;
			
		case l2_blink1:
			if (iteration > 5)
			{
				transmit_data2(0x01);
				PORTA = arr[y];
				comparing = arr[y];
				y++;
				if (y == 10)
				{
				
					y = 0;
				}
				iteration = 0;
			}
			iteration++;
			break;
			
		case l2_blink2:
			if (iteration > 4.5)
			{
				transmit_data2(0x02);
				PORTA = arr[y];
				comparing2 = arr[y];
				y++;
				if (y == 10)
				{
					
					y = 0;
				}
				iteration = 0;
			}
			iteration++;
			break;
			
		case l2_blink3:
			if (iteration > 3)
			{
				transmit_data2(0x04);
				PORTA = arr[y];
				comparing3 = arr[y];
				
				if (y < 6)
				{
					two_dot_check = arr2[y];
					two_dot_check2 = arr2[y+1];
				}
				else if ( y >= 6)
				{
					two_dot_check = arr2[y+1];
					two_dot_check2 = arr2[y+2];
				}
				y++;
				if (y == 10)
				{
					
					y = 0;
				}
				iteration = 0;
			}
			iteration++;
			break;
			
		case l2_blink4:
			if (iteration > 2.5)
			{
				transmit_data2(0x08);
				PORTA = arr2[y];
				comparing4 = arr2[y];
				y++;
				if (y == 12)
				{
					y = 0;
				}
				iteration = 0;
			}
			iteration++;
			break;
		
		case l2_blink5:
			if (iteration > 2)
			{
				transmit_data2(0x10);
				PORTA = arr2[y];
				comparing5 = arr2[y];
				y++;
				if (y == 12)
				{
					y = 0;
				}
				iteration = 0;
			}
			iteration++;
			break;
			
			
		case l2_blink6:
			if (iteration > 1.5)
			{
				transmit_data2(0x20);
				PORTA = arr2[y];
				comparing6 = arr2[y];
				if (y < 7)
				{
					one_dot_check = arr3[y];
					one_dot_check2 = arr3[y+1];
				}
				else if (y >= 7)
				{
					one_dot_check = arr3[y+1];
					one_dot_check2 = arr3[y+2];
				}
				y++;
				if (y == 12)
				{
					y = 0;
				}
				iteration = 0;
			}
			iteration++;
			break;
			
		case l2_blink7:
			if (iteration > 1.3)
			{
				transmit_data2(0x40);
				PORTA = arr3[y];
				comparing7 = arr3[y];
				y++;
				if (y == 14)
				{
					y = 0;
				}
				iteration = 0;
			}
			iteration++;
			break;
		
		case l2_blink8:
			if (iteration > 1)
			{
				transmit_data2(0x80);
				PORTA = arr3[y];
				comparing8 = arr3[y];
				y++;
				if (y == 14)
				{
					y  =0;
				}
				iteration = 0;
			}
			iteration++;
			break;
			
					
		default:
			break;
	}
}

enum level2_stops {stop2} level2_stop;
int level2_stop_tick()
{
	//---------------Transitions---------------
	switch(level2_stop)
	{
		case stop2:
			break;
		
		default:
			break;
	}
	//---------------Action---------------
	switch(level2_stop)
	{
		case stop2:
			if (start_normal)
			{
				if (ggg)
				{
					if (!light_fail && !light_fail2)
					{
						ggg = 0;
						transmit_data2(0x01);
						PORTA = comparing;
						row_counter++;
						y = 0;
					}
				}
				else if (ggg2)
				{
					if (!light_fail && !light_fail2)
					{
						transmit_data2(0x02);
						PORTA = comparing2;
						row_counter2++;
						y = 0;
					}
				}
				else if (ggg3)
				{
					if (!light_fail && !light_fail2)
					{
						transmit_data2(0x04);
						PORTA = comparing3;
						row_counter3++;
						y = 0;
					}
				}
				else if (ggg4)
				{
					if (!light_fail && !light_fail2)
					{
						transmit_data2(0x08);
						PORTA = comparing4;
						row_counter4++;
						y = 0;
					}
				}
				else if (ggg5)
				{
					if (!light_fail && !light_fail2)
					{
						transmit_data2(0x10);
						PORTA = comparing5;
						row_counter5++;
						y = 0;
					}
				}
				else if (ggg6)
				{
					if (!light_fail && !light_fail2)
					{
						transmit_data2(0x20);
						PORTA = comparing6;
						row_counter6++;
						y = 0;
					}
				}
				else if (ggg7)
				{
					if (!light_fail && !light_fail2)
					{
						transmit_data2(0x40);
						PORTA = comparing7;
						row_counter7++;
						y = 0;
					}
				}
				else if (ggg8)
				{
					if (!light_fail && !light_fail2)
					{
						transmit_data2(0x80);
						PORTA = comparing8;
					}
				}
			}
			break;
			
		default:
			break;
	}
}

enum level3s {l3_init} level3;
int level3_tick()
{
	switch(level3)
	{
		case l3_init:
		end_level = 1;
		if (!start_hard)
		{
			level3 = l3_init;
		}
		else if (start_hard)
		{
			//level3 = ;
			end_level = 1;
		}
		break;

		default:
		break;
	}
}

enum win_loser_s {wl_init, winner_display, loser_display} win_loser;
int win_loser_tick()
{
	switch(win_loser)
	{
		case wl_init:
			if (winner)
			{
				LCD_ClearScreen();
				LCD_DisplayString(1, win_string);
				LCD_WriteData(0);
				win_loser = winner_display;
			}
			if (fail)
			{
				
				LCD_ClearScreen();
				LCD_DisplayString(1, lose_string);
				LCD_WriteData(0);
				win_loser = loser_display;
			}
			break;
			
		case winner_display:
			break;
			
		case loser_display:
			break;
			
		default:
			break;
	}
	switch(win_loser)
	{
		case wl_init:
			break;
			
		case winner_display:
			transmit_data2(0xFF);
			PORTA = comparing;
			
			break;
			
		case loser_display:
			break;
			
		default:
			break;
	}
}

enum LED_Win_Lose_s{LED_init, the_normal} LED_Win_Lose;
int LED_Win_Lose_Tick()
{
	switch(LED_Win_Lose)
	{
		case LED_init:
			if (Winner_Winner)
			{
				LCD_ClearScreen();
				LCD_DisplayString(1, win_string);
				LCD_WriteData(0);
				LED_Win_Lose = the_normal;
			}
			
			break;
			
		case the_normal:
			break;
		
		default:
			break;
	}
	switch(LED_Win_Lose)
	{
		case the_normal:
			
				transmit_data2(0x07);
				PORTA = comparing;
			
			break;
			
		default:
			break;
	}
}
enum LED2_Win_Lose_s{LED2_init, the2_normal} LED2_Win_Lose;
int LED2_Win_Lose_Tick()
{
	switch(LED2_Win_Lose)
	{
		case LED2_init:
			if (Winner_Winner)
			{
				LED2_Win_Lose = the2_normal;
			}
			break;
		
		case the2_normal:
			break;
		
		default:
			break;
	}
	switch(LED2_Win_Lose)
	{
		case the2_normal:
		
			transmit_data2(0x38);
			PORTA = comparing5;
		
		break;
		
		default:
			break;
	}
}
enum LED3_Win_Lose_s{LED3_init, the3_normal} LED3_Win_Lose;
int LED3_Win_Lose_Tick()
{
	switch(LED3_Win_Lose)
	{
		case LED3_init:
			if (Winner_Winner)
			{
				LED3_Win_Lose = the3_normal;
			}
			break;
		
		case the3_normal:
			break;
		
		default:
			break;
	}
	switch(LED3_Win_Lose)
	{
		case the3_normal:
		
			transmit_data2(0xC0);
			PORTA = comparing8;
			
			break;
		
		default:
			break;
	}
}

int main()
{
	DDRA = 0xFF; PORTA = 0x00;
	DDRD = 0xFF; PORTD = 0x00;
	DDRB = 0xFF; PORTB = 0x00;
	DDRC = 0x03; PORTC = 0xFC;
	
	LCD_init();

	A2D_init();
	
	// MENU PERIOD
	unsigned long int menu_calc = 300;
	// EASY LEVEL PERIOD
	unsigned long int level1_calc = 115;
	// EASY LEVEL STOP PERIOD
	unsigned long int level1_stop_calc = 1;
	// LOSING THE GAME ON LED PERIOD
	unsigned long int fail_light_calc = 200;
	// WINNER OR LOSER ON LCD PERIOD
	unsigned long int winner_loser_calc = 500;
	// NORMAL LEVEL PERIOD
	unsigned long int level2_calc = 70;
	// NORMAL LEVEL STOP PERIOD
	unsigned long int level2_stop_calc = 1;
	
	// TEST
	unsigned long int LED_Win_calc = 1;
	unsigned long int LED2_Win_calc = 1;
	unsigned long int LED3_Win_calc = 1;
		
	
	unsigned long int tmpGCD = 1;
	
	// EASY LEVEL
	tmpGCD = findGCD(menu_calc, level1_calc);
	tmpGCD = findGCD(tmpGCD, level1_stop_calc);
	
	// NORMAL LEVEL
	tmpGCD = findGCD(tmpGCD, level2_calc);
	tmpGCD = findGCD(tmpGCD, level2_stop_calc);
	
	// MISC.
	tmpGCD = findGCD(tmpGCD, fail_light_calc);
	tmpGCD = findGCD(tmpGCD, winner_loser_calc);
	
	tmpGCD = findGCD(tmpGCD, LED_Win_calc);
	tmpGCD = findGCD(tmpGCD, LED2_Win_calc);
	tmpGCD = findGCD(tmpGCD, LED3_Win_calc);
	
	
	
	unsigned long int menu_period = menu_calc/tmpGCD;
	
	unsigned long int level1_period = level1_calc/tmpGCD;
	unsigned long int level1_stop_period = level1_stop_calc/tmpGCD;
	
	unsigned long int level2_period = level2_calc/tmpGCD;
	unsigned long int level2_stop_period = level2_stop_calc/tmpGCD;
	
	unsigned long int fail_light_period = fail_light_calc/tmpGCD;
	unsigned long int winner_loser_period = winner_loser_calc/tmpGCD;
	
	unsigned long int LED_Win_period = LED2_Win_calc/tmpGCD;
	unsigned long int LED2_Win_period = LED2_Win_calc/tmpGCD;
	unsigned long int LED3_Win_period = LED3_Win_calc/tmpGCD;
	
	static task task1, task2, task3, task4, task5, task6, task7, task8, task9, task10;
	task *tasks[] = {&task1, &task2, &task3, &task4, &task5, &task6, &task7, &task8, &task9, &task10};
	const unsigned short numTasks = 10;
	
	task1.state = init;
	task1.period = menu_period;
	task1.elapsedTime = menu_period;
	task1.TickFct = &menu_sm_tick;
	
	task2.state = l1_init;
	task2.period = level1_period;
	task2.elapsedTime = level1_period;
	task2.TickFct = &level1_tick;
	
	task3.state = l1_stop;
	task3.period = level1_stop_period;
	task3.elapsedTime = level1_stop_period;
	task3.TickFct = &level1_stop_tick;
	
	task4.state = fl_init;
	task4.period = fail_light_period;
	task4.elapsedTime = fail_light_period;
	task4.TickFct = &fail_light_tick;
	
	task5.state = wl_init;
	task5.period = winner_loser_period;
	task5.elapsedTime = winner_loser_period;
	task5.TickFct = &win_loser_tick;
	
	// Normal LEVEL
	task6.state = l2_init;
	task6.period = level2_period;
	task6.elapsedTime = level2_period;
	task6.TickFct = &level2_tick;
	
	task7.state = stop2;
	task7.period = level2_stop_period;
	task7.elapsedTime = level2_stop_period;
	task7.TickFct = &level2_stop_tick;
	
	task8.state = LED_init;
	task8.period = LED_Win_period;
	task8.elapsedTime = LED_Win_period;
	task8.TickFct = &LED_Win_Lose_Tick;
	
	task9.state = LED2_init;
	task9.period = LED2_Win_period;
	task9.elapsedTime = LED2_Win_period;
	task9.TickFct = &LED2_Win_Lose_Tick;
	
	task10.state = LED3_init;
	task10.period = LED3_Win_period;
	task10.elapsedTime = LED3_Win_period;
	task10.TickFct = &LED3_Win_Lose_Tick;
	
	
	
	TimerSet(tmpGCD);
	TimerOn();
	
	while(1)
	{
		
		for (unsigned char i = 0; i < numTasks; i++ ) {
			if ( tasks[i]->elapsedTime == tasks[i]->period ) {
				tasks[i]->state = tasks[i]->TickFct(tasks[i]->state);
				tasks[i]->elapsedTime = 0;
			}
			tasks[i]->elapsedTime += 1;
		}
		while(!TimerFlag){}
		TimerFlag = 0;
	}
}