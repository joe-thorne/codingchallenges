/*
 * ccwc
 * 12/11/25
 *
 */

#include <stdio.h>
#include <stdlib.h>

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
Parameters processCommandLine(int argc, char* argv[], CommandLine* command); 

int main(int argc, char* argv[]) {
  // check command line
  Parameters params = processCommandLine(argc, argv, &params);
  // open file
    
  // read/count
  
  // output
  return 0;
}

Parameters processCommandLine(int argc, char* argv[], Parameters* params) {

  Parameters params {
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
