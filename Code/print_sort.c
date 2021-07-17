#include <stdio.h>
#include "print_sort.h"
/*
 * Print each individual song for each artist
 */
void printSong(Song * song, FILE * out) {
    fprintf(out, "\to %s%s%d:", song->title, SUB_STRING, song->duration.minutes);
    if (song->duration.seconds < 10) {
        fprintf(out, "0");
    }
    fprintf(out, "%d\n", song->duration.seconds);
}

/*
 * Print the songs for each artist using the above function
 */
void printSongList(SongList list, FILE * out) {
    int i;
    for (i = 0; i < list.songNum; i++) {
        printSong(list.songs[i], out);
    }
}

/*
 * Print each individual artist in the list
 */
void printArtist(Artist * artist, FILE * out) {
    fprintf(out, "%s\n", artist->name);
    printSongList(artist->songs, out);
}

/*
 * Print out the list of artists using the above function
 */
void printArtistList(ArtistList all, FILE * out) {
    fprintf(out, "Sorted list of artists & their songs:\n\n");
    for (int i = 0; i < all.artistNum; i++) {
        printArtist(all.artists[i], out);
        fprintf(out, "\n");
    }
}

/*
 * Print the complete sorted playlist using the above functions
 *
 * This function is called in the main.c file so that the above functions
 * and the functions in the sorted library
 * can be executed to produce the sorted list
 */
void printSortedList(ArtistList all){

    // Print the output to the console
    printArtistList(all, stdout);

    /* Print the output to a file called sorted playlist as specified in the
     * SORTED_OUTPUT_FILE declaration in the utilities library
     */
     FILE * sortedFile = fopen(SORTED_OUTPUT_FILE, "w");
    if (sortedFile != NULL) {
        printArtistList(all, sortedFile);
        fclose(sortedFile);
    }
}


