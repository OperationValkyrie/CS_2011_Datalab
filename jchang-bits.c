/* 
 * CS:APP Data Lab 
 * 
 * Jonathan Chang
 * jchang
 * 
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.  
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:
 
  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code 
  must conform to the following style:
 
  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>
    
  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.

 
  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting an integer by more
     than the word size.

EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

FLOATING POINT CODING RULES

For the problems that require you to implent floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operators (! ~ & ^ | + << >>)
     that you are allowed to use for your implementation of the function. 
     The max operator count is checked by dlc. Note that '=' is not 
     counted; you may use as many of these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce 
 *      the correct answers.
 */


#endif
/* 
 * bitXor - x^y using only ~ and & 
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 14
 *   Rating: 1
 */
int bitXor(int x, int y) {
	/* if x and y are neither And or None, then it can be Xor */
	int ifAnd= (x & y);
	int ifNone = ( ~x & ~y );
	return ~ifAnd & ~ifNone;
}

/* 
 * TMax - return maximum two's complement integer 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmax(void) {
	/* Shifting causes it to overflow and complement changes TMin to TMax */
	return ~(1 << 31);

}
/* 
 * isNotEqual - return 0 if x == y, and 1 otherwise 
 *   Examples: isNotEqual(5,5) = 0, isNotEqual(4,5) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 2
 */
int isNotEqual(int x, int y) {
	/* Xor is equivalent to !=; for some reason, !! to convert to boolean*/
	return !!(x ^ y);
}
/* 
 * replaceByte(x,n,c) - Replace byte n in x with c
 *   Bytes numbered from 0 (LSB) to 3 (MSB)
 *   Examples: replaceByte(0x12345678,1,0xab) = 0x1234ab78
 *   You can assume 0 <= n <= 3 and 0 <= c <= 255
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 10
 *   Rating: 3
 */
int replaceByte(int x, int n, int c) {
	/* Save the bits higher than n and OR bits together to replace */
	int nBits = n << 3;
	int higherBits = ~(255 << nBits) & x;
	int shiftedBits = c << nBits;
	return shiftedBits | higherBits;
}
/* 
 * fitsBits - return 1 if x can be represented as an 
 *  n-bit, two's complement integer.
 *   1 <= n <= 32
 *   Examples: fitsBits(5,3) = 0, fitsBits(-4,3) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int fitsBits(int x, int n) {
	/* Use shifting and ANDs to get the highest bit in x. Shift by n-1 and not to see if it stays */
	int signBit = x >> 31;
	int highestBit = (~x & signBit) + (x & ~signBit);
	return !(highestBit >> (n + ~0));
}
/* 
 * rotateLeft - Rotate x to the left by n
 *   Can assume that 0 <= n <= 31
 *   Examples: rotateLeft(0x87654321,4) = 0x76543218
 *   Legal ops: ~ & ^ | + << >> !
 *   Max ops: 25
 *   Rating: 3 
 */
int rotateLeft(int x, int n) {
	/* Slipt the shifting into right and left and then put those sides back together */
	int actualShift = 31 & (32 + ~n + 1);
	int rightSide = (x >> actualShift) & (~(~0 << n));
	int leftSide = x << n;
	return leftSide | rightSide;
}
/*
 * isPower2 - returns 1 if x is a power of 2, and 0 otherwise
 *   Examples: isPower2(5) = 0, isPower2(8) = 1, isPower2(0) = 0
 *   Note that no negative number is a power of 2.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 4
 */
int isPower2(int x) {
	/* Test if there is only one 1 and test if also positive */
	int isPower2= !(x ^ (x & (~x + 1)));
	int isNegative = ((x >> 31) | !x);         
	return isPower2 & !isNegative;
}
/* 
 * rempwr - Returns x%(2^n)
 *   Negative arguments should yield negative remainders
 *   Examples: rempwr2(15,2) = 3, rempwr2(-35,3) = -3
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3
 */
