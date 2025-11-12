/*
 * ccwc
 * 12/11/25
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BYTE 1
#define LINE 2
#define WORD 4
#define CHAR 8

const char* const byteArg = "-c";
const char* const lineArg = "-l";
const char* const wordArg = "-w";
const char* const charArg = "-m";

// Constants and Data structures
const char* const countBytesArg = "-c";
const char* const noFileMessage = "To be implemented, for now you must specify a filename\n";

typedef struct Parameters {
  unsigned char outputs;
  char* filename;
} Parameters;

// Prototypes
Parameters processCommandLine(int argc, char* argv[]); 
int countBytes(FILE* file);

int main(int argc, char* argv[]) {
  int numBytes;
  // check command line
  Parameters params = processCommandLine(argc, argv);
  // open file
  FILE* handle = fopen(params.filename, "r");
  if (!handle) {
    // Unable to open file
    fprintf(stderr, "Unable to open \"%s\" \n" , params.filename);
    exit(2);
  } else {

    if (params.outputs & BYTE) {
      numBytes = countBytes(handle);
    }
    printf("  %i %s", numBytes, params.filename);
  }  
  
  // output
  return 0;
}

Parameters processCommandLine(int argc, char* argv[]) {
  Parameters params = {
    .outputs = 0,
    .filename = NULL
  };
  // Skip program name
  argc--;
  argv++;
  while (argv[0] && strncmp(argv[0], "-", 1) == 0) {
    // current argument begins with '-'
    if (!strcmp(argv[0], byteArg)) {
      params.outputs = params.outputs | BYTE;
    } else if (!strcmp(argv[0], lineArg)) {
      params.outputs = params.outputs | LINE;
    } else if (!strcmp(argv[0], wordArg)) {
      params.outputs = params.outputs | WORD;
    } else if (!strcmp(argv[0], charArg)) {
      params.outputs = params.outputs | CHAR;
    }
    // Skip one argument
    argc--;
    argv++;
  }
  if (argv[0]) {
    params.filename = argv[0];
  }
  return params;
} 

int countBytes(FILE* file) {
  int count = 0;
  char nextChar = fgetc(file);
  while (nextChar != EOF) {
    count++;
    nextChar = fgetc(file);
  }
  return count;
}
