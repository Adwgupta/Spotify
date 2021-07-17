/*
 * This library will contain function declarations for functions that will sort the input
 */

#ifndef ASSIGNMENT_1_SORT_H
#define ASSIGNMENT_1_SORT_H
//This will allow us to use the utilities library containing our structs
#include "utilities.h"

// Removes any newline characters from the string
void removeNewLineCharacter(char *line);

// Sorts each artist in alphabetical order
void sortArtistByName(ArtistList list);

// Adds each artist to the sorted list
void addArtistToList(ArtistList * list, Artist * artist);

// Adds each artists songs to the sorted list
void addSongToList(SongList * list, Song * song);

// Gets the duration of each song
char * getDurationStartPosition(char * line);

// parses the duration of each song to its song in the sorted list
Duration parseDuration(char * start);

// Parses each song to the sorted list
Song * parseSong(char * line);

// Reads in each song
SongList readSongList(FILE * input, Artist * artist);

// Sorts all the songs by titles
void sortSongByTitle(SongList list);

// Reads in each artist
Artist * readArtist(FILE * input);

// Reads the input data in its entirety
ArtistList readData(FILE * input);

#endif //ASSIGNMENT_1_SORT_H
