#pragma once
#ifndef __ILLUMINATED_PUSH_BUTTON_H__
#define __ILLUMINATED_PUSH_BUTTON_H__
#include <stdint.h>
#include <Arduino.h>
class IlluminatedPushButton {
public:
	IlluminatedPushButton(uint8_t switch_pin, uint8_t led_pin);
	void process();
	void ledOn();
	void ledOff();
	void setLed(bool);
	void attachPressCallback(void (*cb)(void)){
		if (cb){
			this->press_callback_ = cb;
		}
	}
	void attachReleaseCallback(void (*cb)(void)){
		if (cb){
			this->release_callback_ = cb;
		}
	}
	bool isLit(void);
private:
	void (*press_callback_)(void);
	void (*release_callback_)(void);
	uint8_t switch_pin_, led_pin_;
	uint16_t debounce_start_;
	bool press_key_, illuminated_;
};


#endif