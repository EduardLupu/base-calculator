#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

vector <int> add(vector <int> number_1, vector <int> number_2, int base)
{
    /// This function adds 2 numbers in a specified base.
    int carry = 0, auxiliary, index, number_2_index, number_1_index;
    int number_1_size = number_1.size(), number_2_size = number_2.size();
    int min_length, max_length, is_bigger;
    std::vector< int > sum;
    std::reverse(number_1.begin(), number_1.end());
    std::reverse(number_2.begin(), number_2.end()); /// We reverse the list of digits of the numbers because we start from the last digits.
    if (number_1_size > number_2_size) /// We check which number is bigger.
    {
        is_bigger = 1;
        min_length = number_2_size;
        max_length = number_1_size;
    }
    else
    {
        is_bigger = 2;
        min_length = number_1_size;
        max_length = number_2_size;
    }

    for (index = 0; index < max_length; index++)
    {
        if (index < min_length)
        {
            number_1_index = number_1[index];
            number_2_index = number_2[index];
        }
        else if (is_bigger == 1)
        {
            number_1_index = number_1[index];           /// We put the digits into the variables number_1_index and number_2_index.
            number_2_index = 0;
        }
        else
        {
            number_1_index = 0;
            number_2_index = number_2[index];
        }
        auxiliary = number_1_index + number_2_index + carry; /// The algorithm is like the one on paper: We add
        sum.push_back(auxiliary % base);                     /// the last 2 digits and the carry, and we add the result to the sum list in the specified base.
        carry = auxiliary / base;
    }
    if (carry != 0) /// If there is any carry which hasn't been added, we add it now as the first digit of the sum.
        sum.push_back(carry);
    std::reverse(sum.begin(), sum.end()); /// We need to rotate the sum list once in order to get it.
    return sum;
}

vector <int> sub(vector <int> number_1, vector <int> number_2, int base)
{
    /// This function substract number_2 from number_1; number_1 >= number_2
    int carry = 0, auxiliary, index, number_2_index, number_1_index;
    int number_1_size = number_1.size(), number_2_size = number_2.size();
    int min_length, max_length, is_bigger;
    std::vector< int > result;
    std::reverse(number_1.begin(), number_1.end());
    std::reverse(number_2.begin(), number_2.end());
    if (number_1_size > number_2_size)
    {
        is_bigger = 1;
        min_length = number_2_size;
        max_length = number_1_size;
    }
    else
    {
        is_bigger = 2;
        min_length = number_1_size;
        max_length = number_2_size;
    }
    for (index = 0; index < max_length; index++)
    {
        if (index < min_length)
        {
            number_1_index = number_1[index];
            number_2_index = number_2[index];
        }
        else if (is_bigger == 1)
        {
            number_1_index = number_1[index];          /// We put the digits into the variables number_1_index and number_2_index.
            number_2_index = 0;
        }
        else
        {
            number_1_index = 0;
            number_2_index = number_2[index];
        }
        auxiliary = number_1_index - number_2_index - carry;
        if (auxiliary < 0)
            carry = 1;
        else carry = 0;
        if (carry)
            auxiliary += base;
        result.push_back(auxiliary);
    }
    while(result[result.size()-1] == 0 && result.size() > 1)  /// We eliminate the 0 at the start of the number, if there are any.
        result.pop_back();
    std::reverse(result.begin(), result.end()); /// We need to rotate the result list once in order to get it correct.
    return result;
}

vector <int> mul(vector <int> number_1, vector <int> number_2, int base)
{
    /// This function multiplies 2 numbers in a specified base.
    int carry = 0, index, index2;
    int number_1_size = number_1.size(), number_2_size = number_2.size();
    std::vector< int > result(100, 0);
    std::reverse(number_1.begin(), number_1.end());
    std::reverse(number_2.begin(), number_2.end());
    for (index = 0; index < number_1_size; index++)            /// We multiply every 2 digits of the numbers and store the result.
    {
        for (index2 = 0; index2 < number_2_size; index2++)
        {
            result[index + index2] += number_1[index] * number_2[index2];
        }
    }
    for (index = 0; index < (int)result.size(); index++)  /// We add the carries.
    {
        result[index] += carry;
        carry = result[index] / base;
        result[index] = result[index] % base;
    }
    while (carry)                  /// If the carry isn't 0, we have to add him at the start of the result until he is.
    {
        result.push_back(carry % base);
        carry = carry / base;
    }
    while(result[result.size()-1] == 0 && result.size() > 1) /// We eliminate 0 from the start, in case they are any
        result.pop_back();
    std::reverse(result.begin(), result.end());
    return result;
}

