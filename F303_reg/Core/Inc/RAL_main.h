/*
 * RAL_main.h
 *
 *  Created on: Nov 1, 2023
 *      Author: romanlobach
 */

#ifndef INC_RAL_MAIN_H_
#define INC_RAL_MAIN_H_

typedef struct PinConfig PinConfig;

typedef enum {
	RAL_OK,
	RAL_ERROR
} RAL_Status;

typedef enum {
	INPUT  = 0b00U,
	OUTPUT = 0b01U,
	ALT_F  = 0b10U,
	ANALOG = 0b11U
} RAL_PinMode;

typedef enum {
	PUSH_PULL  = 0b0U,
	OPEN_DRAIN = 0b1U,
} RAL_PinOutputType;

typedef enum {
	LOW = 0b00U,
	MED = 0b01U,
	HI 	= 0b11U
} RAL_PinOutputSpeed;

typedef enum {
	NO_PUPD   = 0b00U,
	PULL_UP   = 0b01U,
	PULL_DOWN = 0b10U,
	RESERVED  = 0b11U
} RAL_PinPullUpPullDownResistor;

typedef enum {
	PIN_LOW = 0,
	PIN_HI  = 1
} RAL_PinLevel;

struct PinConfig{
	GPIO_TypeDef* port;
    int pin_number;
    RAL_PinMode mode;
    RAL_PinOutputType type;
    RAL_PinPullUpPullDownResistor pullResistor;
    RAL_PinOutputSpeed speed;
    RAL_PinLevel initLevel;

    // Function pointers
    RAL_Status (*configure)(struct PinConfig *pin);
    RAL_PinLevel (*read)(struct PinConfig *pin);
    RAL_Status (*write)(struct PinConfig *pin, RAL_PinLevel level);

    // Add more configuration parameters as needed
};

RAL_PinLevel RAL_readPin(PinConfig *pin);
RAL_Status RAL_writePin(PinConfig *pin, RAL_PinLevel level);
RAL_Status RAL_pinConfig(PinConfig *pin);
RAL_Status RAL_pinRegister(
							PinConfig *pin,
							GPIO_TypeDef* port,
							int pin_number,
							RAL_PinMode initMode,
							RAL_PinOutputType initType,
							RAL_PinOutputSpeed initSpeed,
							RAL_PinPullUpPullDownResistor initResistor,
							RAL_PinLevel initLevel
							);

#endif /* INC_RAL_MAIN_H_ */
