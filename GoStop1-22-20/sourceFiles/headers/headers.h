#pragma once
#include <stdio.h>
#include <vector>
#include <iostream>
#include <string>
#include <time.h>
#include <algorithm>
#include <random>
#include <cstdlib>
#include <fstream>

/**********************************************************************
Function Name: dashedLine
Purpose: Used to seperate different parts in the UI and make it more
readable
Parameters:
		None
Return Value: None
Local Variables:
		None
Algorithm:
		1) Prints a line
Assistance Received: Edwin O'Connor suggested I use this to seperate 
output and make it more readable 1/23/20
**********************************************************************/
inline void dashedLine() 
{
	std::cout << "----------------------------------------------------------\n";
}
