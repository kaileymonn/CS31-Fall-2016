#include "grid.h"
#include "iostream"
#include "cassert"
#include "string"
#include "cctype"

using namespace std;

bool isRouteWellFormed(string route)
{
	if (isdigit(route[0])) //Checking if 1st char is a digit
			return false;
	for (int i = 0; i != route.size(); i++) //For each char in string
	{
		if (!isdigit(route[i]) && !isalpha(route[i])) //Checking if char is neither digit nor alphabet
			return false;
		else if (isalpha(route[i])) //If char is an alphabet
		{
			if (route[i] != 'N' && route[i] != 'n' && route[i] != 'S' && route[i] != 's' && route[i] != 'E' && route[i] != 'e' && route[i] != 'W' && route[i] != 'w')
				return false; //If alphabet is not NSEW or nsew
			else if (isdigit(route[i + 1]) && isdigit(route[i + 2]) && isdigit(route[i + 3]))
				return false; //If >2 digits follow direction
			else
				continue;
		}
	}
	return true; //If no errors found, route is well-formed.
}

int navigateSegment(int r, int c, char dir, int maxSteps)
{
	int steps = 0;
	if (r < 1 || r > getRows() || c < 1 || c > getCols() || isWall(r,c))
		return -1; //Check if starting position is valid empty grid position
	else if (!isalpha(dir))
		return -1; //Check if direction is valid character
	else if (dir != 'N' && dir != 'n' && dir != 'S' && dir != 's' && dir != 'E' && dir != 'e' && dir != 'W' && dir != 'w')
		return -1; //Check if direction is valid character
	else if (maxSteps < 0)
		return -1; //Check if maxSteps is valid
	else
		if (dir == 'E' || dir == 'e') //Robot moves East
		{
			for (int k = c + 1; k <= c + maxSteps; k++)
			{
				if (isWall(r, k))
				{
					return steps;
					break;
				}
				else
					steps++;
			}
			return steps;
		}

		else if (dir == 'N' || dir == 'n') //Robot moves North	
		{
			for (int k = r - 1; k >= r - maxSteps; k--)
			{
				if (isWall(k, c))
				{
					return steps;
					break;
				}
				else
					steps++;
			}
			return steps;
		}

		else if (dir == 'W' || dir == 'w') //Robot moves West
		{
			for (int k = c - 1; k >= c - maxSteps; k--)
			{
				if (isWall(r, k))
				{
					return steps;
					break;
				}
				else
					steps++;
			}
			return steps;
		}

		else if (dir == 'S' || dir == 's') //Robot moves South
		{
			for (int k = r + 1; k <= r + maxSteps; k++)
			{
				if (isWall(k, c))
				{
					return steps;
					break;
				}
				else
					steps++;
			}
			return steps;
		}
		
}

int navigateRoute(int sr, int sc, int er, int ec, string route, int& nsteps)
{
	nsteps = 0; // Set nsteps to 0


	if (!isRouteWellFormed(route)  || sr < 1 || sr > getRows() || sc < 1 || sc > getCols() || er < 1 || er > getRows() || ec < 1 || ec > getCols()|| isWall(sr, sc) || isWall(er, ec))
		return 2; //If route is not valid or start and end points are not empty valid grid positions

		for (int k = 0; k != route.length(); k++) //For every char in route string
		{
			int first = route[k + 1] - '0';
			int second = route[k + 2] - '0';
			if (isalpha(route[k]) && isdigit(route[k+1]) && isdigit(route[k+2]))
			{ //Case of 'N11'
				if (navigateSegment(sr, sc, route[k], ((first * 10) + second)) < ((first * 10) + second))
				{ //If segment runs into wall/off grid, exit
					nsteps += navigateSegment(sr, sc, route[k], ((first * 10) + second));
					return 3;
					return nsteps;
					break;
				}
				else
				{ //If segment is valid, change position accordingly
					nsteps += ((first * 10) + second);
					if (route[k] == 'N' || route[k] == 'n')
						sr -= ((first * 10) + second);
					else if (route[k] == 'S' || route[k] == 's')
						sr += ((first * 10) + second);
					else if (route[k] == 'E' || route[k] == 'e')
						sc += ((first * 10) + second);
					else if (route[k] == 'W' || route[k] == 'w')
						sc -= ((first * 10) + second);
				}
			}

			else if (isalpha(route[k]) && isdigit(route[k + 1]) && !isdigit(route[k + 2]))
			{ //Case of 'N1'
				if (navigateSegment(sr, sc, route[k], first) < first)
				{ //If segment runs into wall/off grid, exit
					nsteps += navigateSegment(sr, sc, route[k], first);
					return 3;
					return nsteps;
					break;
				}
				else
				{ //If segment is valid, change position accordingly
					nsteps += first;
					if (route[k] == 'N' || route[k] == 'n')
						sr -= first;
					else if (route[k] == 'S' || route[k] == 's')
						sr += first;
					else if (route[k] == 'E' || route[k] == 'e')
						sc += first;
					else if (route[k] == 'W' || route[k] == 'w')
						sc -= first;
				}
			}

			else if (isalpha(route[k]) && !isdigit(route[k + 1]))
			{ //Case of 'N'
				if (navigateSegment(sr, sc, route[k], 1) < 1)
				{ //If segment runs into wall/off grid, exit
					nsteps += navigateSegment(sr, sc, route[k], 1);
					return 3;
					return nsteps;
					break;

				}
				else
				{ //If segment is valid, change position accordingly
					nsteps += 1;
					if (route[k] == 'N' || route[k] == 'n')
						sr -= 1;
					else if (route[k] == 'S' || route[k] == 's')
						sr += 1;
					else if (route[k] == 'E' || route[k] == 'e')
						sc += 1;
					else if (route[k] == 'W' || route[k] == 'w')
						sc -= 1;
				}
			}
		}
		if (sr == er && sc == ec) //After all iterations of segments and if end points are reached
		{
			return 0;
			return nsteps;
		}
		else //Successful iterations of all segments but end points not reached
		{
			return 1;
			return nsteps;
		}
}

int main()
{
	setSize(3, 4);
	setWall(1, 4);
	setWall(2, 2);
	setWall(3, 2);
	assert(isRouteWellFormed("n2e1"));
	assert(!isRouteWellFormed("e1x"));
	assert(navigateSegment(3, 1, 'N', 2) == 2);
	int len;
	len = -999;  // so we can detect whether navigateRoute sets len
	assert(navigateRoute(3, 1, 3, 4, "N2eE01n0s2e1", len) == 0 && len == 7);
	len = -999;  // so we can detect whether navigateRoute sets len
	assert(navigateRoute(3, 1, 3, 4, "e1x", len) == 2 && len == 0);
	len = -999;  // so we can detect whether navigateRoute sets len
	assert(navigateRoute(2, 4, 1, 1, "w3n1", len) == 3 && len == 1);
	
	cout << "All tests succeeded" << endl;
}
