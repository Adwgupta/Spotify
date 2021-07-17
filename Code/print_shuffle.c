#include <stdio.h>
#include <stdlib.h>
#include "utilities.h"
#include "print_shuffle.h"

/*
 * Print the randomised playlist
 */
void printRandomSongList(SongList list, FILE * out) {
    int i;
    fprintf(out, "\nYour Randomised Playlist:\n\n");
    Song * song;
    Duration duration;
    Duration total;
    total.minutes = 0;
    total.seconds = 0;

    // Prints out the playlist
    for (i = 0; i < list.songNum; i++) {
        song = list.songs[i];
        duration = song->duration;
        fprintf(out, "%s:\n\t\"%s\" -- %d:", song->artist->name,song->title, duration.minutes);
        if (duration.seconds < 10) {
            fprintf(out, "0");
        }
        fprintf(out, "%d\n\n", duration.seconds);

        // This correctly modifies the time to print out in minutes and seconds
        total.seconds += duration.seconds;
        total.minutes += duration.minutes + (total.seconds / 60);
        total.seconds = total.seconds % 60;
    }

    // This correctly modifies the seconds so that it prints out correctly
    fprintf(out, "Total duration:\t [%d:", total.minutes);
    if (total.seconds < 10) {
        fprintf(out, "0");
    }
    fprintf(out, "%d]\n", total.seconds);
}

/*
 * Print the randomised playlist using the above function
 *
 * This function is called in the main.c file so that the above function
 * and the functions in the shuffle library
 * can be executed to produce the shuffled list
 */
void printRandomList(ArtistList all) {

    //The following are function calls to the functions in the shuffled library

    // Get all songs from the list of artists
    SongList list = getAllSongs(all);
    // Shuffles the songs
    shuffleSong(list);
    //Resets the artists for the next time the program is called
    resetArtists(all);
    // Gets the shuffled playlist with the program specifications' constraints
    SongList select = getSelectedList(list);

    // Print the output to the console
    printRandomSongList(select, stdout);

    /* Print the output to a file called sorted playlist as specified in the
     * SORTED_OUTPUT_FILE declaration in the utilities library
     */
    FILE * randomFile = fopen(RANDOM_OUTPUT_FILE, "w");
    if (randomFile != NULL) {
        printRandomSongList(select, randomFile);
        fclose(randomFile);
    }

    /* Uses the freeing memory functions in the shuffle library
     * so that the next time the program is run, it runs correctly
     */
    free(select.songs);
    free(list.songs);
}