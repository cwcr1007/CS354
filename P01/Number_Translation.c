#include <stdio.h>

#define BINARY_STRING_LENGTH 33
#define HEX_STRING_LENGTH 11

void GetBinaryFromUser(char *binary);
void GetHexFromUser(char *hex);
void GetDecimalFromUser(unsigned int *x);

void ConvertBinaryToDecimal(const char *binary, unsigned int *decimal);
void ConvertHexToDecimal(const char *hex, unsigned int *decimal);
void ConvertDecimalToBinary(const unsigned int decimal, char *binary); 
void ConvertDecimalToHex(const unsigned int decimal, char *hex); 

int main(){
    char binary[BINARY_STRING_LENGTH] = "11011";
    char hex[HEX_STRING_LENGTH] = "0x3F";
	unsigned int decimal = 31;
	
	enum MENU {binary_to_decimal=1, hex_to_decimal, decimal_to_binary, decimal_to_hex};
	while (1) {
		printf("Which conversion would you like to do?\n");
		printf("  %d. Binary to Decimal\n", binary_to_decimal);
		printf("  %d. Hex to Decimal\n", hex_to_decimal);
		printf("  %d. Decimal to Binary\n", decimal_to_binary);
		printf("  %d. Decimal to Hex\n", decimal_to_hex);
		printf("  q to Quit\n");
		int choice;
		if (!scanf("%d", &choice)) return 0;  // exits if user enters something other than a digit
		
		switch (choice) {
			case binary_to_decimal: {
				GetBinaryFromUser(binary); 
				ConvertBinaryToDecimal(binary, &decimal); 
				printf("Binary: %s\nDecimal: %u\n\n", binary, decimal);
			} break;
			case hex_to_decimal: {
				GetHexFromUser(hex); 
				ConvertHexToDecimal(hex, &decimal); 
				printf("Hex: %s\nDecimal: %u\n\n", hex, decimal);
			} break;
			case decimal_to_binary: {
				GetDecimalFromUser(&decimal); 
				ConvertDecimalToBinary(decimal, binary); 
				printf("Decimal: %u\nbinary: %s\n\n", decimal, binary);
			} break;
			case decimal_to_hex: {
				GetDecimalFromUser(&decimal); 
				ConvertDecimalToHex(decimal, hex); 
				printf("Decimal: %u\nHex: %s\n\n", decimal, hex);
			} break;
			default: return 0; // exit if user enters an invalid number
		}
	}
	return 0;
}

void GetBinaryFromUser(char * binary) {
    // write your code here to complete this function
    printf("Please enter binary string here: ");
    scanf("%s", binary);
    return;
}

void GetHexFromUser(char * hex) {
    // this function has been written for you
    printf("Please enter hex string here (do include the 0x prefix): ");
    scanf("%s", hex);
	for (char *p=hex;*p;p++) if(*p>='a') *p-='a'-'A';  // to upper case
    return;
}

void GetDecimalFromUser(unsigned int *x) {
    // write your code here to complete this function
    printf("Please enter decimal number here: ");
    scanf("%u", x);
    return;
}

void ConvertBinaryToDecimal(const char * binary, unsigned int *decimal) {
    // write your code here to complete this function
    int length = 0;
    while (*(binary+length) != '\0'){
        length++;
    }
    length--;

    *decimal = 0;
    if (*(binary+length) == '1'){
        *decimal = 1;
    }    
    length--;

    int digit = 1;
    while (length>=0){
        if (*(binary+length) == '1'){
            int num = 1;
            for (int i=0; i<digit; i++){
                num = num * 2;
            }
            *decimal += num;
        }   
        length--;
        digit++;
    } 
     // This hardcoded answer will be incorrect for all but one input. Change this line!
	return;
}

void ConvertHexToDecimal(const char *hex, unsigned int *decimal) {
    // write your code here to complete this function
    int length = 0;
    int base = 1;
    while (*(hex+length) !='\0'){
        length++;
    }
    length --;
    *decimal = 0;
    while (length>=2){
        if (*(hex+length) >= '0' && *(hex+length) <= '9'){
            *decimal += (*(hex+length)-48) * base;
            base = base*16;
        }    
        else if (*(hex+length) >= 'A'&& *(hex+length) <= 'F'){
            *decimal += (*(hex+length)-55) * base;
            base = base*16;
        }
        length--;
    }
	// This hardcoded answer will be incorrect for all but one input. Change this line!
	return;
}

void ConvertDecimalToBinary(const unsigned int decimal, char *binary) {
    // write your code here to complete this function
    // do not include leading zeros in the answer
    // if the input is 0 then the output should be just 0
    int total = decimal;
    int arr[BINARY_STRING_LENGTH];
    int idx = 0;

    if (decimal == 0){
        binary = "0";
    }    
    else{
        while (total>0){
            int num = 1;
            int power = 0;
            if (num == total){
                arr[idx] = 0;
                total--;
            }
            else{
                while (num<=total){
                    num = num * 2;
                    power++;   
                }
                total -= num/2;
                arr[idx] = power-1;
            }
            idx++;
        }
        
        binary[arr[0]+1] = '\0';
        for (int j=0; j<arr[0]+1; j++){
            binary[j] = '0';
        }

        for (int i=0; i<idx; i++){
            binary[arr[0]-arr[i]] = '1';
        }        
    }
    // This hardcoded answer will be incorrect for all but one input. Change this line!
    return;
}
void ConvertDecimalToHex(const unsigned int decimal, char *hex) {
    // write your code here to complete this function
    // do not include leading zeros in the answer
    // do include the prefix 0x
    // if the input is 0 then the output should be 0x0 
    int num = decimal;
    char arr[HEX_STRING_LENGTH];    
    int idx = 0;

    while (num > 0){
        int reminder = num % 16;
        switch (reminder){
            case 10:
                arr[idx] = 'A';
                break;
            case 11:
                arr[idx] = 'B';
                break;
            case 12:
                arr[idx] = 'C';
                break;
            case 13:
                arr[idx] = 'D';
                break;
            case 14:
                arr[idx] = 'E';
                break;
            case 15:
                arr[idx] = 'F';
                break;
            default:
                arr[idx] = reminder+'0';
        }
        num = num/16;
        idx++;
    }
    hex[0] = '0';
    hex[1] = 'X';   
    for (int i=2, j=idx-1; j>=0; i++,j--){
        hex[i] = arr[j];
    }
    hex[idx+2] = '\0';
    // This hardcoded answer will be incorrect for all but one input. Change this line!
    return;
}


