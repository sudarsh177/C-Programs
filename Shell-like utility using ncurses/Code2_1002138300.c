/*

Sudarshan Potdar
1002138300
Assignment 2


*/



#include <sys/types.h>      // including all libraries
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <time.h>
#include <ncurses.h>

void selection_display(WINDOW *win);                               // declaring all functions
void list_options(WINDOW *win, int num, int type, int offset);
void change_directory(WINDOW *win);
void execute_file(WINDOW *win);

int main() 
{
    initscr();
    start_color();
 
    cbreak();
    noecho();
    curs_set(0);

    int ymax, xmax;                          // declaring size of window
    getmaxyx(stdscr, ymax, xmax);
     
    WINDOW *win = newwin(ymax-4, xmax-4, 2, 2);           // creating a window
    keypad(win, TRUE);
    box(win, '|', '-');

    int selection;
    int file_count = 0;
    int directory_count = 0;

    while (1) 
    {
        selection_display(win);
        
        wprintw(win, "\nEnter your choice from the menu: ");               

        wrefresh(win);
        selection = wgetch(win) - '0';

        switch (selection)                       // switch case statements execute based on users input
        {
            case 1:
                list_options(win, 10, DT_REG, file_count);              // list 10 files
                break;
            case 2:
                list_options(win, 10, DT_DIR, directory_count);           // list 10 directories
                break;
            case 3:
                change_directory(win);                                 // change directory
                break;
            case 4:
                execute_file(win);                          // execute a file
                break;
            case 5:
                file_count += 10;
                list_options(win, 10, DT_REG, file_count);           // display next 10 files
                break; 
            case 6:
                directory_count += 10;
                list_options(win, 10, DT_DIR, directory_count);         // display next 10 directories
                break;
            case 7:
                wclear(win);
                box(win, '|', '-');                                   // restart the window
                break;
            case 8:
                endwin();
                exit(0);                                             // terminate the operation 
            default:
                mvwprintw(win, ymax-6, 2, "Invalid selection!");
                break;
        }

        wprintw(win, "\nEnter any key to continue...\n");         // asking user to input a character a character to continue
        wgetch(win);
        wclear(win);
        box(win, '|', '-');
    }

    endwin();
    return 0;
}

void selection_display(WINDOW *win) 
{
    wclear(win);
    box(win, '|', '-');
                                                                          // displaying all options
    time_t t = time(NULL);
    mvwprintw(win, 1, 2, "It is now: %s", ctime(&t));
    mvwprintw(win, 3, 2, "1. List 10 file names");
    mvwprintw(win, 4, 2, "2. List 10 directory names");
    mvwprintw(win, 5, 2, "3. Change directory");
    mvwprintw(win, 6, 2, "4. Run file");
    mvwprintw(win, 7, 2, "5. Next 10 file entries");
    mvwprintw(win, 8, 2, "6. Next 10 directory entries");
    mvwprintw(win, 9, 2, "7. Refresh/rerun");
    mvwprintw(win, 10, 2, "8. Exit");
    
    wrefresh(win);
}

void list_options(WINDOW *win, int num, int type, int offset) 
{
    DIR *d = opendir(".");
    struct dirent *de;
    int count = 0;
    int y, x;                                               // function to list 10 files and directories
    getyx(win, y, x);

    while ((de = readdir(d)) && count < num + offset) 
    {
        if (de->d_type == type) 
        {
            if (count >= offset)
            {
                mvwprintw(win, y++, 2, "%s", de->d_name);
            }
            count++;
        }
    }
    closedir(d);
    wrefresh(win);
}

void change_directory(WINDOW *win)                        // function to change directory
{
    char path[256];
    echo();
    mvwprintw(win, 12, 2, "Enter directory path: ");
    wgetstr(win, path);
    noecho();

    if (chdir(path) != 0) 
    {
        mvwprintw(win, 14, 2, "Error changing directory.");
    }
    wrefresh(win);
}

void execute_file(WINDOW *win)                    // execute a file
{
    char cmd[256];
    echo();
    mvwprintw(win, 12, 2, "Enter file/command to run: ");
    wgetstr(win, cmd);
    noecho();
    
    system(cmd);
    mvwprintw(win, 14, 2, "Executed: %s", cmd);
    wrefresh(win);
}