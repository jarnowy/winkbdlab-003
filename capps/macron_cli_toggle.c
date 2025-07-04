
#include <windows.h>
#include <stdio.h>
#include <stdbool.h>

#define ID_HOTKEY_A       1
#define ID_HOTKEY_A_SHIFT 2

bool hotkeys_enabled = true;

DWORD WINAPI InputThread(LPVOID param) {
    char c;
    while (1) {
        c = getchar();
        if (c == 't') {
            hotkeys_enabled = !hotkeys_enabled;
            printf("Hotkeys: %s\n", hotkeys_enabled ? "ON" : "OFF");
        } else if (c == 'q') {
            PostQuitMessage(0);
            break;
        }
    }
    return 0;
}

void SendUnicodeChar(wchar_t ch) {
    INPUT ip = {0};
    ip.type = INPUT_KEYBOARD;
    ip.ki.wScan = ch;
    ip.ki.dwFlags = KEYEVENTF_UNICODE;
    ip.ki.wVk = 0;
    ip.ki.dwExtraInfo = GetMessageExtraInfo();
    SendInput(1, &ip, sizeof(INPUT));
    ip.ki.dwFlags |= KEYEVENTF_KEYUP;
    SendInput(1, &ip, sizeof(INPUT));
}

int main() {
    printf("Macron CLI hotkey tool\n");
    printf("Press 't' to toggle hotkeys, 'q' to quit\n");

    RegisterHotKey(NULL, ID_HOTKEY_A, MOD_CONTROL | MOD_ALT, 0x41); // Ctrl+Alt+A
    RegisterHotKey(NULL, ID_HOTKEY_A_SHIFT, MOD_CONTROL | MOD_ALT | MOD_SHIFT, 0x41); // Ctrl+Alt+Shift+A

    CreateThread(NULL, 0, InputThread, NULL, 0, NULL);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        if (msg.message == WM_HOTKEY && hotkeys_enabled) {
            switch (msg.wParam) {
                case ID_HOTKEY_A:
                    SendUnicodeChar(L'ā');
                    break;
                case ID_HOTKEY_A_SHIFT:
                    SendUnicodeChar(L'Ā');
                    break;
            }
        }
    }

    UnregisterHotKey(NULL, ID_HOTKEY_A);
    UnregisterHotKey(NULL, ID_HOTKEY_A_SHIFT);
    printf("Exiting...\n");
    return 0;
}
