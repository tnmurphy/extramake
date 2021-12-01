#include <stdio.h>
#include <malloc.h>

int main(int argc, char *argv[]) {
char *str;
str = malloc(6+1);
sprintf(str, "%02x%02x%02x", 12, 13, 14);
puts(str);
return 1;
}
