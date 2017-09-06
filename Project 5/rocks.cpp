#define _CRT_SECURE_NO_DEPRECATE

#include "utilities.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <cctype>
#include <random>
#include <utility>
#include <string>
using namespace std;

const int MAXWORDS = 10000;


int probecheck(char a[], const char list[][7], int nWords)	//Function to check if PROBE is all lower case alphabets, btw 4 and 6 letters in length, and is a word in wordList
{
	for (int i = 0; a[i] != '\0'; i++)
	{
		if (!isalpha(a[i]) || !islower(a[i]) || strlen(a) < 4 || strlen(a) > 6)
		{
			return 1;
		}
		else
		{
			for (int k = 0; k != nWords; k++)
			{
				if (strcmp(a, list[k]) == 0)
				{
					return 0;
				}
			}
			return 2;
		}
	}
}

int manageOneRound(const char words[][7], int nWords, int wordnum)
{
	if (nWords < 0 || wordnum < 0 || wordnum >= nWords)
		return -1;

	for (int attempts = 1; attempts != 0; attempts++) //Loop each attempt
	{
		int rocks = 0;
		int pebbles = 0;

		char list[10];  //Making new c string for modification
		strcpy(list, words[wordnum]);

		char PROBE[50] = "";	//Resets PROBE each attempt
		cout << "Probe word: ";
		cin.getline(PROBE, 50);

		if (strcmp(PROBE, words[wordnum]) == 0) //Player gets it right
		{
			return attempts;
		}
		else if (probecheck(PROBE, words, nWords) == 1) //Check if PROBE is lower case and alphabetical
		{
			cout << "Your probe word must be a word of 4 to 6 case letters." << endl;
			attempts--;
			continue;
		}

		else if (probecheck(PROBE, words, nWords) == 2) //Check if PROBE is not in wordList
		{
			cout << "I don't know that word." << endl;
			attempts--;
			continue;
		}

		else
		{
			for (int i = 0; list[i] != '\0'; i++) //Checking for rocks
			{
				
				if (list[i] == PROBE[i])
				{
					rocks++;
					for (int j = i; list[j] != '\0'; j++) //Remove rock from both arrays
					{
						list[j] = list[j + 1];
						PROBE[j] = PROBE[j + 1];
					}
					i--;
				}
			}

			for (int i = 0; list[i] != '\0'; i++) //Checking for pebbles
			{
				for (int k = 0; PROBE[k] != '\0'; k++)
				{
					if (list[i] == PROBE[k])
					{
						pebbles++;
						for (int j = k; PROBE[j] != '\0'; j++) //Remove pebble from remaining PROBE array
						{
							PROBE[j] = PROBE[j + 1];
						}
					}
				}
			}
			cout << "Rocks: " << rocks << ", Pebbles: " << pebbles << endl;
			//cerr << list << endl; //For debugging purposes
		}
	}
}

int main()
{
	int ROUNDS;
	char wordList[MAXWORDS][MAXWORDLEN + 1];
	int nWords = loadWords(wordList, MAXWORDS); //Load words

	if (nWords < 1)
	{
		cout << "No words were loaded, so I can't play the game." << endl;
		return 0;
	}

	cout << "How many rounds do you want to play? ";
	cin >> ROUNDS;
	cin.ignore(10000, '\n');
	cout << endl;

	if (ROUNDS <= 0)
		cout << "The number of rounds must be positive" << endl;

	int min = 0;
	int max = 0;
	double currenttotal = 0.00;

	for (int r = 1; r <= ROUNDS; r++) //Loop for every round
	{
		int random = randInt(0, nWords - 1);	
		cout << "Round " << r << endl;	//Write round number	
		cout << "The secret word is " << strlen(wordList[random]) << " letters long." << endl;	//Write secret word length
		//cerr << wordList[random] << endl; //For debugging purposes
			 
		int tries = manageOneRound(wordList, nWords, random);	//Call function

		if (tries == 1)	//Write how many tries you took
			cout << "You got it in 1 try." << endl;
		else
			cout << "You got it in " << tries << " tries." << endl;

		currenttotal += tries; //Incrementing total score to calculate average

		if (r == 1)
			min = tries;

		else if (tries < min)
			min = tries;

		if (max < tries)
			max = tries;

		double average = currenttotal / static_cast<double>(r); 

		cout.setf(ios::fixed); //Write Average, Min and Max
		cout.precision(2);
		cout << "Average: " << average << ", minimum: " << min << ", maximum: " << max << endl << endl;
	}
}