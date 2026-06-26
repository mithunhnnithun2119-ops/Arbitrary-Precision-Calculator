#include "apc.h"   

void create_list(char *opr, node **head, node **tail) // Function to create linked list from operand string
{
    int i = 0; // Initialize index variable

    if(opr[0] == '+' || opr[0] == '-') // Check if first character is sign (+ or -)
        i = 1; // Skip the sign by starting from index 1

    while(opr[i] != '\0') // Loop until end of string
    {
        insert_last(head, tail, opr[i] - '0'); // Convert char to int and insert at end of list
        i++; // Move to next character
    }
}

// print list
void print_list(node *head)
{
    while(head != NULL)   // Traverse till end of list
    {
        printf("%d", head->data);   // Print each node data
        head = head->next;   // Move to next node
    }
    printf("\n");   // Print newline
}

//Insert First 
int insert_first(node **head, node **tail, int data)
{
    node *new_node = malloc(sizeof(node));   // Allocate memory for new node
    if(new_node == NULL)   // Check allocation failure
        return FAILURE;   // Return failure

    new_node->data = data;   // Assign data
    new_node->prev = NULL;   // Previous pointer is NULL
    new_node->next = *head;   // Next points to current head

    if(*head == NULL)   // If list is empty
    {
        *head = new_node;   // Head becomes new node
        *tail = new_node;   // Tail becomes new node
    }
    else   // If list not empty
    {
        (*head)->prev = new_node;   // Update old head's prev
        *head = new_node;   // Update head
    }

    return SUCCESS;   // Return success
}


//Insert Last 
int insert_last(node **head, node **tail, int data)
{
    node *new_node = malloc(sizeof(node));   // Allocate memory
    if(new_node == NULL)   // Check failure
        return FAILURE;   // Return failure

    new_node->data = data;   // Assign data
    new_node->next = NULL;   // Next is NULL
    new_node->prev = NULL;   // Prev is NULL

    if(*head == NULL)   // If list empty
    {
        *head = new_node;   // Head becomes new node
        *tail = new_node;   // Tail becomes new node
    }
    else   // If list not empty
    {
        (*tail)->next = new_node;   // Link old tail to new node
        new_node->prev = *tail;   // Set prev of new node
        *tail = new_node;   // Update tail
    }

    return SUCCESS;   // Return success
}

// compare list
int list_len(node *head)
{
    int count = 0;   // Initialize counter
    while(head)   // Traverse list
    {
        count++;   // Increment count
        head = head->next;   // Move to next node
    }
    return count;   // Return length
}

int compare_list(node *head1, node *head2)
{
    int len1 = list_len(head1);   // Get length of list1
    int len2 = list_len(head2);   // Get length of list2

    if(len1 > len2) return OPERAND1;   // If list1 longer
    if(len2 > len1) return OPERAND2;   // If list2 longer

    while(head1 && head2)   // Traverse both lists
    {
        if(head1->data > head2->data) return OPERAND1;   // Compare data
        if(head2->data > head1->data) return OPERAND2;   // Compare data

        head1 = head1->next;   // Move list1
        head2 = head2->next;   // Move list2
    }

    return SAME;   // If both equal
}

// remove zeros
void remove_pre_zeros(node **head)
{
    while (*head != NULL && (*head)->data == 0 && (*head)->next != NULL)   // Check leading zeros
    {
        node *temp = *head;   // Store current head
        *head = (*head)->next;   // Move head forward
        (*head)->prev = NULL;   // Set new head prev to NULL
        free(temp);   // Free old node
    }
}

//delete list
int delete_list(node **head, node **tail)
{
    if (*head == NULL)   // If list empty
        return FAILURE;   // Return failure

    node *temp = *head;   // Start from head

    while (temp != NULL)   // Traverse list
    {
        node *next = temp->next;   // Store next node
        free(temp);   // Free current node
        temp = next;   // Move to next node
    }

    *head = NULL;   // Set head to NULL
    *tail = NULL;   // Set tail to NULL

    return SUCCESS;   // Return success
}

