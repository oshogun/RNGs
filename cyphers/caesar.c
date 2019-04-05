// Caesar's cypher
// An ancient and very simple encryption algorythm that was used in
// ancient Rome, adapted to a modern version that uses the entire
// ascii table instead of just the 26 letters

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

void encrypt (char * text, unsigned int size)
{
    for (int i = 0; i < size; i++) {
        text[i] += 3;
    }
}

void decrypt (char * text, unsigned int size)
{
    for (int i = 0; i < size; i++) {
        text[i] -=3;
    }
}

int main(int argc, char** argv)
{
    if (argc != 3) {
        printf("Usage: %s {text} {size}, where {text} is the text to be ", argv[0]);
        printf("encrypted and {size} is the number of bytes to encrypt\n");
        return 1;
    }
    char * text = argv[1];
    int size = atoi(argv[2]);
    printf("Encrypting text %s\n", text);
    encrypt(text, size);
    printf("Encrypted text: %s\n", text);
    decrypt(text, size);
    printf("Decrypted text: %s\n", text);
}

