#include <stdio.h>
#include <stdlib.h>

#include "zkldoom/w_file.h"
#include "zkldoom/w_wad.h"
#include "zkldoom/doomdata.h"


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
    unsigned int aprx_total_wad_state_size = 0;
    
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
    int MAP_LUMPNUM = -1;

    for (int i =0; i < numfilelumps; i++) {
        if (!strncmp(filerover->name, "MAP01", 5)) {
            MAP_LUMPNUM = i;
            break;
        }   
    }
    if (MAP_LUMPNUM < 0) {
        printf("[ERROR] Cannot find MAP_LUMPNUM in wad!\n");
        exit(1);
    }
    
    filerover = fileinfo;
    for (int i = 0; i < numfilelumps; ++i) {
        char div = (i == 0) ? ' ': ',';
        filerover->name[7] = 0x0;
        if (lump_can_be_skipped_in_zk(filerover->name, MAP_LUMPNUM, i) == 0 ) {
            printf("taking lumpname: %s, size: %d\n", filerover->name, filerover->size);
            fprintf(ofd, "  %c {.name = \"%s\", .position = %d, .size = %d, .next = 0}\n",
                div, filerover->name,filerover->filepos, filerover->size);
        } else {
        fprintf(ofd, "  %c {.name = \"%s\", .position = %d, .size = 0, .next = 0}\n",
            div, filerover->name,filerover->filepos);
        
        }
        aprx_total_wad_state_size += sizeof(filelump_t);
        ++filerover;
        
    }
    fprintf(ofd, "};\n");
    

	fprintf(ofd, "unsigned char * ZK_LUMPBODIES[] = {\n");
    filerover = fileinfo;
    for (int i = 0; i < numfilelumps; ++i) {
        char div = (i == 0) ? ' ': ',';
        unsigned char *cache = malloc(filerover->size);                                                                                                                               
        bufread(wad_contents, filerover->filepos, filerover->size, cache); 
        if (lump_can_be_skipped_in_zk(filerover->name, MAP_LUMPNUM, i) == 0) {
            fprintf(ofd, "  %c  (unsigned char *) \"", div);
            for (int j = 0; j < filerover->size; j++) {
                fprintf(ofd, "\\x%02x", cache[j]);
            }
            fprintf(ofd, "\"\n");
            aprx_total_wad_state_size += filerover->size;
        } else {
            fprintf(ofd, "  %c  (unsigned char *) \"\"\n", div);
        }
        ++filerover;
    }
    fprintf(ofd, "};\n");
    

    fclose(ofd);
    printf("Approximate size of zk .wad state: %d\n", aprx_total_wad_state_size);
    exit(0);
}

int lump_can_be_skipped_in_zk(char * lumpname, int maplumpnum, int num) {
    if (
            num == maplumpnum + ML_BLOCKMAP ||
            num == maplumpnum + ML_VERTEXES ||
            num == maplumpnum + ML_SECTORS ||
            num == maplumpnum + ML_SIDEDEFS ||
            num == maplumpnum + ML_LINEDEFS ||
            num == maplumpnum + ML_SSECTORS ||
            num == maplumpnum + ML_NODES ||
            num == maplumpnum + ML_SEGS ||
            num == maplumpnum + ML_REJECT ||
            num == maplumpnum + ML_THINGS) {
        printf("Adding maplump + indexxxx\n");
        return 0;
    }
        
    if (
        !strncmp(lumpname,"MAP01",5) ||   // WARNING - THIS SHOULD BE TAKEN EXACTLY FROM MAP LUMP NAME in P_SetupLevel()
        !strncmp(lumpname,"VERTEXE",7) ||
        !strncmp(lumpname, "SECTORS",7) ||
        !strncmp(lumpname, "SIDEDEF",7) ||
        !strncmp(lumpname, "LINEDEF",7) ||
        !strncmp(lumpname,"SSECTOR",7) ||
        !strncmp(lumpname, "NODES", 7) ||
        !strncmp(lumpname, "SEGS",7) ||
        !strncmp(lumpname, "REJECT",7) ||
        !strncmp(lumpname, "THINGS",7 )) {
        return 0;
    }
    return 1;
}

