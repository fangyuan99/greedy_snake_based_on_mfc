@echo off
set /p commit=ÃèÊö:
set /p url=²Ö¿âurl:
title auto commit
git init
git add .
git commit -m %commit%
git remote add origin %url%
git pull --rebase origin master
git push -u origin master
echo ÃüÁîÖ´ÐÐÍê±Ï£¬°´ÈÎÒâ¼ü¹Ø±Õ
pause >null