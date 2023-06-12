#include "stdio.h"
#include "stdlib.h"

int main(int argc, char *argv[]) {

    FILE *file = fopen(argv[1], "r");
    FILE *ofd = fopen(argv[2], "w");

    // skip checks, fuck them
    fseek(file, 0, SEEK_END);
    int length = ftell(file);
    fseek(file, 0, SEEK_SET);
    unsigned char *wad_contents = malloc(sizeof(char) * length);
    fread(wad_contents, length, 1, file);
    fclose(file);


    fprintf(ofd, "\n\nunsigned char *wad_contents=\"");
    for (int jj=0; jj< length; jj++)
        fprintf(ofd, "\\x%02x",wad_contents[jj]);
    fprintf(ofd, "\";\n");
    fclose(ofd);
    exit(0);
}


