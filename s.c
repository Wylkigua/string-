#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "s.h"

void test(void);

int main(void) {
	const char s[] = "hel \0 lk";
	const char *p = NULL;
	p = strrchr(s, '\0');
	printf("%p %p\n", p, &s[3]);
	
	p = s21_strrchr(s, '\0');
	printf("%p %p\n", p, &s[3]);
}

char *s21_strrchr(const char *s, int c) {
	int offset = -1;
	const char *p = s;
	for (; ;p++) {
		if (!(*p)) {
			if (c == '\0') offset = p - s;
			break;
		}
		if (*p == c) offset = p - s;
	}
	p = s + offset;
	if (offset < 0) p = NULL;
	return ((char*)p);
}

char *s21_strpbrk(const char *s1, const char *s2) {
	char assci[ASSCI_L];
	const char *p;
	for (int i = 0; i < ASSCI_L; i++) *(assci+i) = 0;
	for (int i = 0; *(s2+i); i++) assci[(int)*(s2+i)]++;
	for (p = s1; ;p++) if (!(*p) || assci[(int)*p] > 0) break;
	if (!(*p)) p = NULL;
	return ((char*)p);
}

size_t s21_strcspn(const char *s1, const char *s2) {
	char assci[ASSCI_L];
	for (int i = 0; i < ASSCI_L; i++) *(assci+i) = 0;
	for (int i = 0; *(s2+i); i++) assci[(int)*(s2+i)]++;

	size_t byte = 0;
	while (1) {
		if (!(*(s1+byte)) || assci[(int)*(s1+byte)] > 0) break;
		byte++;
	}
	return (byte);
}

void *s21_memchr(const void *arr, int c, size_t n) {
	const unsigned char *p = arr;
	if (*p) {
		while (1) {
			if (!n || *p == c) break;
			n--;
			p++;
		}
	}
	if (!n) p = NULL;
	return ((void*)p);
}


/*
void test(void) {

	
	const char *s1 = "Hello";
	const char *s2 = "o";
	char *p;
	p = strpbrk(s1, s2);
	printf("%p %p\n", p, &s1[4]);
	p = s21_strpbrk(s1, s2);
	printf("%p %p\n", p, &s1[4]);
	
	const char str1[] = "Tutorialspoint";
	const char str2[] = "tbook";
	p = strpbrk(str1, str2);
	printf("%p %p\n", p, &str1[0]);

	p = s21_strpbrk(str1, str2);
	printf("%p %p\n", p, &str1[0]);



	long int num[] = {1,2,3}, *pint;
	char arr[] = {'a', 's', 'w'}, *pchar;
	double dub[] = {1.2, 5.3, 7.3}, *pdub;
	float flot[] = {3.1, 7.3, 9.2}, *pflot;
	
	
	char arr[] = {'a', 's', 'w'}, *pchar;
	pchar = s21_memchr(arr, 'w', 0);
	//printf("%p %p\n", pchar, &arr[2]);
	printf("%p\n", pchar);
	pchar = memchr(arr, 'w', 0);
	printf("%p\n", pchar);


	pint = memchr(num, 3, sizeof(num));
	printf("%ld %ld\n", *pint, sizeof(*pint));
	printf("%p %p\n", pint, &num[2]);
	printf("-----------------------\n");
	
	pchar = memchr(arr, 'w', sizeof(arr));
	printf("%c %ld\n", *pchar, sizeof(*pchar));
	printf("%p %p\n", pchar, &arr[2]);
	printf("-----------------------\n");
	
	pdub = memchr(dub, 7.3, sizeof(dub));
	printf("%p\n", pdub);
	pflot = memchr(flot, 9.2, sizeof(flot));
	printf("%p\n", pflot);

	//printf("%lf\n", *pdub);
	printf("%p %p\n", pdub, &dub[2]);
	printf("-----------------------\n");


}*/
