#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*  
    Computer Security 
    HW1 Implement DES
    21300691 Cheung Won Sik
    2019.09.21

    *********** Steps of DES Algorithms ***********
    Step1: Get Plain Text
    Step2: Convert Plain Text to LeftSection(0) and RightSection(0) by using Initial Permutation
    Step3: Take 16 rounds which need LS, RS, and key
    Step3-1: Convert 64bits key to 48bits key
    Step3-2: Convert 32bits RS to 48bits by using Expansion P-box
    Step3-3: XOR operation to 48bits key and RS
    Step3-4: Convert 48bits to 32bits by using S-boxes
    Step3-5: Convert 32bits to 32bits by using straight P-box
    Step3-6: XOR operation to LS and result of 3-5, and swap it to RS (in round 16 doesn't swap)
    Step4: Convert LS(16) and RS(16) to Cipher Text by using Final Permutation

    *********** Step of Running Program ***********
    Step1: in command line type(windows)    gcc .\HW1_Cheung_WonSik.c -o hw1.exe
    Step2: in command line type(windows)    .\hw1.exe (KEY) (PLAIN TEXT)

    *********** Execute Enviroment ***********
    1. windows
    2. gcc version 6.3.0
*/

const char parity_drop[56]={57,49,41,33,25,17,9,1,58,50,42,34,26,18,10,2,59,51,43,35,27,19,11,3,60,52,44,36,63,55,
    47,39,31,23,15,7,62,54,46,38,30,22,14,6,61,53,45,37,29,21,13,5,28,20,12,4};
const char compression_table[48]={14,17,11,24,1,5,3,28,15,6,21,10,23,19,12,4,26,8,16,7,27,20,13,2,41,52,31,37,47,
    55,30,40,51,45,33,48,44,49,39,56,34,53,46,42,50,36,29,32};
const char initial_permutation[64]={58,50,42,34,26,18,10,2,60,52,44,36,28,20,12,4,62,54,46,38,30,22,14,6,64,56,48,40,
    32,24,16,8,57,49,41,33,25,17,9,1,59,51,43,35,27,19,11,3,61,53,45,37,29,21,13,5,63,55,47,39,31,23,15,7};
const char final_permutation[64]={40,8,48,16,56,24,64,32,39,7,47,15,55,23,63,31,38,6,46,14,54,22,62,30,37,5,45,13,
    53,21,61,29,36,4,44,12,52,20,60,28,35,3,43,11,51,19,59,27,34,2,42,10,50,18,58,26,33,1,41,9,49,17,57,25};
const char expansion_pbox[48]={32,1,2,3,4,5,4,5,6,7,8,9,8,9,10,11,12,13,12,13,14,15,16,17,16,17,18,19,20,21,20,21,22,
    23,24,25,24,25,26,27,28,29,28,29,30,31,32,1};
const char straight_pbox[32]={16,7,20,21,29,12,28,17,1,15,23,26,5,18,31,10,2,8,24,14,32,27,3,9,19,13,30,6,22,11,4,25};
const char sbox[8][16][4]={{14,0,4,15,4,15,1,12,13,7,14,8,1,4,8,2,2,14,13,4,15,2,6,9,11,13,2,1,8,1,11,7,3,10,15,5,10,6,12,11,6,12,9,3,12,11,7,14,5,9,3,10,9,5,10,0,0,3,5,6,7,8,0,13},
    {15,3,0,13,1,13,14,8,8,4,7,10,14,7,11,1,6,15,10,3,11,2,4,15,3,8,13,4,4,14,1,2,9,12,5,11,7,0,8,6,2,1,12,7,13,10,6,12,12,6,9,0,0,9,3,5,5,11,2,14,10,5,15,9},
    {10,13,13,1,0,7,6,10,9,0,4,13,14,9,9,0,6,3,8,6,3,4,15,9,15,6,3,8,5,10,0,7,1,2,11,4,13,8,1,15,12,5,2,14,7,14,12,3,11,12,5,11,4,11,10,5,2,15,14,2,8,1,7,12},
    {7,13,10,3,13,8,6,15,14,11,9,0,3,5,0,6,0,6,12,10,6,15,11,1,9,0,7,13,10,3,13,8,1,4,15,9,2,7,1,4,8,2,3,5,5,12,14,11,11,1,5,12,12,10,2,7,4,14,8,2,15,9,4,14},
    {2,14,4,11,12,11,2,8,4,2,1,12,1,12,11,7,7,4,10,1,10,7,13,14,11,13,7,2,6,1,8,13,8,5,15,6,5,0,9,15,3,15,12,0,15,10,5,9,13,3,6,10,0,9,3,4,14,8,0,5,9,6,14,3},
    {12,10,9,4,1,15,14,3,10,4,15,2,15,2,5,12,9,7,2,9,2,12,8,5,6,9,12,15,8,5,3,10,0,6,7,11,13,1,0,14,3,13,4,1,4,14,10,7,14,0,1,6,7,11,13,0,5,3,11,8,11,8,6,13},
    {4,13,1,6,11,0,4,11,2,11,11,13,14,7,13,8,15,4,12,1,0,9,3,4,8,1,7,10,13,10,14,7,3,14,10,9,12,3,15,5,9,5,6,0,7,12,8,15,5,2,0,14,10,15,5,2,6,8,9,3,1,6,2,12},
    {13,1,7,2,2,15,11,1,8,13,4,14,4,8,1,7,6,10,9,4,15,3,12,10,11,7,14,8,1,4,2,13,10,12,0,15,9,5,6,12,3,6,10,9,14,11,13,0,5,0,15,3,0,14,3,5,12,9,5,6,7,2,8,11}};

#define ULL unsigned long long
#define UL unsigned long

#define DEFAULT_KEY 0xAABB09182736CCDD;
#define  DEFAULT_PLAIN_TEXT 0x123456ABCD132536;
#define RIGHT_SECTION_MASK 0x00000000FFFFFFFF
#define LEFT_CIPHER_KEY_MASK 0x0000FFFFFFF0000000
#define RIGHT_CIPHER_KEY_MASK 0x000000000FFFFFFF
#define TEXT_LENGTH 64
#define CIPHER_KEY_LENGTH 56
#define ROUND_KEY_LENGTH 48
#define ROUNDS 16

ULL permutation(ULL text, const char table[]);
void tranformKey(ULL key, ULL keys[]);
ULL compression(UL left, UL right);
ULL rounds(UL left, UL right, ULL keys[]);
void substitution(char origin[], char result[], int idx);
void setKeyPlainText(ULL* key, ULL* plainText, char* argv[]);
void ull2BinStr(ULL num, char* binStr, int size);
ULL hexStr2ULL(char* hexStr);
ULL binStr2ULL(char* binStr, const int size);
UL getLeftSection(ULL text);
UL getRightSection(ULL text);
UL getLeftSectionOfCipherKey(ULL key);
UL getRightSectionOfCipherKey(ULL key);
UL leftShift(UL num, int const shift);

int main(){
    ULL key;
    ULL plainText;

    // Step1: Get Key and Plain Text
    printf("Please enter your key: ");
    scanf("%llx", &key);
    printf("Please enter your Plain Text: ");
    scanf("%llx", &plainText);

    printf("Selected Key: 0x%016llX\n",key);
    printf("Selected Plain Text: 0x%016llX\n\n",plainText);

    // Step2: Convert Plain Text to LeftSection(0) and RightSection(0) by using Initial Permutation
    ULL afterInitPermut = permutation(plainText, initial_permutation);
    UL left = getLeftSection(afterInitPermut);
    UL right = getRightSection(afterInitPermut);
    printf("After Initial Permutation: 0x%016llX\n",afterInitPermut);
    printf("After Splitting: L0 = 0x%08lX, R0 = 0x%08lX\n",left,right);

    // Step3: Take 16 rounds which need LS, RS, and key
    ULL keys[16];
    // Step3-1: Convert 64bits key to 48bits key
    tranformKey(key, keys);
    ULL afterRounds = rounds(left, right, keys);
    printf("After Combination: 0x%016llX\n",afterRounds);

    // Step4: Convert LS(16) and RS(16) to Cipher Text by using Final Permutation
    ULL cipherText = permutation(afterRounds, final_permutation);
    printf("Cipher Text: 0x%016llX\n",cipherText);

    return 0;
}

// convert text to unsigned long long by using permutation table
ULL permutation(ULL text, const char table[]){
    char binText[TEXT_LENGTH];
    char ret[TEXT_LENGTH];

    ull2BinStr(text,binText,TEXT_LENGTH);

    for(int i=0;i<TEXT_LENGTH;i++){
        ret[i] = binText[table[i]-1];
    }
    
    return binStr2ULL(ret,TEXT_LENGTH);
}

// transform key to 16 keys
void tranformKey(ULL key, ULL keys[]){
    char strKey[TEXT_LENGTH];
    char cipherKey[CIPHER_KEY_LENGTH];
    ull2BinStr(key,strKey,TEXT_LENGTH); 

    // parity bit drop
    for(int i=0;i<CIPHER_KEY_LENGTH;i++){
        cipherKey[i] = strKey[parity_drop[i]-1];
    }

    ULL ullCipherKey = binStr2ULL(cipherKey,CIPHER_KEY_LENGTH);
    UL left = getLeftSectionOfCipherKey(ullCipherKey);
    UL right = getRightSectionOfCipherKey(ullCipherKey);
    // printf("After Parity Bit Drop: 0x%014llX\n",ullCipherKey);
    // printf("After Splitting: L[0] = 0x%07lX, R[0] = 0x%07lX\n",left,right);

    for(int i=1;i<=ROUNDS;i++){
        // set shift bit
        int shift = 0;
        if(i==1||i==2||i==9||i==16)
            shift = 1;
        else
            shift = 2;
        // shift left and right section of cipher key
        left = leftShift(left, shift);
        right = leftShift(right, shift);

        //compression pbox
        keys[i-1] = compression(left,right);
        // printf("Round Key[%d]: 0x%012llX\n",i,keys[i-1]);
    }
}

// compress 28bits of left and right to 48bits round key
ULL compression(UL left, UL right){
    ULL mergeLeftRight = 0;
    char mergeLeftRightStr[CIPHER_KEY_LENGTH];
    char roundKey[ROUND_KEY_LENGTH];    

    // merge left to right
    mergeLeftRight |= ((ULL)left<<(CIPHER_KEY_LENGTH/2));
    mergeLeftRight |= (ULL)right;
    // printf("left: 0x%07lX, right: 0x%07lX\n",left,right);
    // printf("mergeLeftRight: 0x%014llX\n",mergeLeftRight);
    ull2BinStr(mergeLeftRight,mergeLeftRightStr,CIPHER_KEY_LENGTH);

    // get round key by using left, right ,and compression_table
    for(int i=0;i<ROUND_KEY_LENGTH;i++){
        roundKey[i] = mergeLeftRightStr[compression_table[i]-1];
    }

    return binStr2ULL(roundKey,ROUND_KEY_LENGTH);
}

// convert text to cipher text at each round
ULL rounds(UL left, UL right, ULL keys[]){
    ULL ret = 0;

    for(int i=0;i<ROUNDS;i++){
        // Step3-2: Convert 32bits RS to 48bits by using Expansion P-box
        char rightStr[TEXT_LENGTH/2];
        char expandedRightStr[ROUND_KEY_LENGTH];
        ULL expandedRight;

        ull2BinStr((ULL)right,rightStr,TEXT_LENGTH/2);
        for(int j=0;j<ROUND_KEY_LENGTH;j++){
            expandedRightStr[j] = rightStr[expansion_pbox[j]-1];
        }
        expandedRight = binStr2ULL(expandedRightStr, ROUND_KEY_LENGTH);

        // Step3-3: XOR operation to 48bits key and RS
        ULL afterXOR = expandedRight^keys[i];
        char afterXORStr[ROUND_KEY_LENGTH];
        ull2BinStr(afterXOR, afterXORStr,ROUND_KEY_LENGTH);

        // Step3-4: Convert 48bits to 32bits by using S-boxes
        char afterSBox[TEXT_LENGTH/2];
        for(int j=0;j<8;j++){
            substitution(afterXORStr, afterSBox, j);
        }

        // Step3-5: Convert 32bits to 32bits by using straight P-box
        char afterStrPBox[TEXT_LENGTH/2];
        for(int j=0;j<(TEXT_LENGTH/2);j++){
            afterStrPBox[j] = afterSBox[straight_pbox[j]-1];
        }
        UL afterFunc = (UL)binStr2ULL(afterStrPBox,TEXT_LENGTH/2);

        // Step3-6: XOR operation to LS and result of 3-5, and swap it to RS (in round 16 doesn't swap)
        if(i != ROUNDS-1){
            UL temp = left;
            left = right;
            right = temp^afterFunc;
        }else{
            left = left^afterFunc;
        }

        printf("L[%02d] = 0x%08lX, R[%02d] = 0x%08lX, Key[%02d] = 0x%012llX\n",i+1,left,i+1,right,i+1,keys[i]);
    }
    ret |= ((ULL)left<<(TEXT_LENGTH/2));
    ret |= (ULL)right;

    return ret;
}

// convert origin to result by using s-boxes
// idx is for select s-box from s-boxes
void substitution(char origin[], char result[], int idx){
    int row = 8*(origin[idx*6+1]-'0') + 4*(origin[idx*6+2]-'0') + 2*(origin[idx*6+3]-'0') + (origin[idx*6+4]-'0');
    int col = 2*(origin[idx*6]-'0') + (origin[idx*6+5]-'0');

    int ret = sbox[idx][row][col];
    for(int i=0;i<4;i++){
        if(ret%2==1)
            result[idx*4+3-i] = '1';
        else
            result[idx*4+3-i] = '0';

        ret/=2;
    }
}

// convert string of user input of key and plain text to ULL variable
void setKeyPlainText(ULL* key, ULL* plainText, char* argv[]){
    *key = hexStr2ULL(argv[1]);
    *plainText = hexStr2ULL(argv[2]);
}

// convert unsigned long long to binary string
void ull2BinStr(ULL num, char* binStr, const int size){
    char* ret = malloc(sizeof(char)*(size+1));    //*
    ret[size+1] = 0; //*
    ULL mask = 1;
    
    for(int i=0;i<size;i++){
        char bit = (char)(mask&num);
        ret[size-i-1] = '0' + bit;
        num>>=1;
    }
    strcpy(binStr,ret);
    free(ret);
    return;
}

// convert hexademical string to unsigned long long
ULL hexStr2ULL(char* hexStr){
    ULL ret;
    char value[16];
    char *eptr;

    strcpy(value, hexStr);
    ret = strtoll(value,&eptr,16);
    return ret;
}

// convert binary string to unsigned long long
ULL binStr2ULL(char* binStr, const int size){
    ULL ret = 0;
    ULL mask = 1;

    for(int i=0;i<size-1;i++){
        if(binStr[i] == '1')
            ret++;
        ret<<=1;
    }
    if(binStr[size-1] == '1')
        ret++;
    return ret;
}

// get left section of 64 bits text
UL getLeftSection(ULL text){
    return (UL)(text>>(TEXT_LENGTH/2));
}

// get right section of 64 bits text
UL getRightSection(ULL text){
    return (UL)(text&RIGHT_SECTION_MASK);
}

// get left section of 64 bits text
UL getLeftSectionOfCipherKey(ULL key){
    return (UL)((key&LEFT_CIPHER_KEY_MASK)>>28);
}

// get right section of 64 bits text
UL getRightSectionOfCipherKey(ULL key){
    return (UL)(key&RIGHT_CIPHER_KEY_MASK);
}

// circulary left shift
UL leftShift(UL num, int const shift){
    int add = 0;
    for(int i=0;i<shift;i++){
        // check MSB is 1
        if((num>>(CIPHER_KEY_LENGTH/2-1)) %2 == 1)
            add = 1;
        else
            add = 0;
        num <<= 1;
        num += add;
    }
    num &= RIGHT_CIPHER_KEY_MASK;
    return num;
}