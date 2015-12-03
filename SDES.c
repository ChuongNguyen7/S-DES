#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// method parameters
int permutation10(int key, int answer);
int ls1(int permute10, int answer);
int permutation8(int ls1, int answer);
int ls2(int ls1, int answer);
int initialP(int plain, int answer);
int ep(int plainanswer, int answer);
int xorkey(int key, int init, int answer);
int s0Box(int xorFK1answer, int answer);
int s1Box(int xorFK1answer, int answer);
int permute4(int s0, int s1, int answer);
int xorFK1(int p4, int init, int answer);
int switchsw(int fk1, int answer);
int xorFK2(int p4, int init, int answer);
int inverseP(int fk2, int answer);
int arrayrconvert8(int *array, int answer);
int arrayrconvert10(int *array, int answer);


int main()
{
	// open or create files
	FILE *filelist = fopen("/Users/Nguyen/Documents/cs468/project1/filelist.txt","r");
	FILE *cryptFile = fopen("/Users/Nguyen/Documents/cs468/project1/crypt-17.txt","r");
	FILE *hello = fopen("/Users/Nguyen/Documents/cs468/project1/plain-17.txt","w");
	FILE *filename;
	// if filelist.txt not found
	if (filelist == NULL) {
 		 printf("file not found! \n");
 		 exit(1);
	}
	// for writing to output text
	char nameplain[12] = "plain-17.txt";
	char namecrypt[12] = "crypt-17.txt";
	char line2[13] = {"Chuong Nguyen"};
	char line5[3] = {"ECB"};
	int line6[8] = {0,0,0,0,0,0,0,0};
	
	for (int i = 0; i < 12; i++){
		fprintf(hello, "%c", nameplain[i]);
	}
	fprintf(hello, "\n");
	for (int i = 0; i < 13; i++){
		fprintf(hello, "%c", line2[i]);
	}
	fprintf(hello, "\n");
	// initial arrays to hold key and block of ciphertext 
	int line = 0;
	char *input = malloc(1024 * sizeof(char));
	char crypt17[10];
	char *crypttext = malloc(1024 * sizeof(char));
	char eightblock[8];
	char *cryptcopy = malloc(1024 * sizeof(char));
	char filelistarray[50];
	int filetype = 0;
	int status = 0;
	int textblocks = 8;
	int blockcount = 0;
	
	while(fgets(filelistarray, 50, filelist)){
	
		line++;
		printf("Line:%d -> %s", line, filelistarray);
		printf("\n");
		
		if (line == 1){
			// open crypt-17 if first letter starts with c
			if (filelistarray[0] == 'c'){
				filetype = 1;
			}else{
				filetype = 0;
			}		
		}		
	}
	
	if (filetype == 1){
		filename = cryptFile;
	}else{
		filename = hello;
	}
	
	line = 0;
	fclose(filelist);
	
	// open either crypt-17 or plain and read line by line
	while(fgets(input, 1024, filename)){
	
		line++;
		
		if (line == 3){
			 // status of encrypt/decrypt used later to print to output
			 if (input[0] == 'D'){
			 	status = 1;
			 	fprintf(hello, "E");
			 }else{
			 	status = 0;
			 	fprintf(hello, "D");
			 } 
		}
		if (line == 4){
			 for (int i = 0; i < 10; i++){
			 	crypt17[i] = input[i];
		}
		}
		// line of cryptext gets assign to array
		if (line == 7){
			 for (int i = 0; i < 1000; i++){
			 	crypttext[i] = input[i];
		}
		}
	}
	fprintf(hello, "\n");
	fprintf(hello, "ECB");
	fprintf(hello, "\n");
	for (int i = 0; i < 10; i++){
		fprintf(hello, "%c", crypt17[i]);
	}
	fprintf(hello, "\n");
	fprintf(hello, "00000000");
	fprintf(hello, "\n");
	

	int length = strlen(crypttext);
	int sum8 = 0;
	while (sum8 < 8){

		eightblock[sum8] = crypttext[sum8];
		sum8++;
	}
	// extract every 8 bit and place in array
	for (int i = 0; i < length;){
		
		for (int j = 0; j < 8; j++){
		
			eightblock[j] = crypttext[i+j];
		}
		
		int eightanswer[8] = {0,0,0,0,0,0,0,0};
		int *eightbitanswer = eightanswer;
		for (int i = 0; i < 8; i++){
			eightbitanswer[i] = eightblock[i] - '0';
		}
		
		int initkey[10] = {0,0,0,0,0,0,0,0,0,0};	
		int *keyarray = initkey;
		for (int i = 0; i < 10; i++){
			keyarray[i] = crypt17[i] - '0';
		}
		

		// convert using powers of two into an int 
		int eightintanswer = 0;
		eightintanswer = arrayrconvert8(eightbitanswer, eightintanswer);
		int keyintanswer = 0;
		keyintanswer = arrayrconvert10(keyarray, keyintanswer);
		
		// padding if crypttext array is clean multiple of 8
		blockcount++;
		textblocks = length / 8;
		if (textblocks == blockcount){
			printf("cool");
			int mod = length % 8;
			if (mod != 0){
				/* create 8 bits of all 1s and depending on how much is remainder
					shift it right certain places then back left to zero out right side
				*/
				int allones = 225;
				int remainder = 8 - mod;
			    allones = allones >> remainder;
				eightintanswer = allones << remainder;
			}
		}
		
		
		
		// arrays for use for key generation and encryption methods	
		int keyvalue[10] = {1,1,0,0,1,0,0,0,0,1};
		int answer[10] = {0,0,0,0,0,0,0,0,0,0};
		int leftshift[10] = {0,0,0,0,0,0,0,0,0,0};
		int leftshift2a[10] = {0,0,0,0,0,0,0,0,0,0};
		int permute8[10] = {0,0,0,0,0,0,0,0,0,0};
		int secondpermute8[8] = {0,0,0,0,0,0,0,0};
		int initialanswer[8] = {0,0,0,0,0,0,0,0};
		int xor[8] = {0,0,0,0,0,0,0,0};
		int epanswer[8] = {0,0,0,0,0,0,0,0};
		int p4array[4] = {0,0,0,0};
		int fk1array[8] = {0,0,0,0,0,0,0,0};
		int fk2array[8] = {0,0,0,0,0,0,0,0};
		int swarray[8] = {0,0,0,0,0,0,0,0};
		int cipher[8] = {0,0,0,0,0,0,0,0};
		int sboxanswer[4] = {0,0,0,0};
		int *ciphertext = cipher;
		int *fk2 = fk1array;
		int *sw = swarray;
		int *fk1 = fk1array;
		int *p4answer = p4array;
		int *sbox = sboxanswer;
		int *xoranswer = xor;
		int *ep1 = epanswer;
		int *init = initialanswer;
		int initialkey = keyintanswer;
		int *p10answer = answer;
		int *p8answer = permute8;
		int *secondpermute = secondpermute8;
		int *lsanswer = leftshift;
		int *ls2answer = leftshift2a;
		int total = 0;
		int permute10answer = 0;

		
		permute10answer = permutation10(initialkey,permute10answer);
	
		int ls1output = 0;
		int permute8answer = 0;
		
		ls1output = ls1(permute10answer, ls1output);

		permute8answer = permutation8(ls1output, permute8answer);
		
		int ls2output = 0;
		
		ls2output = ls2(ls1output, ls2output);
		
		int secondkey = 0;
		secondkey = permutation8(ls2output, secondkey);
		
		int plainanswer = 0;
		plainanswer = initialP(eightintanswer, plainanswer);
		
		int epoutput = 0;
		epoutput = ep(plainanswer, epoutput);
		
		int xorkeyanswer = 0;
		
		if (status == 1){
			xorkeyanswer = xorkey(secondkey, epoutput, xorkeyanswer);
		}else{
			xorkeyanswer = xorkey(permute8answer, epoutput, xorkeyanswer);
		}

		int sbox0output = 0;
		
		sbox0output = s0Box(xorkeyanswer, sbox0output);
			
		int sbox1output = 0;
		
		sbox1output = s1Box(xorkeyanswer, sbox1output);
		
		int permute4answer = 0;
		permute4answer = permute4(sbox0output, sbox1output, permute4answer);
		
		int xorFK1answer = 0;
		xorFK1answer = xorFK1(permute4answer, plainanswer, xorFK1answer);
			
		int switchanswer = 0;
		switchanswer = switchsw(xorFK1answer, switchanswer);
	
		// second part of plaintext side
		
		int goodep = 0;
		goodep = ep(switchanswer, goodep);
		
		int xoransweragain = 0;
		if (status == 1){
			xoransweragain = xorkey(permute8answer, goodep, xoransweragain);
		}else{
			xoransweragain = xorkey(secondkey, goodep, xoransweragain);
		}
			
		sbox0output = s0Box(xoransweragain, sbox0output);
			
		sbox1output = s1Box(xoransweragain, sbox1output);
			
		int p4answeragain = 0;
		p4answeragain = permute4(sbox0output, sbox1output, p4answeragain);
			
		int fk2answer = 0;
		fk2answer = xorFK2(p4answeragain, switchanswer, fk2answer);
		
		int ipinverseanswer = 0;
		ipinverseanswer =  inverseP(fk2answer, ipinverseanswer);
			
		char c = (char)ipinverseanswer;	
		fprintf(hello, "%c", c);
		
		
		i = i + 8;	
		
		
	}
	}

