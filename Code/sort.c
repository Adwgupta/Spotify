#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sort.h"

// removes any newline characters from the string
void removeNewLineCharacter(char *line) {
    if (line[strlen(line) - 1] == '\n') {
        line[strlen(line) - 1] = '\0';
    }
}

/*
 * Sorts each artist in alphabetical order
 * using insertion sort
 */
void sortArtistByName(ArtistList list) {
    int i, j;
    Artist ** artists = list.artists;
    Artist * key = NULL;
    for (i = 0; i < list.artistNum; i++) {
        key = artists[i];
        j = i - 1;
        while (j >= 0 && strcmp(artists[j]->name, key->name) > 0) {
            artists[j + 1] = artists[j];
            j--;
        }
        artists[j + 1] = key;
    }
}


/*
 * Adds each artist to the sorted list
 */
void addArtistToList(ArtistList * list, Artist * artist) {

    // allocate new array of items
    Artist ** artists = (Artist **) calloc(list->artistNum + 1, sizeof (Artist*));
    int i;

    // copies the old object to the new array
    for (i = 0; i < list->artistNum; i++) {
        artists[i] = list->artists[i];
    }

    // appends artist to the last position
    artists[i] = artist;

    // frees the old array for the next cycle
    if (list->artists != NULL) {
        free(list->artists);
    }

    // update the list
    list->artists = artists;
    list->artistNum = list->artistNum + 1;
}

/*
 * Adds each artists songs to the sorted list
 */
void addSongToList(SongList * list, Song * song) {

    // allocates a new array of items
    Song ** songs = (Song **) calloc(list->songNum + 1, sizeof (Song*));
    int i;

    // copies the old object to the new array
    for (i = 0; i < list->songNum; i++) {
        songs[i] = list->songs[i];
    }

    // appends artist to the last position
    songs[i] = song;

    // frees up the old array for the next cycle
    if (list->songs != NULL) {
        free(list->songs);
    }

    // updates the list
    list->songs = songs;
    list->songNum = list->songNum + 1;
}


/*
 * Gets the duration of each song
 */
char * getDurationStartPosition(char * line) {

    /*
     * get the pointer to the first occurrence of sub string
     */
    char * ret = strstr(line, SUB_STRING);
    // get the end point of the current line
    const char * endPoint = line + strlen(line);
    //get start position of the duration
    char * duration = ret + strlen(SUB_STRING);
    char ch = *duration;

    while (duration < endPoint // it should not get out of bound, as the the first position should be a number
           && (ch < '0' || ch > '9')) {
        // otherwise move the start position of the sub string forward
        ret++;

        // find it again to restart the cycle for the next song
        ret = strstr(ret, SUB_STRING);
        duration = ret + strlen(SUB_STRING);
        ch = *duration;
    }
    //return the duration
    return duration;
}

/*
 * parses the duration of each song to its song in the sorted list
 */
Duration parseDuration(char * start) {
    Duration duration;
    /*
     * “Song duration” is in the form [m]m:ss, where [m]m denotes a
     * one- or two-digit number of minutes and ss denotes a two-digit number of seconds.
     */
    char * colon = start;
    // move to colon position
    while (*colon != ':') {
        colon++;
    }
    // get seconds
    duration.seconds = atoi(colon + 1);

    // mark the end of the string
    colon = '\0';
    // get minutes
    duration.minutes = atoi(start);

    // return the duration and parse it
    return duration;
}

/*
 * Parses each song to the sorted list
 */
Song * parseSong(char * line) {
    // allocate memory for a song
    Song * song = (Song*) malloc(sizeof (Song));

    // get start position of the duration
    char * durationStartPosition = getDurationStartPosition(line);
    // set up duration of the song
    song->duration = parseDuration(durationStartPosition);

    // set null to mark the end of song title
    durationStartPosition = durationStartPosition - strlen(SUB_STRING);
    *durationStartPosition = '\0';
    // allocate memory for title of song
    song->title = (char *) calloc(strlen(line) + 1, sizeof (char));
    // copy title to the song
    strcpy(song->title, line);

    // return the song and parse it
    return song;
}

/*
 * Reads in each song
 */
SongList readSongList(FILE * input, Artist * artist) {
    char line[DEFAULT_STRING_LENGTH];
    SongList list;
    list.songNum = 0;
    list.songs = NULL;
    Song * song;

    // read line from input stream
    while (fgets(line, DEFAULT_STRING_LENGTH, input)) {
        // clean the line
        removeNewLineCharacter(line);
        // stop when the line is empty
        if (strlen(line) == 0) {
            // stop at blank line
            break;
        }
        // get song
        song = parseSong(line);
        // set the artist
        song->artist = artist;
        // add the song to the current list
        addSongToList(&list, song);
    }
    //return the modified list
    return list;
}


/*
 * Sorts all the songs by titles
 */
void sortSongByTitle(SongList list) {
    int i, j;
    Song **songs = list.songs;
    Song *key = NULL;
    for (i = 0; i < list.songNum; i++) {
        key = songs[i];
        j = i - 1;
        while (j >= 0 && strcmp(songs[j]->title, key->title) > 0) {
            songs[j + 1] = songs[j];
            j--;
        }
        songs[j + 1] = key;
    }
}

/*
 * Reads in each artist
 */
Artist * readArtist(FILE * input) {
    char line[DEFAULT_STRING_LENGTH];
    Artist * artist = NULL;
    if (fgets(line, DEFAULT_STRING_LENGTH, input)) {
        removeNewLineCharacter(line);

        // while the input has a blank line at the end
        if (strlen(line) > 0) {
            // allocate new artist
            artist = (Artist*) malloc(sizeof (Artist));
            // allocate memory for the name artist
            artist->name = (char *) calloc(strlen(line) + 1, sizeof (char));
            // copy the name
            strcpy(artist->name, line);
            // read songs from input stream
            artist->songs = readSongList(input, artist);
            // sort song by title
            sortSongByTitle(artist->songs);
        }
    }
    //return the artist
    return artist;
}

/*
 * Reads the input data in its entirety
 */
ArtistList readData(FILE * input) {
    ArtistList list;
    list.artistNum = 0;
    list.artists = NULL;

    // read an artist
    Artist * artist = readArtist(input);

    // stop when there isn't any art ist
    while (artist != NULL) {
        // add it to the list
        addArtistToList(&list, artist);
        // read a new one
        artist = readArtist(input);
    }

    //Return the list of input
    return list;
}