#include <stdio.h>
#include <unistd.h>

int main() {
	char buf[10000];
	memset(buf, 'a', 9999);
	buf[9999] = 0;
	printf("%s", buf);
	write(1, "How did this happen\n", 20);
}
