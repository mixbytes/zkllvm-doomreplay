#include <stdio.h>
#include <stdlib.h>

#include "zkldoom/w_file.h"
#include "zkldoom/w_wad.h"


void bufread(unsigned char * buf, unsigned int offset, unsigned int buffer_len, unsigned char *dest) {
    for (int i = offset; i < offset+buffer_len; i++) {
        dest[i - offset] = buf[i];
    }
    return;
}                    

int main(int argc, char *argv[]) {

    FILE *file = fopen(argv[1], "r");

    // skip checks, fuck them
    fseek(file, 0, SEEK_END);
    int length = ftell(file);
    fseek(file, 0, SEEK_SET);
    unsigned char *wad_contents = malloc(sizeof(char) * length);
    fread(wad_contents, length, 1, file);
    fclose(file);
    
    wadinfo_t *header;
    lumpindex_t i;
    wad_file_t *wad_file = NULL;
    int startlump;
    filelump_t *fileinfo;
    filelump_t *filerover;
    int numfilelumps;

    
    FILE *ofd = fopen("./zk_wad_hardcoded.h", "w");

    header = malloc(sizeof(wadinfo_t));
    bufread(wad_contents, 0, sizeof(wadinfo_t), (unsigned char *)header);

    // printf("static const wadinfo_t header = {{'identification', \"%c%c%c%c\"}, {'numlumps', %d}, {'infotableofs', %d}}\n",
    //header->identification[0],header->identification[1], header->identification[2],header->identification[3],
    //header->numlumps, header->infotableofs);

	length = header->numlumps*sizeof(filelump_t);
	fileinfo = malloc(length);
    bufread(wad_contents, header->infotableofs, length, (unsigned char *)fileinfo);
	numfilelumps = header->numlumps;
    
	fprintf(ofd, "unsigned int ZK_NUMLUMPS = %d;\n", numfilelumps);
	fprintf(ofd, "struct lumpinfo_s ZK_LUMPSTRUCTS[%d] = {\n", numfilelumps);
    filerover = fileinfo;
    for (int i = 0; i < numfilelumps; ++i) {
        char div = (i == 0) ? ' ': ',';
        filerover->name[7] = 0x0;
        fprintf(ofd, "  %c {.name = \"%s\", .position = %d, .size = %d, .next = 0}\n",
            div, filerover->name,filerover->filepos, filerover->size);
        ++filerover;
    }
    fprintf(ofd, "};\n");
    

	fprintf(ofd, "unsigned char * ZK_LUMPBODIES[] = {\n");
    filerover = fileinfo;
    for (int i = 0; i < numfilelumps; ++i) {
        char div = (i == 0) ? ' ': ',';
        unsigned char *cache = malloc(filerover->size);                                                                                                                               
        bufread(wad_contents, filerover->filepos, filerover->size, cache); 
        
        fprintf(ofd, "  %c  (unsigned char *) \"", div);
        for (int j = 0; j < filerover->size; j++) {
            fprintf(ofd, "\\x%02x", cache[j]);
        }
        fprintf(ofd, "\"\n");
        ++filerover;
    }
    fprintf(ofd, "};\n");
    

    fclose(ofd);
    exit(0);
}


