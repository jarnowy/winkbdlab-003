
#include <windows.h>
#include <stdio.h>

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

#define ID_HOTKEY_C_CARET        25
#define ID_HOTKEY_C_CARET_SHIFT  26
#define ID_HOTKEY_G_CARET        27
#define ID_HOTKEY_G_CARET_SHIFT  28
#define ID_HOTKEY_H_CARET        29
#define ID_HOTKEY_H_CARET_SHIFT  30
#define ID_HOTKEY_J_CARET        31
#define ID_HOTKEY_J_CARET_SHIFT  32
#define ID_HOTKEY_S_CARET        33
#define ID_HOTKEY_S_CARET_SHIFT  34
#define ID_HOTKEY_U_BREVE        35
#define ID_HOTKEY_U_BREVE_SHIFT  36

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

int main() {
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
    
// void RegisterAllHotkeys() {
    RegisterHotKey(NULL, ID_HOTKEY_N_TILDE, MOD_CONTROL | MOD_ALT, 0x4E); // Ctrl+Alt+N → ñ
    RegisterHotKey(NULL, ID_HOTKEY_C_CEDILLA, MOD_CONTROL | MOD_ALT, 0x58); // Ctrl+Alt+C → ç
    RegisterHotKey(NULL, ID_HOTKEY_AE, MOD_CONTROL | MOD_ALT, 0x5A); // Ctrl+Alt+Z → æ
    RegisterHotKey(NULL, ID_HOTKEY_A_RING, MOD_CONTROL | MOD_ALT, 0x57); // Ctrl+Alt+W → å
    RegisterHotKey(NULL, ID_HOTKEY_O_SLASH, MOD_CONTROL | MOD_ALT, 0x4C); // Ctrl+Alt+L → ø

   // Mayúsculas (Shift)
    RegisterHotKey(NULL, ID_HOTKEY_N_TILDE_SHIFT, MOD_CONTROL | MOD_ALT | MOD_SHIFT, 0x4E); // Ñ
    RegisterHotKey(NULL, ID_HOTKEY_C_CEDILLA_SHIFT, MOD_CONTROL | MOD_ALT | MOD_SHIFT, 0x58); // Ç
    RegisterHotKey(NULL, ID_HOTKEY_AE_SHIFT, MOD_CONTROL | MOD_ALT | MOD_SHIFT, 0x5A); // Æ
    RegisterHotKey(NULL, ID_HOTKEY_A_RING_SHIFT, MOD_CONTROL | MOD_ALT | MOD_SHIFT, 0x57); // Å
    RegisterHotKey(NULL, ID_HOTKEY_O_SLASH_SHIFT, MOD_CONTROL | MOD_ALT | MOD_SHIFT, 0x4C); // Ø

    RegisterHotKey(NULL, ID_HOTKEY_EXCLAM_INV, MOD_CONTROL | MOD_ALT, 0x31); // Ctrl+Alt+1 → ¡
    RegisterHotKey(NULL, ID_HOTKEY_QUESTION_INV, MOD_CONTROL | MOD_ALT | MOD_SHIFT, 0x31); // Ctrl+Alt+/ → ¿ BF

    RegisterHotKey(NULL, ID_HOTKEY_GUILLEMET_LEFT, MOD_CONTROL | MOD_ALT | MOD_SHIFT, 0xBC); // Ctrl+Alt+Shift+, → «
    RegisterHotKey(NULL, ID_HOTKEY_GUILLEMET_RIGHT, MOD_CONTROL | MOD_ALT | MOD_SHIFT, 0xBE); // Ctrl+Alt+Shift+. → »
// }

// void RegisterEsperantoHotkeys() {
    RegisterHotKey(NULL, ID_HOTKEY_C_CARET,       MOD_CONTROL | MOD_ALT, 0x43); // c
    RegisterHotKey(NULL, ID_HOTKEY_C_CARET_SHIFT, MOD_CONTROL | MOD_ALT | MOD_SHIFT, 0x43); // C

    RegisterHotKey(NULL, ID_HOTKEY_G_CARET,       MOD_CONTROL | MOD_ALT, 0x47); // g
    RegisterHotKey(NULL, ID_HOTKEY_G_CARET_SHIFT, MOD_CONTROL | MOD_ALT | MOD_SHIFT, 0x47); // G

    RegisterHotKey(NULL, ID_HOTKEY_H_CARET,       MOD_CONTROL | MOD_ALT, 0x48); // h
    RegisterHotKey(NULL, ID_HOTKEY_H_CARET_SHIFT, MOD_CONTROL | MOD_ALT | MOD_SHIFT, 0x48); // H

    RegisterHotKey(NULL, ID_HOTKEY_J_CARET,       MOD_CONTROL | MOD_ALT, 0x4A); // j
    RegisterHotKey(NULL, ID_HOTKEY_J_CARET_SHIFT, MOD_CONTROL | MOD_ALT | MOD_SHIFT, 0x4A); // J

    RegisterHotKey(NULL, ID_HOTKEY_S_CARET,       MOD_CONTROL | MOD_ALT, 0x53); // s
    RegisterHotKey(NULL, ID_HOTKEY_S_CARET_SHIFT, MOD_CONTROL | MOD_ALT | MOD_SHIFT, 0x53); // S

    RegisterHotKey(NULL, ID_HOTKEY_U_BREVE,       MOD_CONTROL | MOD_ALT, 0x59); // y
    RegisterHotKey(NULL, ID_HOTKEY_U_BREVE_SHIFT, MOD_CONTROL | MOD_ALT | MOD_SHIFT, 0x59); // Y

    MSG msg = {0};
    while (GetMessage(&msg, NULL, 0, 0)) {
        if (msg.message == WM_HOTKEY) {
            switch (msg.wParam) {
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


    case ID_HOTKEY_C_CARET:       SendUnicodeChar(L'ĉ'); break; // \u0109
    case ID_HOTKEY_C_CARET_SHIFT: SendUnicodeChar(L'Ĉ'); break; // \u0108
    case ID_HOTKEY_G_CARET:       SendUnicodeChar(L'ĝ'); break; // \u011D
    case ID_HOTKEY_G_CARET_SHIFT: SendUnicodeChar(L'Ĝ'); break; // \u011C
    case ID_HOTKEY_H_CARET:       SendUnicodeChar(L'ĥ'); break; // \u0125
    case ID_HOTKEY_H_CARET_SHIFT: SendUnicodeChar(L'Ĥ'); break; // \u0124
    case ID_HOTKEY_J_CARET:       SendUnicodeChar(L'ĵ'); break; // \u0135
    case ID_HOTKEY_J_CARET_SHIFT: SendUnicodeChar(L'Ĵ'); break; // \u0134
    case ID_HOTKEY_S_CARET:       SendUnicodeChar(L'ŝ'); break; // \u015D
    case ID_HOTKEY_S_CARET_SHIFT: SendUnicodeChar(L'Ŝ'); break; // \u015C
    case ID_HOTKEY_U_BREVE:       SendUnicodeChar(L'ŭ'); break; // \u016D
    case ID_HOTKEY_U_BREVE_SHIFT: SendUnicodeChar(L'Ŭ'); break; // \u016C

            }
        }
    }
// void UnregisterAllHotkeys() {
    for (int id = 1; id <= 36; ++id) {
        UnregisterHotKey(NULL, id);
    // }
}


    return 0;
}
