#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "io.h"

#define LINEMAX 200

int nodenum; // number of nodes //
Nodehash *nodehash; //  nodes hash table //componentarraystruct 

//                  *** processSPICE ***                      //
// parses SPICE format file                                   //
// e.g    V1           5              0         2             //
//         |           |              |         |             //
//     tokennum = 0 tokennum = 1  tokennum = 2 tokennum = 3   //
// i) if tokennum = 1 or 2, this means that it constitutes    //
//    a node so it is inserted to the nodehash table          //
//    and it is stored to componentarraystruct array          //
//    which stores information about components               //
// ii) In other cases we examine what token we have and we    //
//     allocate memory for the new entry in                   //  
//     componentarraystruct and we fill the structure fields  //
int processSPICE(char *filename)
{
    FILE *spicefile; 
    char delimiters[] = " \t\n\a";
    char componenttype; // type of component R, C, L, D //
    char *pstring = NULL; // parsing string //
    char *temp = NULL; // file line string //
    int tokennum = 0; // for token numbering //
    int pstringnum = 0; // for pstring numbering //

    // *** Local Variables End *** //
    temp = (char *) malloc(LINEMAX * sizeof(char));
    spicefile = fopen(filename, "r");
    if (spicefile == NULL)
        {
            printf("ERROR: Unable to open SPICE file %s.\n", filename);
        }


    while (!feof(spicefile))
        {   
            // get file line in temporary sting variable temp //
            if (fgets(temp, LINEMAX, spicefile) == NULL)
                break;

            // check if SPICE line is a comment and ignore if it is //
            if (temp[0] == '*')
                continue;
            
            componenttype = temp[0]; // R, C, L, D //
            pstring = strtok(temp, delimiters);
            tokennum = 0;
            printf("-->DEBUG: pstring %s tokennum %d\n", pstring, tokennum);    
            componentarray = (Componentarray *) realloc(componentarray, sizeof(Componentarray) * (pstringnum + 1));

            while (pstring != NULL)
                {   
                    // insert nw component to componentarray //
                    // initialize componentname //
                    if (tokennum == 0)
                        {
                            (componentarray + pstringnum)->componentname =  (char *) realloc((componentarray + pstringnum)->componentname, strlen(pstring) * sizeof(pstring));
                            strcpy((componentarray + pstringnum)->componentname, pstring);
                            // initialize componenttype
                            if ((componenttype == 'R') || (componenttype == 'r'))
                                {
                                    (componentarray + pstringnum)->componenttype = 'R';
                                }

                            else if ((componenttype == 'L') || (componenttype == 'l'))
                                {
                                    (componentarray + pstringnum)->componenttype = 'L';
                                }   

                            else if ((componenttype == 'D') || (componenttype == 'd'))
                                {
                                    (componentarray + pstringnum)->componenttype = 'D';
                                }  


                            else if ((componenttype == 'V') || (componenttype == 'v'))
                                {
                                    (componentarray + pstringnum)->componenttype = 'V';
                                }  


                            else if ((componenttype == 'I') || (componenttype == 'i'))
                                {
                                    (componentarray + pstringnum)->componenttype = 'I';
                                }  
                        }
                    else if ((tokennum == 1) || (tokennum == 2))
                    {
                        if ((componenttype == 'R') || (componenttype == 'r') || (componenttype == 'L') || (componenttype == 'l') || (componenttype == 'D') 
                        || (componenttype == 'd') || (componenttype == 'V')|| (componenttype == 'v') || (componenttype == 'I') || (componenttype == 'i'))
                            {
                                printf("insert node: %s\n", pstring);
                                insert_node(pstring);
                            }

                        if (tokennum == 1)
                            {
                                (componentarray + pstringnum)->positivenodename =  (char *) realloc((componentarray + pstringnum)->positivenodename, strlen(pstring) * sizeof(pstring));
                                strcpy((componentarray + pstringnum)->positivenodename, pstring);
                            }
                        else if (tokennum == 2)
                            {
                                (componentarray + pstringnum)->negativenodename =  (char *) realloc((componentarray + pstringnum)->negativenodename, strlen(pstring) * sizeof(pstring));
                                strcpy((componentarray + pstringnum)->negativenodename, pstring);
                            }
                    }
                    else if (tokennum == 3)
                        {
                            (componentarray + pstringnum)->componentvalue =  (char *) realloc((componentarray + pstringnum)->componentvalue, strlen(pstring) * sizeof(pstring));
                            strcpy((componentarray + pstringnum)->componentvalue, pstring);

                        }
                    
                    tokennum++;
                    pstring = strtok(NULL, delimiters);
                    printf("DEBUG: pstring %s tokennum %d\n", pstring, tokennum);
                }
            pstringnum++;
        }
    dump_nodehash(INITIAL_CAPACITY);
    dump_componentarray(pstringnum - 1);
    return nodenum;
}

