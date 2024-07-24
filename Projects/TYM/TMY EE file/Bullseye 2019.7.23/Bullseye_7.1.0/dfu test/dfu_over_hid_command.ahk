;path to dll
PathToDLL := "HidDfu.dll"

;load the dll into memory
hModule := DllCall("LoadLibrary", "str", PathToDLL)

vid := 1447
pid := 16638
result := DllCall("HidDfu\hidDfuConnect","Short",vid,"Short",pid,"Short",0,"Short",0)
if result <> 0
{
    MsgBox ,0,"Device not found",Result = %result%
}
else
{
    VarSetCapacity(command,3)
    NumPut(1,command,0,"Char")
    NumPut(176,command,1,"Char")
    NumPut(7,command,2,"Char")
    result := DllCall("HidDfu\hidDfuSendCommand","Str",command,"Int",3)
    if result <> 0
    {
        MsgBox ,0,"Send Command Error",Result = %result%
    }
}

;unload dll
DllCall("FreeLibrary", "UInt", hModule)

