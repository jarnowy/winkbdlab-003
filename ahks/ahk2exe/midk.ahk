; Script para escribir vocales con macrón usando AltGr
; AltGr = <^>!
; Shift + AltGr = mayúscula

#NoEnv
#SingleInstance Force
SetTitleMatchMode, 2
SetWorkingDir, %A_ScriptDir%
Menu, Tray, Icon, midk.ico

; Mapeos de vocales minúsculas
<^>!a::Send, ā
<^>!e::Send, ē
<^>!i::Send, ī
<^>!o::Send, ō
<^>!u::Send, ū

; Mapeos de vocales mayúsculas con Shift
+<^>!a::Send, Ā
+<^>!e::Send, Ē
+<^>!i::Send, Ī
+<^>!o::Send, Ō
+<^>!u::Send, Ū

; Mapa de tildes

<^>!z::Send, æ      ; AltGr + z
<^>!w::Send, å      ; AltGr + w
<^>!n::Send, ñ      ; AltGr + n
<^>!l::Send, ø      ; AltGr + n

+<^>!Z::Send, Æ      ; AltGr + Shift + z
+<^>!W::Send, Å      ; AltGr + Shift + w
+<^>!N::Send, Ñ      ; AltGr + Shift + n
+<^>!L::Send, ø      ; AltGr + Shift + n

; Mapa de puntuación

<^>!/::Send, ¿      ; AltGr + /
<^>!1::Send, ¡      ; AltGr + 1 (Shift+1 = !)

return
