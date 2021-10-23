#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>
#include <vector>
#include <unistd.h>

namespace fs = std::filesystem;

bool CheckFeh()
{
    return access("/usr/bin/feh", X_OK) == 0;
}

bool CheckSwaybg()
{
    return access("/usr/bin/swaybg", X_OK) == 0;
}

bool CheckCmake()
{
    return access("/usr/bin/cmake", X_OK) == 0;
}

bool CheckGcc()
{
    return access("/usr/bin/gcc", X_OK) == 0;
}

std::string OpenConfigFile()
{
    std::string filepath;
    std::string line;
    std::ifstream wallpaper_path;
    std::string config_path = std::getenv("HOME");

    config_path += "/.config/.wallchange/filepath.ini";

    wallpaper_path.open(config_path);

    if (wallpaper_path.is_open())
    {
        std::getline(wallpaper_path, line);
        filepath = line;
    }
    else
    {
        std::cout << "Set the wallpaper directory path, this is only a one time thing" << std::endl;

        fs::path configfile_path(config_path);
        fs::create_directories(configfile_path.parent_path());

        std::cin >> filepath;

        std::ofstream ofs(configfile_path);
        ofs << filepath;

        ofs.close();
        wallpaper_path.close();
    }

    return filepath;
}

void SaveLastChoice(std::string command)
{
    std::string line;
    std::ifstream LastChoicePath;

    std::string config_path = std::getenv("HOME");

    config_path += "/.config/.wallchange/lastwallpaper.sh";

    LastChoicePath.open(config_path);

    fs::path configfile_path(config_path);

    std::ofstream ofs(configfile_path);

    ofs << command; 

    ofs.close();
    LastChoicePath.close();
}

void GetWallpapers(std::string wallpaper_path, bool random)
{
    std::vector<std::string> wallpapers;

    int filecount = 1;

    for (const auto& file: fs::directory_iterator(wallpaper_path))
    { 
        std::string wallpaper_name = file.path().filename();

        if (!random)
        {
            std::cout << "[" << filecount << "] " << wallpaper_name << std::endl;
        }

        wallpapers.push_back(wallpaper_name);

        filecount++;
    }
    
    int wallpaper_pick;
    
    if (!random)
    {
        int wallpaper_pick;
        printf(">> ");
        std::cin >> wallpaper_pick;

        if (wallpaper_pick > 0 && wallpaper_pick <= wallpapers.size())
        {
            std::cout << "Setting wallpaper to: " << wallpapers[wallpaper_pick - 1] << std::endl;
            std::string wallpaper_command;        

            if (!CheckSwaybg() || !CheckFeh())
            {
                if (CheckSwaybg())
                {
                    wallpaper_command = (std::string)"swaybg -i " += wallpaper_path += (std::string)"/" += wallpapers[wallpaper_pick - 1] += (std::string)" -m fill";
                }
                else
                {
                    wallpaper_command = (std::string)"feh --bg-fill " += wallpaper_path += (std::string)"/" += wallpapers[wallpaper_pick - 1];
                    SaveLastChoice(wallpaper_command);
                }

                system(wallpaper_command.c_str());
            }
            else 
            {
                std::cout << "ERROR: swaybg and feh are both installed in your system." << std::endl;
            }
        }
        else 
            std::cout << "ERROR: This number is not valid" << std::endl;
    }
    else
    {
        srand(time(NULL));

        std::string wallpaper_command;

        int randomWallpaper = (rand() % wallpapers.size());

        if (!CheckSwaybg() || !CheckFeh())
        {
            if (CheckSwaybg())
            {
                wallpaper_command = (std::string)"swaybg -i " += wallpaper_path += (std::string)"/" += wallpapers[randomWallpaper] += (std::string)" -m fill";
                std::cout << "Setting wallpaper to: " << wallpapers[randomWallpaper] << std::endl;
            }
            else
            {
                wallpaper_command = (std::string)"feh --bg-fill " += wallpaper_path += (std::string)"/" += wallpapers[randomWallpaper];
                std::cout << "Setting wallpaper to: " << wallpapers[randomWallpaper] << std::endl;
            }
            system(wallpaper_command.c_str());
        }
        else
            std::cout << "ERROR: swaybg and feh are both installed in your system." << std::endl;
    }
}

int main(int argc, char *argv[])
{
    if (CheckSwaybg())
    {
        if (CheckCmake() && CheckGcc())
        {
            if (argv[1] != NULL)
                GetWallpapers(OpenConfigFile(), (std::string)argv[1] == "-r");
            else 
                GetWallpapers(OpenConfigFile(), false);
        }
        else
        {
            if (!CheckCmake())
            {
                std::cout << "ERROR: CMake is not installed!!" << std::endl;
                std::cout << "Please install CMake" << std::endl;
            }

            if (!CheckGcc())
            {
                std::cout << "ERROR: GCC is not installed!!" << std::endl;
                std::cout << "Please install GCC" << std::endl;
            }                    
        }
    }
    else if (CheckFeh() && CheckCmake() && CheckGcc())
    {
        if (argv[1] != NULL)
            GetWallpapers(OpenConfigFile(), (std::string)argv[1] == "-r");
        else
            GetWallpapers(OpenConfigFile(), false);
    }
    else
    {
        if (!CheckFeh())
        {
            std::cout << "ERROR: feh is not installed!!" << std::endl;
            std::cout << "feh's github repo: https://github.com/derf/feh" << std::endl;
        }

        if (!CheckCmake())
        {
            std::cout << "ERROR: CMake is not installed!!" << std::endl;
            std::cout << "Please install CMake" << std::endl;
        }

        if (!CheckGcc())
        {
            std::cout << "ERROR: GCC is not installed!!" << std::endl;
            std::cout << "Please install GCC" << std::endl;
        }
    }

    return 0;
}
