#include "Utility.h"

bool Utility::getYesNo(void)
{
	//purpose: requests yes/no response from user

	string strInput = "";
	bool boolIsYes = true;

	cin >> strInput;
	while (strInput != "Y" && strInput != "Yes" && strInput != "YES" && strInput != "yes" && strInput != "N" && strInput != "No" && strInput != "NO" && strInput != "no" && strInput != "y" && strInput != "n")
	{
		cout << "ERROR: you can only enter 'Yes', 'No' or a similar variation.\nTry again: ";
		cin >> strInput;
	}

	if (strInput == "Y" || strInput == "Yes" || strInput == "YES" || strInput == "yes" || strInput == "y")
		boolIsYes = true;
	else if (strInput == "N" || strInput == "No" || strInput == "NO" || strInput == "no" || strInput == "n")
		boolIsYes = false;
	return boolIsYes;
}
bool Utility::getYesNo(string strMessage)
{
	//purpose: requests yes/no response from user
	//parameters: (strMessage) required notice of entry

	string strInput = "";
	bool boolIsYes = true;

	cout << strMessage;
	cin >> strInput;
	cin.ignore();
	while (strInput != "Y" && strInput != "Yes" && strInput != "YES" && strInput != "yes" && strInput != "N" && strInput != "No" && strInput != "NO" && strInput != "no" && strInput != "y" && strInput != "n")
	{
		cout << "ERROR: you can only enter 'Yes', 'No' or a similar variation.\nTry again: ";
		cin >> strInput;
	}

	if (strInput == "Y" || strInput == "Yes" || strInput == "YES" || strInput == "yes" || strInput == "y")
		boolIsYes = true;
	else if (strInput == "N" || strInput == "No" || strInput == "NO" || strInput == "no" || strInput == "n")
		boolIsYes = false;
	return boolIsYes;
}
string Utility::getString(void)
{
	//purpose: gets any string value safely (requires a notice for entry beforehand)

	string strInput = "";
	getline(cin, strInput);
	return strInput;
}
string Utility::getString(string strMessage)
{
	//purpose: gets any string value safely (is given notice of entry)
	//parameters: (strMessage) required notice of entry

	cout << strMessage;
	string strInput = "";
	getline(cin, strInput);
	return strInput;
}

int Utility::getInteger(void)
{
	//purpose: gets any integer value safely (requires a notice for entry beforehand)

	string strInput = "";
	int intInputAsInt = -1024;

	cin >> strInput;
	cin.ignore();
	stringstream strStream(strInput);
	strStream >> intInputAsInt;
	return intInputAsInt;
}
int Utility::getInteger(string strMessage, int intMin, int intMax)
{
	//purpose: gets any integer value safely (is given notice of entry)
	//parameters: (strMessage) required notice of entry, (intMin) minimum value limit, (intMax) maximum value limit

	string strInput = "";
	int intInputAsInt = -1024;

	cout << strMessage;
	cin >> strInput;
	cin.ignore();
	stringstream strStream(strInput);
	strStream >> intInputAsInt;
	while (intInputAsInt < intMin || intInputAsInt > intMax)
	{
		cout << "ERROR: you can only enter a whole number between " << intMin << " and " << intMax << ".\nTry again: ";
		cin >> strInput;
		cin.ignore();
		stringstream strStream(strInput);
		strStream >> intInputAsInt;
	}
	return intInputAsInt;
}

int Utility::generateNumber(int intMin, int intMax)
{
	//purpose: generates a number using Mersenne Twister 19937 method with provided minimum and maximum values for range
	//parameters: (intMin) minimum bound for range, (intMax) maximum bound for range

	int intResult;
	random_device randGenerator;
	mt19937_64 mersenne(randGenerator());
	uniform_int_distribution<int> distInt(intMin, intMax);
	intResult = distInt(mersenne);
	return intResult;
}

void Utility::clearScreen(void)
{
	//purpose: clears the screen
	system("cls");
}
void Utility::setWindowTitle(string strTitle)
{
	//purpose: sets the window title
	//parametres: (strTitle) specified title for window
	SetConsoleTitle(strTitle.c_str());
}
void Utility::setWindowSize(unsigned int uintWidth, unsigned int uintHeight)
{
	//purpose: sets the window size
	//parametres: (uintWidth) specified window width, (uintHeight) specified window height

	HWND console = GetConsoleWindow();
	RECT rectWindow;

	GetWindowRect(console, &rectWindow);
	MoveWindow(console, rectWindow.left, rectWindow.top, uintWidth, uintHeight, TRUE);
}
void Utility::setColour(Colour clrFore, Colour clrBack = BLACK)
{
	//purpose: sets the console colour
	//parametres: (clrFore) enumeration for foreground colour, (clrBack) enumeration for background colour (defaulted as black)

	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	int intColour = clrBack * 16 + clrFore;

	SetConsoleTextAttribute(handle, intColour);
}
void Utility::moveCursor(SHORT shrtX, SHORT shrtY)
{
	//purpose: moves cursor 
	//parametres: (uintWidth) specified cursor X, (uintHeight) specified cursor Y

	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD point = { shrtX, shrtY };
	SetConsoleCursorPosition(handle, point);
}