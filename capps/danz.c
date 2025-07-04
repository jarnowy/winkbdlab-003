
#include <windows.h>
#include <shellapi.h>
#include <stdbool.h>

#define ID_TRAYICON 1001
#define IDR_ICON1 101

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

#define ID_HOTKEY_N_TILDE          11
#define ID_HOTKEY_C_CEDILLA        12
#define ID_HOTKEY_AE               13
#define ID_HOTKEY_A_RING           14
#define ID_HOTKEY_O_SLASH          15

#define ID_HOTKEY_N_TILDE_SHIFT    16
#define ID_HOTKEY_C_CEDILLA_SHIFT  17
#define ID_HOTKEY_AE_SHIFT         18
#define ID_HOTKEY_A_RING_SHIFT     19
#define ID_HOTKEY_O_SLASH_SHIFT    20

#define ID_HOTKEY_EXCLAM_INV       21
#define ID_HOTKEY_QUESTION_INV     22
#define ID_HOTKEY_GUILLEMET_LEFT   23
#define ID_HOTKEY_GUILLEMET_RIGHT  24

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
// }

// void RegisterAllHotkeys() {
    RegisterHotKey(NULL, ID_HOTKEY_N_TILDE, MOD_CONTROL | MOD_ALT, 0x4E); // Ctrl+Alt+N → ñ
    RegisterHotKey(NULL, ID_HOTKEY_C_CEDILLA, MOD_CONTROL | MOD_ALT, 0x43); // Ctrl+Alt+C → ç
    RegisterHotKey(NULL, ID_HOTKEY_AE, MOD_CONTROL | MOD_ALT, 0x5A); // Ctrl+Alt+Z → æ
    RegisterHotKey(NULL, ID_HOTKEY_A_RING, MOD_CONTROL | MOD_ALT, 0x57); // Ctrl+Alt+W → å
    RegisterHotKey(NULL, ID_HOTKEY_O_SLASH, MOD_CONTROL | MOD_ALT, 0x4C); // Ctrl+Alt+L → ø

   // Mayúsculas (Shift)
    RegisterHotKey(NULL, ID_HOTKEY_N_TILDE_SHIFT, MOD_CONTROL | MOD_ALT | MOD_SHIFT, 0x4E); // Ñ
    RegisterHotKey(NULL, ID_HOTKEY_C_CEDILLA_SHIFT, MOD_CONTROL | MOD_ALT | MOD_SHIFT, 0x43); // Ç
    RegisterHotKey(NULL, ID_HOTKEY_AE_SHIFT, MOD_CONTROL | MOD_ALT | MOD_SHIFT, 0x5A); // Æ
    RegisterHotKey(NULL, ID_HOTKEY_A_RING_SHIFT, MOD_CONTROL | MOD_ALT | MOD_SHIFT, 0x57); // Å
    RegisterHotKey(NULL, ID_HOTKEY_O_SLASH_SHIFT, MOD_CONTROL | MOD_ALT | MOD_SHIFT, 0x4C); // Ø

    RegisterHotKey(NULL, ID_HOTKEY_EXCLAM_INV, MOD_CONTROL | MOD_ALT, 0x31); // Ctrl+Alt+1 → ¡
    RegisterHotKey(NULL, ID_HOTKEY_QUESTION_INV, MOD_CONTROL | MOD_ALT, 0xBF); // Ctrl+Alt+/ → ¿

    RegisterHotKey(NULL, ID_HOTKEY_GUILLEMET_LEFT, MOD_CONTROL | MOD_ALT | MOD_SHIFT, 0xBC); // Ctrl+Alt+Shift+, → «
    RegisterHotKey(NULL, ID_HOTKEY_GUILLEMET_RIGHT, MOD_CONTROL | MOD_ALT | MOD_SHIFT, 0xBE); // Ctrl+Alt+Shift+. → »
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
                    // Nuevos caracteres definidos por ti
                case ID_HOTKEY_N_TILDE: SendUnicodeChar(L'ñ'); break;
    case ID_HOTKEY_N_TILDE_SHIFT: SendUnicodeChar(L'Ñ'); break;

    case ID_HOTKEY_C_CEDILLA: SendUnicodeChar(L'ç'); break;
    case ID_HOTKEY_C_CEDILLA_SHIFT: SendUnicodeChar(L'Ç'); break;

    case ID_HOTKEY_AE: SendUnicodeChar(L'æ'); break;
    case ID_HOTKEY_AE_SHIFT: SendUnicodeChar(L'Æ'); break;

    case ID_HOTKEY_A_RING: SendUnicodeChar(L'å'); break;
    case ID_HOTKEY_A_RING_SHIFT: SendUnicodeChar(L'Å'); break;

    case ID_HOTKEY_O_SLASH: SendUnicodeChar(L'ø'); break;
    case ID_HOTKEY_O_SLASH_SHIFT: SendUnicodeChar(L'Ø'); break;

    case ID_HOTKEY_EXCLAM_INV: SendUnicodeChar(L'¡'); break;
    case ID_HOTKEY_QUESTION_INV: SendUnicodeChar(L'¿'); break;

    case ID_HOTKEY_GUILLEMET_LEFT: SendUnicodeChar(L'«'); break;
    case ID_HOTKEY_GUILLEMET_RIGHT: SendUnicodeChar(L'»'); break;

            }
            break;
    }
    return DefWindowProc(hwnd, msg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    WNDCLASS wc = {0};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = "daNZon";
    RegisterClass(&wc);

    HWND hwnd = CreateWindowEx(0, "MacronHotkeyWnd", "MacronHotkeys", 0, 0, 0, 0, 0,
        // WS_OVERLAPPEDWINDOW,  // must be a real window type
    // CW_USEDEFAULT, CW_USEDEFAULT, 100, 100,
                               NULL, NULL, hInstance, NULL);

    RegisterAllHotkeys();

    HICON hIcon = (HICON)LoadImage(hInstance, MAKEINTRESOURCE(IDR_ICON1), IMAGE_ICON, 16, 16, LR_DEFAULTCOLOR);

    nid.cbSize = sizeof(NOTIFYICONDATA);
    nid.hWnd = hwnd;
    nid.uID = ID_TRAYICON;
    nid.uFlags = NIF_ICON | NIF_TIP;
    nid.hIcon = hIcon;
    strcpy(nid.szTip, "daNZon");
    Shell_NotifyIcon(NIM_ADD, &nid);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}
