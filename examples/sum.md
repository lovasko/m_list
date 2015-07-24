### Sum of integers
Initialise the list with numbers between `1` to `10` inclusive and print them to
the `stdout`.
```C
static void
add(void* arg, void* sum)
{
  *((uint8_t*)sum) += *((uint8_t*)arg);
}

int
main(void)
{
  struct m_list list;
  uint8_t i;
  uint8_t sum;

  m_list_init(&list);
  for (i = 0; i < 10; i++)
    m_list_append(&list, M_LIST_COPY_DEEP, &i, sizeof(uint8_t));

  sum = 0;
  m_list_map(&list, add, &sum);
  printf("sum = %d\n", sum);

  return EXIT_SUCCESS;
}
```

Compile & run:

```
$ clang -o sum sum.c -lmlist
$ ./sum
sum = 55
```
