cmake_minimum_required(VERSION 3.17)
project(test)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(test
        artistes+songs.txt
        sample_song_file.txt
        sample_song_file2.txt
        sample_song_file3.txt
        main.c
        main.exe
        print_shuffle.c
        print_shuffle.h
        print_sort.c
        print_sort.h
        shuffle.c
        shuffle.h
        sort.c
        sort.h
        utilities.h)
