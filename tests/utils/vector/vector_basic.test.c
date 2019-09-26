#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <utils/vector.h>

int main()
{
    int i;

    struct vector v;
    vector_init(&v);

    char *s = "Bonjour";
    vector_add(&v, s);

    s = "tout";
    vector_add(&v, s);

    s = "le";
    vector_add(&v, s);

    s = "monde";
    vector_add(&v, s);

    for (i = 0; i < vector_count(&v); i++)
        printf("%s ", (char *)vector_get(&v, i));
    printf("\n");

    vector_delete(&v, 3);
    vector_delete(&v, 2);
    vector_delete(&v, 1);

    s = "Hello";
    vector_set(&v, 0, s);
    s = "World";
    vector_add(&v, s);

    for (i = 0; i < vector_count(&v); i++)
        printf("%s ", (char *)vector_get(&v, i));
    printf("\n");
}