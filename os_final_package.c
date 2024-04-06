#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#include <unistd.h>

#include <sys/types.h>

#include <sys/wait.h>

#include <readline/readline.h>

#include <readline/history.h>

#include <time.h>

#include <dirent.h>

#include <sys/stat.h>



#define MAXCOM 1000

#define MAXLIST 100



void init_shell() {

    printf("\n\n\n\n******************"

           "************************");

    printf("\n\n\n\t****MY SHELL****");

    printf("\n\n\t-USE AT YOUR OWN RISK-");

    printf("\n\n\n\n*******************"

           "***********************");

    char *username = getenv("USER");

    printf("\n\n\nUSER is: @%s", username);

    printf("\n");

    sleep(1);

    system("clear");

}



int takeInput(char *str) {

    char *buf = readline("\n>>> ");

    if (strlen(buf) != 0) {

        add_history(buf);

        strcpy(str, buf);

        free(buf);

        return 0;

    } else {

        return 1;

    }

}



void printDir() {

    char cwd[1024];

    getcwd(cwd, sizeof(cwd));

    printf("\nDir: %s", cwd);

}



// n frequently used frequent for



// frequently used command

// function

void frequent_command(int num) {

    FILE *hist_file = fopen("example.txt", "a");

    if (hist_file == NULL) {

        perror("Error opening file");

        return;

    }



    // Write command history to file

    HIST_ENTRY *entry;

    for (int i = history_base; i < history_length; i++) {

        entry = history_get(i);

        if (entry != NULL) {

            fprintf(hist_file, "%s\n", entry->line);

        }

    }

    //free_history_entry(entry);

    fclose(hist_file);

    char command[200];

    // Print most frequently used command

    sprintf(command, "sort %s | uniq -c | sort -nr | awk '{$1=\"\"; print $0}' | head -n %d", "example.txt", num);



    system(command);

}

void execArgs(char **parsed, int background) {

    pid_t pid = fork();

    if (pid == -1) {

        printf("\nFailed forking child..");

        return;

    } else if (pid == 0) {

        if (execvp(parsed[0], parsed) < 0) {

            printf("\nCould not execute command..");

        }

        exit(0);

    } else {

        if (!background) {

            wait(NULL);

        }

        return;

    }

}



void openHelp() {



    puts("\n***WELCOME TO MY SHELL HELP***"



         "\n-USE THE SHELL AT YOUR OWN RISK-"



         "\nList of Commands supported:"



         "\n>help"



         "\n>exit" "\t\t\t\t\t\t --Exits from the shell"



         "\n>cd,change_directory [path]" "\t\t\t --Changes the current directory"



         "\n>date" "\t\t\t\t\t\t --prints the date"



         "\n>man,manual [command]" "\t\t\t\t--prints the manual for a particular command"



         "\n>list_files,ls " "\t\t\t\t\t--Lists the files in current directory"



         "\n>create_directory,make_directory,mkdir [directory]" "\t\t--Creates a new directory"



         "\n>remove_directory,rmdir [directory]" "\t\t--Removes the specified directory"



         "\n>list_all_files" "\t\t\t\t\t--Lists all files in the current directory (including hidden files)"



         "\n>list_files_recursively" "\t\t\t\t--Lists the files recursively(including all files in the subdirectory)"



         "\n>create_file [file]" "\t\t\t\t--Creates a New file"



         "\n>append_to_file [file]" "\t\t\t\t--Appends the content at the end of the given file"



         "\n>word_count [directory]" "\t\t\t\t--Prints the total number of files and directories within the given directory"



         "\n>count_file [file_extension]" "\t\t\t-- counts the no of files with the given extension"



         "\n>count_nullfile" "\t\t\t\t\t--Counts all the null files"



         "\n>numbered_cat [file]" "\t\t\t\t--Prints all the content of the file with line numbers"



         "\n>move,mv [source] [destination]" "\t\t\t--Moves the file to the new destination"



         "\n>rm,remove [file]" "\t\t\t\t--Removes the gives file"



         "\n>copy,cp [source] [destination]" "\t\t\t--Copies the file from source to destination"



         "\n>list_with_inode" "\t\t\t\t--Lists the files with inode"



         "\n>echo [content to display]" "\t\t\t--Displays the specified content"



         "\n>head,first [n] [file]" "\t\t\t\t--Prints the first n lines in the given file"



         "\n>tail,last [n] [file]"  "\t\t\t\t--Prints the last n lines in the given file"



         "\n>install (Homebrew)"

         "\n>update  (Homebrew)"



         "\n>frequent_command [n]" "\t\t\t\t-- prints the 1st n frequently used commands"



         "\n>first_n_lines [file] [number of lines]" "\t\t-- prints the 1st n lines of the given file"



         "\n>last_n_lines [file] [number of lines]" "\t\t-- prints the last n lines of the given file"



   );



    return;



}





