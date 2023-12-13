/*
 * RAL_main.c
 *
 *  Created on: Nov 1, 2023
 *      Author: romanlobach
 */

#include "main.h"
#include "RAL_main.h"

void setBitHandler(volatile uint32_t* reg, uint32_t setBit, uint32_t width, int position) {

	uint32_t resultRegConfig = *reg;
	uint32_t clearMask = ~(width << position);
	resultRegConfig &= clearMask;
	uint32_t setBits = ((uint32_t)setBit) << position;
	resultRegConfig |= setBits;

	*reg = resultRegConfig;
}

RAL_Status RAL_portClockEnable(GPIO_TypeDef* GPIO) {
	int portOffset = (GPIO == GPIOA) ? 17 :
	             (GPIO == GPIOB) ? 18 :
	             (GPIO == GPIOC) ? 19 :
	             (GPIO == GPIOD) ? 20 :
//	             (GPIO == GPIOE) ? 21 :
	             (GPIO == GPIOF) ? 22 : -1;
//	             (GPIO == GPIOG) ? 23 :
//	             (GPIO == GPIOH) ? 16 : -1;

	if (portOffset != -1) {
		if ((RCC->AHBENR & (1U << portOffset)) == 0) {
			RCC->AHBENR |= 1U << portOffset;
		}

		if ((RCC->AHBENR & (1U << portOffset)) != 0) {
			return RAL_OK;
		}
	}

	return RAL_ERROR;
}

RAL_Status RAL_pinConfig(PinConfig *pin) {

	if (pin == NULL || pin->port == NULL) {
		return RAL_ERROR;
	}

	GPIO_TypeDef* GPIO = pin->port;
	uint32_t mode = (uint32_t)pin->mode;
	uint32_t type = (uint32_t)pin->type;
	uint32_t speed = (uint32_t)pin->speed;
	uint32_t pullResistor = (uint32_t)pin->pullResistor;
	int pinNumber = pin->pin_number;

	RAL_portClockEnable(GPIO);

	setBitHandler(&GPIO->MODER, mode, 0b11U, pinNumber * 2);
	setBitHandler(&GPIO->OTYPER, type, 0b1U, pinNumber);
	setBitHandler(&GPIO->OSPEEDR, speed, 0b11U, pinNumber * 2);
	setBitHandler(&GPIO->PUPDR, pullResistor, 0b11U, pinNumber * 2);

	if(
		pin->mode == OUTPUT &&
	   (GPIO->MODER >> (pinNumber * 2) & 0x3U) == mode &&
	   (GPIO->OTYPER >> pinNumber & 0x1U) == type &&
	   (GPIO->OSPEEDR >> (pinNumber * 2) & 0x3U) == speed &&
	   (GPIO->PUPDR >> (pinNumber * 2) & 0x3U) == pullResistor
	  ) {
		return RAL_OK;
	}

	if(
		pin->mode == INPUT &&
	   (GPIO->MODER >> (pinNumber * 2) & 0x3U) == mode
      ) {
		return RAL_OK;
	}

	return RAL_ERROR;
}

RAL_Status RAL_writePin(PinConfig *pin, RAL_PinLevel level) {

	if (pin == NULL || pin->port == NULL) {
		return RAL_ERROR;  // Add appropriate error handling
	}

	GPIO_TypeDef* GPIO = pin->port;
	int pinNumber = pin->pin_number;
	uint32_t pinSetBit = 1U << pinNumber;
	uint32_t pinResetBit = 1U << (pinNumber + 16);

	if(level == PIN_HI) {
		setBitHandler(&GPIO->BSRR, level, 0b1U, pinNumber);
		setBitHandler(&GPIO->BSRR, ~level, 0b1U, pinNumber + 16);
	} else if (level == PIN_LOW) {
		setBitHandler(&GPIO->BSRR, level, 0b1U, pinNumber);
		setBitHandler(&GPIO->BSRR, ~level, 0b1U, pinNumber + 16);
	} else {
		return RAL_ERROR;
	}

	if(
		 level == PIN_HI &&
		(GPIO->BSRR & pinSetBit) == 1 &&
		(GPIO->BSRR & pinResetBit) == 0
	  ) {
		return RAL_ERROR;
	}

	if(
		 level != PIN_LOW &&
		(GPIO->BSRR & pinSetBit) == 0 &&
		(GPIO->BSRR & pinResetBit) == 1
	  ) {
		return RAL_ERROR;
	}

	return RAL_OK;
}


RAL_PinLevel RAL_readPin(PinConfig *pin) {

	GPIO_TypeDef* GPIO = pin->port;
	int pinNumber = pin->pin_number;

	return (GPIO->IDR & (1U << pinNumber)) ? PIN_HI : PIN_LOW;

}

RAL_Status RAL_pinRegister(
							PinConfig *pin,
							GPIO_TypeDef* port,
							int pin_number,
							RAL_PinMode initMode,
							RAL_PinOutputType initType,
							RAL_PinOutputSpeed initSpeed,
							RAL_PinPullUpPullDownResistor initResistor,
							RAL_PinLevel initLevel
							) {

	pin->port = port;
	pin->pin_number = pin_number;
	pin->mode = initMode;
	pin->type = initType;
	pin->pullResistor = initResistor;
	pin->speed = initSpeed;
	pin->initLevel = initLevel;
	pin->configure = RAL_pinConfig;
	pin->read = RAL_readPin;
	pin->write = RAL_writePin;
	if(pin->configure(pin) != RAL_OK) return RAL_ERROR;
	if(pin->write(pin, initLevel) != RAL_OK) return RAL_ERROR;
	if(pin->read(pin) != initLevel) return RAL_ERROR;

	return RAL_OK;

}
