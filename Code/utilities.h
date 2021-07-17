/*
 * This library contains declarations that are used frequently throughout the program
 * As well, it contains the structs that will be used to store and manipulate the data
 */
#ifndef ASSIGNMENT_1_UTILITIES_H
#define ASSIGNMENT_1_UTILITIES_H

#define DEFAULT_STRING_LENGTH 1000                              //This sets the total length that a song name, artist, etc can be to 1,000
#define DEFAULT_INPUT_FILE "artistes+songs.txt"                 //Creates the default file
#define SORTED_OUTPUT_FILE "sorted_playlist.txt"                //Creates the sorted playlist output file
#define RANDOM_OUTPUT_FILE "shuffled_playlist.txt"              //Creates the shuffled playlist output file
#define SUB_STRING "***"                                        //To separate song name from duration
#define MAX_ARTIST_PER_ROW 2                                    //Sets the max artists in a row to 2
#define MAX_ARTIST_PER_PLAYLIST 3                               //Sets the max artists in the total playlist to 3
#define LAST_CALL 59                                            //To be used for the last call which is 59:59

//A struct to store the duration of songs
struct Duration {
    int minutes;
    int seconds;
};
typedef struct Duration Duration;

//A struct to store an individual song
struct Song {
    char * title;
    Duration duration;
    struct Artist * artist;
};
typedef struct Song Song;

//A struct to store the song list for an artist
struct SongList {
    Song ** songs;
    int songNum;
};
typedef struct SongList SongList;

//A struct to store each artist
struct Artist {
    char * name;
    SongList songs;
    int appearance;
    int songsInRow;
};
typedef struct Artist Artist;

//A struct that will store every artist
struct ArtistList {
    Artist ** artists;
    int artistNum;
};
typedef struct ArtistList ArtistList;

#endif