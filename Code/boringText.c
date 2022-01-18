#include <stdio.h>
#include "boringText.h"


void preCredits() {
   puts("No such file exists...\nYou are required to manually enter the list of artists their respective songs.\n");
   puts("Please note the following:\n\t1) When entering information line by line press enter 3 times to indicate the end of input.");
   puts("\t2) Input must be in the following format:\n\t\tArtiste name\n\t\tSong title***Song duration\n\t\t...\n\t\tSong title***Song duration\n\t\t<blank line>");
   puts("\t\tArtiste name\n\t\tSong title***Song duration\n\t\t...\n\t\tSong title***Song duration\n\t\t<blank line>\n\t\t...");
   puts("\n\t3) An artist's names must be separated by their first song by a single new line\n\t   Song durations must be separated by song titles by \"***\", but on the same line as their respective song");
   puts("\t   A new song must be separated by the last by a single new line\n\t   and a new artist must be separated by a blank line (2 new lines)");
   puts("\nPlease enter artistes and songs information from the keyboard now:\n");
}

void endCredits() {
   puts("Enjoy your music");
}
