/*
Giovanni Tshibangu 
CS 492 : Homework 2 Problem 1 TEA Block encryption
9/24/2022

Part: 1,2,3
*/
#include <stdio.h>
#include <stdint.h>
#include <ctype.h>

// Part 1:  Use your TEA algorithm to encrypt the 64-bit plaintext block:
void TEAencrypt (unsigned int LeftRight [2], unsigned int key [4]) {
    unsigned int DELTA = 0x9E3779B9;    // (232/golden ratio, key scheduling constant)
    unsigned int sum = 0;               // Init SUM
    
    for (int i = 0; i < 32; i++) {     // for i = 1 to 32
        sum += DELTA;  //sum += delta
        // Repeatedly shift bits, xor and add as per TEA algorithm
        LeftRight [0] += ((LeftRight [1] << 4) + key [0]) ^ (LeftRight [1] + sum) ^ ((LeftRight [1] >> 5) + key [1]);  // L += ((R<<4)+K[0]) XOR (R+sum) XOR ((R>>5)+K[1])
        LeftRight [1] += ((LeftRight [0] << 4) + key [2]) ^ (LeftRight [0] + sum) ^ ((LeftRight [0] >> 5) + key [3]);  // R += ((L<<4)+K[2]) XOR (L+sum) XOR ((L>>5)+K[3])
    }                                              
}
// Part 2:  Implement decryption and verify that you obtain the original plain text 
void TEAdecrypt (unsigned int LeftRight [2], unsigned int key [4]) {
    unsigned int DELTA = 0x9E3779B9;    // (232/golden ratio, key scheduling constant)
    unsigned int sum = 32 * DELTA;

    for (int i = 0; i < 32; i++) {     // for i = 1 to 32                     
        // Similar steps as encryption; sum is reduced each loop
        LeftRight [1] -= ((LeftRight [0] << 4) + key [2]) ^ (LeftRight [0] + sum) ^ ((LeftRight [0] >> 5) + key [3]);  // R −= ((L<<4)+K[2]) XOR (L+sum) XOR ((L>>5)+K[3])
        LeftRight [0] -= ((LeftRight [1] << 4) + key [0]) ^ (LeftRight [1] + sum) ^ ((LeftRight [1] >> 5) + key [1]);  // L −= ((R<<4)+K[0]) XOR (R+sum) XOR ((R>>5)+K[1])
        sum -= DELTA;  // sum −= delta
    }                                              
}
// MAIN FUNCION
int main(){
    unsigned int plaintext [2] = {0x0FCB4567, 0x0CABCDEF};                    // Plaintext = 0x0FCB45670CABCDEF
    unsigned int key[4] = {0xBF6BBBCD, 0xEF00F000, 0xFEAFAFBF, 0xACCDEF01};  // KEY 128 bit (K[0],K[1],K[2],K[3]) = 128 bit key = 0xBF6BBBCDEF00F000FEAFAFBFACCDEF01

//  Encryting Function call
    TEAencrypt (plaintext, key);            // Fucntion call, Passing plaintext and Key to this function
    printf ("\n Encrypted Message : ");     // Print to screen
    for (int i = 0; i < 2; i++)             // Loop twice to print both part 
        printf ("%x", plaintext[i]);        // Print Message

//  Decrypting Function call 
    printf ("\n Decrypted Message : ");     // Print to screen
    printf("0");
    TEAdecrypt (plaintext, key);            // Function call, Passing plaintext and Key to this function
    for (int i = 0; i < 2; i++)             // Loop twice to print both part 
        printf ("%x", plaintext[i]);        // Print Message
    printf("\n \n");                        // Double Space below
    
    return 0;                               // end here
}
/*
Part 3: In comments in your code explain how you would make your code encode/decode a longer set of plaintexts 
(i.e. multiple blocks) using CBC.  You do not need to code this, but your explanation should be detailed and related to your implementation

==> First, you will need to padd the plaintext with zeroes if the length of the text is not multiple of 64 bits. We will need an IV, 
    then XOR(IV, P) before encrypting. Then Encrypt the result E(XOR).
    The CBC algorithm will stay the sanme but we will need to make  sure that the plaintext is a multiple of 64bit. We can use padding with zeroes if not.
*/