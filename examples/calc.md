### Postfix calculator
This example showcases the usage of `m_list` as a stack. To demonstrate the
approach, we will create a postfix calculator for `float`ing point numbers that
supports operations `+`, `-`, `*` and `/`. In order to print the result and
exit, use the command `=`'.

Code:
```C
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <m_list.h>

static void
operation(struct m_list* stack, char op)
{
	struct m_elem* first;
	struct m_elem* second;
	float* val1;
	float* val2;
	float res;

	m_list_first(stack, &first);
	m_elem_next(first, &second);

	m_elem_data(first, (void**)&val1);
	m_elem_data(second, (void**)&val2);

	switch (op) {
		case '+':
			res = *val1 + *val2;
		break;

		case '-':
		 res = *val1 - *val2;
		break;

		case '*':
			res = *val1 * *val2;
		break;

		case '/':
			if (*val2 == 0.0f) {
				printf("ERROR: Division by zero.\n");
				m_list_remove_all(stack);
				exit(EXIT_FAILURE);
			}
			res = *val1 / *val2;
		break;
	}

	m_list_remove_first(stack);
	m_list_remove_first(stack);
	m_list_prepend(stack, M_LIST_COPY_DEEP, &res, sizeof(float));
}

int
main(void)
{
	float number;
	char op;
	struct m_list stack;
	struct m_elem* first;
	uint64_t length;
	float* data;

	m_list_init(&stack);

	while (1) {
		if (scanf("%f", &number) == 1) {
			m_list_prepend(&stack, M_LIST_COPY_DEEP, &number, sizeof(float));
		} else {
			scanf("%c", &op);
			switch (op) {
				case '+':
				case '-':
				case '*':
				case '/':
					m_list_length(&stack, &length);
					if (length < 2) {
						printf("ERROR: Not enough operands available.\n");
						m_list_remove_all(&stack);
						return EXIT_FAILURE;
					}

					operation(&stack, op);
				break;

				case '=':
					m_list_first(&stack, &first);
					m_elem_data(first, (void**)&data);
					printf("Result: %f\n", *((float*)data));
					m_list_remove_all(&stack);
				return EXIT_SUCCESS;

				default:
					printf("ERROR: Unknown operation '%c'.\n", op);
					m_list_remove_all(&stack);
				return EXIT_FAILURE;
			}
		}
	}

	return EXIT_SUCCESS;
}
```

#### Usage
Compile and run:
```
$ clang -o calc calc.c -lmlist
$ ./calc
4 5 + =
Result: 9.000000
```

#### Approximation of PI
Python script to generate the postfix notation of the Netwon formula:
```python
import sys

def up(n):
	print "1 " + " * ".join([str(x) for x in xrange(n*2) if x % 2 == 1]) + " * "

def down(n):
	print "1 " + " * ".join([str(x) for x in xrange(2, n*2+1) if x % 2 == 0]) + " * " + str((n*2 + 1)) + " * " + str(pow(2, (n*2 + 1))) + " * "

print 0
for i in xrange(1, int(sys.argv[1])):
	down(i)
	up(i)
	print " / + "

print "2 1 / + 6 * ="
```

Example run:
```
$ python2.7 gen_pi.py 4
0
1 2 * 3 * 8 *
1 1 *
 / +
1 2 * 4 * 5 * 32 *
1 1 * 3 *
 / +
1 2 * 4 * 6 * 7 * 128 *
1 1 * 3 * 5 *
 / +
2 1 / + 6 * =
```

Putting it all together:
```
$ python2.7 gen_pi.py 6 | ./calc
Result: 3.141577
```

