#include <iostream>
#include <string>
#include <cassert>
using namespace std;

//repeats the same string and appends to the original one
//returns -1 if n is negative
int reduplicate(string a[], int n)
{
	if (n < 0)
	{
		return -1;
	}
	
	for (int i = 0; i < n; i++)
	{
		a[i] += a[i];
	}

	return n;
}

//returns position of the string in the array
//returns -1 if can't find
int locate(const string a[], int n, string target)
{
	for (int i = 0; i < n; i++)
	{
		if (a[i] == target)
		{
			return i;
		}
	}

	return -1;
}

//returns position of string with latest alphabetical order
//returns -1 if n is negative
int locationOfMax(const string a[], int n)
{
	if (n <= 0)
	{
		return -1;
	}

	string maxString = "";
	int maxIndex = -1;

	for (int i = 0;i < n; i++)
	{
		if (a[i] > maxString)
		{
			maxIndex = i;
			maxString = a[i];
		}
	}

	return maxIndex;
}

//put the selected string at the end of the array, and move everything next to it one place left
//return -1 if invalid pos or n
int circleLeft(string a[], int n, int pos)
{
	if (n < 0 || pos >= n || pos < 0)
	{
		return -1;
	}

	string temp = a[pos];

	for (int i = pos; i < n; i++)
	{
		a[i] = a[(i+1)%n];
	}

	a[n-1] = temp;

	return pos;
}

//returns number of sequences of one or more consecutive identical items in the array
int enumerateRuns(const string a[], int n)
{
	if (n < 0)
	{
		return -1;
	}
	else if (n == 0)
	{
		return 0;
	}

	int count = 1;
	string repeat = a[0];

	for (int i = 0; i < n; i++)
	{
		if (repeat == a[i])
		{
			continue;
		}

		count++;
		repeat = a[i];
	}

	return count;
}

//Reverses the order of the array
int flip(string a[], int n)
{
	if (n < 0)
	{
		return -1;
	}

	string temp;

	for(int i = 0; i < n/2; i++)
	{
		temp = a[i];
		a[i] = a[n-1-i];
		a[n-1-i] = temp;
	}

	return n;
}

//compares two input array and returns first index that is different
//if one of the array runs out, it returns the length of the shorter array
int locateDifference(const string a1[], int n1, const string a2[], int n2)
{
	if (n1 < 0 || n2 < 0 || (n1 == 0 && n2 == 0))
	{
		return -1;
	}

	int total;

	if (n1 <= n2)
	{
		total = n1;
	}
	else
	{
		total = n2;
	}

	for (int i = 0; i < total; i++)
	{
		if (a1[i] != a2[i])
		{
			return i;
		}
	}

	return total;
}

//If all n2 elements of a2 appear in a1, consecutively in the same order, then return the position in a1 where that subsequence begins
//If the subsequence appears more than once in a1, return the smallest such beginning position in the array.
//returns -1 if a1 does not contain a2 as a contiguous subsequence.
int subsequence(const string a1[], int n1, const string a2[], int n2)
{
	if (n1 < 0 || n2 < 0 || n1 < n2)
	{
		return -1;
	}
	else if (n2 == 0 || (n1 == 0 && n2 == 0))
	{
		return 0;
	}

	int count = 0;

	for (int i = 0; i < n1; i++)
	{
		for (int j = 0; j < n2; j++)
		{
			if (a1[i] == a2[j])
			{
				count++;
				if (count == n2)
				{
					return i-count+1;
				}
				i++;
			}
			else
			{
				count = 0;
			}
		}
	}
	return -1;
}

//Return the smallest position in a1 of an element that is equal to any of the n2 elements in a2
//Return −1 if no element of a1 is equal to any element of a2.
int locateAny(const string a1[], int n1, const string a2[], int n2)
{
	if (n1 < 0 || n2 < 0)
	{
		return -1;
	}

	for (int i = 0; i < n1; i++)
	{
		if (locate(a2, n2, a1[i]) != -1)
		{
			return i;
		}
	}
	return -1;
}

//Rearrange the elements of the array so that all the elements whose value is < separator come before all the other elements, and all the elements whose value is > separator come after all the other elements
//Return the position of the first element that, after the rearrangement, is not < separator, or n if there are no such elements.
int separate(string a[], int n, string separator)
{
	if (n < 0)
	{
		return -1;
	}

	int same = 0;

	for (int i = n-1; i >= 0; i--)
	{
		if (a[i] >= separator)
		{
			circleLeft(a, n, i);
		}
		else
		{
			same++;
		}
	}

	string temp;
	
	for (int i = 0; i < n; i++)
	{
		if (a[i] == separator)
		{
			temp = a[i];
			a[i] = a[same];
			a[same] = temp;
			same++;
		}
	}

	for (int i = 0; i < n; i++)
	{
		if (a[i] >= separator)
		{
			return i;
		}
	}

	return n;
}

int main()
{
    string h[7] = { "moana", "mulan", "ariel", "tiana", "", "belle", "elsa" };
    assert(locate(h, 7, "belle") == 5);

	assert(locate(h, 7, "ariel") == 2);
	assert(locate(h, 2, "ariel") == -1);
	assert(locationOfMax(h, 7) == 3);

	string g[4] = { "moana", "mulan", "belle", "raya" };
  	assert(locateDifference(h, 4, g, 4) == 2);
  	assert(circleLeft(g, 4, 1) == 1 && g[1] == "belle" && g[3] == "mulan");

	string c[4] = { "ma", "can", "tu", "do" };
  	assert(reduplicate(c, 4) == 4 && c[0] == "mama" && c[3] == "dodo");

  	string e[4] = { "ariel", "tiana", "", "belle" };
  	assert(subsequence(h, 7, e, 4) == 2);
  	
	string d[5] = { "mulan", "mulan", "mulan", "belle", "belle" };
	assert(enumerateRuns(d, 5) == 2);
  																		
  	string f[3] = { "tiana", "ariel", "raya" };
  	assert(locateAny(h, 7, f, 3) == 2);
  	assert(flip(f, 3) == 3 && f[0] == "raya" && f[2] == "tiana");
  	
	assert(separate(h, 7, "elsa") == 3);
 
	cout << "All tests succeeded" << endl;

	return 0;
}
