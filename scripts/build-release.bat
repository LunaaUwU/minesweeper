@echo off

cd ..

echo Configuring for Release...
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release

echo Building the game...
cmake --build build --config Release

pause