/* for method, assign each permute index then shift to right to mask and isolate
	shift back left and OR with answer. every shift back right goes one less space
*/
int permutation10(int key, int answer)
{

    int p10[10] = {3,5,2,7,4,10,1,9,8,6};
    for (int i = 0; i < 10; i++){
    
    	int index = p10[i];
    	int a = key >> (10-index);
    	int b = a & 1;
    	b = b << (9 - i);
    	answer = answer | b;
    		
    }
    return answer;       
}

// mask with int 31 saves blocks of 5 and 0s out left 
int ls1(int permute10, int answer)
{

	int a = permute10 >> 5;
	int b = permute10 & 31;
	int c = a >> 4;
	int d = b >> 4;
	int e = (a << 1); 
	int f = (b << 1);
	e = e & 31;
	f = f & 31;
	e = e | c;
	f = f | d;
	e = e << 5;
	answer = e | f;
	return answer;
	
}

// same type of technique as permute10 method, except used with 8 position array
int permutation8(int ls1, int answer)
{

    int p8[8] = {6,3,7,4,8,5,10,9};
    for (int i = 0; i < 8; i++){
    
    	int index = p8[i];
    	int a = ls1 >> (10-index);
    	int b = a & 1;
    	b = b << (7 - i);
    	answer = answer | b;
    	
    }
    return answer;   
}
// shift to right and mask to isolate value
int ls2(int ls1, int answer)	
{

	int a = ls1 >> 5;
	int b = ls1 & 31;
	int c = a >> 3;
	int d = b >> 3;
	int e = (a << 2); 
	int f = (b << 2);
	e = e & 31;
	f = f & 31;
	e = e | c;
	f = f | d;
	e = e << 5;
	answer = e | f;
	return answer;
}
// same technique as the other permutation methods
int initialP(int plain, int answer){

	int ip[8] = {2,6,3,1,4,8,5,7};
    for (int i = 0; i < 8; i++){
    
    	int index = ip[i];
    	int a = plain >> (8-index);
    	int b = a & 1;
    	b = b << (7 - i);
    	answer = answer | b;
    }
    return answer;
}
// same technique as the other permutation methods
int ep(int plainanswer, int answer){
	
	int eparray[8] = {4,1,2,3,2,3,4,1};
	int a = plainanswer & 15;
    for (int i = 0; i < 8; i++){
    
    	int index = eparray[i];
    	int a = plainanswer >> (4-index);
    	int b = a & 1;
    	b = b << (7 - i);
    	answer = answer | b;
    	 	
    }
    return answer;
}

