#include <stdio.h>
#include "convert.c"
#include <stdlib.h>

int main() {
  FILE *file = fopen("a1_test_file.txt", "r");
  if (file == NULL) {
    printf("Error: Could not open file\n");
    return 1;
  }

  char line[256];
  int count = 0;
  int pass_count = 0;
  while (fgets(line, sizeof(line), file) != NULL) {

    //Skips comments and blank lines
   if (line[0] == '#' || line[0] == '\n' || strlen(line) == 0)
    continue;
    
    char buffer[32];
    char* token = strtok(line, " ");
    count++;
    printf("Test %d: %s", count, token);
    char pass[5];

    //Tests div_convert
    if (line[0] == 'd') {
      token = strtok(NULL, " ");
      int n = atoi(token);
      token = strtok(NULL, " ");
      int base = atoi(token);
      token = strtok(NULL, " ");
      token[strlen(token) - 1] = '\0';
      div_convert(n, base, buffer);
      if (strcmp(buffer, token) == 0) {
	pass[0] = 'P';
	pass[1] = 'A';
	pass[2] = 'S';
	pass[3] = 'S';
	pass[4] = '\0';
	pass_count++;
      }
      else {
	pass[0] = 'F';
	pass[1] = 'A';
	pass[2] = 'I';
	pass[3] = 'L';
	pass[4] = '\0';
      }
      printf("(%d, %d) -> Expected: %s, Got: %s [%s]\n", n, base, token, buffer, pass);
    }

    //Tests sub_convert
    else if (line[0] == 's') {
      token = strtok(NULL, " ");
      int n = atoi(token);
      token = strtok(NULL, " ");
      int base = atoi(token);
      token = strtok(NULL, " ");
      sub_convert(n, base, buffer);
      token[strlen(token) - 1] = '\0';
      if (strcmp(buffer, token) == 0) {
	pass[0] = 'P';
	pass[1] = 'A';
	pass[2] = 'S';
	pass[3] = 'S';
	pass[4] = '\0';
	pass_count++;
      }
      else {
	pass[0] = 'F';
	pass[1] = 'A';
	pass[2] = 'I';
	pass[3] = 'L';
	pass[4] = '\0';
      }
      printf("(%d, %d) -> Expected: %s, Got: %s [%s]\n", n, base, token, buffer, pass);
    }

    //Tests print_tables
    else if (line[0] == 'p') {
    token = strtok(NULL, " ");
    int n = atoi(token);

    char expected[512] = "";
    for (int i = 0; i < 3; i++) {
        fgets(line, sizeof(line), file);
        strcat(expected, line);
    }

    char actual[512];
    printf("%d -> ", n);
    print_tables(n, actual);

    if (strcmp(expected, actual) == 0) {
        printf("[PASS]\n");
        pass_count++;
    } else {
        printf("[FAIL]\n");
        printf("\n%s\n", expected);
        printf("Got:\n%s\n", actual);
    }
}
  }
  fclose(file);
  printf("\nSummary: %d/%d tests passed", pass_count, count);
}
