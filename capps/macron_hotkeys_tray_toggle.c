
#include <windows.h>
#include <shellapi.h>
#include <stdbool.h>

#define ID_TRAYICON 1001
#define WM_TRAYICON (WM_USER + 1)
#define ID_HOTKEY_TOGGLE 5000

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

HINSTANCE hInst;
bool hotkeysEnabled = true;
NOTIFYICONDATA nid;

void RegisterAllHotkeys() {
    RegisterHotKey(NULL, ID_HOTKEY_A, MOD_CONTROL | MOD_ALT, 0x41); // a
    RegisterHotKey(NULL, ID_HOTKEY_A_SHIFT, MOD_CONTROL | MOD_ALT | MOD_SHIFT, 0x41); // A
    RegisterHotKey(NULL, ID_HOTKEY_E, MOD_CONTROL | MOD_ALT, 0x45); // e
    RegisterHotKey(NULL, ID_HOTKEY_E_SHIFT, MOD_CONTROL | MOD_ALT | MOD_SHIFT, 0x45); // E
    RegisterHotKey(NULL, ID_HOTKEY_I, MOD_CONTROL | MOD_ALT, 0x49); // i
    RegisterHotKey(NULL, ID_HOTKEY_I_SHIFT, MOD_CONTROL | MOD_ALT | MOD_SHIFT, 0x49); // I
    RegisterHotKey(NULL, ID_HOTKEY_O, MOD_CONTROL | MOD_ALT, 0x4F); // o
    RegisterHotKey(NULL, ID_HOTKEY_O_SHIFT, MOD_CONTROL | MOD_ALT | MOD_SHIFT, 0x4F); // O
    RegisterHotKey(NULL, ID_HOTKEY_U, MOD_CONTROL | MOD_ALT, 0x55); // u
    RegisterHotKey(NULL, ID_HOTKEY_U_SHIFT, MOD_CONTROL | MOD_ALT | MOD_SHIFT, 0x55); // U
}

void UnregisterAllHotkeys() {
    for (int i = ID_HOTKEY_A; i <= ID_HOTKEY_U_SHIFT; i++) {
        UnregisterHotKey(NULL, i);
    }
}

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

LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
        case WM_DESTROY:
            Shell_NotifyIcon(NIM_DELETE, &nid);
            PostQuitMessage(0);
            return 0;
        case WM_HOTKEY:
            if (wParam == ID_HOTKEY_TOGGLE) {
                hotkeysEnabled = !hotkeysEnabled;
                if (hotkeysEnabled) {
                    RegisterAllHotkeys();
                    wcscpy(nid.szTip, L"Macron Hotkeys: ON");
                } else {
                    UnregisterAllHotkeys();
                    wcscpy(nid.szTip, L"Macron Hotkeys: OFF");
                }
                Shell_NotifyIcon(NIM_MODIFY, &nid);
                break;
            }
            if (!hotkeysEnabled) break;
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
        case WM_TRAYICON:
            if (lParam == WM_LBUTTONDBLCLK) {
                SendMessage(hwnd, WM_CLOSE, 0, 0);
            }
            break;
    }
    return DefWindowProc(hwnd, msg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    hInst = hInstance;

    WNDCLASS wc = {0};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = L"MacronHotkeyWnd";
    RegisterClass(&wc);

    HWND hwnd = CreateWindowEx(0, L"MacronHotkeyWnd", L"MacronHotkeys", 0, 0, 0, 0, 0,
                               NULL, NULL, hInstance, NULL);

    nid.cbSize = sizeof(NOTIFYICONDATA);
    nid.hWnd = hwnd;
    nid.uID = ID_TRAYICON;
    nid.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
    nid.uCallbackMessage = WM_TRAYICON;
    nid.hIcon = LoadIcon(NULL, IDI_INFORMATION);
    wcscpy(nid.szTip, L"Macron Hotkeys: ON");
    Shell_NotifyIcon(NIM_ADD, &nid);

    RegisterAllHotkeys();
    RegisterHotKey(NULL, ID_HOTKEY_TOGGLE, 0, VK_F12); // F12 toggle

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}
