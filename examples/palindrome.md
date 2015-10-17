### Palindrome
This example is suboptimal in many ways - the task can be performed in a much
more effective way with simple arrays and two indices that traverse the array
from left to right and vice versa. Apart from that, who does even need to check
if a string is a palindrome? It is even completely rational, in fact it is
*right* to question the existence of the example at all.

Anyhow, the example exercises the `m_list` functions `m_list_reverse` and
`m_list_equal`. 

Code:
```c
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <m_list.h>

static void
gen(uint64_t n, void* payload, void** out_data, size_t* out_size)
{
	char* letter;

	letter = malloc(sizeof(char));
	*letter = ((char*)payload)[n];

	*out_data = letter;
	*out_size = sizeof(char);
}

int
main(int argc, char* argv[])
{
	struct m_list list;
	struct m_list mirror_list;

	if (argc < 2) {
		printf("ERROR: Expected one argument.\n");
		return EXIT_FAILURE;
	}

	m_list_init(&list);	
	m_list_init(&mirror_list);	
	m_list_generate(&list, M_LIST_COPY_DEEP, gen, (uint64_t)strlen(argv[1]), argv[1]);
	m_list_copy(&list, &mirror_list, M_LIST_COPY_DEEP);
	m_list_reverse(&mirror_list);

	if (m_list_equal(&list, &mirror_list) == M_LIST_TRUE)
		printf("The string %s is a palindrome.\n", argv[1]);
	else
		printf("The string %s is not a palindrome.\n", argv[1]);

	return EXIT_SUCCESS;
}
```

Compile and run:
```
$ clang -o pd palindrome.c -lmlist
$ ./pd radar
The string radar is a palindrome.
$ ./pd raaaadar
The string raaaadar is not a palindrome.
```

