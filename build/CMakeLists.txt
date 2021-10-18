set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE INTERNAL "")
cmake_minimum_required(VERSION 3.0.0)
project(Wallpaper_Change VERSION 0.0.1)

file (GLOB SOURCE_fILES
  "../src/*.cpp"
  )

add_executable(Wallpaper_Change ${SOURCE_fILES})
target_compile_features(Wallpaper_Change PRIVATE cxx_std_17)
