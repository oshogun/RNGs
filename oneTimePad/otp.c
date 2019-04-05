/*
* Standard C99 implementation of one time pad algorythm.
* For fun only, uses a bad RNG and should not be used for
* real security stuff.
*/
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

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
    for (int i = 0; i < textSize; i++) {
        text[i] ^= key[i];
    }
}

int main(int argc, char **argv)
{
    if (argc != 3) {
        printf("Usage: %s [text] [bytes] where [text] is the text to be ", argv[0]);
        printf("encrypted and [bytes] is the number of ascii characters\n");
        return -1;
    }
    srand(time(NULL));
    unsigned int size = atoi(argv[2]);

    char * text = argv[1];
    
    char * key = (char*) malloc(size);
    generateRandomBytes(key, size);

    printf("Encrypting text: %s\n", text);
    encrypt(text, size, key);

    printf("Encrypted bytes: %x\n", text);
    printf("Decripting with key %x\n", key);

    encrypt(text, size, key);
    printf("Decrypted text: %s\n", text);

    printf("DESTROYING THE KEY.\n");
    free(key);
}