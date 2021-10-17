#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>
#include <vector>
#include <unistd.h>

namespace fs = std::filesystem;

bool CheckPackages()
{
    return access("/usr/bin/feh", X_OK) == 0;
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
    }

    return filepath;
}

void GetWallpapers(std::string wallpaper_path)
{
    std::vector<std::string> wallpapers;

    int filecount = 1;

    for (const auto& file: fs::directory_iterator(wallpaper_path))
    { 
        std::string wallpaper_name = file.path().filename();
        std::cout << "[" << filecount << "] " << wallpaper_name << std::endl;
        wallpapers.push_back(wallpaper_name);

        filecount++;
    }

    int wallpaper_pick;
    
    printf(">> ");

    std::cin >> wallpaper_pick;

    if (wallpaper_pick > 0 && wallpaper_pick <= wallpapers.size())
    {
        std::cout << "Setting wallpaper to: " << wallpapers[wallpaper_pick - 1] << std::endl;
        std::string wallpaper_command = (std::string)"feh --bg-fill " += wallpaper_path += (std::string)"/" += wallpapers[wallpaper_pick - 1];
        system(wallpaper_command.c_str());
    }
    else 
    {
        std::cout << "ERROR: This number is not valid" << std::endl;
    }
}

int main(int argc, char *argv[])
{
    if (CheckPackages())
        GetWallpapers(OpenConfigFile());
    else
    {
        std::cout << "ERROR: feh is not installed!!" << std::endl;
        std::cout << "feh's github repo: https://github.com/derf/feh" << std::endl;
        std::cout << "feh's AUR Repo: https://aur.archlinux.org/packages/feh-git" << std::endl;
    }

    return 0;
}