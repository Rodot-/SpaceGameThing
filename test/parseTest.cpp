#include "../Parsers/StringOps.h"






int main(void) {

	const char* t1 = "This is a test sentence to see if\nwhitespace removal is working";
	const char* t2 = "gggThis tests if lstrip is working";
	const char* t3 = "This tests if rstrip is workinghhh";
	const char* t4 = "000 this tests is strip is working 000";
	const char* t5 = "this tEsts if UpPer is WorkINg";
	const char* t6 = "THIS TESTS if LOwEr is WORKInG"; 

	printf("%s\n %s\n\n", t1, removeWhiteSpace(t1));
	printf("%s\n %s\n\n", t2, lstrip(t2, 'g'));
	printf("%s\n %s\n\n", t3, rstrip(t3, 'h'));
	printf("%s\n %s\n\n", t4, strip(t4, '0'));
	printf("%s\n %s\n\n", t5, upper(t5));
	printf("%s\n %s\n\n", t6, lower(t6));
	

	return 0;
}
