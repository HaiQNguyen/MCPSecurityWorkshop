
/** @file main.c
 *  @brief main function, entry point of the application.  
 *
 *	Trusted application. Handling and verifying the pass code from the keypad 
 *
 *  @author Quang Hai Nguyen - TFAE- Engineering DACH - Arrow Central Europe GmbH 
 *
 *	@date	01.06.2019 - initial 
 *
 *  @bug No known bugs.
 */

/* Include section ----------------------------------------------------------*/
#include <atmel_start.h>
#include <string.h>



/* define section ----------------------------------------------------------*/
#define TOUCH_TIMER_MILI		5
#define KEY_PRESS_THRESHOLD		25
#define NUM_OF_PASSCODE_CHAR	5
			
/* external variable section ----------------------------------------------------------*/
extern volatile uint8_t measurement_done_touch;

/* local variable section -------------------------------------------------------------*/
typedef enum KEY_PAD
{
	KEY_NULL = -1, //No key is stored so far 
	KEY_1,
	KEY_2,
	KEY_3,
	KEY_4,
	KEY_5,
	KEY_6,
	KEY_7,
	KEY_8,
	KEY_9,
	KEY_C,
	KEY_0,
	KEY_POUND,
	NUM_OF_KEY,
}KeyPad;


static KeyPad input_code[NUM_OF_PASSCODE_CHAR] ={KEY_NULL, KEY_NULL, KEY_NULL, KEY_NULL, KEY_NULL};
static KeyPad pass_code[NUM_OF_PASSCODE_CHAR] = {KEY_6, KEY_3, KEY_2, KEY_6, KEY_3}; // password is 63263

static uint8_t input_code_index = 0; //pointer to current input character
static uint8_t key_pressed = 0;
static uint8_t key_press_count[NUM_OF_KEY];

static struct timer_task touch_timer;

/* local function section -------------------------------------------------------------*/

/**
 *  @brief	Handle the input from the keypad 
 *
 *	@param	NULL	no params
 *	
 *	@return	NULL	always return
 *
 *	Check which key is pressed and if the pressing action is over the threshold or not,\n
 *	which indicates a successful press action 
 *	
 *	@date	01.06.2019 - initial 
 *
 *  @bug No known bugs.
 */
static void HandleKeypadInput(void);

/**
 *  @brief	Timer callback 
 *
 *	@param	timer_task	timer invokes the callback
 *	
 *	@return	NULL	always return
 *
 *	Calling touch_process() and handle the imput if touch measurement is finished 
 *	
 *	@date	01.06.2019 - initial 
 *
 *  @bug No known bugs.
 */
static void TouchTimer_CB(const struct timer_task *const timer_task);

/**
 *  @brief	Print pass code on the screen
 *
 *	@param	NULL	no params
 *	
 *	@return	NULL	always return
 *	
 *	@date	01.06.2019 - initial 
 *
 *  @bug No known bugs.
 */
static void PrintPassCode(void);

/**
 *  @brief	Verify the input from the keypad 
 *
 *	@param	NULL	no params
 *	
 *	@return	true	if the input and password are matching 
 *	
 *	@date	01.06.2019 - initial 
 *
 *  @bug No known bugs.
 */
static bool VerifyPassCode(void);

/**
 *  @brief	Process the input key from the keypad
 *
 *	@param	NULL	no params
 *	
 *	@return	NULL	always return
 *
 *	Check if the input is a number, the pound sign,\n
 *	#: veryfy the input 
 *	C: clear the previous input
 *	other: next character of the pass code
 *	
 *	@date	01.06.2019 - initial 
 *
 *  @bug No known bugs.
 */
static void ProcessKey(KeyPad key);

int main(void)
{
	/* Initializes MCU, drivers and middleware */
	atmel_start_init();
	
	/* Timer initialization */
	touch_timer.interval = TOUCH_TIMER_MILI;
	touch_timer.cb       = TouchTimer_CB;
	touch_timer.mode     = TIMER_TASK_REPEAT;


	timer_add_task(&Timer, &touch_timer);
	timer_start(&Timer);
	
	printf("\x1b[2J");
	printf("Enter Password:\r\n");
	printf("_ _ _ _ _\r\n");

	/* Replace with your application code */
	while (1) {
		
	}
}


static void HandleKeypadInput(void)
{
	for(KeyPad i = KEY_1; i < NUM_OF_KEY; i++){
		key_pressed = get_sensor_state(i) & KEY_TOUCHED_MASK;
		if (0u != key_pressed) {
			++key_press_count[i];
			
			if(key_press_count[i] >= KEY_PRESS_THRESHOLD){
				key_press_count[i] = 0;
				ProcessKey(i);
			}
			else{
			}
		}
	}
}

static void TouchTimer_CB(const struct timer_task *const timer_task)
{

	touch_process();
	if (measurement_done_touch == 1) {
		HandleKeypadInput();
	}
}

static void PrintPassCode(void)
{
	printf("\x1b[2J");
	printf("Enter Password:\r\n");
	for(uint8_t i = 0; i < NUM_OF_PASSCODE_CHAR; i++)
	{
		if(input_code[i] == KEY_NULL)
			printf("_ ");
		else
			printf("* ");
	}
	printf("\r\n");	
}

static bool VerifyPassCode(void)
{
	bool result = false;
	if(!memcmp(input_code, pass_code,NUM_OF_PASSCODE_CHAR)){
		result = true;
		return result;
	}
	return result;
}

static void ProcessKey(KeyPad key)
{
	if(key == KEY_C){
		if(input_code_index  > 0 )
		{
			--input_code_index;
			input_code[input_code_index] = KEY_NULL;
		}
		PrintPassCode();
	}
	else if (key == KEY_POUND){
		if(true != VerifyPassCode())
		printf("wrong password! \r\n");
		else
		printf("password correct\r\n");
	}
	else{
		if(input_code_index < NUM_OF_PASSCODE_CHAR){
			input_code[input_code_index] = key;
			++input_code_index;
		}
		PrintPassCode();
	}
}