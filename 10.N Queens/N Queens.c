#include <stdio.h>
#include <stdlib.h>
static void print_board(int *board, int n, int solution_no) {
    int row, col;
    printf("\nSolution %d:\n", solution_no);
    for (row = 0; row < n; row++) {
        for (col = 0; col < n; col++) {
            if (board[row] == col) {
                printf(" Q ");
            } else {
                printf(" . ");
            }
        }
        printf("\n");
    }
}
static int is_safe(int *board, int row, int col) {
    int prev_row;
    for (prev_row = 0; prev_row < row; prev_row++) {
        int prev_col = board[prev_row];
        if (prev_col == col) {
            return 0;
        }
        if (abs(prev_col - col) == abs(prev_row - row)) {
            return 0;
        }
    }
    return 1;
}
static void solve_n_queens(int *board, int row, int n, int *solution_count) {
    int col;
    if (row == n) {
        (*solution_count)++;
        print_board(board, n, *solution_count);
        return;
    }
    for (col = 0; col < n; col++) {
        if (is_safe(board, row, col)) {
            board[row] = col;
            solve_n_queens(board, row + 1, n, solution_count);
            board[row] = -1;
        }
    }
}
int main(void) {
    int n;
    int *board;
    int solution_count = 0;
    int i;
    printf("Enter the number of queens: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Please enter a positive integer.\n");
        return 1;
    }
    board = (int *)malloc((size_t)n * sizeof(int));
    if (board == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }
    for (i = 0; i < n; i++) {
        board[i] = -1;
    }
    solve_n_queens(board, 0, n, &solution_count);
    if (solution_count == 0) {
        printf("\nNo solution exists for %d queens.\n", n);
    } else {
        printf("\nTotal solutions: %d\n", solution_count);
    }
    free(board);
    return 0;
}
