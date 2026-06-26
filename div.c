#include "apc.h"   

void division(node *head1, node *head2, node **headR, node **tailR)   // Function to perform division using linked lists
{
    node *tempH = NULL, *tempT = NULL;   // Temporary list to store current partial dividend
    node *temp = head1;   // Pointer to traverse the dividend number

    // find tail of divisor
    node *tail2 = head2;   // Initialize pointer to find last node of divisor
    while(tail2->next != NULL)   // Traverse until last node
        tail2 = tail2->next;   // Move to next node

    while (temp != NULL)   // Loop through each digit of dividend
    {
        insert_last(&tempH, &tempT, temp->data);   // Add current digit to partial dividend
        remove_pre_zeros(&tempH);   // Remove leading zeros for accurate comparison

        int count = 0;   // Initialize count for how many times divisor fits

        while (compare_list(tempH, head2) != OPERAND2)   // Repeat while partial dividend ≥ divisor
        {
            node *resH = NULL, *resT = NULL;   // Temporary list for subtraction result

            subtraction(tempT, tail2, &resH, &resT);   // Subtract divisor from partial dividend

            delete_list(&tempH, &tempT);   // Free old partial dividend list

            tempH = resH;   // Update head with new result
            tempT = resT;   // Update tail with new result

            count++;   // Increment quotient digit (how many times subtraction occurred)
        }

        insert_last(headR, tailR, count);   // Store quotient digit in result list

        temp = temp->next;   // Move to next digit of dividend
    }

    remove_pre_zeros(headR);   // Remove leading zeros from final quotient
}
