@ECHO OFF
set THIS=%~pd0
mkdir %THIS%..\build 2>nul
pushd %THIS%..\build

cmake ..

:EXIT
popd

