#include "minirt.h"

t_vector    *new_vector(float x, float y, float z)              //создание нового вектора
{
    t_vector    *vector;

    vector = malloc(sizeof(t_vector));
    if (!vector)
        exit (1);    //написать функцию при возникновении ошибки
    vector->x = x;
    vector->y = y;
    vector->z = z;
    return (vector);
}

t_vector    *subtraction_vector(t_vector *vector_a, t_vector *vector_b)         //вычитание векторов
{
    t_vector    *vector_c;

    vector_c = new_vector(vector_a->x - vector_b->x, vector_a->y - vector_b->y, \
        vector_a->z - vector_b->z);
    return (vector_c);
}

float   vector_length(t_vector *vector)             //модуль вектора
{
    float length;

    length = sqrt((vector->x * vector->x) + (vector->y * vector->y) + (vector->z * vector->z));
    return (length);
}

void    normalize_vector(t_vector *vector)          //нормализация вектора
{
    float   norm;
    float   length;

    length = vector_length(vector);
    norm = 1/length;
    vector->x = vector->x * norm;
    vector->y = vector->y * norm;
    vector->z = vector->z * norm;
}

float   dot_product_of_vectors(t_vector *vector_a, t_vector *vector_b)
{
    float res;

    res = ((vector_a->x * vector_b->x) + (vector_a->y * vector_b->y) + (vector_a->z * vector_b->z));
   /*
   скалярное произведение векторов, но у векторов есть ещё углы ориентации пространства
   пока что косинус этих углов берём равным 1, потом если понадобиться, то надо будет домножать на
   косинус угла между векторов
   */

    return (res);
}