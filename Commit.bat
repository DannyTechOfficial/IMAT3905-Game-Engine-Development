@echo off
cls
echo [102;93m Github Commit [0m
echo ^<Console^> [92mCommit to github starting...[0m
set /p message= [91mEnter Message:
echo [92m
git add .
git commit -m "%message%"
git push
echo.
echo [92mCommit Finished!![0m
pause