#include <iostream>
#include <Windows.h>
#include <string>
#include <conio.h>
#include <vector>
#include <array>

enum key {
	Arrow_Up = 72,
	Arrow_Down = 80,
	Enter = 13
};

void outputItems(std::vector<std::pair<std::string, std::wstring>>& items, int& command) {
	std::cout << "\x1b[H__________МЕНЮ_АКТИВАЦИИ_WINDOWS_________\n\n  \x1b[94m# \x1b[90mДоступные издания: \n";
	std::cout << "  ~~~~~~~~~~~~~~~~~~~~\n";
	for (size_t i = 0; i < items.size(); i++) {
		if (i == command && i == 8) { std::cout << "\x1b[101;30m"; }
		else if (i == command) { std::cout << "\x1b[107;30m"; }
		else { std::cout << "\x1b[0m"; }
		std::cout << items[i].first << std::endl;
	}
	std::cout << "\x1b[0m_________________________________________\n";
}

int userChooseCommand(std::vector<std::pair<std::string, std::wstring>>& items, int& command) {
	while (true) {
		outputItems(items, command);
		switch (_getch()) {
		case Arrow_Up: command = command - 1 >= 0 ? command - 1 : 8;
			break;
		case Arrow_Down: command = command + 1 < 9 ? command + 1 : 0;
			break;
		case Enter: return command;
		}
	}
}

void controllerMenu(std::wstring& activateKey)
{
	int command = 0;
	std::vector<std::pair<std::string, std::wstring>> items;

	items.emplace_back("    Windows 10(11) Домашняя              ", L"[TX9XD - 98N7V - 6WMQ6 - BX7FG - H8Q99]");
	items.emplace_back("    Windows 10(11) Домашняя N            ", L"[3KHY7 - WNT83 - DGQKR - F7HPR - 844BM]");
	items.emplace_back("    Windows 10(11) Профессиональная      ", L"[W269N - WFGWX - YVC9B - 4J6C9 - T83GX]");
	items.emplace_back("    Windows 10(11) Профессиональная N    ", L"[MH37W - N47XK - V7XM9 - C7227 - GCQG9]");
	items.emplace_back("    Windows 10(11) Образовательная       ", L"[NW6C2 - QMPVW - D7KKK - 3GKT6 - VCFB2]");
	items.emplace_back("    Windows 10(11) Образовательная N     ", L"[DPH2V - TTNVB - 4X9Q3 - TJR4H - KHJW4]");
	items.emplace_back("    Windows 10(11) Корпоративная         ", L"[NPPR9 - FWDCX - D2C8J - H872K - 2YT43]");
	items.emplace_back("    Windows 10(11) Корпоративная N       ", L"[DPH2V - TTNVB - 4X9Q3 - TJR4H - KHJW4]");
	items.emplace_back("    ~ ВЫХОД ~                            ", L"");

	switch (userChooseCommand(items, command)) {
	case 8: exit(0);
	default:
		activateKey = items[userChooseCommand(items, command)].second;
		break;
	}

	STARTUPINFOW startupInfo;
	PROCESS_INFORMATION processInfo;
	ZeroMemory(&startupInfo, sizeof(startupInfo));
	startupInfo.cb = sizeof(startupInfo);
	ZeroMemory(&processInfo, sizeof(processInfo));

	std::array<std::wstring, 3> commands{
		(L"cmd.exe /C slmgr /ipk " + activateKey),
		L"cmd.exe /C slmgr /skms kms.digiboy.ir",
		L"cmd.exe /C slmgr /ato"
	};

	for (auto& command : commands) {
		if (!CreateProcessW(NULL, (LPWSTR)command.c_str(), NULL, NULL, FALSE, 0, NULL, NULL, &startupInfo, &processInfo)) {
			system("pause");
			std::cerr << "\n\n\x1b[91Ошибка запуска процесса: " << GetLastError() << std::endl;
		}
	}

	WaitForSingleObject(processInfo.hProcess, INFINITE);
	CloseHandle(processInfo.hProcess);
	CloseHandle(processInfo.hThread);
}

void activateWindows() {
	std::wstring activateKey;
	while (true) { controllerMenu(activateKey); }
}

int main() {

	system("chcp 1251");

	activateWindows();

	return 0;
}
