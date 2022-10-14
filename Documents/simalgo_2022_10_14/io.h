///////////////////////////////////////
// Simulator                         //

// Data stuctures : Nodes hash //
//
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_NODENAME 10 // max length of namenode //
#define INITIAL_CAPACITY 20 // size of nodehush table //
#define HASHDEPTH 10 // hashing depth //
// hashtable for nodes //

typedef unsigned long hash;
struct Nodehashstruct
    {   
        // HASHDEPTH numper of hash collisions //
        char *nodename[HASHDEPTH]; // hash stringS // 
        int hashpresent[HASHDEPTH]; // hash present flagS //
    }; 

struct Componentstruct
    {   
        char *componentname; // name of component //
        char componenttype; // type of component V, I, R, C, D//
        char *positivenodename; // name of the node of positive connection //
        char *negativenodename; // name of the node of negative connection //
        char *componentvalue; // the value of component //
    }; 

typedef struct Componentstruct Componentarray;
typedef struct Nodehashstruct Nodehash;

int nodenum;
Nodehash *nodehash;
Componentarray *componentarray;
void init_componentarray();
void init_nodehash(unsigned long);
void dump_nodehash(unsigned long int);
void dump_componentarray(unsigned long int);
void insert_node(char *);
int processSPICE(char *);
unsigned long hashstring(char *, unsigned long);
