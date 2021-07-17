/*
 * This library will contain function declarations for functions to shuffle the sorted input
 */

#ifndef ASSIGNMENT_1_SHUFFLE_H
#define ASSIGNMENT_1_SHUFFLE_H
#include "utilities.h"

// This is a counter for each time a song appears
int getSongNum(ArtistList all);

// Get all songs from the list of artists
SongList getAllSongs(ArtistList all);

// Shuffles the songs
void shuffleSong(SongList list);

// Resets the artists for the next time the program is called
void resetArtists(ArtistList all);

// Gets the shuffled playlist with the program specifications' constraints
SongList getSelectedList(SongList list);

//Frees the memory after printing the shuffled playlist
void freeArtistList(ArtistList all);

#endif //ASSIGNMENT_1_SHUFFLE_H