#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

int main()
{
    int fd, fd1;
    char *myfifo = "myfifo";
    char *myfifo1 = "myfifo1";
    char buf[1024], ch[400];

    int words = 0, character = 0, line = 0, i = 0, j = 0;
    FILE *fp;

    // Create the named pipe (FIFO)
    mkfifo(myfifo1, 0777);  // This creates the second FIFO pipe with full access permissions

    // Open the first FIFO for reading
    fd = open(myfifo, O_RDONLY);
    if (fd == -1) {
        perror("Error opening FIFO for reading");
        return 1;
    }
    
    // Read the data from FIFO
    read(fd, buf, 1024);
    printf("\nFirst message received: \n\n%s\n\n", buf);
    
    // Counting words, lines, and characters
    while (buf[i] != '\0') {
        // Skip spaces to count words
        while (buf[i] == ' ' || buf[i] == '\n') {
            if (buf[i] == ' ') words++;
            if (buf[i] == '\n') line++;
            i++;
        }
        
        // If the character is a non-space, increment word count and character count
        if (buf[i] != ' ' && buf[i] != '\n' && buf[i] != '\0') {
            words++;
            character++;
        }
        
        i++; // Increment character pointer
    }
    
    // Adjust for the final line (since last line might not have a newline)
    if (buf[i-1] != '\n') line++;

    printf("\nTotal Words := %d\n", words);
    printf("\nTotal Lines := %d\n", line);
    printf("\nTotal Characters := %d\n", character);

    // Write the results to a file
    fp = fopen("test.txt", "w+");
    if (fp == NULL) {
        perror("Error opening file for writing");
        return 1;
    }
    
    fprintf(fp, "\nTotal Words := %d\n", words);
    fprintf(fp, "\nTotal Lines := %d\n", line);
    fprintf(fp, "\nTotal Characters := %d\n", character);
    fclose(fp);

    // Read the content of the file and store it in 'ch'
    fp = fopen("test.txt", "r");
    if (fp == NULL) {
        perror("Error opening file for reading");
        return 1;
    }
    
    while ((ch[j] = fgetc(fp)) != EOF) {
        j++;
    }
    ch[j] = '\0';  // Null-terminate the string
    fclose(fp);

    // Close the first FIFO
    close(fd);

    // Unlink the first FIFO after use
    unlink(myfifo);

    // Open the second FIFO for writing
    fd1 = open(myfifo1, O_WRONLY);
    if (fd1 == -1) {
        perror("Error opening second FIFO for writing");
        return 1;
    }

    // Write the content of 'ch' to the second FIFO
    write(fd1, ch, strlen(ch));
    
    // Close the second FIFO
    close(fd1);

    return 0;
}
