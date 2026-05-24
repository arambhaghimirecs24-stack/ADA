#include <stdio.h>
int max(int a, int b) {
    return (a > b) ? a : b;
}
int knapsack(int n, int W, int weight[], int profit[], int dp[][100]) {
    if (n == 0 || W == 0)
        return 0;
    if (dp[n][W] != -1)
        return dp[n][W];
    if (weight[n - 1] <= W) {
        dp[n][W] = max(
            profit[n - 1] + knapsack(n - 1, W - weight[n - 1], weight, profit, dp),
            knapsack(n - 1, W, weight, profit, dp)
        );
    } else {
        dp[n][W] = knapsack(n - 1, W, weight, profit, dp);
    }
    return dp[n][W];
}
int main() {
    int n, W;
    printf("Enter number of items: ");
    scanf("%d", &n);
    int weight[n], profit[n];
    printf("Enter weights:\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &weight[i]);
    printf("Enter profits:\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &profit[i]);
    printf("Enter knapsack capacity: ");
    scanf("%d", &W);
    int dp[100][100];
    for (int i = 0; i < 100; i++)
        for (int j = 0; j < 100; j++)
            dp[i][j] = -1;
    int result = knapsack(n, W, weight, profit, dp);
    printf("Maximum profit = %d\n", result);
    return 0;
}
