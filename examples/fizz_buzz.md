### Fizz Buzz
Every now and then, when you are being interviewed by a major corporation, your
interviewees are afraid that you are not able to write a simple `for` loop. To
test for this, they ask you to write a program that prints out numbers, from
`0` to `n`, but instead of numbers evenly divisible by `3` you print `fizz` and
for numbers divisible by `5` you print `buzz`. To spice things up even more,
numbers that are divisible by `3` *and* by `5`, you print both `fizz` and
`buzz` together. This is how you do it with `m_list`!.

Code:
```c
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <m_list.h>

static void
generator(uint64_t n, void* payload, void** out_data, size_t* out_size)
{
	char* string;

	(void)payload;

	if (n % 3 == 0 || n % 5 == 0)
		asprintf(&string, "%s%s",
			n % 3 == 0 ? "fizz" : "",
			n % 5 == 0 ? "buzz" : "");
	else
		asprintf(&string, "%d", (int)n);

	*out_data = string;
	*out_size = strlen(string);
}

static void
print_string(void* string, void* payload)
{
	printf("%s\n", (char*)string);
}

int
main(int argc, char* argv[])
{
	struct m_list list;
	int n;

	if (argc < 2) {
		printf("ERROR: Expected one argument.\n");
		return EXIT_FAILURE;
	}

	n = atoi(argv[1]);

	m_list_init(&list);
	m_list_generate(&list, M_LIST_COPY_SHALLOW, generator, (uint64_t)n, NULL);
	m_list_map(&list, print_string, NULL);
	m_list_remove_all(&list);

	return EXIT_SUCCESS;
}
```

Compile and run:
```
$ clang -o fb fizz_buzz.c -lmlist
$ ./fb 18
1
2
fizz
4
buzz
fizz
7
8
fizz
buzz
11
fizz
13
14
fizzbuzz
16
17
fizz
```

If this got you hired, do not forget to thank me via email!
