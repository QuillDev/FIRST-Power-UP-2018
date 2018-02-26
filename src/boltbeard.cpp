//boltbeard.cpp
#include "boltbeard.h"

//Set Motor Speed
double spd(int x, int y){
	double z = (x*.005 + .5) *y;
	return(z);
}
