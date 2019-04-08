/*
* Standard C99 implementation of one time pad algorythm.
* For fun only, uses a bad RNG and should not be used for
* real security stuff.
*/
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

void generateRandomBytes(char *bytes, int size);
void encrypt(char * text, unsigned int textSize, char * key);
unsigned int measureString(char * string);

int main(int argc, char **argv)
{
    if (argc != 2) {
        printf("Usage: %s [text] where [text] is the text to be ", argv[0]);
        printf("encrypted\n");
        return -1;
    }
    srand(time(NULL));
  

    char * text = argv[1];
    unsigned int size = measureString(text);

    char * key = (char*) malloc(size);
    generateRandomBytes(key, size);

    printf("Encrypting text: %s\n", text);
    encrypt(text, size, key);

    printf("Encrypted bytes: %p\n", text);
    printf("Decrypting with key %p\n", key);

    encrypt(text, size, key);
    printf("Decrypted text: %s\n", text);

    printf("DESTROYING THE KEY.\n");
}

// Generates "size" random bytes
void generateRandomBytes(char *bytes, int size)
{   
     for(int i = 0; i < size; i++) {
        bytes[i] = rand();
    }
}
// Encrypts or decrypts a text using one time pad and
// a given key. The key must only be used once, otherwise
// the algorithm becomes useless.
void encrypt(char * text, unsigned int textSize, char * key)
{
    for (unsigned int i = 0; i < textSize; i++) {
        text[i] ^= key[i];
    }
}

// Measures size of string
unsigned int measureString(char * string) {
    unsigned int i = 0;
    while (string[i] != '\0') i++;
    return i;
} 