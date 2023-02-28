#include <stdio.h>


//	Define Local Variables

float k_i, k_d, k_p;
float error;
float time_step;
float previous_Value=0;


float i_error, p_error, d_error;

void setPIDValues(float i, float d, float p)	{
	k_i	= i;
	k_d	= d;
	k_p	= p;
}
void calculateError(float newValue)	{
	//if (((i_error < 1000.0) && (i_error > -1000.0)) || (i_error > 1000 && error < 0) || (i_error < -1000 && error > 0))	{
	//	i_error	+= error * time_step; 	//Limiter	
	//}
	i_error += error * time_step;
	d_error = (newValue - previous_Value)/time_step;
	previous_Value = newValue;
	p_error = error;
}
void geterror(float e, float ts, float newValue)	{
	error	= e;
	time_step = ts;
	calculateError(newValue);
}
float generatePIDOut()	{
			// + (i_error * k_i) + (d_error * k_d)); 
	return ((p_error * k_p)+ (i_error * k_i) + (d_error * k_d)); // + (d_error * k_d)); 
}
float printi()	{
	return i_error;
}
float printd()	{
	return d_error;
}
float printp()	{
	return p_error;
}
float getPrevious_Value()	{
	return previous_Value;
}
float peor()	{
	return i_error;
}
