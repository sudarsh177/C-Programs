#include <stdio.h>   // Declaring libraries
#include <string.h>
#include <stdlib.h>

#define ROWS 15  // Change this to the number of rows in your 2D array
#define COLUMNS 6  // Change this to the number of columns in your 2D array

#ifdef PRINTARRAY  
void display_output(char text[ROWS][COLUMNS]) {
    for (int a = 0; a < ROWS; a++) {
        for (int b = 0; b < COLUMNS; b++) {
            printf("%c ", text[a][b]);
        }
        printf("\n");
    }
}
#endif

int main(int no_arg, char *cmd[])   // Reading the Command-Line Parameters
{
    if (no_arg == 1) 
    {
        printf("An input file name must be given on the command line\n");       
        exit(0);
    }
    else if (no_arg > 2)
    {
        printf("Invalid argument!\n");
        exit(0);
    }    
    
    char inputfile[25];   // Giving the same names for Input and Output files and changing the extension for Output File 
    char outputfile[25];
    strcpy(inputfile, cmd[1]); 
    strcpy(outputfile, cmd[1]);
    int len = strlen(outputfile);
    outputfile[len-4] = '.';
    outputfile[len-3] = 'o';
    outputfile[len-2] = 'u';
    outputfile[len-1] = 't';

    FILE *input = fopen(inputfile, "r");     // Opening the input and output files in read and write modes respecctively
    FILE *output = fopen(outputfile, "w");

    if (input == NULL || output == NULL)   // Displaying the error message and exiting the program if Files fail to open
    {
        printf("Unable to open file %s\n",inputfile);
        exit(0);
    }

    char entries[50];
    char ascii[ROWS][COLUMNS] = {};  // 2D array initialization

    int last_line = 0; // Reading lines
    while (1) 
    {
    if (last_line) {
        break;  
    }

    if (!fgets(entries, sizeof(entries), input)) 
    {
        break;  
    }

    
    char peek = fgetc(input);
    if (peek == EOF) {
        last_line = 1; 
    }

    ungetc(peek, input);  

    int ascii_sum = 0;
    for (int a = 0; entries[a] != '\0' && a < sizeof(entries); a++)  // calculating ascii sum of line
    {
        ascii_sum += entries[a];
        // printf("%d ", entries[a]);
    }        

    if (!last_line) 
    {
        ascii_sum -= 23;
    }

    int rows = ascii_sum % ROWS;
    int columns = ascii_sum % COLUMNS;    
    char ascii_eq = 33 + (ascii_sum % 94);  // ASCII value between 33 and 126
    // printf("%c ",ascii_eq);
    // printf("= %d \n", ascii_sum);              
    ascii[rows][columns] = ascii_eq;
    }        

    for (int i = 0; i < ROWS; i++)     
    {
    for (int j = 0; j < COLUMNS; j++)    // feeding values into the 2D array
        {
            if (ascii[i][j] >= 33 && ascii[i][j] <= 126) 
            {
                fputc(ascii[i][j], output);
            }
        }
    }  

    #ifdef PRINTARRAY
    display_output(ascii);  // display Output if PRINTARRAY is passed in arguments
    #endif

    fclose(input);
    fclose(output);   
}    