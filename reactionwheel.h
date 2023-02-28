#include <stdio.h>
#include <math.h>

/*	Defining Physics
 *	Clock wise rotation = +
 *	Anti Clock rotation = -
*/


//	Local variable

float momIRocket, 	momIWheel;	//Moment of inertia
float angVelRocket,	angVelWheel;	//Angular Velcoity
float accWheel=0;
float previousWheelSpeed;

//	Initilise Values
void setValues(float iR, float iW, float vR, float vW)	{
	
	momIRocket	= iR;
	momIWheel	= iW;

	angVelRocket	= vR;
	angVelWheel	= vW;
}

//	Ideal Angular Momentum Tranfer 0 = iR * vR + iW * vW

void idealAngTransfer(float dVR)	{
	angVelRocket	= angVelRocket+dVR;
	previousWheelSpeed = angVelWheel;
	angVelWheel	+= (-1*momIRocket*dVR/momIWheel);

	//return angVelRocket;
}
void limitedAcceleration (float vR, float tS)	{
	float vWSigmoided = ((50*tS)/(1+pow(2.7182818,-vR/10)))-((50*tS)/2);  //Add Sigma S function
	//printf("\nSigmoided : %f\n", vWSigmoided);
	//printf("\nCurrent AngVelRocket: %f",angVelRocket);
	//printf("\nAngVel+Sigmoid: %f\n", angVelRocket-vWSigmoided);	//
	idealAngTransfer(-vWSigmoided);
}
void idealAngTransfer_MotorDelay(float Voltage, float timeStep)	{
	if ((accWheel < 50 && accWheel >-50) || (accWheel > 50 && Voltage < 0) || (accWheel < -50 && Voltage > 0))	{ //Put Torque or max acceleration
		accWheel += Voltage;
		if ((angVelWheel > 3000 && accWheel < 0) || (angVelWheel < -3000 && accWheel > 0) || (angVelWheel < 3000 && angVelWheel > -3000))	{
			angVelWheel += accWheel*timeStep;	
		}
	}
	idealAngTransfer(angVelWheel);
}

float getAcc()	{
	return accWheel;
}

float getAngVelRocket()	{
	return angVelRocket;
}
float getAngVelWheel()	{
	return angVelWheel;
}
float getPreviousWheel()	{
	return previousWheelSpeed;
}