int cla_validation(int argc, char *argv[])   // Function to validate command-line inputs
{
    if(argc != 4)   // Check if total arguments are not equal to 4 (program + 3 inputs)
    {
        printf("Usage: ./a.out operand1 operator operand2\n");   // Show correct usage format
        return FAILURE;   // Return failure if argument count is wrong
    }

    // check operand1
    int i = 0;   // Initialize index to traverse operand1 string
    if(argv[1][0] == '+' || argv[1][0] == '-')   // Check if operand1 starts with '+' or '-'
        i = 1;   // Skip the sign character for validation

    for(; argv[1][i] != '\0'; i++)   // Loop through each character of operand1
    {
        if(argv[1][i] < '0' || argv[1][i] > '9')   // Ensure character is a digit (0–9)
        {
            printf("Invalid operand1\n");   // Print error if invalid character found
            return FAILURE;   // Return failure for invalid operand1
        }
    }

    // check operand2
    i = 0;   // Reset index for operand2
    if(argv[3][0] == '+' || argv[3][0] == '-')   // Check if operand2 starts with '+' or '-'
        i = 1;   // Skip the sign character

    for(; argv[3][i] != '\0'; i++)   // Loop through each character of operand2
    {
        if(argv[3][i] < '0' || argv[3][i] > '9')   // Ensure character is a digit (0–9)
        {
            printf("Invalid operand2\n");   // Print error if invalid character found
            return FAILURE;   // Return failure for invalid operand2
        }
    }

    return SUCCESS;   // Return success if both operands are valid

}
void operation_decider(char *op1, char oper, char *op2,node *head1, node *tail1,node *head2, node *tail2, node **headR, node **tailR)   // Function to decide and perform operation
{
    int sign1 = 1, sign2 = 1;   // Initialize signs of operands as positive

    // detect signs
    if(op1[0] == '-') sign1 = -1;   // If operand1 starts with '-', mark it negative
    if(op2[0] == '-') sign2 = -1;   // If operand2 starts with '-', mark it negative

    int result_sign = 1;   // Initialize result sign as positive

    //addition
    if(oper == '+')   // Check if operation is addition
    {
        if(sign1 == sign2)   // If both operands have same sign
        {
            // (+A)+(+B) or (-A)+(-B)
            addition(tail1, tail2, headR, tailR);   // Perform addition
            result_sign = sign1;   // Result sign same as operands
        }
        else   // If operands have different signs
        {
            // (+A)+(-B) or (-A)+(+B) → subtraction
            int cmp = compare_list(head1, head2);   // Compare magnitudes

            if(cmp == SAME)   // If both numbers are equal
            {
                insert_first(headR, tailR, 0);   // Result is 0
                result_sign = 1;   // Zero is positive
            }
            else if(cmp == OPERAND1)   // If operand1 > operand2
            {
                subtraction(tail1, tail2, headR, tailR);   // Subtract operand2 from operand1
                result_sign = sign1;   // Result sign same as operand1
            }
            else   // If operand2 > operand1
            {
                subtraction(tail2, tail1, headR, tailR);   // Subtract operand1 from operand2
                result_sign = sign2;   // Result sign same as operand2
            }
        }
    }

    // subtraction
    else if(oper == '-')   // Check if operation is subtraction
    {
        // A - B = A + (-B)
        sign2 = -sign2;   // Reverse sign of operand2

        if(sign1 == sign2)   // If both signs now match
        {
            addition(tail1, tail2, headR, tailR);   // Perform addition
            result_sign = sign1;   // Result sign same as operands
        }
        else   // If signs differ
        {
            int cmp = compare_list(head1, head2);   // Compare magnitudes

            if(cmp == SAME)   // If both numbers equal
            {
                insert_first(headR, tailR, 0);   // Result is 0
                result_sign = 1;   // Zero is positive
            }
            else if(cmp == OPERAND1)   // If operand1 > operand2
            {
                subtraction(tail1, tail2, headR, tailR);   // Subtract operand2 from operand1
                result_sign = sign1;   // Result sign same as operand1
            }
            else   // If operand2 > operand1
            {
                subtraction(tail2, tail1, headR, tailR);   // Subtract operand1 from operand2
                result_sign = sign2;   // Result sign same as operand2
            }
        }
    }

    // multipiction
    else if(oper == 'x' || oper == 'X')   // Check if operation is multiplication
    {
        multiplication(tail1, tail2, headR, tailR);   // Perform multiplication
        result_sign = sign1 * sign2;   // Result sign based on operand signs
    }

    //division
    else if(oper == '/')   // Check if operation is division
    {
        division(head1, head2, headR, tailR);   // Perform division
        result_sign = sign1 * sign2;   // Result sign based on operand signs
    }

    //result
    if(result_sign == -1 && *headR != NULL && (*headR)->data != 0)   // If result is negative and not zero
    {
      
        printf("-");   // Print negative sign before result
    }
}
