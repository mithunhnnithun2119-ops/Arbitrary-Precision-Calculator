/*
    NAME : MITHUN HN

    DATE :3/04/2026
    
    DESCRIPTION : The APC (Arbitrary Precision Calculator) project implements arithmetic operations like addition, subtraction, multiplication, 
    and division for large numbers using doubly linked lists.Each digit of the number is stored in a node, 
    allowing operations beyond standard data type limits.The program processes input through command-line arguments 
    and performs calculations digit-by-digit with proper handling of carry and borrow. Intermediate helper functions 
    like comparison, insertion, and deletion manage list operations efficiently.The final result is displayed after 
    removing leading zeros, ensuring accurate large number computation.
    */

#include "apc.h" 

int main(int argc, char *argv[])   // Entry point of the program with command-line arguments
{
    node *head1 = NULL, *tail1 = NULL;   // Initialize linked list for operand1
    node *head2 = NULL, *tail2 = NULL;   // Initialize linked list for operand2
    node *headR = NULL, *tailR = NULL;   // Initialize linked list for result

    if(cla_validation(argc, argv) == FAILURE)   // Validate input arguments
        return FAILURE;   // Exit if validation fails

    create_list(argv[1], &head1, &tail1);   // Convert operand1 string into linked list
    create_list(argv[3], &head2, &tail2);   // Convert operand2 string into linked list

    operation_decider(argv[1], argv[2][0], argv[3],   // Decide operation based on operator
                      head1, tail1,   // Pass operand1 list
                      head2, tail2,   // Pass operand2 list
                      &headR, &tailR);   // Pass result list pointers

    print_list(headR);   // Print the final result

    return SUCCESS;   // End program successfully

    char oper = argv[2][0];   // Store operator from command-line (unreachable due to return above)

    switch(oper)   // Switch case to perform operation manually (dead code)
    {

	case '+':   // If operator is addition
         addition(tail1, tail2, &headR, &tailR);   // Perform addition
            print_list(headR);   // Print result
        break;   // Exit switch

    case '-':   // If operator is subtraction

    int cmp = compare_list(head1, head2);   // Compare both operands

    if(cmp == SAME)   // If both operands are equal
    {
        printf("0\n");   // Result is zero
    }
    else if(cmp == OPERAND1)   // If operand1 is greater
    {
        // operand1 >= operand2
        subtraction(tail1, tail2, &headR, &tailR);   // Perform subtraction
        print_list(headR);   // Print result
    }
    else   // If operand2 is greater
    {
        // operand2 > operand1 → negative result
        subtraction(tail2, tail1, &headR, &tailR);   // Perform subtraction in reverse order
        printf("-");   // Print negative sign
        print_list(headR);   // Print result
    }
    break;   // Exit switch

    case 'x':   // If operator is multiplication (lowercase)
	case 'X':   // If operator is multiplication (uppercase)
    multiplication(tail1, tail2, &headR, &tailR);   // Perform multiplication
    print_list(headR);   // Print result

	    break;   // Exit switch

	case '/':   // If operator is division
    division(head1, head2, &headR, &tailR);   // Perform division
    print_list(headR);   // Print result
    
	    break;   // Exit switch

	default:   // If operator is invalid
	    printf("Invalid operator\n");   // Print error message
    }
}

