#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "s.h"

void test(void);
/*
int main(void) {
	char s1[] = "--  -hi.-.frie  nd$$$-ok(((((((hel  lo))---ok....l!w", *p1 = NULL;
	char s2[] = "--  -hi.-.frie  nd$$$-ok(((((((hel  lo))---ok....l!w", *p2 = NULL;
	char sep[] = "-.()!$r d";
	int brk, sccs, cmp;
	p1 = s21_strtok(s1, sep);
	p2 = strtok(s2, sep);
	sccs = !(brk = (p1 && p2) ? 0 : 1);
	while (!brk) {
		p1 = s21_strtok(NULL, sep);
		p2 = strtok(NULL, sep);
		if (p1 && p2) {
			printf("%s %s\n", p1, p2);
			cmp = strcmp(p1, p2);
			sccs = !(brk = (cmp == 0) ? 0 : 1);
		} else if ((p1 && !p2) || (!p1 && p2)) {
			sccs = !(brk = 1);
		} else {
			sccs = brk = 1;
		}
	}
	printf("%d\n", sccs);
}
*/

int main(void) {
	char s[] = "mississippi";
	//char s[] = "mississippi";
	//char c[] = "ss";
	char c[] = "ppi";
	char *p = s21_strstr(s, c);
	printf("%c\n", *p);
}

char *s21_strtok(char *str, const char *sep) {
	static char *prev = NULL;
	char *ps = str;
	if (str == NULL) {
		if (prev == NULL || *prev == '\0') return (NULL);
		ps = prev;
	}
	char *pt = NULL;
	int l, r, brk, srh, first;
	r = l = first = srh = brk = 0;

	for (; !brk && *(ps + l) != '\0'; l++) {
		for (r = srh = 0; !srh && *(ps+l) != '\0'; r++) {
			if (*(sep+r) != '\0' && *(ps+l) == *(sep+r)) {
				*(ps+l) = '\0';
			} else if (*(sep+r) == '\0') srh = 1;
		}
		if (*(ps+l) == '\0' && first) {
				brk = 1;
		} else if (*(ps+l) != '\0') {
			if (!first) pt = ps + l;
			first++;
		}
	}
	prev = ps + l;
	return ((char*)pt);
}
/*
int main(void) {
	char s[] = "glllh.....elk.lk..xc";
	//char s[] = "gghg.w";
	char d[] = "lx.";
	char *p = NULL;
	p = strtok(s, d);
	while (p != NULL) {
		printf("%s\n", p);
		p = strtok(NULL, d);
	}
	printf("---------------------\n");
	char s1[] = "glllh....elk.lk..xc";
	//char s1[] = "gghg.w";
	char d1[] = "lx.";
	char *p1 = NULL;
	p1 = s21_strtok(s1, d1);
	while (p1 != NULL) {
		printf("%s\n", p1);
		p1 = s21_strtok(NULL, d1);
	}

	p = strtok(s, d);
	printf("%s - %p\n", p, p);
	p = strtok(NULL, d);
	printf("%s - %p\n", p, p);
	p = strtok(NULL, d);
	printf("%s - %p\n", p, p);
	p = strtok(NULL, d);
	printf("%s - %p\n\n", p, p);

	p1 = s21_strtok(s1, d1);
	printf("%s - %p\n", p1, p1);
	p1 = s21_strtok(NULL, d1);
	printf("%s - %p\n", p1, p1);
	p1 = s21_strtok(NULL, d1);
	printf("%s - %p\n", p1, p1);
	p1 = s21_strtok(NULL, d1);
	printf("%s - %p\n", p1, p1);
	p1 = s21_strtok(NULL, d1);
	printf("%s - %p\n", p1, p1);
	p1 = s21_strtok(NULL, d1);
	printf("%s - %p\n", p1, p1);

}
*/
//  char s[] = "mississippi";
//	char c[] = "issip";

char *s21_strstr(const char *str, const char *sub) {
	int l, r, f;
	const char *p = NULL;
	for (f = 1, l = r = 0; f && *(str+l); ++l) {
		if (*(str+l) == *(sub+r)) {
			++r;
			if (!*(sub+r)) {
				p = str + l - r + 1;
				f = 0;
			}
		} else if (r) {
			l -= r;
			r = 0;
		}
	}
	return ((char*)p);
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

	const char str[] = "hell";
	const char sub[] = "1";
	const char *p = NULL;
	p = strstr(str, sub);
	printf("%p %p\n", p, &str[3]);
	
	p = s21_strstr(str, sub);
	printf("%p %p\n", p, &str[3]);
	
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
