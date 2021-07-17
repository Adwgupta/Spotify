/*
 * C Program that produces a randomised set of songs from a longer list entered as input
 * using the following constraints:
      1) The program takes its input from a file specified as an argument to the program.
         If the file does not exists or is not readable, the program prints out an error message to this effect.
         If no file is specifed, the program searches in the current directory for a file called artistes+songs.txt.
         If no such file exists, it prompts the user to enter the artistes and songs information from the keyboard
         according to the specified format.

      2) Sort the playlist without using bubble/exchange sort
      3) Shuffle the playlist with the following constraints:
            i,    An artiste cannot have more than two songs in a row (so no “triple play”, as the radio DJs might say);
            ii,   An artiste cannot have more than three songs in total in the playlist,
            iii,  A song cannot appear twice in the playlist;
            iv,   The total playlist length should be as close as possible to one hour.
            v,    Specifically, the last song must start on or before 59:59.


 *
 * Author:           Adityaa Gupta
 * Student Number:   20324976
 */

#include <stdio.h>
#include "sort.h"
#include "shuffle.h"
#include "print_sort.h"
#include "print_shuffle.h"
#include "boringText.h"


int main(int argc, char const *argv[]) {
    //creates an input fil
    FILE * inputFile =  NULL;

    /*
     * A call to the struct "artistList" in utilities library
     * This keyword all, will be used to read in & store input from the input file
     */
    ArtistList all;

    //If the user gives a file specified as an argument to the program, it will be opened
    if (argc > 1) {
        inputFile = fopen(argv[1], "r");
    }

    //If the user doesnt specify a file, the default file of "artistes+songs.txt" will be opened
    else if (argc < 1) {
        inputFile = fopen(DEFAULT_INPUT_FILE, "r");
    }

    //If no such file exists,
    if (inputFile == NULL) {
       
        //Reads and stores the user's input into the struct all
        all = readData(stdin);
    }

    //If the file exists, the file is read using the following function
    else {
        //Reads and store's the specified file's contents into the struct all
        all = readData(inputFile);
        //Closes the file
        fclose(inputFile);
    }

   /*
    * function calls to sort and shuffle the input
    * then print the modified input
    * and finally free the allocated memory
         
   sort the input  */
   sortArtistByName(all);
   //Print the sorted input
   printSortedList(all);
   //print the shuffled input after shuflling
   printRandomList(all);
   //free's any allocated memory
   freeArtistList(all);
   endCredits(*);
   return (0);
}