// *** dump_nodehash *** //
// prints the nodehash table //
void dump_nodehash(unsigned long int size)
    {
        unsigned long int i;
        int j;

        printf("Hash table\n");
        for (i = 0; i < size + 1; i++)
            {   printf("DEBUG:");
                for (j = 0; j < HASHDEPTH; j++)
                    {   if ((nodehash + i)->nodename[j] != NULL)
                            {
                                printf("nodehash[%lu][%d] = %s", i, j,(nodehash + i)->nodename[j]);
                            }
                    }
                printf("\n");
            }

    }

// *** dump_Componentstruct *** //
// prints the Componentarray //
void dump_componentarray(unsigned long int size)
    {
        unsigned long int i;
        printf("componentarray\n");
        for (i = 0; i < size + 1; i++)
            {   printf("DEBUG: component %lu name %s type %c positive %s negtive %s value %s", i, (componentarray + i)->componentname, (componentarray + i)->componenttype, (componentarray + i)->positivenodename, (componentarray + i)->negativenodename, (componentarray + i)->componentvalue);
                printf("\n");
            }

    }

void init_nodehash(unsigned long size)
    {
        unsigned long int i;
        int j;
        nodehash = NULL;
        nodehash = (Nodehash *) malloc((size + 1) * sizeof(Nodehash));

        // initialize structure //
        for (i = 0; i < size; i++)
            {
                for (j = 0; j < HASHDEPTH; j++)
                    {
                        (nodehash + i)->nodename[j] = NULL;
                        (nodehash + i)->hashpresent[j] = 0; 
                    }
                
            }
    }

void init_componentarray()
  {
      // initializestructure //
    //   componentarray->componentname = NULL; 
    //   componentarray->componenttype = NULL; 
    //   componentarray->positivenodename = NULL;
    //   componentarray->positivenodename = NULL;
    //   componentarray->componentvalue = NULL;
  }

// *** insert_node **//
// inserts nodehash by name //
void insert_node(char *nodename)
    {   
        int nd; //nodedepth //
        int nodeexists = 0;
        hash nh; // nodehash //

        
        // get node hash //
        nh = hashstring(nodename, INITIAL_CAPACITY);
        for (nd = 0; nd < HASHDEPTH; nd++)
            {
                if ((nodehash + nh)->hashpresent[nd] == 1)
                    {   
                        // if there is already in hashtable ignore it //
                        if (strcmp((nodehash + nh)->nodename[nd], nodename) == 0)
                            return;

                        continue;
                    }

                // store nodename //
                (nodehash + nh)->nodename[nd] = calloc(strlen(nodename) + 1, sizeof(char));
                strcpy((nodehash + nh)->nodename[nd], nodename);

                // set hashpresent flag //
                (nodehash + nh)->hashpresent[nd] = 1;
                return;
            }
        return;
    }

unsigned long hashstring(char *pstring, unsigned long hashsize)
    {
        unsigned long hash = 5381;
        int c;
        int i;
        unsigned long h;


        for (i = 0; i < strlen((const char *) pstring); i++)
            {
                c = (unsigned char) pstring[i];
                hash = (((hash << 5)) + hash) ^ c; // ((hash * 33) + c) //
            }

        h = hash % hashsize;
        return (h + 1); // never return 0 //
    }