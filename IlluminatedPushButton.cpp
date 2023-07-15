#include "IlluminatedPushButton.h"
#define PRESS_TIME 5
#define DEBUG
#include <debug.h>


IlluminatedPushButton::IlluminatedPushButton(uint8_t switch_pin, uint8_t led_pin):
switch_pin_(switch_pin), led_pin_(led_pin), debounce_start_(0), press_key_(false)
{
	pinMode(switch_pin, INPUT);
	pinMode(led_pin, OUTPUT);
	pinMode(switch_pin, INPUT_PULLUP);
	this->illuminated_ = false;
	this->press_callback_ = nullptr;
	this->release_callback_ = nullptr;
	digitalWrite(led_pin_, LOW);
}

void IlluminatedPushButton::setLed(bool lighted){
	digitalWrite(led_pin_, lighted ? HIGH : LOW);
	debug("PB::led: "); debugln(lighted);
	this->illuminated_ = lighted;
}

void IlluminatedPushButton::ledOn(void)		{	setLed(true); 	}
void IlluminatedPushButton::ledOff(void) 	{ 	setLed(false);	}
bool IlluminatedPushButton::isLit(void) 	{	return illuminated_;	}

/** \brief process
 *  Check for a press, set state variables, enter callback functions.
 *  Hold functionality is not implemented.
 */
void IlluminatedPushButton::process(void){
	uint16_t curr_time = millis();
	bool pressed = (digitalRead(switch_pin_) == LOW);
	if (pressed){
		if (debounce_start_ == 0) {
	      debounce_start_ = curr_time;
		  debugln("PB::Debounce Started");
	    } else if ((curr_time - debounce_start_) > PRESS_TIME) {
			if (!press_key_) {
				debugln("PB::Pressed");
				if (press_callback_){
					press_callback_();
				}
          		// set flag to indicate this press has been dealt with already.
          		press_key_ = true;
        	} // if (!press_key_)
		}
	  } else {  // PushButton Not Depressed:
	    if (debounce_start_ > 0) {
	      debounce_start_ = 0;
	    }
	    if (press_key_) {
		  debugln("PB::Released");
		  if (release_callback_){
          	release_callback_();
          }
	      press_key_ = false;
	    } // end if (press_key_)
	  } // end else (Pushbutton release)
}

