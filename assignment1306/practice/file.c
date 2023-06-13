#include <stdio.h>
#include <dirent.h>


int main(){
    DIR *dir = opendir(".");
    struct dirent *entry;

    while ((entry = readdir(dir)) != NULL)
    {
        if(entry->d_type == 8){
            printf("%s\n", entry->d_name);
        }
    }

    closedir(dir);

    return 0;
    
}