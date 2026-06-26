#include "apc.h"   

void subtraction(node *tail1, node *tail2, node **headR, node **tailR)   // Function for subtraction
{
    int borrow = 0;   // Initialize borrow to 0

    while (tail1 != NULL || tail2 != NULL)   // Loop until both lists are processed
    {
        int val1 = 0, val2 = 0;   // Initialize values for digits

        if (tail1 != NULL)   // If first list has node
        {
            val1 = tail1->data;   // Get digit from first list
            tail1 = tail1->prev;   // Move to previous node
        }

        if (tail2 != NULL)   // If second list has node
        {
            val2 = tail2->data;   // Get digit from second list
            tail2 = tail2->prev;   // Move to previous node
        }

        val1 = val1 - borrow;   // Subtract previous borrow

        if (val1 < val2)   // If borrowing is needed
        {
            val1 += 10;   // Add 10 to current digit
            borrow = 1;   // Set borrow for next iteration
        }
        else   // No borrow needed
        {
            borrow = 0;   // Reset borrow
        }

        int diff = val1 - val2;   // Compute difference

        insert_first(headR, tailR, diff);   // Insert result digit at beginning
    }

    // remove leading zeros
    remove_pre_zeros(headR);   // Remove unnecessary leading zeros
}
