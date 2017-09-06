#include <iostream>
using namespace std;

void removeS(char* message)
{
	while (*message != '\0')
	{
		if (*message == 'S' || *message == 's')
		{
			for (char* message2 = message; *message2 != '\0'; message2++)
				*message2 = *(message2 + 1);
		}
		else
			message++;
	}
}

int main()
{
	char msg[50] = "She'll be a massless princess.";
	removeS(msg);
	cout << msg;  // prints   he'll be a male prince.
}