int rempwr2(int x, int n) {
	/* Calculate the 2^n and use & to mod, shift and & to account for n = 0 */
	int signBit = x >> 31;
	int power2 = 1 << n;
	int mod = ~((!!(x & (power2 + ~0)) << n)) + 1;
	return (x & (power2 + ~0)) + (mod & signBit);
}
/* 
 * conditional - same as x ? y : z 
 *   Example: conditional(2,4,5) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
int conditional(int x, int y, int z) {
	/* Use !! and ~ to turn x into boolean, then use  & to get necissary parts */
	int ifNotZero = !!x;
	int ifX = 1 + ~(ifNotZero & 1);
	int truePart = y & ifX;
	int falsePart = z & ~ifX;
	return truePart + falsePart;
}
/*
 * bitParity - returns 1 if x contains an odd number of 0's
 *   Examples: bitParity(5) = 0, bitParity(7) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 4
 */
int bitParity(int x) {
	  /* XORing returns a number with same even/odd number of 0's. Keep shifting until only 1 bit*/
	int fold = x;
	fold ^= fold >> 16;
	fold ^= fold >> 8;
	fold ^= fold >> 4;
	fold ^= fold >> 2;
	fold ^= fold >> 1;
	return fold & 1;
}
/* 
 * greatestBitPos - return a mask that marks the position of the
 *               most significant 1 bit. If x == 0, return 0
 *   Example: greatestBitPos(96) = 0x40
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 70
 *   Rating: 4 
 */
int greatestBitPos(int x) {
	/* ORing the folds together puts 1's after the significant bit, remove and mask remove all 1's but the first */
	int fold = x;
	int remove;
	int mask;
	fold |= fold >> 1;
	fold |= fold >> 2;
	fold |= fold >> 4;
	fold |= fold >> 8;
	fold |= fold >> 16;
	remove = (~fold >> 1) ^ (1 << 31);
	mask = fold & remove;
	return mask;
}
/* 
 * logicalNeg - implement the ! operator, using all of 
 *              the legal operators except !
 *   Examples: logicalNeg(3) = 0, logicalNeg(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 */
int logicalNeg(int x) {
	/* Use sign bit and sign of complement to do logical negative */
	int signBit = x >> 31;
	int complement = (~x + 1) >> 31;
	return (signBit | complement) + 1;
}
/* 
 * float_neg - Return bit-level equivalent of expression -f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representations of
 *   single-precision floating point values.
 *   When argument is NaN, return argument.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 10
 *   Rating: 2
 */
unsigned float_neg(unsigned uf) {
	/* Check for NaN and then return opposite of sign bit */
	int exp = uf & 0x7F800000;
	int mant = uf & 0x007FFFFF;
	
	if(exp == 0x7F800000 && mant > 0) {
		return uf;
	}
	return uf ^ 0x80000000;
}
/* 
 * float_f2i - Return bit-level equivalent of expression (int) f
 *   for floating point argument f.
 *   Argument is passed as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point value.
 *   Anything out of range (including NaN and infinity) should return
 *   0x80000000u.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
int float_f2i(unsigned uf) {
	/* Unable to compensate for overlflow overwise works */
	int sign = uf & 0x80000000;
	int exp = uf & 0x7F800000;
	int mant = uf & 0x007FFFFF;

	if(exp == 0x7F800000 && mant > 0) {
		return 0x80000000u;
	} else if(mant == 0 && exp == 0) {
		return 0;
	}
	
	exp >>= 23;
	exp -= 127;
	if(exp < 0) {
		return 0;
	} else if(mant == 0) {
		mant = 1;
	}
	if((mant << exp) > 0x7fffffff) {
		return 0x80000000u;
	}
	if(!!sign) {
		return ~mant + 1;
	}	
	return mant;
}
/* 
 * float_twice - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned float_twice(unsigned uf) {
	/* Check for NaN, else shift mant or add to exp */
	int sign = uf & 0x80000000;
	int exp = uf & 0x7F800000;
	int mant = uf & 0x007FFFFF;

	if(exp == 0x7F800000) {
		return uf;
	} else if(exp == 0) {
		mant <<= 1;
	} else {
		exp += 0x800000;
	}
	return sign + exp + mant;
}
