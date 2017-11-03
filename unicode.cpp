#include <iostream>
#include <fstream>
#include <stdint.h>

using namespace std;
	FILE* input;
int getWidth(char a){
	int width;
	if((a & 0x80) == 0)
		width = 1;
	else if((a & 0xE0) == 0xC0)
		width = 2;
	else if((a & 0xF0) == 0xE0)
		width = 3;
	else if((a & 0xF8) == 0xF0)
		width = 4;
	else{
		 width = -1;
		// cout << (a & 0x80) << endl;
		 //cout << (a & 0xE0) << endl;
		 //cout << (a & 0xF0) << endl;
		 //cout << (a & 0xF8) << endl;
	 }
	return width;
}

uint32_t get1byte(uint32_t a){
	return a;
	
}

uint32_t get2bytes(uint32_t a){
	uint32_t ans;
	uint32_t b = fgetc(input);
	ans = 	((( a & 0x3F) << 6) +
			 (( b & 0x7F))); 
	return ans;
}

uint32_t get3bytes(uint32_t a){
	uint32_t ans;
	uint32_t b = fgetc(input);
	uint32_t c = fgetc(input);
	ans = 	((( a & 0x1F) << 12) +
			 (( b & 0x7F) <<  6) +
			 (( c & 0x7F))); 
	return ans;
}

uint32_t get4bytes(uint32_t a){
	uint32_t ans;
	uint32_t b = fgetc(input);
	uint32_t c = fgetc(input);
	uint32_t d = fgetc(input);
	ans = 	((( a & 0x0F) << 18) +
			 (( b & 0x7F) << 12) +
			 (( c & 0x7F) <<  6) +
			 (( d & 0x7F))	   ); 
	return ans;
}

uint32_t getUtf8Value(uint32_t a, int width){
	if(width ==1)
		return get1byte(a);
	else if (width == 2)
		return get2bytes(a);
	else if(width == 3)
		return get3bytes(a);
	else if(width == 4)
		return get4bytes(a);
	else cout << "invalid width" << endl;
	return 0;
}

int main(int argc, char** argv){

	int width;
	int ans;
	input=fopen("unicode_input.txt", "r+b");
	uint8_t bytes[4];
	uint32_t a = fgetc(input);
	while (a != EOF){
		width = getWidth(a);
		ans = getUtf8Value(a, width);
		cout << hex << ans << " ";
		a = fgetc(input);
	}
	
	system("PAUSE");
	return 0;
	
}
