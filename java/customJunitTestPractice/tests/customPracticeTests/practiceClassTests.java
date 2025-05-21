package customPracticeTests;

import static org.junit.jupiter.api.Assertions.*;

import org.junit.jupiter.api.Test;

class practiceClassTests {

	@Test
	void testMultiply(){
		int output = practiceClass.myMultiply(4,2);
		assertEquals(8,output);
	}
	
	@Test
	void testListEquals() {
		int[] testList = {1,2,3,4,5};
		assertArrayEquals(testList,practiceClass.getList());
	}
	
	
}

