@echo off
set /p commit=����:
title auto commit
git add -A
git commit -m %commit%
git pull --rebase origin master
git push
echo ����ִ����ϣ���������ر�
pause >null