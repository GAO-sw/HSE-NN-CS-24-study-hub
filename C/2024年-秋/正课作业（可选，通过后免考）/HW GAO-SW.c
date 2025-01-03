
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tinyexpr.h"

#define MAX_ITER 100 // Set the maximum number of iterations
#define EPSILON 1e-6 // Set the precision
#define DELTA 1e-6   // The change value for finite differences

// Function: Calculate the inverse of the Jacobian matrix
int invert_matrix(double **matrix, double **inverse, int n);

int main() {
    // Input start

    // Input the number of variables
    int n;
    printf("please enter the number of the variables:\n");
    scanf("%d", &n);

    // Create a 2D array to store the (n * (n+1)) matrix
    double **equation = (double **)malloc(n * sizeof(double *));
    for (int i = 0; i < n; i++) {
        equation[i] = (double *)malloc((n + 1) * sizeof(double));
    }

    // Input the values of the matrix
    printf("Please enter the matrix of the equation:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n + 1; j++) {
            scanf("%lf", &equation[i][j]);
        }
    }

    // Print the input matrix
    printf("The matrix you entered is:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n + 1; j++) {
            printf("%lf ", equation[i][j]);
        }
        printf("\n");
    }
    // Input end

    // Create an array of te_variable to store n variables, and initialize their names as x_k and initial values as 1.0
    te_variable *te_vars = (te_variable *)malloc(n * sizeof(te_variable));
    for (int i = 0; i < n; i++) {
        char name[4];
        sprintf(name, "x%d", i + 1);
        te_vars[i].name = strdup(name);          // Use strdup to dynamically allocate memory for variable names
        te_vars[i].address = malloc(sizeof(double)); // Dynamically allocate memory to store variable values
        *(double *)te_vars[i].address = 1.0;     // Initialize variable value to 1.0
        te_vars[i].type = TE_VARIABLE;           // Mark this as a variable
    }

    // Generate the equation strings
    char **equation_strings = (char **)malloc(n * sizeof(char *));
    for (int i = 0; i < n; i++) {
        equation_strings[i] = (char *)malloc((50 * n) * sizeof(char)); // Adjust string size dynamically based on n
        equation_strings[i][0] = '\0'; // Initialize as an empty string

        // Traverse each row of the matrix to construct the expression string
        for (int j = 0; j < n; j++) {
            char term[50];
            if (j == 0) {
                // The first term does not need a sign
                sprintf(term, "%.2lf*x%d", equation[i][j], j + 1);
            } else {
                // Subsequent terms need a plus or minus sign
                if (equation[i][j] >= 0) {
                    sprintf(term, " + %.2lf*x%d", equation[i][j], j + 1);
                } else {
                    sprintf(term, " - %.2lf*x%d", -equation[i][j], j + 1);
                }
            }
            strcat(equation_strings[i], term);
        }

        // Add the constant term on the right-hand side
        char constant_term[50];
        sprintf(constant_term, " - (%.2lf)", equation[i][n]); // Convert to equal 0 form
        strcat(equation_strings[i], constant_term);
    }

    // Newton's method iteration to solve the equations
    for (int iter = 0; iter < MAX_ITER; iter++) {
        // Calculate the value of the equations F(X)
        double *F = (double *)malloc(n * sizeof(double));
        for (int i = 0; i < n; i++) {
            int error;
            te_expr *expr = te_compile(equation_strings[i], te_vars, n, &error);
            if (expr) {
                F[i] = te_eval(expr);
                te_free(expr);
            } else {
                printf("Parse error at position %d in equation %d\n", error, i + 1);
                free(F);
                return -1;
            }
        }

        // Check if we are close enough to the solution
        double norm = 0.0;
        for (int i = 0; i < n; i++) {
            norm += F[i] * F[i];
        }
        if (norm < EPSILON) {
            printf("Converged after %d iterations.\n", iter);
            break;
        }

        // Calculate the Jacobian matrix J(X)
        double **J = (double **)malloc(n * sizeof(double *));
        for (int i = 0; i < n; i++) {
            J[i] = (double *)malloc(n * sizeof(double));
        }

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                // Use finite difference to calculate the partial derivative
                double original_value = *(double *)te_vars[j].address;
                *(double *)te_vars[j].address += DELTA; // Add Δx

                int error;
                te_expr *expr = te_compile(equation_strings[i], te_vars, n, &error);
                if (expr) {
                    double f_plus_delta = te_eval(expr);
                    te_free(expr);
                    J[i][j] = (f_plus_delta - F[i]) / DELTA; // Calculate finite difference
                } else {
                    printf("Parse error at position %d during Jacobian calculation in equation %d\n", error, i + 1);
                    // Release all resources
                    for (int k = 0; k <= i; k++) {
                        free(J[k]);
                    }
                    free(J);
                    free(F);
                    return -1;
                }

                *(double *)te_vars[j].address = original_value; // Restore the original value
            }
        }

        // Calculate the inverse of the Jacobian matrix
        double **J_inv = (double **)malloc(n * sizeof(double *));
        for (int i = 0; i < n; i++) {
            J_inv[i] = (double *)malloc(n * sizeof(double));
        }
        if (invert_matrix(J, J_inv, n) == -1) {
            printf("Jacobian matrix inversion failed.\n");
            for (int i = 0; i < n; i++) {
                free(J[i]);
                free(J_inv[i]);
            }
            free(J);
            free(J_inv);
            free(F);
            return -1;
        }

        // Update variables X = X - J_inv * F
        for (int i = 0; i < n; i++) {
            double delta = 0.0;
            for (int j = 0; j < n; j++) {
                delta += J_inv[i][j] * F[j];
            }
            *(double *)te_vars[i].address -= delta; // Update variable value
        }

        // Release memory for the Jacobian matrix and its inverse
        for (int i = 0; i < n; i++) {
            free(J[i]);
            free(J_inv[i]);
        }
        free(J);
        free(J_inv);

        free(F);
    }

    // Output the final solution
    printf("The solution is:\n");
    for (int i = 0; i < n; i++) {
        printf("%s = %.6lf\n", te_vars[i].name, *(double *)te_vars[i].address);
    }

    // Free memory
    for (int i = 0; i < n; i++) {
        free(equation[i]);             // Release memory for the matrix
        free((void *)te_vars[i].name); // Release memory for variable names (allocated by strdup)
        free(te_vars[i].address);      // Release memory for variable values
        free(equation_strings[i]);     // Release memory for equation strings
    }
    free(equation);       // Release memory for the matrix pointer array
    free(te_vars);        // Release memory for the te_variable array
    free(equation_strings); // Release memory for the equation string pointer array

    return 0;
}

// Function to calculate the inverse of a matrix (using Gaussian-Jordan elimination)
int invert_matrix(double **matrix, double **inverse, int n) {
    // Initialize the inverse matrix as an identity matrix
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            inverse[i][j] = (i == j) ? 1.0 : 0.0;
        }
    }

    // Gaussian-Jordan elimination
    for (int i = 0; i < n; i++) {
        double diag = matrix[i][i];
        if (diag == 0) {
            return -1; // If the diagonal element is 0, the matrix is non-invertible
        }
        for (int j = 0; j < n; j++) {
            matrix[i][j] /= diag;
            inverse[i][j] /= diag;
        }
        for (int k = 0; k < n; k++) {
            if (k != i) {
                double factor = matrix[k][i];
                for (int j = 0; j < n; j++) {
                    matrix[k][j] -= factor * matrix[i][j];
                    inverse[k][j] -= factor * inverse[i][j];
                }
            }
        }
    }
    return 0;
}
