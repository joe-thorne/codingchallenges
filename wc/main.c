/*
 * ccwc
 * 12/11/25
 *
 */

#include <stdio.h>
#include <stdlib.h>

// Constants and Data structures
const char* const countBytesArg = "-c";
const char* const usageMessage = "Usage: ccwc -c file\n";

typedef struct CommandLine {
  unsigned char bytes;
  unsigned char lines;
  unsigned char words;
  unsigned char chars;
  char* filename;
} CommandLine;

// Prototypes
void getCL(int argc, char* argv[], CommandLine* command); 

int main(int argc, char* argv[]) {
  // check command line
  CommandLine command;
  getCL(argc, argv, &command);
  printf("filename is %s\n", command.filename);
  // open file
    
  // read/count
  
  // output
  return 0;
}

void getCL(int argc, char* argv[], CommandLine* command) {
  
  switch (argc) {
    case 1:
      printf(usageMessage);
      exit(1);
    case 2: // only filename
      command->bytes = 1;
      command->lines = 1;
      command->words = 1;
      command->chars = 1;
      command->filename = argv[1];
  }
} 
