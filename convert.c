#include <stdint.h>
#include <string.h>
#include <stdio.h>

//Converts number to a different base using division method
void div_convert(uint32_t n, int base, char *out) {
  char temp[65];
  int pos = 0;

  if (n == 0) {
    strcpy(out, "0");
    return;
  }

  while (n > 0) {
    int remainder = n % base;
    n = n / base;

    if (remainder < 10){
      temp[pos++] = '0' + remainder;
    }
    else {
      temp[pos++] = 'A' + (remainder - 10);
    } 
  }
  temp[pos] = '\0';
  
  for (int i = 0; i < strlen(temp); i++) {
    out[strlen(temp) - i - 1] = temp[i];
  }
  out[pos] = '\0';
}

//Converts number to a different base using subtraction method
void sub_convert(uint32_t n, int base, char *out) {
    int pos = 0;

    if (n == 0) {
        strcpy(out, "0");
        return;
    }

    uint64_t pow = 1;
    while (pow * base <= n) {
        pow *= base;
    }

    while (pow > 0) {
        int remainder = n / pow;
        n = n % pow;

        if (remainder < 10) {
            out[pos++] = '0' + remainder;
        } else {
            out[pos++] = 'A' + (remainder - 10);
        }

        pow /= base;
    }

    out[pos] = '\0';
}

//First prints converted numbers using common bases
//Then left shifts by 3 using same bases
//Lastly uses AND with 0xFF mask
void print_tables(uint32_t n, char *out) {
    char bin[33], oct[12], hex[9];
    char temp[256];
    out[0] = '\0';

    div_convert(n, 2, bin);
    div_convert(n, 8, oct);
    div_convert(n, 16, hex);
    snprintf(temp, sizeof(temp), "Binary=%s Octal=%s Decimal=%u Hex=%s\n", bin, oct, n, hex);
    printf("Original: Binary=%s Octal=%s Decimal=%u Hex=%s\n", bin, oct, n, hex);
    strcat(out, temp);

    uint32_t shifted = n << 3;
    div_convert(shifted, 2, bin);
    div_convert(shifted, 8, oct);
    div_convert(shifted, 16, hex);
    snprintf(temp, sizeof(temp), "Left Shift by 3: Binary=%s Octal=%s Decimal=%u Hex=%s\n", bin, oct, shifted, hex);
    printf("Left Shift by 3: Binary=%s Octal=%s Decimal=%u Hex=%s\n", bin, oct, shifted, hex);
    strcat(out, temp);

    uint32_t masked = n & 0xFF;
    div_convert(masked, 2, bin);
    div_convert(masked, 8, oct);
    div_convert(masked, 16, hex);
    snprintf(temp, sizeof(temp), "AND with 0xFF: Binary=%s Octal=%s Decimal=%u Hex=%s\n", bin, oct, masked, hex);
    printf("AND with 0xFF: Binary=%s Octal=%s Decimal=%u Hex=%s\n", bin, oct, masked, hex);
    strcat(out, temp);
}
