//****************************************************************************
// This file contains the implementation of the motor-driver
// By: Jad El-khoury
// Copyright: 2006
//****************************************************************************

#include "motorDriver.h"
#include "support_common.h"

static int md_PWMPeriod = 250;

void motors_initialise()
{
	//The motors are configured to run on Ports TD & TC!
	//At end of this function, 
	//(1) The PWM signals are enabled
	//(2) The motors are disabled 

	int initialDutyCycle;
	int prescaleClock; //Value between 0b000 & 0b111
	
	initialDutyCycle = md_PWMPeriod/2;
	prescaleClock = 0b011;

	//FOR both PWM1 & PWM3, set the PWM frequency to 20 KHz.
	MCF_PWM_PWMCLK = 0x00;
	MCF_PWM_PWMPRCLK = MCF_PWM_PWMPRCLK_PCKA(prescaleClock) 
					| MCF_PWM_PWMPRCLK_PCKB(prescaleClock);
	
	//Setup the enable/disable pin (TD[2/3])
    //Enable TD[2/3] as GPIO
	MCF_GPIO_PTDPAR &= 0b11111011;
	MCF_GPIO_PTDPAR &= 0b11110111;
    // Enable TD[2/3] as digital output
    MCF_GPIO_DDRTD |= 0b00000100;
    MCF_GPIO_DDRTD |= 0b00001000;
    //Set port TD[2/3] to 0	(disable the motors by default)
    MCF_GPIO_PORTTD &= 0b11111011;
    MCF_GPIO_PORTTD &= 0b11110111;

	//Setup PWM1/3 port to drive the motor
	//Enable TD[0/1] as PWM
	MCF_GPIO_PTDPAR |= 0b00000001;
	MCF_GPIO_PTDPAR |= 0b00000010;

	//Setup the PWM1/3 period and dutycycle
	MCF_PWM_PWMPER1 = md_PWMPeriod;
	MCF_PWM_PWMDTY1 = initialDutyCycle;
	MCF_PWM_PWMPER3 = md_PWMPeriod;
	MCF_PWM_PWMDTY3 = initialDutyCycle;

	//Enable PWM1/3
	MCF_PWM_PWME |= 0b00000010;
	MCF_PWM_PWME |= 0b00001000;
}

void motor1_enable(void)
{
    /* Set port TD[2] to 1 */
	MCF_GPIO_PORTTD |= 0b00000100;
}
void motor2_enable(void)
{
    /* Set port TD[3] to 1 */
	MCF_GPIO_PORTTD |= 0b00001000;
}

void motor1_disable(void)
{
    /* Set port TD[2] to 0 */
    MCF_GPIO_PORTTD &= 0b11111011;
}
void motor2_disable(void)
{
    /* Set port TD[3] to 0 */
    MCF_GPIO_PORTTD &= 0b11110111;
}


int pwm_set_duty_cycle(int pwmNumber, int desiredDutyCycle)
{
	//Boundary values seem to be special to program!
	//We stick to range 1 to md_PWMPeriod-1, so we slip boundary cases!
	//One beautiful day, I will program them in ;-)
	if ((desiredDutyCycle >= MCF_PWM_PWMPER(pwmNumber)) || (desiredDutyCycle < 1)) {
		//printf("You are sending a too high/low pwm value:%i\n", desiredDutyCycle);
		return 0;		
	}
	MCF_PWM_PWMDTY(pwmNumber) = desiredDutyCycle;
	return 1;
}
int motor1_set_duty_cycle(int desiredDutyCycle)
{
	return pwm_set_duty_cycle(1, desiredDutyCycle);
}
int motor2_set_duty_cycle(int desiredDutyCycle)
{
	return pwm_set_duty_cycle(3, desiredDutyCycle);
}


int pwm_set_speed(int pwmNumber, int desiredSpeed)
//desiredSpeed ranges between -(md_PWMPeriod/2-1) & +(md_PWMPeriod/2-1)
//0 to +(md_PWMPeriod/2-1) gives positive speeds.
//0 to -(md_PWMPeriod/2-1) gives negative speeds.
//For positive speeds, we need pwm signals to range from 0 to (md_PWMPeriod/2)-1
//This is due to the definition of the encoder direction!
//We want to make sure that what is defined as positive in the encoder,
//is the same as that for positive speeds.
//If desiredSpeed is beyound the above range, then
//(2) the request is ignored.
//(1) The function returns 0
{
	return pwm_set_duty_cycle (pwmNumber, (-1*desiredSpeed)+125);
}
int motor1_set_speed(int desiredSpeed)
{
	return pwm_set_speed(1, desiredSpeed);
}
int motor2_set_speed(int desiredSpeed)
{
	return pwm_set_speed(3, desiredSpeed);
}

