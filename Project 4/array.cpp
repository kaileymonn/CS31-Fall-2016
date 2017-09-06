#include <iostream>	
#include <string>
#include <cassert>
using namespace std;

int appendToAll(string a[], int n, string value)
{
	if (n < 0)
		return -1;
	for (int k = 0; k < n; k++)
	{
		a[k] = a[k] + value;
	}
	return n;
}

int lookup(const string a[], int n, string target)
{
	if (n < 0)
		return -1;
	for (int i = 0; i < n; i++)
	{
		if (a[i] == target)
			return i;
	}
	return -1;
}

int positionOfMax(const string a[], int n)
{
	int currentMax = 0;
	if (n <= 0)
		return -1;
	for (int k = 0; k < n; k++)
	{
		if (a[k] > a[currentMax])
			currentMax = k; //Overwrite former currentMax with new currentMax
		else if (a[k] == a[currentMax])
			currentMax = currentMax; //In the event of more than one element with same value
	}
	return currentMax;
}

int rotateLeft(string a[], int n, int pos)
{
	string x = a[pos]; //Saving a[pos] in a separate memory slot
	if (n < 0)
		return -1;
	for (int k = pos; k < n -1; k++)
	{
		a[k] = a[k + 1]; //Shift left
	}
	a[n - 1] = x; //Rewrite last element as a[pos]
	return pos;
}

int countRuns(const string a[], int n)
{
	int count = 1;
	if (n < 0)
		return -1;
	for (int k = 1; k < n; k++) //Start with second element
	{
		if (a[k] != a[k - 1])
			count++; //Increment count when 2 consecutive elements are not equal
	}
	return count;
}

int flip(string a[], int n)
{
	if (n < 0)
		return -1;
	int j = n - 1;
	for (int k = 0; k <= j; k++)
	{
		string x = a[k]; //Save a[k] in separate memory slot for later use
		a[k] = a[j];
		a[j] = x;
		j--; //Switch positions and decrement j for next iteration of k++
	}
	return n;
}

int differ(const string a1[], int n1, const string a2[], int n2)
{
	if (n1 < 0 || n2 < 0)
		return -1;
	if (n1 <= n2) //When more elements from a2 considered than those in a1
	{
		for (int k = 0; k < n1; k++)
		{
			if (a1[k] != a2[k])
				return k; 
		}
		return n1;
	}
	else //When more elements from a1 considered than those in a2
	{
		for (int k = 0; k < n2; k++)
		{
			if (a1[k] != a2[k])
				return k;
		}
		return n2;
	}

}

int subsequence(const string a1[], int n1, const string a2[], int n2)
{
	if (n1 < 0 || n2 < 0 || n2 > n1)
		return -1;

	for (int k = 0; k < n1; k++)
	{
		int m = k; //Create separate integer m to increment to save original k value to return
		for (int j = 0; j < n2; j++)
		{
			if (a1[m] == a2[j]) //Checking if entire sequence appears
			{
				m++;
			}
			else
				break; //Leaves loop at end of sequence
		} 
		if ((m-k)==n2) //In the event that entire sequence in a2 is present
			return k;
		else
			continue; //Entire sequence in a2 not present, increment k
	}
	return -1;
}

int lookupAny(const string a1[], int n1, const string a2[], int n2)
{
	if (n1 < 0 || n2 < 0)
		return -1;

	for (int k = 0; k < n1; k++)
		for (int j = 0; j < n2; j++) //Checking each item in a1 against each item in a2
		{
			if (a1[k] == a2[j])
				return k;
		}
	return -1;
}

int split(string a[], int n, string splitter)
{
	if (n < 0)
		return -1;
	int j = n - 1;
	for (int k = 0; k < j; k++)
	{
		if (a[k] > splitter) //Element in a1 larger than split
		{
			string x = a[k];
			a[k] = a[j];
			a[j] = x;
			k--; //After position switch, check element in current k position in next iteration
			j--; 
		}
		else if (a[k] == splitter)
		{
			string x = a[k];
			a[k] = a[j];
			a[j] = x;
			k--; //After position switch, check element in current k position in next iteration
				 //j is not decremented as we might need to switch splitter over again in next iteration
		}
	}
	return j;
}

int main()
{
	string g[4] = { "bernie", "hillary", "jeb", "carly" };
	//Test appendToAll
	assert(appendToAll(g, 4, "?") == 4 && g[0] == "bernie?" && g[3] == "carly?");
	assert(appendToAll(g, -5, "?") == -1);

	string h[8] = { "bernie", "hillary", "donald", "jeb", "", "carly", "ben", "jeb"};
	//Test lookup
	assert(lookup(h, -5, "carly") == -1);
	assert(lookup(h, 7, "carly") == 5);
	assert(lookup(h, 7, "donald") == 2);
	assert(lookup(h, 2, "donald") == -1);

	//Test positionOfMax
	assert(positionOfMax(h, 0) == -1);
	assert(positionOfMax(h, 8) == 3);

	//Test rotateLeft
	string running[5] = { "carly", "mike", "ted", "bernie", "jeb" };
	assert(rotateLeft(running, 5, 1) == 1 && running[1] == "ted" && running[3] == "jeb" && running[4] == "mike");

	//Test countRuns
	string d[10] = { "ben", "ben", "chris", "marco", "marco", "donald", "donald", "donald", "marco", "marco" };
	assert(countRuns(d, 10) == 5);

	//Test flip
	string folks[6] = { "chris", "marco", "", "ben", "donald", "john" };
	assert(flip(folks, 4) == 4 && folks[0] == "ben" && folks[1] == "" && folks[3] == "chris" && folks[5] == "john");

	//Test differ
	string folk[6] = { "chris", "marco", "", "ben", "donald", "john" };
	string group[5] = { "chris", "marco", "john", "", "carly" };
	assert(differ(folk, 6, group, 5) == 2);
	assert(differ(folk, 2, group, 1) == 1);

	//Test subsequence
	string e[4] = { "donald", "jeb", "", "carly" };
	string random[4] = { "lol", "this", "is", "rubbish" };
	string k1[7] = {"hi", "im", "hey", "hi", "im", "kai"};
	string k2[3] = {"hi", "im", "kai"};
	string k3[7] = { "hi", "im", "kai", "hey", "hi", "im", "kai" };
	assert(subsequence(h, 7, e, 4) == 2);
	assert(subsequence(h, 7, random, 4) == -1);
	assert(subsequence(h, 7, random, 0) == 0);
	assert(subsequence(h, 0, random, 4) == -1);
	assert(subsequence(k1, 6, k2, 3) == 3); //Test if full sequence in a2 is accounted for
	assert(subsequence(k3, 7, k2, 3) == 0); //Test for multiple occurences of sequence

	//Test lookupAny
	string names[10] = { "ted", "hillary", "rand", "bernie", "mike", "jeb" };
	string set1[10] = { "carly", "mike", "bernie", "hillary" };
	string set2[10] = { "ben", "donald" };
	assert(lookupAny(names, 6, set1, 4) == 1);
	assert(lookupAny(names, 6, set2, 2) == -1);

	//Test split
	string cand[6] = { "bernie", "hillary", "donald", "marco", "carly", "ben" };
	string cand2[4] = { "donald", "hillary", "jeb", "ben" };
	assert(split(cand, 6, "chris") == 3);
	assert(split(h, 8, "carly") == 3 && h[3] == "carly");
	assert(split(cand2, 4, "donald") == 1 && cand2[1] == "donald");

	cout << "All tests succeeded" << endl;
}

