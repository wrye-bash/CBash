::@ECHO OFF
set THIS=%~pd0
pushd %THIS%..\build || EXIT
RD /S /Q %THIS%..\build 2> NUL
popd

