#include <iostream>
#include <cassert>
#include <string>
#include <cctype>
#include "grid.h"
using namespace std;

bool hasCorrectForm(string plan)
{
	if (!isalpha(plan[plan.length()-1]))	//returns false if the plan does not end with a turn letter
	{
		return false;
	}
	
	for (int i = 0; i < plan.length(); i++)	
	{
		if (isalpha(plan[i]))
		{
			if (plan[i] != 'L' && plan[i] != 'l' && plan[i] != 'R' && plan[i] != 'r')	//returns false if the plan contains letters other than turn letters
			{
				return false;
			}
		}
		else if (isdigit(plan[i]))
		{
			if (i+2 < plan.length())
			{
				if (isdigit(plan[i+1]) && isdigit(plan[i+2]))	//returns false if the plan contains more than 2 digits of number
				{
					return false;
				}
			}
		}
	}
	return true;
}

int determineSafeDistance(int r, int c, char dir, int maxSteps)
{
	int steps = 0;

	if (maxSteps < 0 || r <= 0 || c <= 0 || isWall(r, c))	//returns -1 if maxSteps is negative number or starting at invalid position
	{
		steps = -1;
	}
	
	switch(dir)		//increments steps until it meets the wall or edge
	{
		case 'N':
		case 'n':
			for (int i = 0; i < maxSteps; i++)	
			{
				if (r-i-1 > 0)
				{
					if(isWall(r-i-1, c))
					{
						return steps;
					}
					steps++;
				}
			}
			break;
		case 'E':
		case 'e':
			for (int i = 0; i < maxSteps; i++)
			{
				if (c+i+1 <= getCols())
				{
					if(isWall(r, c+i+1))
					{
						return steps;
					}
					steps++;
				}	
			}
			break;
		case 'W':
		case 'w':
			for (int i = 0; i < maxSteps; i++)
			{
				if (c-i-1 > 0)
				{
					if(isWall(r, c-i-1))
					{
						return steps;
					}
					steps++;
				}
			}
			break;
		case 'S':
		case 's':
			for (int i = 0; i < maxSteps; i++)
			{
				if (r+i+1 <= getRows())
				{
					if(isWall(r+i+1, c))
					{
						return steps;
					}
					steps++;
				}
			}
			break;
		}		
	return steps;
}

int obeyPlan(int sr, int sc, int er, int ec, char dir, string plan, int& nsteps)
{
	int r = sr;
	int c = sc;
	char currDir = dir;
	int steps = 0;

	//returns 2 if starting or ending at invalid position, or plan does not have correct form
	if (isWall(sr, sc) || isWall(er, ec) || sr <= 0 || sr > getRows() || sc <= 0 || sc > getCols() || (dir != 'N' && dir != 'n' && dir != 'E' && dir != 'e' && dir != 'W' && dir != 'w' && dir != 'S' && dir != 's') || !hasCorrectForm(plan))
	{	
		return 2;
	}
	else
	{
		nsteps = 0;		//nsteps reset
		for (int i = 0; i < plan.length(); i++)
		{
			if (isalpha(plan[i]))	//changes direction if turn letter
			{
				switch(plan[i])
				{
					case 'R':
					case 'r':
						switch (currDir)
						{
							case 'N':
							case 'n':
								currDir = 'E';
								break;
							case 'E':
							case 'e':
								currDir = 'S';
								break;
							case 'W':
							case 'w':
								currDir = 'N';
								break;
							case 'S':
							case 's':
								currDir = 'W';
								break;
						}
						break;
					case 'L':
					case 'l':
						switch (currDir)
						{
							case 'N':
							case 'n':
								currDir = 'W';
								break;
							case 'E':
							case 'e':
								currDir = 'N';
								break;
							case 'W':
							case 'w':
								currDir = 'S';
								break;
							case 'S':
							case 's':
								currDir = 'E';
								break;
						}
						break;
				}
			}
			else if (isdigit(plan[i]))	//taking steps if digit, if meets wall or edge before intended steps, stops and returns the max valid steps
			{
				if(isdigit(plan[i+1]))
				{
					steps = (10*(((int)plan[i])-48))+(((int)plan[i+1])-48);
					i++;
				}
				else
				{
					steps = (int)plan[i] - 48;
				}	

				nsteps += determineSafeDistance(r, c, currDir, steps);
			
				if (determineSafeDistance(r, c, currDir, steps) < steps)	//returns 3 if blocked by wall/edge before taking all intended steps
				{
					return 3;
				}

				switch (currDir)	//changing position through taking steps to current direction
				{
					case 'N':
					case 'n':
						r -= determineSafeDistance(r, c, currDir, steps);
						break;
					case 'E':
					case 'e':
						c += determineSafeDistance(r, c, currDir, steps);
						break;
					case 'W':
					case 'w':
						c -= determineSafeDistance(r, c, currDir, steps);
						break;
					case 'S':
					case 's':
						r += determineSafeDistance(r, c, currDir, steps);
						break;
				}
				
				if ((r == er) && (c == ec))		//returns 0 if arrives at end
				{
					return 0;
				}

			}
		}
	}
	return 1;	//returns 1 if plan completed but not at the end position
}




int main()
{
	setSize(3, 4);
	setWall(1, 4);
	setWall(2, 2);
	setWall(3, 2);
	assert(hasCorrectForm("2R1r"));	
	assert(determineSafeDistance(3, 1, 'N', 2) == 2);
	int len;
	len = -999;
	assert(obeyPlan(3, 1, 3, 4, 'S', "LL2R2r2L1R", len) == 0 && len == 7);
	
	len = -999;
	assert(obeyPlan(3, 1, 3, 4, 'N', "1Lx", len) == 2 && len == -999);
	len = -999;
	assert(obeyPlan(2, 4, 1, 1, 'w', "3R1L", len) == 3 && len == 1);

	cerr << "All tests succeeded" << endl;

	return 0;
}
