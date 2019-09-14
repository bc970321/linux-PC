Set WshShell
WScript.CreateObject
("WScript.Shell")
WshShell.AppActivate "网名"
for i=1 to 10
WScript.Sleep 99
WshShell.SendKeys "^v"
WshShell.SendKeys i
WshShell.SendKeys "%s"
Next
