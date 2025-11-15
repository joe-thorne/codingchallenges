/*
 * ccwc
 * 12/11/25
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <wchar.h>
#include <unistd.h>

#define BYTE   1
#define LINE   2
#define WORD   4
#define CHAR   8
#define EMPTY  7

typedef struct Parameters {
  unsigned char outputs;
  char* filename;
  unsigned long byteCount;
  unsigned long lineCount;
  unsigned long wordCount;
  unsigned long charCount;
} Parameters;

void processCommandLine(int argc, char* argv[], Parameters* params) {
  int ch;
  while ((ch = getopt(argc, argv, "clwm")) != -1) {
    switch (ch) {
      case 'c':
        params->outputs |= BYTE;
        break;
      case 'l':
        params->outputs |= LINE;
        break;
      case 'w':
        params->outputs |= WORD;
        break;
      case 'm':
        params->outputs |= CHAR;
        break;
      default:
        printf("Error reading from CL, exiting");
        exit(1);
    }
  }
  // no args means "-clw"
  if (!params->outputs) {
    params->outputs = EMPTY;
  }
  if (argv[optind]) {
    params->filename = argv[optind];
  }
} 

void count(FILE* file, Parameters* params) {
  char inWord = 0;
  char nextChar = fgetc(file);
  while (nextChar != EOF) {
    params->byteCount++;
    if (nextChar == '\n') {
      params->lineCount++;
    }
    if (isspace(nextChar)) {
      if (inWord) {
        inWord = 0;
      } 
    } else {
      if (!inWord) {
        inWord = 1;
        params->wordCount++;
      }
    }
    nextChar = fgetc(file);
  }

  if (params->outputs | CHAR) {
    rewind(file);
    wchar_t wc = fgetwc(file);
    while (wc != EOF) {
      params->charCount++;
      wc = fgetwc(file);
    }
  }
}

int main(int argc, char* argv[]) {
  setlocale(LC_ALL, "");
  Parameters params = {0};
  processCommandLine(argc, argv, &params);
  FILE* handle;

  if (params.filename){
    handle = fopen(params.filename, "r");
  } else {
    handle = stdin;
  }
  if (!handle) {
    fprintf(stderr, "Unable to open \"%s\" \n" , params.filename);
    exit(2);
  } 
  count(handle, &params);
  
  // TODO: Should be a function
  if (params.outputs & LINE) printf(" %7lu", params.lineCount);
  if (params.outputs & WORD) printf(" %7lu", params.wordCount);
  if (params.outputs & BYTE) printf(" %7lu", params.byteCount);
  if (params.outputs & CHAR) printf(" %7lu", params.charCount);
  if (params.filename) {
    printf(" %7s\n", params.filename);
  } else {
    printf("\n");
  }
  return 0;
}

