#include <windows.h>
#include <shellapi.h>
#include <stdio.h>

#define ID_TRAY_ICON 1001
#define ID_TRAY_EXIT 1002

#define ID_HOTKEY_A       1
#define ID_HOTKEY_A_SHIFT 2
#define ID_HOTKEY_E       3
#define ID_HOTKEY_E_SHIFT 4
#define ID_HOTKEY_I       5
#define ID_HOTKEY_I_SHIFT 6
#define ID_HOTKEY_O       7
#define ID_HOTKEY_O_SHIFT 8
#define ID_HOTKEY_U       9
#define ID_HOTKEY_U_SHIFT 10

const wchar_t CLASS_NAME[] = L"MacronTrayApp";

NOTIFYICONDATA nid;
HMENU hMenu;

void SendUnicodeChar(wchar_t ch) {
    INPUT ip;
    ip.type = INPUT_KEYBOARD;
    ip.ki.wScan = ch;
    ip.ki.time = 0;
    ip.ki.dwExtraInfo = GetMessageExtraInfo();
    ip.ki.wVk = 0;
    ip.ki.dwFlags = KEYEVENTF_UNICODE;
    SendInput(1, &ip, sizeof(INPUT));
    ip.ki.dwFlags = KEYEVENTF_UNICODE | KEYEVENTF_KEYUP;
    SendInput(1, &ip, sizeof(INPUT));
}

void RegisterAllHotkeys(HWND hwnd) {
    RegisterHotKey(hwnd, ID_HOTKEY_A, MOD_CONTROL | MOD_ALT, 0x41); // A
    RegisterHotKey(hwnd, ID_HOTKEY_A_SHIFT, MOD_CONTROL | MOD_ALT | MOD_SHIFT, 0x41);
    RegisterHotKey(hwnd, ID_HOTKEY_E, MOD_CONTROL | MOD_ALT, 0x45); // E
    RegisterHotKey(hwnd, ID_HOTKEY_E_SHIFT, MOD_CONTROL | MOD_ALT | MOD_SHIFT, 0x45);
    RegisterHotKey(hwnd, ID_HOTKEY_I, MOD_CONTROL | MOD_ALT, 0x49); // I
    RegisterHotKey(hwnd, ID_HOTKEY_I_SHIFT, MOD_CONTROL | MOD_ALT | MOD_SHIFT, 0x49);
    RegisterHotKey(hwnd, ID_HOTKEY_O, MOD_CONTROL | MOD_ALT, 0x4F); // O
    RegisterHotKey(hwnd, ID_HOTKEY_O_SHIFT, MOD_CONTROL | MOD_ALT | MOD_SHIFT, 0x4F);
    RegisterHotKey(hwnd, ID_HOTKEY_U, MOD_CONTROL | MOD_ALT, 0x55); // U
    RegisterHotKey(hwnd, ID_HOTKEY_U_SHIFT, MOD_CONTROL | MOD_ALT | MOD_SHIFT, 0x55);
}

void UnregisterAllHotkeys(HWND hwnd) {
    for (int i = ID_HOTKEY_A; i <= ID_HOTKEY_U_SHIFT; ++i)
        UnregisterHotKey(hwnd, i);
}

void ShowContextMenu(HWND hwnd) {
    POINT pt;
    GetCursorPos(&pt);
    SetForegroundWindow(hwnd); // Required for TrackPopupMenu
    TrackPopupMenu(hMenu, TPM_RIGHTBUTTON, pt.x, pt.y, 0, hwnd, NULL);
    PostMessage(hwnd, WM_NULL, 0, 0); // Required to dismiss menu properly
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
        case WM_CREATE:
            RegisterAllHotkeys(hwnd);
            hMenu = CreatePopupMenu();
            AppendMenu(hMenu, MF_STRING, ID_TRAY_EXIT, TEXT("Exit"));
            break;

        case WM_COMMAND:
            if (LOWORD(wParam) == ID_TRAY_EXIT) {
                UnregisterAllHotkeys(hwnd);
                Shell_NotifyIcon(NIM_DELETE, &nid);
                PostQuitMessage(0);
            }
            break;

        case WM_HOTKEY:
            switch (wParam) {
                case ID_HOTKEY_A: SendUnicodeChar(L'ā'); break;
                case ID_HOTKEY_A_SHIFT: SendUnicodeChar(L'Ā'); break;
                case ID_HOTKEY_E: SendUnicodeChar(L'ē'); break;
                case ID_HOTKEY_E_SHIFT: SendUnicodeChar(L'Ē'); break;
                case ID_HOTKEY_I: SendUnicodeChar(L'ī'); break;
                case ID_HOTKEY_I_SHIFT: SendUnicodeChar(L'Ī'); break;
                case ID_HOTKEY_O: SendUnicodeChar(L'ō'); break;
                case ID_HOTKEY_O_SHIFT: SendUnicodeChar(L'Ō'); break;
                case ID_HOTKEY_U: SendUnicodeChar(L'ū'); break;
                case ID_HOTKEY_U_SHIFT: SendUnicodeChar(L'Ū'); break;
            }
            break;

        case WM_USER + 1:
            if (lParam == WM_RBUTTONUP) ShowContextMenu(hwnd);
            break;

        case WM_DESTROY:
            PostQuitMessage(0);
            break;
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    WNDCLASS wc = {0};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;
    RegisterClass(&wc);

    HWND hwnd = CreateWindowEx(0, CLASS_NAME, L"MacronKeys", 0,
                               0, 0, 0, 0, HWND_MESSAGE, NULL, hInstance, NULL);

    nid.cbSize = sizeof(nid);
    nid.hWnd = hwnd;
    nid.uID = ID_TRAY_ICON;
    nid.uFlags = NIF_MESSAGE | NIF_ICON | NIF_TIP;
    nid.uCallbackMessage = WM_USER + 1;
    nid.hIcon = LoadIcon(NULL, IDI_INFORMATION);
    lstrcpy(nid.szTip, L"MacronKeys active");
    Shell_NotifyIcon(NIM_ADD, &nid);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) DispatchMessage(&msg);
    return 0;
}
