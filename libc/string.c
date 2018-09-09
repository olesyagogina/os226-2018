#include <stddef.h>
#include <string.h>


int strcmp(const char *s1, const char *s2) {
	int i = 0;
	while (*s1 == *s2 && *s1 != 0 && *s2 != 0) {
		i++;
		s1++;
		s2++;
        }
	if (*s1 == '\0') return 0;
	else if (*s1 > *s2) return 1;
	else return -1;
}

size_t strlen(const char *s) {
	size_t length = 0;
	while (*s++) 
		++length;
	return length;
}

char *strchr(const char *s, int c) {
	while (*s != c && *s != '\0') 
		s++;
	if (*s == c)
		return (char *) s;
	
	return NULL;
}

size_t strspn(const char *str, const char *accept) {
	size_t res = 0;
	while (*str != '\0' && strchr(accept, *str)) {
		str++; 
		res++;
	}
	return res;		
}


size_t strcspn(const char *str, const char *reject) {
	size_t res = 0;
	while (*str != '\0' && !strchr(reject, *str)) {
		str++; 
		res++;
	}
	return res;		
}

char *strtok_r(char *str, const char *delim, char **saveptr) {
	if (str == NULL) {
		str = *saveptr;
		if (str == NULL)
			return NULL;
	}
	size_t skip = strspn(str,delim);
	str += skip;
	if (*str == '\0') {
		*saveptr = str;
		return NULL;
	}
	char* cur = str + strcspn(str, delim);
	for (; strcspn(cur, delim) == 0 && *cur; cur++) {
		*cur = '\0';
	}
	*saveptr = cur;
	cur = NULL;
	return str;
}

