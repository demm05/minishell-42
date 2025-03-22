#include <dirent.h>
#include <stdio.h>

int main() {
    DIR *dir;
    struct dirent *entry;
    
    dir = opendir(".");  // Open current directory
    if (!dir) {
        perror("opendir");
        return 1;
    }
    
    // Read each entry and skip those starting with '.'
    while ((entry = readdir(dir)) != NULL) {
        // Skip hidden files (those starting with '.')
        if (entry->d_name[0] != '.') {
            printf("%s\n", entry->d_name);
        }
    }
    
    closedir(dir);
    return 0;
}
