#include <stdio.h>
#include <stdlib.h>
#include "b64.h"


void EncodeBase64(char*);

int main(int argc, char *argv[])
{
  printf("Calculo de Base64 de la cadena: Demo 2 Telephaty\n");
  EncodeBase64("Demo 2 Telepathy");
  system("PAUSE");	
  return 0;
}


void EncodeBase64(char* str)
{
    char buf[255] = "";
    int b = 0;
    Base64Encode(str, buf, 255);
    printf(buf);
    printf("\n");
}


void DecodeBase64(char* str)
{
    char buf[255] = "";
    int b = 0;
    Base64Decode(str, buf, 255);
    printf(buf);
    printf("\n");
}
