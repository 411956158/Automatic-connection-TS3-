// AutoIntoChannel.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。

#include <stdio.h>
#include <iostream>
#include <windows.h>
#include <string>
#include <fstream>
#include <cstdlib>

int openFile(std::string address);
int simulateCtrlS();
void printDashEverySecond(int ms100);
HWND FindTeamSpeakWindow();

//DWORD errid;

int forceSucccess = 0;
short tryForcetime = 0;

std::string address = "start C:\\Users\\Public\\Desktop\\\"TeamSpeak 3 Client.lnk\"";
std::string address2 = "start C:\\Users\\Public\\Desktop\\\"TeamSpeak3Client.lnk\"";

int main()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);//设置浅黄色
	printf("开始打开文件\n");
	
	if (openFile(address)!= 0) {
		//errid = GetLastError();
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);//设置浅绿色
		printf("开始打开文件成功11\n\n");
	}
	else if (openFile(address) != 0) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);//设置浅绿色
		printf("开始打开文件成功12\n\n");
	}
	else if (openFile(address2) != 0) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);//设置浅绿色
		printf("开始打开文件成功21\n\n");
	}
	else if(openFile(address2) != 0){
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);//设置浅绿色
		printf("开始打开文件成功22\n\n");
	}
	else {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);//设置浅红色
		printf("开始打开文件失败try out，请查看日志\n\n");
		Sleep(1000);
		exit(114);
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);//设置浅黄色

	printDashEverySecond(6);

	FindTeamSpeakWindow();

	do {
		printDashEverySecond(5);
		FindTeamSpeakWindow();
	} while (forceSucccess != 1 && tryForcetime < 3); 

	if (forceSucccess != 1 && tryForcetime >= 3) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);//设置浅红色
		printf("赋予窗口焦点失败01，请查看日志\n\n");
	}

	/*if (forceSucccess == 0) {
		printDashEverySecond(5);
		FindTeamSpeakWindow();
	}
	if (forceSucccess == 1) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);//设置浅绿色
		printf("赋予窗口焦点成功\n\n");
	}
	else if (forceSucccess == 0) {
		printDashEverySecond(5);
		FindTeamSpeakWindow();
	}
	else {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);//设置浅红色
		printf("赋予窗口焦点失败01，请查看日志\n\n");
	}*/

	printDashEverySecond(2);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);//设置浅黄色
	printf("开始连接服务器\n");
	simulateCtrlS();
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);//设置浅绿色
	printf("连接服务器成功\n");

	exit(114514);
}

void printDashEverySecond(int ms100) {
	for(int i=0;i<ms100;i++) {
		std::cout << "-";
		Sleep(500); // Sleep for 1 second
	}
	std::cout << "\n";
}

int simulateCtrlS() {

	// Press Ctrl key
	keybd_event(VK_CONTROL, 0, 0, 0);

	// Press S key
	keybd_event('S', 0, 0, 0);

	// Release S key
	keybd_event('S', 0, KEYEVENTF_KEYUP, 0);

	// Release Ctrl key
	keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);

	printDashEverySecond(5);

	// Simulate pressing the 'Enter' key
	keybd_event(VK_RETURN, 0, 0, 0);

	// Release the 'Enter' key
	keybd_event(VK_RETURN, 0, KEYEVENTF_KEYUP, 0);

	return 1;
}


int openFile(std::string address) {
	if (system(address.c_str()) != -1) {
		return 1;
	}
	else {
		return 0;
	}
}

HWND FindTeamSpeakWindow(){
	HWND hwnd = NULL;
	wchar_t className[512];
	wchar_t windowName[512];

	// Get the first top-level window
	hwnd = GetTopWindow(NULL);

	// Iterate through all top-level windows
	while (hwnd != NULL)
	{
		// Get the class name of the window
		GetClassNameW(hwnd, className, sizeof(className)/2);

		// Get the window name of the window
		GetWindowTextW(hwnd, windowName, sizeof(windowName)/2);
		//printf("%ws\n", windowName);

		// Check if the window name contains "TeamSpeak"
		if (wcsstr(windowName, L"TeamSpeak") != NULL)
		{
			// Set the focus to the window
			//SetFocus(hwnd);
			//SetForegroundWindow(hwnd);
			SwitchToThisWindow(hwnd, true);
			printf("检测到赋予窗口焦点成功%ws\n\n", windowName);
			forceSucccess = 1;
			//break;
		}

		// Get the next top-level window
		hwnd = GetNextWindow(hwnd, GW_HWNDNEXT);
	}

	return hwnd;
}
