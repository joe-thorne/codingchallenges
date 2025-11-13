/*
 * ccwc
 * 12/11/25
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#define BYTE   1
#define LINE   2
#define WORD   4
#define CHAR   8
#define EMPTY  7

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

typedef struct Counts {
  unsigned long byteCount;
  unsigned long lineCount;
  unsigned long wordCount;
  unsigned long charCount;
} Counts;

// Prototypes
Parameters processCommandLine(int argc, char* argv[]); 
Counts count(FILE* file);

int main(int argc, char* argv[]) {
  setlocale(LC_ALL, "");

  // check command line
  Parameters params = processCommandLine(argc, argv);

  // open file
  FILE* handle = fopen(params.filename, "r");
  if (!handle) {
    // Unable to open file
    fprintf(stderr, "Unable to open \"%s\" \n" , params.filename);
    exit(2);
  } 

  Counts counts = count(handle);
  
  // output
  if (params.outputs & LINE) printf(" %7lu", counts.lineCount);
  if (params.outputs & WORD) printf(" %7lu", counts.wordCount);
  if (params.outputs & BYTE) printf(" %7lu", counts.byteCount);
  if (params.outputs & CHAR) printf(" %7lu", counts.charCount);
  if (params.filename) {
    printf(" %7s\n", params.filename);
  } else {
    printf("\n");
  }
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

  if (!params.outputs) {
    params.outputs = EMPTY;
  }

  if (argv[0]) {
    params.filename = argv[0];
  }

  return params;
} 

Counts count(FILE* file) {
  Counts counts = {.byteCount =0,
    .lineCount = 0,
    .wordCount =0,
    .charCount = 0
  };

  // count bytes
  char nextChar = fgetc(file);
  while (nextChar != EOF) {
    counts.byteCount++;
    if (nextChar == '\n') {
      counts.lineCount++;
    }
    nextChar = fgetc(file);

  }

  rewind(file);

  return counts;
}
