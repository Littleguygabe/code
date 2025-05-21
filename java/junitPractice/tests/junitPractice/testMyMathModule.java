package junitPractice;

import static org.junit.jupiter.api.Assertions.*;

import org.junit.jupiter.api.Test;

class testMyMathModule {

	
	@Test
	void test1() {
		int myAns = MathModule.myMultiply(4, 2);
		assertEquals(9,myAns);
	}

}
