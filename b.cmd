set d=build-win-64
rd /q /s %d%
md %d%
cd %d%
cmake -G "Visual Studio 14 2015 Win64" ..
cd ..

cmake --build %d% --config Release
