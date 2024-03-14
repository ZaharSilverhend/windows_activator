#include <Windows.h>
#include <iostream>
#include <string>


// при возникновении проблем с активацией попробуйте поменять ключ активации
// 
// список ключей лицензий Windows 10(11) различных версий :

// # Windows 10(11) Домашняя : [TX9XD - 98N7V - 6WMQ6 - BX7FG - H8Q99]
// # Windows 10(11) Домашняя N : [3KHY7 - WNT83 - DGQKR - F7HPR - 844BM]
// # Windows 10(11) Профессиональная : [W269N - WFGWX - YVC9B - 4J6C9 - T83GX]
// # Windows 10(11) Профессиональная N : [MH37W - N47XK - V7XM9 - C7227 - GCQG9]
// # Windows 10(11) Образовательная : [NW6C2 - QMPVW - D7KKK - 3GKT6 - VCFB2]
// # Windows 10(11) Образовательная N : [DPH2V - TTNVB - 4X9Q3 - TJR4H - KHJW4]
// # Windows 10(11) Корпоративная : [NPPR9 - FWDCX - D2C8J - H872K - 2YT43]
// # Windows 10(11) Корпоративная N : [DPH2V - TTNVB - 4X9Q3 - TJR4H - KHJW4]


int main()
{
    // создаем структуру STARTUPINFO и PROCESS_INFORMATION
    STARTUPINFOW si;
    PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    // создаем строки с командми для выполнения активации Windows
    std::wstring command = L"cmd.exe /C slmgr /ipk W269N-WFGWX-YVC9B-4J6C9-T83GX";
    std::wstring command2 = L"cmd.exe /C slmgr /skms kms.digiboy.ir";
    std::wstring command3 = L"cmd.exe /C slmgr /ato";

    // запускаем процесс командной строки с указанной командой
    if (!CreateProcessW(NULL, (LPWSTR)command.c_str(), NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {
        std::cerr << "Ошибка запуска процесса: " << GetLastError() << std::endl;
        return 1;
    }
    if (!CreateProcessW(NULL, (LPWSTR)command2.c_str(), NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {
        std::cerr << "Ошибка запуска процесса: " << GetLastError() << std::endl;
        return 1;
    }
    if (!CreateProcessW(NULL, (LPWSTR)command3.c_str(), NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {
        std::cerr << "Ошибка запуска процесса: " << GetLastError() << std::endl;
        return 1;
    }

    // ждем завершения процесса
    WaitForSingleObject(pi.hProcess, INFINITE);

    // закрываем дескрипторы процесса и потока
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    return 0;
}
