@echo off
set /p commit=描述:
title auto commit
git add -A
git commit -m %commit%
git pull --rebase origin master
git push
echo 命令执行完毕，按任意键关闭
pause >null