vector <int> div(vector <int> number, int divisor, int base)
{
    /// This function divides the number <number> in base <base> with the one digit divisor <divisor>
    int carry = 0, index;
    int number_size = number.size();
    for (index = 0; index < number_size; index++)
    {
        carry = base * carry + number[index];
        number[index] = carry / divisor;
        carry = carry % divisor;
    }
    std::reverse(number.begin(), number.end());
    while(number[number.size()-1] == 0 && number.size() > 1) /// We remove 0 from the start
        number.pop_back();
    std::reverse(number.begin(), number.end());
    return number; /// The result of number / divisor in the specified base.
}

int mod(vector <int> number, int divisor, int base)
{
    /// This function calculates the modulo of the operation number % divisor in the specified base.
    int index, rest, number_size;
    number_size = number.size();
    rest = 0;
    for (index = 0; index < number_size; index++)
        rest = (rest * base + number[index]) % divisor;
    return rest;
}

void convert_string_to_list(string s, vector <int> &A)
{
    /// This function converts a string of characters (which mean a number from base {2, ..., 16}) to a vector list.
    for (int i = 0; s[i]; ++i)
    {
        if (s[i] >= 'A' && s[i] <= 'F')
            A.push_back(s[i] - 'A' + 10);
        else A.push_back(s[i] - '0');
    }
    return ;
}

string convert_list_to_string(vector <int> A)
{
    /// This function converts a vector list to a string of characters (which mean a number from base {2, ..., 16})
    string s = "";
    for (int i = 0; i < (int)A.size(); ++i)
        if (A[i] >= 10 && A[i] <= 15)
            s += ('A' + A[i] % 10);
        else if (A[i] >= 0 && A[i] <= 9)
            s += (A[i] + '0');
        else return "Error!";
    return s;
}

vector <int> succesive_division(vector <int> number, int b, int h)
{
    /// This function converts a number from base b to base h using the successive division method. (b > h)
    int rest = 0;
    vector <int> result;
    while (number[0] != 0)
    {
        rest = mod(number, h, b);
        number = div(number, h, b);
        result.push_back(rest);
    }
    std::reverse(result.begin(), result.end());
    return result;
}

vector <int> substitution(vector <int> number, int b, int h)
{
    /// This function converts a number from base b to base h using the substitution method. (b < h)
    int power = 1, index, sum = 0;
    vector <int> result;
    std::reverse(number.begin(), number.end());
    for (index = 0; index < (int)number.size(); index++)
    {
        sum = sum + number[index] * power;
        power *= b;
    }
    while(sum)
    {
        result.push_back(sum % h);
        sum/=h;
    }
    std::reverse(result.begin(), result.end());
    return result;
}

vector <int> rapid_conversion(vector <int> number, int b, int h)
{
    /// This function converts a number from base b to base h.      b, h are from the set {2, 4, 8, 16}
    int index, aux_b = b, aux_h = h;
    vector <int> result;
    std::reverse(number.begin(), number.end());
    if (b > h)
    {
        int diff = 0;
        while(aux_b)
        {
            diff++;
            aux_b/=aux_h;
        }
        for (index = 0; index < (int)number.size(); index++)
        {
            for(int j = 1; j < diff && number[index]; ++j)
            {
                result.push_back(number[index] % h);
                number[index] /= h;
            }
        }
    }
    else
    {
        int diff = 0;
        while(aux_h)
        {
            diff++;
            aux_h/=aux_b;
        }
        diff--;
        for (index = 0; index < (int)number.size(); index+=diff)
        {
            int sum = 0, pow = 1, j;
            for(j = index; j < index + diff; j++)
            {
                if (j >= (int)number.size())
                    break;
                sum = sum + number[j] * pow;
                pow *= b;
            }
            result.push_back(sum);
        }
    }
    std::reverse(result.begin(), result.end());
    return result;
}

vector <int> intermediate_base_10(vector <int> number, int b, int h)
{
    /// This function converts a number from base b to base h using the base 10 as an intermediate.
    vector <int> result;
    if (b <= 10)
        result = substitution(number, b, 10);
    else result = succesive_division(number, b, 10);

    if (h <= 10)
        result = succesive_division(result, 10, h);
    else result = substitution(result, 10, h);
    return result;
}


