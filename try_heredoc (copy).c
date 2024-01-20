#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[]) {
    // Check if the delimiter argument is provided
    if (argc < 2) {
        printf("Usage: ./heredoc <delimiter>\n");
        return 1;
    }

    // Open the temporary file for writing
    FILE *tempFile = open("temp.txt", O_RDWR);
    if (tempFile == NULL) {
        perror("Error opening temporary file");
        return 1;
    }

    // Prompt the user for heredoc content
    printf("Enter the heredoc content (end with the delimiter '%s'):\n", argv[1]);

    // Read the heredoc content from the user and write it to the temporary file
    char *line;
    while (1) 
	{
        line = readline("> ");
        // Check if the delimiter is entered
        if (strcmp(line, argv[1]) == 0) {
            break;
        }
        // Write the line to the temporary file
        fprintf(tempFile, "%s\n", line);
		// append
    }

    // Close the temporary file
    fclose(tempFile);

    // Open the temporary file for reading
    tempFile = fopen("temp.txt", "r");
    if (tempFile == NULL) {
        perror("Error opening temporary file");
        return 1;
    }

    // Read the heredoc content from the temporary file
    printf("Heredoc content:\n");
    while (fgets(line, sizeof(line), tempFile) != NULL) {
        // Process each line of the heredoc content
        printf("%s", line);
    }

    // Close the temporary file
    fclose(tempFile);

    // Delete the temporary file
    if (remove("temp.txt") != 0) {
        perror("Error deleting temporary file");
        return 1;
    }

    return 0;
}