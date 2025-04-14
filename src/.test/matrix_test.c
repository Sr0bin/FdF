/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_test.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rorollin <rorollin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 16:15:37 by rorollin          #+#    #+#             */
/*   Updated: 2025/04/14 13:11:09 by rorollin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "fdf.h"
#include "geometry.h"
#include <stdio.h>

#include "error.h"
void matrix_test(void)
{
    t_matrix a, b, result;
    float scalar = 2.5;

    // Test: Create two matrices
    a = create_matrix(2, 3);
    b = create_matrix(3, 2);
    if (!a || !b)
    {
        printf("Matrix creation failed.\n");
        return;
    }
  // Initialize matrix a (2x3)
    a->index[0][0] = 1.0;
    a->index[0][1] = 2.0;
    a->index[0][2] = 3.0;
    a->index[1][0] = 4.0;
    a->index[1][1] = 5.0;
    a->index[1][2] = 6.0;

    // Initialize matrix b (3x2)
    b->index[0][0] = 7.0;
    b->index[0][1] = 8.0;
    b->index[1][0] = 9.0;
    b->index[1][1] = 10.0;
    b->index[2][0] = 11.0;
    b->index[2][1] = 12.0;

    printf("Matrix A (2x3):\n");
    print_matrix(a);

    printf("\nMatrix B (3x2):\n");
    print_matrix(b);
    // Test: Matrix Addition
    result = add_matrix(a, b);
    if (result)
    {
        printf("\nMatrix A + Matrix B:\n");
        print_matrix(result);
        free_matrix(result);
    }

    // Test: Matrix Subtraction
    result = substract_matrix(a, b);
    if (result)
    {
        printf("\nMatrix A - Matrix B:\n");
        print_matrix(result);
        free_matrix(result);
    }

    // Test: Matrix Scalar Multiplication
    result = scalar_matrix(a, scalar);
    if (result)
    {
        printf("\nMatrix A * %.2f (scalar):\n",(double) scalar);
        print_matrix(result);
        free_matrix(result);
    }

    // Test: Matrix Multiplication
    result = multiply_matrix(a, b);
    if (result)
    {
        printf("\nMatrix A * Matrix B:\n");
        print_matrix(result);
        free_matrix(result);
    }

    // Clean up
    free_matrix(a);
    free_matrix(b);
}
