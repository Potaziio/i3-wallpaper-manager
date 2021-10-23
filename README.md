Dependencies:\
gcc/g++ (https://gcc.gnu.org/) \
cmake (https://github.com/Kitware/CMake) \
feh (https://github.com/derf/feh)

if using sway:\
swaybg (https://github.com/swaywm/swaybg) \

Steps to install:\
chmod +x install\
./install

How to use:\
When you run Wallpaper_Change for the first time, it's going to ask you for a directory, this is the directory the program will use to search for wallpapers\
Ex: /home/$USER/Pictures/Wallpapers
It will list all the wallpapers on that directory\
Choose one of them\
Done. \

If you want to save your last choice to i3wm config so that you don't have to run the wallpaper everytime you turn on the device just add this to your i3wm config.\

exec_always sh ~/.config/.wallchange/lastwallpaper.sh \

Notes: 

This will only work after the first time you run the command \
