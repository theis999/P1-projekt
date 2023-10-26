#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "csvRead.h"
#define HOURS_PER_YEAR 8760


Datapoint* readCSV(char *filename)
{
    FILE *fh = fopen(filename, "r");

    // Uninitialized buffer to input the rows to.
    char buffer[1024];
    int row = 0;
    int column;
    // Allocation of the Datapoint-array, with the expected amounts of rows as the number of elements.
    Datapoint *data = malloc(HOURS_PER_YEAR*sizeof(Datapoint));

    // While-loop that goes through each line of the .csv-file and writes it to buffer[].
    while (fgets(buffer, 1024, fh) && row<9000)
    {
        column = 0;
        
        // Tokenizes buffer with ',' as the delimiter.
        char *tok = strtok(buffer, ",");
        
        /* Remove this comment if the first row does not contain data.
        if (row == 0) {
            continue;
        }
        */

        // Keep going as long as a new token is found.
        while (tok)
        {
            
            if (column == 0)
            {
                int year;
                int month;
                int day;
                int hours;
                int minutes;
                int seconds;

                // Struct containing member that represent a date and time.
                tm datetime;
                
                // Parse the first column of the line to the tm struct.
                sscanf(tok, "%d-%d-%d %d:%d:%d", &year, &month, &day, &hours, &minutes, &seconds);
                datetime.tm_year = year - 1900;
                datetime.tm_mon = month - 1;
                datetime.tm_mday = day;
                datetime.tm_hour = hours;
                datetime.tm_min = minutes;
                datetime.tm_sec = seconds;
                datetime.tm_isdst = -1;
                
                // Convert the tm struct to seconds since epoch.
                data[row].datetime = mktime(&datetime);
                // If the first row does not contain data use this instead:
                //data[row-1].datetime = mktime(&datetime);                
            }

            if (column == 4)
            {
                data[row].ci_direct = strtod(tok, NULL);
                // If the first row does not contain data use this instead:
                //data[row-1].ci_direct = strtod(tok, NULL);                
                
            }
            if (column == 5)
            {
                data[row].ci_lca = strtod(tok, NULL);
                // If the first row does not contain data use this instead:                
                //data[row-1].ci_lca = strtod(tok, NULL);
            }
            if (column == 6)
            {

                data[row].low_percent = strtod(tok, NULL);
                // If the first row does not contain data use this instead:
                //data[row-1].low_percent = strtod(tok, NULL);
                
            }
            if (column == 7)
            {
                data[row].renew_percent = strtod(tok, NULL);
                // If the first row does not contain data use this instead:
                //data[row-1].renew_percent = strtod(tok, NULL);
            }
            
            column++;

            // Find the next token on the line.
            tok = strtok(NULL, ",");
        } 
            
        row++;
    }

fclose(fh);
return data;
}
