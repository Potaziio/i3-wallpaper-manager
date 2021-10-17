#!/usr/bin/env bash

echo Installing...

cd build/ && cmake . && make

cd ..

echo Do you want to add the script to /usr/local/bin/?? [y/n]

read CHOICE

SCRIPT_DIR="$( cd -- "$( dirname -- "${BASH_SOURCE[0]}"  )" &> /dev/null && pwd  )"

if [ -n "$CHOICE" ]
then
    if [ "$CHOICE" == "y" ]
    then
        sudo cp $SCRIPT_DIR/build/Wallpaper_Change /usr/local/bin
        echo "Finished installation. To run type Wallpaper_Change in any terminal."
    elif [ "$CHOICE" == "n" ]
    then
        echo "Finished installation. To run go to the /build/ directory and run the executable created."
    else
        echo "Choice not valid, please use [y/n]"
    fi
else 
    echo choice not valid, please use [y/n]
fi