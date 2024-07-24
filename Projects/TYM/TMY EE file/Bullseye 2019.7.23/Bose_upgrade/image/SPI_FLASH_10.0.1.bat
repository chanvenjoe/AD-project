call ..\tools\set_version_10.0.1.bat

set TOOL_PATH=..\tools

call %TOOL_PATH%\bin\pscli.exe -usb 0 cold_reset
call %TOOL_PATH%\bin\pscli.exe -usb 0 query %TOOL_PATH%\backup.psr %TOOL_PATH%\backup.psq
call %TOOL_PATH%\bin\BlueFlashCmd.exe -usb 0 erase
call %TOOL_PATH%\bin\BlueFlashCmd.exe -usb 0 %PKG_VERSION%
call %TOOL_PATH%\bin\pscli.exe -usb 0 merge %TOOL_PATH%\backup.psr
call %TOOL_PATH%\bin\pscli.exe -usb 0 cold_reset

pause