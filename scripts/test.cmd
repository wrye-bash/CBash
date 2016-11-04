@ECHO OFF
set THIS=%~pd0
pushd %THIS%..\build

SET CONFIG=%1
IF "%CONFIG%"=="" (
    SET CONFIG=Debug
)

cmake --build . --target pytest --config %CONFIG%
popd

