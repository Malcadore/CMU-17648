/* Example showing struct layouts and memory padding.
Author: Scott Pavetti
Date  : March 27, 2025
Course: 17648 Sensor Based Systems
Carnegie Mellon University
*/
#include <iostream>
#include <stdint.h>
#include <iomanip>

using namespace std;

// Compile with:
//>g++ example.c - o example

int main();

// https://stackoverflow.com/questions/21092415/force-c-structure-to-pack-tightly
// Method 1 (GCC specific) : Use __attribute__ ((packed))
// Method 2 (Windows) : Use a #pragma compiler flag.  Example commented below.
//  #pragma pack(push, 1)
//  struct { short a; int b; };
//  #pragma pack(pop)

// A and B have the same types but different 
// ordering.  
// 8 bytes total
struct A
{
   char a; // 1 bytes padding
   char b; // 1 bytes padding
   uint c;  // no padding at the end, 4-byte boundary aligned
};

// Same members as A, different arrangement.
// 12 bytes total.
struct B
{
   char a; // 3 bytes padding
   uint b; //aligned to the nearest 4th byte boundary
   char c; // padded 3 bytes at the end.
};

// 6 bytes in size, since all padding is removed.
struct __attribute__ ((packed)) C {
   byte a;
   int b;   
   byte c;
};

// Similar to B, but instead of int, we use short for i.
// packing is aligned as follows in the comments.
// 6 bytes total.
struct D
{
   byte a; // 1 byte padding
   short b; //aligned to the nearest 2nd byte boundary
   byte c; // padded 1 bytes at the end.
};

// Similar to B3, but instead it's packed.
// packing is aligned as follows in the comments.
// 4 bytes total.
struct __attribute__ ((packed)) E
{
   byte a; // 1 byte padding
   short b; //aligned to the nearest 2nd byte boundary
   byte c; // padded 1 bytes at the end.
};

// 3 bytes in size.
struct F
{
    byte a;
    byte b;
    byte c;
};

// Similar to struct A, but instea of char, use short.
// Note that no padding was used because it was half word
// aligned.
// 8 bytes total.
struct G
{
   short a; // 0 bytes padding
   short b; // 0 bytes padding
   int c;  // no padding at the end, 4-byte boundary aligned
};

int main() {
	cout << "sizeof(A) = " << sizeof(A) << " bytes" << endl;
	cout << "sizeof(B) = " << sizeof(B) << " bytes" << endl;
	cout << "sizeof(C) = " << sizeof(C) << " bytes" << endl;
	cout << "sizeof(D) = " << sizeof(D) << " bytes" << endl;
	cout << "sizeof(E) = " << sizeof(E) << " bytes" << endl;
	cout << "sizeof(F) = " << sizeof(F) << " bytes" << endl;
	cout << "sizeof(G) = " << sizeof(G) << " bytes" << endl;
	// Here's an example of printing out the struct itself.
	B s = {(char)0xFF, 0xFFFFFFFF, (char)0xFF};
	cout << hex << uppercase << "struct.a = 0x" << setw(2) << (int)(unsigned char)(s.a);
	cout << hex << uppercase << "  struct.b = 0x" << s.b;
	cout << hex << uppercase << "  struct.c = 0x" << setw(2) << (int)(unsigned char)s.c << endl;


	// Let's look at the contents of the structure memory.
	B s2;
	s2.a = 0xFF;
	s2.b = 0xFFFFFFFF;
	s2.c = 0xFF;

	// Get the starting address of the structure
	unsigned char* ptr = reinterpret_cast<unsigned char*>(&s2);
	size_t size = sizeof(B);

	std::cout << "Memory block of B (size: " << size << " bytes):" << std::endl;
	for (size_t i = 0; i < size; ++i) {
		// Print each byte in hexadecimal format
		std::cout << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(ptr[i]) << " ";
	}
	std::cout << std::endl;
        
}
