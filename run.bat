@echo off
call common.bat

pushd "%build_dir%"
.\%target%.exe
popd