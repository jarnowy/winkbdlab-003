;#NoTrayIcon
;#RequireAdmin

;~ #Include <TrayConstants.au3>
;~ TraySetIcon("Basquecountry_flags_flag_9313.ico")
;~ TraySetToolTip("Diacritic Hotkeys Active")

HotKeySet("^{ALT}z", "SendAtilde")
HotKeySet("^{ALT}w", "SendOtilde")
HotKeySet("^{ALT}n", "SendNtilde")
HotKeySet("^{ALT}/", "SendIQuest")
HotKeySet("^{ALT}1", "SendExclamInv")

While True
    Sleep(100)
WEnd

Func SendAtilde()
    If _IsPressed("10") Then ; Shift
        Send("�")
    Else
        Send("�")
    EndIf
EndFunc

Func SendOtilde()
    If _IsPressed("10") Then
        Send("�")
    Else
        Send("�")
    EndIf
EndFunc

Func SendNtilde()
    If _IsPressed("10") Then
        Send("�")
    Else
        Send("�")
    EndIf
EndFunc

Func SendIQuest()
    Send("�")
EndFunc

Func SendExclamInv()
    Send("�")
EndFunc
