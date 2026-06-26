#include "apc.h"  

void multiplication(node *tail1, node *tail2, node **headR, node **tailR)   // Function for multiplication
{
    node *temp2 = tail2;   // Pointer to traverse second number from last
    int shift = 0;   // Shift counter for place value

    while (temp2 != NULL)   // Loop through each digit of second number
    {
        node *temp1 = tail1;   // Pointer for first number from last
        node *headT = NULL, *tailT = NULL; // Temporary result list
        int carry = 0;   // Initialize carry

        //add zeros for shifting
        for (int i = 0; i < shift; i++)   // Loop to add shift zeros
        {
            insert_last(&headT, &tailT, 0);   // Insert zero at end
        }

        //multiply each digit
        while (temp1 != NULL)   // Loop through first number digits
        {
            int prod = temp1->data * temp2->data + carry;   // Multiply and add carry

            carry = prod / 10;   // Update carry
            int digit = prod % 10;   // Extract single digit

            insert_first(&headT, &tailT, digit);   // Insert digit at beginning

            temp1 = temp1->prev;   // Move to previous digit
        }

        //handle remaining carry
        if (carry > 0)   // If carry remains
        {
            insert_first(&headT, &tailT, carry);   // Insert carry at beginning
        }

        //add to final result
        if (*headR == NULL)   // If result list is empty
        {
            *headR = headT;   // Assign temporary result to final head
            *tailR = tailT;   // Assign temporary result to final tail
        }
        else   // If result already exists
        {
            node *newHead = NULL, *newTail = NULL;   // New result list

            addition(*tailR, tailT, &newHead, &newTail);   // Add current result with temp result

            // free old result
            delete_list(headR, tailR);   // Delete old result list

            *headR = newHead;   // Update head to new result
            *tailR = newTail;   // Update tail to new result
        }

        temp2 = temp2->prev;   // Move to previous digit of second number
        shift++;   // Increase shift value
    }

    remove_pre_zeros(headR);   // Remove leading zeros from final result
}