void menu()
{   /// This function displays the menu
    std::cout << " Author: Lupu Eduard \n\n                       Base Calculator \n";
    std::cout << " 1. Add \n 2. Substract \n 3. Multiplication \n 4. Division by one digit \n\n";
    std::cout << "                       Base Converter \n\n";
    std::cout << " 5. Successive divisions \n 6. Substitution \n 7. Rapid conversions \n 8. Intermediate base 10\n\n";
    return ;
}

int main()
{   /// Main function
    int base, divisor, h_base;
    string a, b, command;
    vector <int> A, B, result;
    menu();
    std::cout << "Please enter a command: ";
    std::cin >> command;
    if (command == "1")
    {
        std::cout << "Please enter the first number: ";
        std::cin >> a;
        std::cout << "Please enter the second number: ";
        std::cin >> b;
        std::cout << "Please enter the base: ";
        std::cin >> base;
        convert_string_to_list(a, A);
        convert_string_to_list(b, B);
        result = add(A, B, base);
        std::cout << "Result: " <<  a << " + " << b << " = " << convert_list_to_string(result);
    }
    else if (command == "2")
    {
        std::cout << "Please enter the first number: ";
        std::cin >> a;
        std::cout << "Please enter the second number: ";
        std::cin >> b;
        std::cout << "Please enter the base: ";
        std::cin >> base;
        convert_string_to_list(a, A);
        convert_string_to_list(b, B);
        result = sub(A, B, base);
        std::cout << "Result: " <<  a << " - " << b << " = " << convert_list_to_string(result);
    }
    else if (command == "3")
    {
        std::cout << "Please enter the first number: ";
        std::cin >> a;
        std::cout << "Please enter the second number: ";
        std::cin >> b;
        std::cout << "Please enter the base: ";
        std::cin >> base;
        convert_string_to_list(a, A);
        convert_string_to_list(b, B);
        result = mul(A, B, base);
        std::cout << "Result: " <<  a << " * " << b << " = " << convert_list_to_string(result);
    }
    else if (command == "4")
    {
        std::cout << "Please enter the first number: ";
        std::cin >> a;
        std::cout << "Please enter the digit: ";
        std::cin >> divisor;
        std::cout << "Please enter the base: ";
        std::cin >> base;
        convert_string_to_list(a, A);
        result = div(A, divisor, base);
        std::cout << "Result: " <<  a << " / " << divisor << " = " << convert_list_to_string(result) << " rest " << mod(A, divisor, base);
    }
    else if (command == "5")
    {
        std::cout << "Succesive division method (source base > destination base)\nPlease enter the number: ";
        std::cin >> a;
        std::cout << "Please enter the source base: ";
        std::cin >> base;
        std::cout << "Please enter the destination base: ";
        std::cin >> h_base;
        convert_string_to_list(a, A);
        result = succesive_division(A, base, h_base);
        std::cout << "Result: " <<  a << " in base " << base << " is " << convert_list_to_string(result) << " in base " << h_base;
    }
     else if (command == "6")
    {
        std::cout << "Substitution method (source base < destination base)\nPlease enter the number: ";
        std::cin >> a;
        std::cout << "Please enter the source base: ";
        std::cin >> base;
        std::cout << "Please enter the destination base: ";
        std::cin >> h_base;
        convert_string_to_list(a, A);
        result = substitution(A, base, h_base);
        std::cout << "Result: " <<  a << " in base " << base << " is " << convert_list_to_string(result) << " in base " << h_base;
    }
    else if (command == "7")
    {
        std::cout << "Rapid conversion (b, h are from {2, 4, 8, 16})\nPlease enter the number: ";
        std::cin >> a;
        std::cout << "Please enter the source base: ";
        std::cin >> base;
        std::cout << "Please enter the destination base: ";
        std::cin >> h_base;
        convert_string_to_list(a, A);
        result = rapid_conversion(A, base, h_base);
        std::cout << "Result: " <<  a << " in base " << base << " is " << convert_list_to_string(result) << " in base " << h_base;
    }
    else if (command == "8")
    {
         std::cout << "Intermediate base 10\nPlease enter the number: ";
        std::cin >> a;
        std::cout << "Please enter the source base: ";
        std::cin >> base;
        std::cout << "Please enter the destination base: ";
        std::cin >> h_base;
        convert_string_to_list(a, A);
        result = intermediate_base_10(A, base, h_base);
        std::cout << "Result: " <<  a << " in base " << base << " is " << convert_list_to_string(result) << " in base " << h_base;
    }
    return 0;
}
