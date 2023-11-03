#include "stdio.h"
#include "stdlib.h"

#include "w_file.h" // to get SHARD_SIZE

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
    
    unsigned int bytenum = 0;
    unsigned int SHARDS_NUM = (length / SHARD_SIZE + 1);
    fprintf(ofd, "\n\nunsigned char *wad_contents[%d]={\n", SHARDS_NUM);
    for (int shard_num=0; shard_num < SHARDS_NUM; shard_num++) {
        char div = shard_num == 0 ? ' ': ',';   
        fprintf(ofd, "%c (unsigned char *)\"", div);
        for (int jj=0; jj< SHARD_SIZE; jj++) {
            unsigned char byte = (bytenum++ > length) ? 0 : wad_contents[shard_num*SHARD_SIZE + jj];
            fprintf(ofd, "\\x%02x", byte);
        }
        fprintf(ofd, "\"\n");
    }
    fprintf(ofd, "};\n");
    fclose(ofd);
    exit(0);
}
