/*
 * This library will contain function declarations for functions to print the modified data
 */

#ifndef ASSIGNMENT_1_PRINT_SHUFFLE_H
#define ASSIGNMENT_1_PRINT_SHUFFLE_H
#include "utilities.h"
#include "shuffle.h"

// Print the randomised playlist
void printRandomSongList(SongList list, FILE * out);

// Print the randomised playlist using the above function
void printRandomList(ArtistList all);

#endif //ASSIGNMENT_1_PRINT_SHUFFLE_H
