### Comma-separated words
Add all program arguments to the list and interconnect all the words with a
comma.
```C
void
print_string(void* arg, void* payload)
{
  (void)payload;
  printf("%s", (char*)arg);
}

int
main(int argc, char* argv[])
{
  struct m_list list;
  int i;

  m_list_init(&list);
  for (i = 1; i < argc; i++)
    m_list_append(&list, M_LIST_COPY_SHALLOW, argv[i], 0);

  m_list_join(&list, M_LIST_COPY_SHALLOW, ", ", 0);
  m_list_map(&list, print_string, NULL);
  printf("\n");

  return EXIT_SUCCESS;
}
```

Compile & run:

```
$ clang -o comma comma.c -lmlist
$ ./comma bananas oranges apples
bananas, oranges, apples
```