int ownCmdHandler(char **parsed) {

    if (strcmp(parsed[0], "exit") == 0) {

        printf("\nGoodbye\n");

        exit(0);

    } else if (strcmp(parsed[0], "help") == 0) {

        openHelp();

        return 1;

    } else if (strcmp(parsed[0], "cd") == 0 || strcmp(parsed[0], "change_directory") == 0) {

        if (parsed[1] == NULL)

            chdir(getenv("HOME"));

        else

            chdir(parsed[1]);

        return 1;

    } else if (strcmp(parsed[0], "date") == 0) {

        time_t t;

        time(&t);

        printf("Current time: %s", ctime(&t));

        return 1;

    } else if (strcmp(parsed[0], "manual") == 0 || strcmp(parsed[0], "man") == 0) {

        // Provide manual for the command

        if (parsed[1] != NULL) {

            char command[200],command_name[100];

            strcpy(command_name,parsed[1]);

            sprintf(command, "man %s", command_name);



        // Execute the command using the system function

            system(command);



        } else {

            printf("Usage: manual [command]\n");

        }

        return 1;

    } else if (strcmp(parsed[0], "list_files") == 0 || strcmp(parsed[0], "ls") == 0) {

        // List files in current directory

        DIR *d;

        struct dirent *dir;

        d = opendir(".");

        if (d) {

            while ((dir = readdir(d)) != NULL) {

                printf("%s\n", dir->d_name);

            }

            closedir(d);

        }

        return 1;

    } else if (strcmp(parsed[0], "create_directory") == 0 || strcmp(parsed[0], "mkdir") == 0 || strcmp(parsed[0], "make_directory") ==

0) {

        // Create directory

        if (parsed[1] != NULL) {

            if (mkdir(parsed[1], 0777) == -1)

                perror("mkdir");

        } else {

            printf("Usage: create_directory [dirname]\n");

        }

        return 1;

    } else if (strcmp(parsed[0], "remove_directory") == 0 || strcmp(parsed[0], "rmdir") == 0) {

        // Remove directory

        if (parsed[1] != NULL) {

            if (rmdir(parsed[1]) == -1)

                perror("rmdir");

        } else {

            printf("Usage: remove_directory [dirname]\n");

        }

        return 1;

    } else if (strcmp(parsed[0], "list_all_files") == 0) {

        // List all files including hidden files

        system("ls -a");

        return 1;

    } else if (strcmp(parsed[0], "list_files_recursively") == 0) {

        // List files recursively

        system("ls -R");

        return 1;

    } else if (strcmp(parsed[0], "create_file") == 0) {

        // Create file

        if (parsed[1] != NULL) {            FILE *fp;

            fp = fopen(parsed[1], "w");

            if (fp != NULL) {

                fclose(fp);

                printf("File %s created successfully.\n", parsed[1]);

            } else {

                perror("fopen");

            }

        } else {

            printf("Usage: create_file [filename]\n");

        }

        return 1;

    }else if (strcmp(parsed[0], "word_count") == 0){

        if(parsed[1]==NULL)

        {

                printf("Printing the total no of files and directories\n");

                system("ls | wc -l");

        }

        else if(parsed[1]!=NULL)

        {

                char file[100];

                strcpy(file, parsed[1]);

                char command[200];  // Define a buffer for the command

                sprintf(command, "cat %s | wc -w", file);  // Create the command string

                system(command);

        }

        else {

            printf("Usage: word_count [directoryname]\n");

        }

        return 1;

    } else if (strcmp(parsed[0], "append_to_file") == 0) {

        // Append to file

        if (parsed[1] != NULL) {

            FILE *fp;

            fp = fopen(parsed[1], "a");

            if (fp != NULL) {

                char buffer[1024];

                printf("Enter text to append (Ctrl+D to end):\n");

                while (fgets(buffer, sizeof(buffer), stdin) != NULL) {

                    fputs(buffer, fp);

                }

                fclose(fp);

            } else {

                perror("fopen");

            }

        } else {

            printf("Usage: append_to_file [filename]\n");

        }

        return 1;

    }else if (strcmp(parsed[0], "count_file") == 0){



        if(parsed[1]==NULL)



        {



                printf("Printing the total no of files \n");



                system("ls -p | grep -v / | wc -l");



        }



        else if(parsed[1]!=NULL)



        {



                char file[100];



                strcpy(file, parsed[1]);



                char command[200];  // Define a buffer for the command



                sprintf(command, "ls *%s | wc -w", file);  // Create the command string



                system(command);



        }



        else {



            printf("Usage: count_file [file_extension]\n");



        }



        return 1;



    }else if (strcmp(parsed[0],"count_nullfile")==0){

        if(parsed[1]==NULL)

        {

                printf("Printing the total no of null files and directories\n");

                system("find . -type f -empty | wc -l");

        }

        else {

            printf("Usage: count_nullfile\n");

        }

        return 1;

       } else if (strcmp(parsed[0], "numbered_cat") == 0) {

        // Numbered cat

        if (parsed[1] != NULL) {

            FILE *fp;

            fp = fopen(parsed[1], "r");

            if (fp != NULL) {

                char buffer[1024];

                int line_num = 1;

                while (fgets(buffer, sizeof(buffer), fp) != NULL) {

                    printf("%d %s", line_num++, buffer);

                }

                fclose(fp);

            } else {

                perror("fopen");

            }

        } else {

            printf("Usage: numbered_cat [filename]\n");

        }

        return 1;

    } else if (strcmp(parsed[0], "move") == 0 || strcmp(parsed[0], "mv")==0) {

        // Move file or directory

        if (parsed[1] != NULL && parsed[2] != NULL) {

            if (rename(parsed[1], parsed[2]) == -1)

                perror("rename");

        } else {

            printf("Usage: move [source] [destination]\n");

        }

        return 1;

    } else if (strcmp(parsed[0], "remove") == 0 || strcmp(parsed[0], "rm") == 0) {

        // Remove file

        if (parsed[1] != NULL) {

            if (remove(parsed[1]) == -1)

                perror("remove");

        } else {

            printf("Usage: remove [filename]\n");

        }

        return 1;

    } else if (strcmp(parsed[0], "copy") == 0 || strcmp(parsed[0], "cp") == 0) {

        // Copy file

        if (parsed[1] != NULL && parsed[2] != NULL) {

            FILE *source, *target;

            char ch;

            source = fopen(parsed[1], "r");

            if (source == NULL) {

                perror("fopen");

                return 1;

            }

            target = fopen(parsed[2], "w");

            if (target == NULL) {

                fclose(source);

                perror("fopen");

                return 1;

            }

            while ((ch = fgetc(source)) != EOF) {

                fputc(ch, target);

            }

            fclose(source);

            fclose(target);

            printf("File copied successfully.\n");

        } else {

            printf("Usage: copy [source] [destination]\n");

        }

        return 1;

    } else if (strcmp(parsed[0], "list_with_inode") == 0) {

        // List files with inode

        system("ls -l -i");

        return 1;

    } else if (strcmp(parsed[0], "echo") == 0) {

        // Echo command

        for (int i = 1; parsed[i] != NULL; i++) {

            printf("%s ", parsed[i]);

        }

        printf("\n");

        return 1;

    }  else if (strcmp(parsed[0], "head") == 0 || strcmp(parsed[0], "first") == 0) {

        // Head command

        if (parsed[2] != NULL) {

            FILE *fp;

            fp = fopen(parsed[2], "r");

            if (fp != NULL) {

                char buffer[1024];

                int lines = atoi(parsed[1]); // default number of lines to display

                int count = 0;

                while (fgets(buffer, sizeof(buffer), fp) != NULL && count < lines) {

                    printf("%s", buffer);

                    count++;

                }

                fclose(fp);

            } else {

                perror("fopen");

            }

        } else {

           printf("Usage: head [n] [filename]\n");

        }

        return 1;

    } else if (strcmp(parsed[0], "tail") == 0 || strcmp(parsed[0], "last") == 0) {

        // Tail command

        if (parsed[2] != NULL) {

            FILE *fp;

            fp = fopen(parsed[2], "r");

            if (fp != NULL) {

                char buffer[1024][1024]; // store last 1024 lines

                int lines = atoi(parsed[1]); // default number of lines to display

                int count = 0;

                int total_lines = 0;

                while (fgets(buffer[total_lines % 1024], sizeof(buffer[0]), fp) != NULL) {

                    total_lines++;

                }

                fclose(fp);

                int start = total_lines > lines ? total_lines - lines : 0;

                for (int i = start; i < total_lines; i++) {

                    printf("%s", buffer[i % 1024]);

                }

            } else {

                perror("fopen");

            }

        } else {

            printf("Usage: tail [n] [filename]\n");

        }

        return 1;

    } else if (strcmp(parsed[0], "touch") == 0) {

        // Touch command

        if (parsed[1] != NULL) {

            FILE *fp;

            fp = fopen(parsed[1], "w");

            if (fp != NULL) {

                fclose(fp);

                printf("File %s created.\n", parsed[1]);

            } else {

                perror("fopen");

            }

        } else {

            printf("Usage: touch [filename]\n");

        }

        return 1;

    } else if (strcmp(parsed[0], "sort") == 0) {

        // Sort command

        if (parsed[1] != NULL) {

            system("sort -o sorted.txt parsed[1]");

        } else {

            printf("Usage: sort [filename]\n");

        }

        return 1;

    } else if (strcmp(parsed[0], "diff") == 0) {

        // Diff command

        if (parsed[1] != NULL && parsed[2] != NULL) {

            system("diff parsed[1] parsed[2]");

        } else {

            printf("Usage: diff [file1] [file2]\n");

        }

        return 1;

    } else if (strcmp(parsed[0], "paste") == 0) {

        // Paste command

        if (parsed[1] != NULL && parsed[2] != NULL) {

            system("paste parsed[1] parsed[2]");

        } else {

            printf("Usage: paste [file1] [file2]\n");

        }

        return 1;

    } else if (strcmp(parsed[0], "install") == 0) {

        // Install package using Homebrew

        if (parsed[1] != NULL) {

            char command[100];

            sprintf(command, "brew install %s", parsed[1]);

            system(command);

        } else {

            printf("Usage: install [package]\n");

        }

        return 1;

    } else if (strcmp(parsed[0], "update") == 0) {

        // Update all installed packages using Homebrew

        system("brew update && brew upgrade");

        return 1;

    }else if (strcmp(parsed[0], "print_file") == 0){



       if(parsed[1]!=NULL)



        {



                char file[100];



                strcpy(file, parsed[1]);



                char command[200];  // Define a buffer for the command

                sprintf(command, "ls *%s", file);  // Create the command string



                system(command);



        }



        else {



            printf("Usage: print_file [file_extension]\n");



        }



        return 1;



    } else if (strcmp(parsed[0], "frequent_command") == 0){



       if(parsed[1]==NULL)



        {



                frequent_command(1);



        }

        else if(parsed[1]!=NULL)

        {

                int n;

                n=atoi(parsed[1]);

                frequent_command(n);

        }

         else {

            printf("Usage: frequent_command [n]\n");

        }

        return 1;



    }else if(strcmp (parsed[0],"first_n_lines")==0){

        if(parsed[1]!=NULL && parsed[2]!=NULL)

        {

                int num=atoi(parsed[2]);

                char file[100];

                strcpy(file, parsed[1]);

                char command[200];  // Define a buffer for the command

                sprintf(command, "head -n %d %s > first_n_lines.txt",num, file);  // Create the command string



                system(command);

        }else if(parsed[1]!=NULL && parsed[2]==NULL){



                char file[100];

                strcpy(file, parsed[1]);

                char command[200];  // Define a buffer for the command

                sprintf(command, "head -n 10 %s > first_10_lines.txt", file);  // Create the command string



                system(command);

        }



        else {

            printf("Usage: first_n_lines [filename] [num]\n");

        }

        return 1;

    }else if(strcmp (parsed[0],"last_n_lines")==0){

        if(parsed[1]!=NULL && parsed[2]!=NULL)

        {

                int num=atoi(parsed[2]);

                char file[100];

                strcpy(file, parsed[1]);

                char command[200];  // Define a buffer for the command

                sprintf(command, "tail -n %d  %s > last_n_lines.txt",num, file);  // Create the command string



                system(command);

        }

        else if(parsed[1]!=NULL)

        {

                char file[100];

                strcpy(file, parsed[1]);

                char command[200];  // Define a buffer for the command

                sprintf(command, "tail -n 10  %s > last_10_lines.txt", file);  // Create the command string



                system(command);

        }



        else {

            printf("Usage: last_n_lines [filename]\n");

        }

        return 1;

    }

    return 0;

}



void parseSpace(char *str, char **parsed) {

    int i;

    for (i = 0; i < MAXLIST; i++) {

        parsed[i] = strsep(&str, " ");

        if (parsed[i] == NULL)

            break;

        if (strlen(parsed[i]) == 0)

            i--;

    }

}



int processString(char *str, char **parsed) {

    parseSpace(str, parsed);

    if (ownCmdHandler(parsed))

        return 0;

    return 1;

}



int main() {

    char inputString[MAXCOM], *parsedArgs[MAXLIST];

    int execFlag = 0;

    init_shell();

    while (1) {

        printDir();

        if (takeInput(inputString))

            continue;

        execFlag = processString(inputString, parsedArgs);

        if (execFlag == 1) {

            int background = 0;

            for (int i = 0; parsedArgs[i] != NULL; i++) {

                if (strcmp(parsedArgs[i], "&") == 0) {

                    background = 1;

                    parsedArgs[i] = NULL;

                    break;

                }

            }

            execArgs(parsedArgs, background);

        }

    }

    return 0;

}






