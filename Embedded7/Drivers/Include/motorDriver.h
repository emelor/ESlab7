#ifndef MOTORDRIVER_H
#define MOTORDRIVER_H


/**********************************************************************************
This driver controls the two motors provided in the test rig for the course 4F1908.
The motors are identical in behaviour and are controlled using pulse width modulation (PWM).
The frequency at which the motors run is set to 20 KHz.
Each motor can be controlled separately by 
(1) specifying the duty cycle of the PWM signal; and 
(2) setting the enable/disable pin as desired.
The motor is set to Disable by default.
So, the motors will not run unless motorx_enable is called first.
***********************************************************************************/

extern int md_PWMPeriod;	//=250. The period at which the PWM signal operates.

//At the end of this function, a PWM signal with a duty cycle of 50% is sent to the motors.
//The motors are set to disable by default.
void motors_initialise();

//Enable the motors, allowing the set PWM signal to drive them.
void motor1_enable(void);
void motor2_enable(void);

//Disable the motors. 
//After calling this function,the motor will not run irrespective of the set PWM signal.
void motor1_disable(void);
void motor2_disable(void);

//Set the duty cycle to run the motor.
//The desiredDutyCycle can only be in the range 1 to md_PWMPeriod-1.
//If desiredDutyCycle is beyound this range, then
//(2) the request is ignored.
//(1) The function returns 0
int motor1_set_duty_cycle(int desiredDutyCycle);
int motor2_set_duty_cycle(int desiredDutyCycle);


//Set the speed to run the motor.
//desiredSpeed ranges between  -(md_PWMPeriod/2-1) & +(md_PWMPeriod/2-1)
//0 to +(md_PWMPeriod/2-1) gives positive speeds.
//0 to -(md_PWMPeriod/2-1) gives negative speeds.
//Positive speeds are defined to match the positive direction of the encoders.
//If desiredSpeed is beyound the above range, then
//(2) the request is ignored.
//(1) The function returns 0
int motor1_set_speed(int desiredSpeed);
int motor2_set_speed(int desiredSpeed);

#endif