#include <windows.h>
#include <stdio.h>
#include <stdbool.h>

#define MAX_HOTKEY_ID 10

bool hotkeys_enabled = true;

 // v2
void ToggleHotkeys(bool enable) {
    char keys[] = { 'A', 'E', 'I', 'O', 'U' };
    for (int i = 0; i < 5; ++i) {
        int base_id = i * 2 + 1;
        UINT vk = keys[i];
        if (enable) {
            RegisterHotKey(NULL, base_id, MOD_CONTROL | MOD_ALT, vk);
            RegisterHotKey(NULL, base_id + 1, MOD_CONTROL | MOD_ALT | MOD_SHIFT, vk);
        } else {
            UnregisterHotKey(NULL, base_id);
            UnregisterHotKey(NULL, base_id + 1);
        }
    }
}


// Toggle hotkeys by pressing 't' in the console
DWORD WINAPI InputThread(LPVOID param) {
    char c;
    while (1) {
        c = getchar();
        // if (c == 't') {
            // hotkeys_enabled = !hotkeys_enabled;
            // printf("Hotkeys: %s\n", hotkeys_enabled ? "ON" : "OFF");
        // }
        // v2
    if (c == 't') {
    hotkeys_enabled = !hotkeys_enabled;
    ToggleHotkeys(hotkeys_enabled);
    printf("Hotkeys: %s\n", hotkeys_enabled ? "ON" : "OFF");
}
    }

    return 0;
}


// Send a Unicode character to the active window
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

// Unregister all hotkeys on Ctrl+C or close
BOOL WINAPI ConsoleHandler(DWORD signal) {
    if (signal == CTRL_CLOSE_EVENT || signal == CTRL_C_EVENT) {
        for (int id = 1; id <= MAX_HOTKEY_ID; ++id) {
            UnregisterHotKey(NULL, id);
        }
        printf("\nAll hotkeys unregistered.\n");
    }
    return FALSE;
}



int main() {
    printf("Macron CLI hotkey tool\n");
    printf("Hotkeys: Ctrl+Alt+<vowel> → macron\n");
    printf("         Ctrl+Alt+Shift+<vowel> → uppercase macron\n");
    printf("Press 't' to toggle hotkeys ON/OFF.\n");
    printf("Close the window or press Ctrl+C to quit.\n");

    SetConsoleCtrlHandler(ConsoleHandler, TRUE);

    // Register hotkeys using a loop
    char keys[] = { 'A', 'E', 'I', 'O', 'U' };
    for (int i = 0; i < 5; ++i) {
        int base_id = i * 2 + 1;
        UINT vk = keys[i];
        RegisterHotKey(NULL, base_id, MOD_CONTROL | MOD_ALT, vk);               // lowercase
        RegisterHotKey(NULL, base_id + 1, MOD_CONTROL | MOD_ALT | MOD_SHIFT, vk); // uppercase
    }

    CreateThread(NULL, 0, InputThread, NULL, 0, NULL);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        if (msg.message == WM_HOTKEY && hotkeys_enabled) {
            switch (msg.wParam) {
                case 1: SendUnicodeChar(L'ā'); break;
                case 2: SendUnicodeChar(L'Ā'); break;
                case 3: SendUnicodeChar(L'ē'); break;
                case 4: SendUnicodeChar(L'Ē'); break;
                case 5: SendUnicodeChar(L'ī'); break;
                case 6: SendUnicodeChar(L'Ī'); break;
                case 7: SendUnicodeChar(L'ō'); break;
                case 8: SendUnicodeChar(L'Ō'); break;
                case 9: SendUnicodeChar(L'ū'); break;
                case 10: SendUnicodeChar(L'Ū'); break;
            }
        }
    }

    return 0;
}
