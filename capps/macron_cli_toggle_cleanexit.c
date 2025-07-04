
#include <windows.h>
#include <stdio.h>
#include <stdbool.h>

#define HOTKEY_BASE_ID 1
#define HOTKEY_COUNT 2

bool hotkeys_enabled = true;

DWORD WINAPI InputThread(LPVOID param) {
    char c;
    while (1) {
        c = getchar();
        if (c == 't') {
            hotkeys_enabled = !hotkeys_enabled;
            printf("Hotkeys: %s\n", hotkeys_enabled ? "ON" : "OFF");
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

BOOL WINAPI ConsoleHandler(DWORD signal) {
    if (signal == CTRL_CLOSE_EVENT || signal == CTRL_C_EVENT) {
        for (int id = HOTKEY_BASE_ID; id < HOTKEY_BASE_ID + HOTKEY_COUNT; ++id) {
            UnregisterHotKey(NULL, id);
        }
        printf("Unregistered all hotkeys.\n");
    }
    return FALSE;
}

int main() {
    printf("Macron CLI hotkey tool\n");
    printf("Press 't' to toggle hotkeys. Close the window to quit.\n");

    SetConsoleCtrlHandler(ConsoleHandler, TRUE);

    RegisterHotKey(NULL, HOTKEY_BASE_ID, MOD_CONTROL | MOD_ALT, 0x41);         // Ctrl+Alt+A
    RegisterHotKey(NULL, HOTKEY_BASE_ID + 1, MOD_CONTROL | MOD_ALT | MOD_SHIFT, 0x41); // Ctrl+Alt+Shift+A

    CreateThread(NULL, 0, InputThread, NULL, 0, NULL);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        if (msg.message == WM_HOTKEY && hotkeys_enabled) {
            switch (msg.wParam) {
                case HOTKEY_BASE_ID:
                    SendUnicodeChar(L'ā');
                    break;
                case HOTKEY_BASE_ID + 1:
                    SendUnicodeChar(L'Ā');
                    break;
            }
        }
    }

    return 0;
}