int xorkey(int key, int init, int answer){

	answer = key ^ init;
	return answer;
}

// created separate variables to hold row and column when indexing into sbox
int s0Box(int xorFK1answer, int answer){

	int s0[4][4] = {{1,0,3,2}, {3,2,1,0}, {0,2,1,3}, {3,1,3,2}};
	int row = 0;
	int col = 0;
	int srow[2];
	srow[0] = 0;
	srow[0] = 0;
	int scol[2];
	scol[0] = 0;
	scol[0] = 0;
	int a = xorFK1answer >> 4;
	int b = a & 1;
	int c = a >> 3;
	c = c << 1;
	c = c | b;
	int d = a >> 1;
	d = d & 3;
	int s0answer = s0[c][d];

	if (s0answer == 3){
		answer = 3;
	}
	if (s0answer == 2){
		answer = 2;
	}
	if (s0answer == 1){
		answer = 1;
	}
	if (s0answer == 0){
		answer = 0;
	}

	return answer;
}

int s1Box(int xorFK1answer, int answer){

	int s1[4][4] = {{0,1,2,3}, {2,0,1,3}, {3,0,1,0}, {2,1,0,3}};
	int row = 0;
	int col = 0;
	int srow[2];
	srow[0] = 0;
	srow[0] = 0;
	int scol[2];
	scol[0] = 0;
	scol[0] = 0;
	int a = xorFK1answer & 15;
	int b = a & 1;
	int c = a >> 3;
	c = c << 1;
	c = c | b;
	int d = a >> 1;
	d = d & 3;
	int s1answer = s1[c][d];
	
	if (s1answer == 3){
		answer = 3;

	}
	if (s1answer == 2){
		answer = 2;

	}
	if (s1answer == 1){
		answer = 1;
	}
	if (s1answer == 0){
		answer = 0;
	}
	return answer;

}


