/*
 * This library will contain function declarations for functions to print the modified data
 */

#ifndef ASSIGNMENT_1_PRINT_SORT_H
#define ASSIGNMENT_1_PRINT_SORT_H
#include "utilities.h"
#include "sort.h"

// Print each individual song for each artist
void printSong(Song * song, FILE * out);

// Print the songs for each artist using the above function
void printSongList(SongList list, FILE * out);

// Print each individual artist in the list
void printArtist(Artist * artist, FILE * out);

// Print out the list of artists using the above function
void printArtistList(ArtistList all, FILE * out);

// Print the complete sorted playlist using the above functions
void printSortedList(ArtistList all);

#endif //ASSIGNMENT_1_PRINT_SORT_H
