///////////////////////////////////////////////////////////////////////////
// simulator                                                             //
//                                                                       //
// Filename: simulator .h                                                //
// Purpose: Functions Related to parser              i.e.                //
//          parse spice file and construct of hash tables and arrays     //
// Authors: Athanasia Karanika                                           //
///////////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define INITIAL_CAPACITY 20 // size of nodehush table //

// *** Externals *** //

extern void init_nodehash(unsigned long);
extern void init_componentarray();
extern void dump_nodehash(unsigned long int);
extern void insert_node(char *);
extern int processSPICE(char *);