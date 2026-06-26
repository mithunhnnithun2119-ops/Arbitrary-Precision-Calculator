#include "apc.h"    

void addition(node *tail1, node *tail2, node **headR, node **tailR)   // Function to add two numbers stored as doubly linked lists
{
    int carry = 0;   // Initialize carry to handle overflow during addition

    while(tail1 != NULL || tail2 != NULL || carry)   // Continue loop until both lists end and no carry remains
    {
        int sum = carry;   // Start sum with previous carry value

        if(tail1 != NULL)   // Check if first number still has digits
        {
            sum = sum + tail1->data;   // Add current digit of first number to sum
            tail1 = tail1->prev;   // Move to previous digit (towards most significant digit)
        }

        if(tail2 != NULL)   // Check if second number still has digits
        {
            sum = sum + tail2->data;   // Add current digit of second number to sum
            tail2 = tail2->prev;   // Move to previous digit
        }

        carry = sum / 10;   // Compute carry for next iteration (tens place)
        int digit = sum % 10;   // Extract current result digit (units place)

        insert_first(headR, tailR, digit);   // Insert result digit at front to maintain correct order
    }
}