int permute4(int s0, int s1, int answer){
	
	int p4[4] = {2,4,3,1};
    int temp1 = 0;
    int temp2 = 0;
    temp1 = s0 << 2;
    temp2 = temp1 | s1;
    
    for (int i = 0; i < 4; i++){
    
    	int index = p4[i];
    	int a = temp2 >> (4-index);    	
    	int b = a & 1;  	
    	b = b << (3 - i);
    	answer = answer | b;
    }

    return answer;
}

int xorFK1(int p4, int init, int answer){

	int a = init >> 4;
	int b = p4 ^ a;
	int c = init & 15;
	int d = b << 4;
	answer = d | c;
	return answer;
}

int switchsw(int fk1, int answer){
	
	int temp = 0;
	temp = fk1 >> 4;
	temp = temp & 15;
	int temp2 = 0;
	temp2 = fk1 & 15;
	temp2 = temp2 << 4;
	answer = temp | temp2;
	return answer;
}

int xorFK2(int p4, int init, int answer){

	int a = init >> 4;
	int b = p4 ^ a;
	int c = init & 15;
	int d = b << 4;
	answer = d | c;
	return answer;
}

int inverseP(int fk2, int answer){
	
	int ip[8] = {4,1,3,5,7,2,8,6};
    for (int i = 0; i < 8; i++){
    
    	int index = ip[i];
    	int a = fk2 >> (8-index);
    	int b = a & 1;
    	b = b << (7 - i);
    	answer = answer | b;	
    }
    return answer;
}

char charconvert(int *array, char character){
	
	int temp[8] = {0,0,0,0,0,0,0,0};
	int count = 0;
	temp[0] = array[7];
	temp[1] = array[6];
	temp[2] = array[5];
	temp[3] = array[4];
	temp[4] = array[3];
	temp[5] = array[2];
	temp[6] = array[1];
	temp[7] = array[0];
	int answer = 0;
	
    for (int i = 0; i < 8; i++){
    	
    	if (temp[i] == 1){
    		answer += pow(2, i);
    	}
    }
    character = (char)answer;
    return character;
}
// look for 1s in array and add value according to powers of 2 according to position
int arrayrconvert8(int *array, int answer){
	
	int temp[8] = {0,0,0,0,0,0,0,0};
	int count = 0;
	temp[0] = array[7];
	temp[1] = array[6];
	temp[2] = array[5];
	temp[3] = array[4];
	temp[4] = array[3];
	temp[5] = array[2];
	temp[6] = array[1];
	temp[7] = array[0];
	
	answer = 0;
	
    for (int i = 0; i < 8; i++){
    	
    	if (temp[i] == 1){
    		answer += pow(2, i);
    	}
    }
    return answer;
}
// same technique as method above except for array of 10 positions
int arrayrconvert10(int *array, int answer){
	
	int temp[10] = {0,0,0,0,0,0,0,0,0,0};
	int count = 0;
	
	temp[0] = array[9];
	temp[1] = array[8];
	temp[2] = array[7];
	temp[3] = array[6];
	temp[4] = array[5];
	temp[5] = array[4];
	temp[6] = array[3];
	temp[7] = array[2];
	temp[8] = array[1];
	temp[9] = array[0];
	
	answer = 0;
	
    for (int i = 0; i < 10; i++){
    	
    	if (temp[i] == 1){
    		answer += pow(2, i);
    	}
    }
    return answer;
}


		



	
