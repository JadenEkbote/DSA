#include <stdio.h>
#include <stdlib.h>

#define NUM_TASKS 5

typedef struct
{
    int id;      // Task ID
    int weight;  // Task weight
    int current; // Current weight
} Task;

// Function to find the greatest common divisor
int gcd(int a, int b)
{
    while (b != 0)
    {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// Function to find the maximum weight
int find_max_weight(Task tasks[], int num_tasks)
{
    int max_weight = tasks[0].weight;
    for (int i = 1; i < num_tasks; i++)
    {
        if (tasks[i].weight > max_weight)
        {
            max_weight = tasks[i].weight;
        }
    }
    return max_weight;
}

// Function to find the greatest common divisor of all weights
int gcd_of_weights(Task tasks[], int num_tasks)
{
    int result = tasks[0].weight;
    for (int i = 1; i < num_tasks; i++)
    {
        result = gcd(result, tasks[i].weight);
    }
    return result;
}

// Function to implement weighted round robin
void weighted_round_robin(Task tasks[], int num_tasks, int num_iterations)
{
    int max_weight = find_max_weight(tasks, num_tasks);
    int gcd_weight = gcd_of_weights(tasks, num_tasks);
    int current_weight = max_weight;
    int i = -1;

    while (num_iterations > 0)
    {
        i = (i + 1) % num_tasks;

        if (i == 0)
        {
            current_weight -= gcd_weight;
            if (current_weight <= 0)
            {
                current_weight = max_weight;
                if (current_weight == 0)
                {
                    break;
                }
            }
        }

        if (tasks[i].weight >= current_weight)
        {
            printf("Task %d is being served\n", tasks[i].id);
            num_iterations--;
        }
    }
}

int main()
{
    Task tasks[NUM_TASKS] = {
        {1, 5, 0},
        {2, 1, 0},
        {3, 1, 0},
        {4, 1, 0},
        {5, 2, 0}};

    int num_iterations = 10;
    weighted_round_robin(tasks, NUM_TASKS, num_iterations);

    return 0;
}
