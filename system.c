#include <stdio.h>
#include "window.h"
#include "reactionwheel.h"
#include "pid.h"

/*
 * Files:
 * -Grapher
 * -PID
 * -Physics/rocket/reaction wheel
 * -Noise
*/

//	Local Variables

float timeStep = 5;
float y_Scale = 0.2;
float x_Scale = 17;
int numbStep = 1000;	//1000;
float currentTime = 0;
void setup()	{
	displaySetUp(800,800);
	setValues(0.01,0.001,100.0,0.0);
	//setPIDValues(68.99525,199.0,198.302);
	//setPIDValues(1.0,0.50,1.0);
	setPIDValues(0.5,0.5,0.5);
}
void update(int counter)	{
	for (float i = (counter*timeStep); i < (counter*timeStep)+(timeStep); i+=(timeStep/numbStep))	{
		geterror(getAngVelRocket(),timeStep/numbStep, getAngVelRocket());	
		float out = generatePIDOut();
		//idealAngTransfer_MotorDelay(out, timeStep);
		//idealAngTransfer(out);
		limitedAcceleration(out, timeStep/numbStep);
		line((i)*x_Scale,getPrevious_Value()*y_Scale,(i+timeStep/numbStep)*x_Scale,getAngVelRocket()*y_Scale);
		line((i)*x_Scale,(getPreviousWheel()*y_Scale)-250,(i+timeStep/numbStep)*x_Scale,(getAngVelWheel()*y_Scale)-250);
	}
}
void main()	{
	setup();
	displayUpdate();
	sleep(3);
	twoDAxis();
	int counter = 0;
	while(1)	{
		displayUpdate();
		scanf("");
		system("clear");
		printf("\n\nAngVel: %f\n",getAngVelRocket());
		printf("AccWheel: %f\n", getAcc());
		printf("AngVelWheel: %f\n", getAngVelWheel());
		printf("\nPress Return for Next Time Step: \n");
		printf("PID out: %f\n", generatePIDOut());
		printf("P: %f\n",printp());
		printf("I: %f\n",printi());
		printf("D: %f\n",printd());
		update(counter);
		counter++;
	}	
}
