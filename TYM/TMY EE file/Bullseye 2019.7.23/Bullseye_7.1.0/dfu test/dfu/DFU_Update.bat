echo off

set _DFU_FILE_="firmware.dfu"

set _USBVID_="0x05a7"
set _USBPID_="0xa211"

::Check if the .dfu file is generated
IF NOT EXIST %_DFU_FILE_% (
  echo Fail: DFU file is not generated
  goto LABEL_FAIL
)

HidDfuCmd.exe upgrade %_USBVID_% %_USBPID_% 0 0 %_DFU_FILE_%

if errorlevel 1 goto TRY_OLD_AGAIN

goto LABEL_EXIT


:TRY_OLD_AGAIN
echo Try the old USB VID / PID

set _USBVID_="0x05a7"
set _USBPID_="0x40fe"
set _DFU_FILE_="firmware.dfu"
HidDfuCmd.exe upgrade %_USBVID_% %_USBPID_% 0 0 %_DFU_FILE_%


:LABLEL_EXIT
:LABEL_FAIL

pause