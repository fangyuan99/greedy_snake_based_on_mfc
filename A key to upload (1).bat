@echo off
set /p commit=����:
set /p url=�ֿ�url:
title auto commit
git init
git add .
git commit -m %commit%
git remote add origin %url%
git pull --rebase origin master
git push -u origin master
echo ����ִ����ϣ���������ر�
pause >null