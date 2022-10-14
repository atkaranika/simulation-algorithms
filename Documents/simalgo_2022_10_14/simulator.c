#include "simulator.h"

#define MAXFILENAMELENGTH 20

int main(int argc, char* argv[])
{   
    char filename[MAXFILENAMELENGTH];
    printf("Give a spice input file\n");
    scanf("%s", filename);
    // allocate nodehash array based on the initial capacity //
    init_nodehash(INITIAL_CAPACITY);
    init_componentarray();
    processSPICE(filename);
    return 0;
}