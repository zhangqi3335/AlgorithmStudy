@echo off
:: 设置窗口标题
title Git Auto Sync Tool
:: 调用同目录下的 PowerShell 脚本，-ExecutionPolicy Bypass 允许脚本执行
powershell -NoProfile -ExecutionPolicy Bypass -File "%~dp0EasySync.ps1"
:: 脚本运行完后暂停，防止窗口闪退，让你能看到结果
pause