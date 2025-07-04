
#NoEnv
#SingleInstance force
SetTitleMatchMode, 2

isEnabled := true  ; Start with hotkeys enabled

; -------------------------------
; Tray Menu
Menu, Tray, NoStandard
Menu, Tray, Add, Toggle Hotkeys, ToggleHotkeys
Menu, Tray, Add, Exit, ExitApp
Menu, Tray, Default, Toggle Hotkeys
Menu, Tray, Tip, Diacritic Hotkeys Active
Return

; -------------------------------
; Toggle Hotkeys with Ctrl + Alt + T
; ^!t::ToggleHotkeys()

ToggleHotkeys() {
    global isEnabled
    isEnabled := !isEnabled
    if (isEnabled) {
        Menu, Tray, Tip, Diacritic Hotkeys Active
        TrayTip, Hotkeys Enabled, Your special characters are active., 1
    } else {
        Menu, Tray, Tip, Hotkeys Disabled
        TrayTip, Hotkeys Disabled, Hotkeys have been turned off., 1
    }
}

; -------------------------------
; Hotkey Definitions
#If (isEnabled)

; AltGr + z/w/n ? ã/õ/ñ (shift = uppercase)
<^>!z::
    if GetKeyState("Shift", "P")
        Send, Ã
    else
        Send, ã
return

<^>!w::
    if GetKeyState("Shift", "P")
        Send, Õ
    else
        Send, õ
return

<^>!n::
    if GetKeyState("Shift", "P")
        Send, Ñ
    else
        Send, ñ
return

<^>!/::Send, ¿      ; AltGr + /
<^>!1::Send, ¡      ; AltGr + 1 (Shift+1 = !)
#If

; -------------------------------
ExitApp:
ExitApp
