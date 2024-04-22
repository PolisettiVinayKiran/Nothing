/*Write any c program in input*/
/*Design a lexical analyzer for a given language and the lexical analyzer should ignore redundant spaces, tabs, and new lines. It should also ignore comments. */

#include <string.h>
#include <ctype.h>
#include <stdio.h>


void keyword(char str[10])
{
    if (strcmp("for", str) == 0 || strcmp("while", str) == 0 || strcmp("do", str) == 0 || strcmp("int", str) == 0 || 
        strcmp("float", str) == 0 || strcmp("char", str) == 0 || strcmp("double", str) == 0 ||
        strcmp("static", str) == 0 || strcmp("switch", str) == 0 || strcmp("case", str) == 0 || strcmp("return", str) == 0)
    {
        printf("\n%s is a keyword", str);
    }
    else
    {
        printf("\n%s is an identifier", str);
    }
}


int main() {
    FILE *input_ptr, *identifier_ptr, *specialchar_ptr, *operator_ptr, *string_ptr;
    char c, str[10], st1[10];
    int num[100], lineno = 0, tokenvalue = 0, i = 0, j = 0, k = 0;
    int inString = 0; // Flag to track if currently inside a string literal

    printf("\nEnter the C program in the \"input\" file\n");

    input_ptr = fopen("input", "r");
    identifier_ptr = fopen("identifier", "w");
    specialchar_ptr = fopen("specialchar", "w");
    operator_ptr = fopen("operator", "w");
    string_ptr = fopen("string", "w");

    while ((c = getc(input_ptr)) != EOF) {
        if (c == '\"') {
            putc(c, string_ptr); // Write the opening quote
            inString = !inString; // Toggle the flag
        } else if (inString) {
            putc(c, string_ptr);
            if (c == '\"') {
                inString = !inString; // Toggle the flag when closing quote is encountered
                putc('\n', string_ptr); // Write a newline to separate each string literal
            }
        } else if (isdigit(c)) {
            tokenvalue = c - '0';
            c = getc(input_ptr);
            while (isdigit(c)) {
                tokenvalue = (tokenvalue * 10) + (c - '0');
                c = getc(input_ptr);
            }
            num[i++] = tokenvalue;
            ungetc(c, input_ptr);
        } else if (isalpha(c)) {
            putc(c, identifier_ptr);
            c = getc(input_ptr);
            while (isdigit(c) || isalpha(c) || c == '_' || c == '$') {
                putc(c, identifier_ptr);
                c = getc(input_ptr);
            }
            putc(' ', identifier_ptr);
            ungetc(c, input_ptr);
        } else if (c == ' ' || c == '\t') {
            // Ignore whitespace
        } else if (c == '\n') {
            lineno++;
        } else if (c == '/' && (getc(input_ptr) == '/')) {
            // Ignore single-line comments
            while ((c = getc(input_ptr)) != '\n' && c != EOF) {
                // Skip comment content
            }
            lineno++;
        } else if (c == '<' || c == '+' || c == '-' || c == '*' || c == '/' || c == '>' || c == '=' || c == '%' || c == '&') {
            putc(c, operator_ptr);
        } else {
            putc(c, specialchar_ptr);
        }
    }

    // Close all files
    fclose(input_ptr);
    fclose(identifier_ptr);
    fclose(specialchar_ptr);
    fclose(operator_ptr);
    fclose(string_ptr);



    printf("\nThe number's in the program are ");
    for (j = 0; j < i; j++)
    {
        printf("%d ", num[j]);
    }
    printf("\n");
    printf("\n");


    identifier_ptr = fopen("identifier", "r");
    k = 0;
    printf("The keywords and identifiers are - ");
    while ((c = getc(identifier_ptr)) != EOF)
    {
        if (c != ' ')
        {
            str[k++] = c;
        }
        else
        {
            str[k] = '\0';
            keyword(str);
            k = 0;
        }
    }
    printf("\n");
    fclose(identifier_ptr);


    specialchar_ptr = fopen("specialchar", "r");
    printf("\nSpecial characters are - ");
    while ((c = getc(specialchar_ptr)) != EOF)
    {
        printf("%c ", c);
    }
    printf("\n");
    printf("\n");
    fclose(specialchar_ptr);


    operator_ptr = fopen("operator", "r");
    printf("\nOperators are - ");
    while ((c = getc(operator_ptr)) != EOF)
    {
        printf("%c ", c);
    }
    printf("\n");
    printf("\n");
    fclose(operator_ptr);
    

    string_ptr = fopen("string", "r");
    printf("\nStrings are - ");
    while ((c = getc(string_ptr)) != EOF)
    {
        printf("%c ", c);
    }
    printf("\n");
    printf("\n");
    fclose(string_ptr);


    printf("Total no. of lines are - %d", lineno);
}