#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "shuffle.h"

/*
 * this is a counter for each time a song appears
 */
int getSongNum(ArtistList all) {
    int i;
    Artist * artist;
    int counter = 0;

    //This will loop around each song and count it
    for (i = 0; i < all.artistNum; i++) {
        artist = all.artists[i];
        counter += artist->songs.songNum;
    }
    return counter;
}

/*
 * Get all songs from the list of artists
 */
SongList getAllSongs(ArtistList all) {
    int i;
    int j;
    SongList list;
    list.songNum = getSongNum(all);
    list.songs = (Song **) calloc(list.songNum + 1, sizeof (Song*));
    int index = 0;
    Artist * artist;

    // for each artist
    for (i = 0; i < all.artistNum; i++) {
        artist = all.artists[i];

        // for each song list of the artist
        for (j = 0; j < artist->songs.songNum; j++) {
            list.songs[index] = artist->songs.songs[j];
            index++;
        }
    }
    // get ending point of the list so we can use it in the random function
    list.songs[index] = NULL;
    return list;
}

/*
 * Shuffles all the songs using the Yates-Fisher algorithm
 */
void shuffleSong(SongList list) {

    int i, j;
    Song ** songs = list.songs;
    Song * song;
    srand(time(NULL));
    for (i = list.songNum - 1; i > 0; i--) {
        j = rand() % (i);
        song = songs[j];
        songs[j] = songs[i];
        songs[i] = song;
    }
}

/*
 * Resets the artists for the next time
 */
void resetArtists(ArtistList all) {
    int i;
    Artist * artist;
    for (i = 0; i < all.artistNum; i++) {
        artist = all.artists[i];
        artist->appearance = 0;
        artist->songsInRow = 0;
    }
}

/*
 * Gets the shuffled list according to the following constraints:
 *
 * An artiste cannot have more than two songs in a row (so no “triple play”,
 *  as the radio DJs might say);
 * An artiste cannot have more than three songs in total in the playlist;
 * A song cannot appear twice in the playlist;
 * The total playlist length should be as close as possible to one hour.
 * Specifically, the last song must start on or before 59:59.
 *
 */
SongList getSelectedList(SongList list) {
    Duration total;
    total.minutes = 0;
    total.seconds = 0;

    Song ** songs = list.songs;
    SongList selected;
    selected.songNum = 0;
    selected.songs = (Song **) calloc(list.songNum, sizeof (Song*));

    Artist * currentArtist = NULL;
    Song * song;
    // pointer to the current song
    Song ** ptr = list.songs;
    // move to the end of the list
    while (ptr != NULL
           // be sure that the playlist is closed to 1 hour
           && total.minutes <= LAST_CALL && total.seconds <= LAST_CALL) {

        // get the song
        song = ptr[0];

        // the artist if different
        if (song->artist != currentArtist) {
            selected.songs[selected.songNum] = song;
            selected.songNum++;
            song->artist->appearance++;
            song->artist->songsInRow = 1;
            ptr++;
            currentArtist = song->artist;
        }

        //The next two else if statements make sure the time constraint is met
        else if (currentArtist->appearance <= MAX_ARTIST_PER_PLAYLIST) {
            // move the ptr forward
            ptr++;
            song = NULL;
        }

        else if (currentArtist->songsInRow <= MAX_ARTIST_PER_ROW) {
            // run out of song to swap
            if (song == songs[list.songNum - 1]) {
                break;
            }
            // swap this song with the last song
            ptr[0] = songs[list.songNum - 1];
            songs[list.songNum - 1] = song;
            // no song is added to selected list
            song = NULL;
        }

        else {
            // otherwise, add song to selected list
            selected.songs[selected.songNum] = song;
            selected.songNum++;
            song->artist->appearance++;
            song->artist->songsInRow++;
            ptr++;
        }

        // Updates the playlist duration
        if (song != NULL) {
            total.seconds += song->duration.seconds;
            total.minutes += song->duration.minutes + (total.seconds / 60);
            total.seconds = total.seconds % 60;
        }
    }
    //Return the selected song
    return selected;
}

/*
 * Frees the memory after printing the shuffled playlist
 */
void freeArtistList(ArtistList all){
    int i;
    int j;
    Artist * artist;
    for (i = 0; i < all.artistNum; i++) {
        artist = all.artists[i];

        // free song data
        for (j = 0; j < artist->songs.songNum; j++) {
            free(artist->songs.songs[j]->title);
            free(artist->songs.songs[j]);
        }

        // free songs
        free(artist->songs.songs);
        // free artist
        free(artist);
    }
    // free array of artist
    free(all.artists);
}