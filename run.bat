@echo off
call common.bat

pushd "%build_dir%"
echo %cd%
.\%target%_%part%.exe
popd