from decimal import Decimal, getcontext

# Set precision for Decimal calculations
getcontext().prec = 30

def to_decimal(number, base):
    dot_pos = number.find('.')
    integer_part = number if dot_pos == -1 else number[:dot_pos]
    fractional_part = "" if dot_pos == -1 else number[dot_pos + 1:]

    decimal = Decimal(0)

    # Convert integer part
    print(f"Converting {integer_part} from base {base} to decimal (Integer part):")
    for i, digit in enumerate(reversed(integer_part)):
        value = int(digit) if digit.isdigit() else ord(digit.upper()) - ord('A') + 10
        if value >= base:
            print(f"Error: Invalid digit '{digit}' for base {base}")
            return -1
        decimal += Decimal(value) * (Decimal(base) ** i)
        print(f"Adding {value} * {base}^{i} = {Decimal(value) * (Decimal(base) ** i)}")

    # Convert fractional part
    print(f"Converting {fractional_part} from base {base} to decimal (Fractional part):")
    for i, digit in enumerate(fractional_part, start=1):
        value = int(digit) if digit.isdigit() else ord(digit.upper()) - ord('A') + 10
        if value >= base:
            print(f"Error: Invalid digit '{digit}' for base {base}")
            return -1
        decimal += Decimal(value) * (Decimal(base) ** -i)
        print(f"Adding {value} * {base}^{-i} = {Decimal(value) * (Decimal(base) ** -i)}")

    print(f"Total decimal value: {decimal}")
    return decimal

def from_decimal(decimal, base):
    integer_part = int(decimal)
    fractional_part = decimal - integer_part
    result = ""
    fractional_result = "."

    # Convert integer part
    print(f"Converting {integer_part} from decimal to base {base} (Integer part):")
    if integer_part == 0:
        result = "0"
    else:
        while integer_part > 0:
            remainder = integer_part % base
            result = (str(remainder) if remainder < 10 else chr(remainder - 10 + ord('A'))) + result
            print(f"{integer_part} / {base}, Remainder = {remainder}, Quotient = {integer_part // base}")
            integer_part //= base

    # Convert fractional part
    print(f"Converting fractional part from decimal to base {base} (Fractional part):")
    while fractional_part > 0 and len(fractional_result) <= 20:
        fractional_part *= base
        digit = int(fractional_part)
        fractional_result += str(digit) if digit < 10 else chr(digit - 10 + ord('A'))
        fractional_part -= digit
        print(f"Fractional Part: {fractional_part}, Digit = {digit}")

    print(f"Total converted value: {result + fractional_result}")
    return result + fractional_result

def perform_operation(num1, num2, op):
    if op == '+':
        return num1 + num2
    elif op == '-':
        return num1 - num2
    elif op == '*':
        return num1 * num2
    elif op == '/' and num2 != 0:
        return num1 / num2
    else:
        return None

def get_base_from_choice(choice):
    bases = {'a': 2, 'b': 8, 'c': 10, 'd': 16}
    return bases.get(choice.lower(), -1)

def main():
    cont = 'y'
    while cont.lower() == 'y':
        print("Select the base of the numbers:")
        print("a) Binary (base 2)")
        print("b) Octal (base 8)")
        print("c) Decimal (base 10)")
        print("d) Hexadecimal (base 16)")
        base_choice = input("Enter your choice (a, b, c, d): ")
        base = get_base_from_choice(base_choice)
        
        if base == -1:
            print("Invalid choice!")
            continue

        num1 = input("Enter the first number: ")
        num2 = input("Enter the second number: ")
        operation = input("Enter the operation (+, -, *, /): ")

        decimal_num1 = to_decimal(num1, base)
        decimal_num2 = to_decimal(num2, base)

        if decimal_num1 == -1 or decimal_num2 == -1:
            print("Error: Conversion failed due to invalid input!")
            continue

        if operation == '/' and decimal_num2 == 0:
            print("Error: Division by zero is not allowed!")
            continue

        print(f"Performing calculation: {decimal_num1} {operation} {decimal_num2}")
        result_decimal = perform_operation(decimal_num1, decimal_num2, operation)
        
        if result_decimal is None:
            print("Error: Invalid operation!")
            continue

        result = from_decimal(result_decimal, base)
        print(f"Result in decimal: {result_decimal}")
        print(f"Result in base {base}: {result}")

        cont = input("Do you want to perform another calculation? (y/n): ")

if __name__ == "__main__":
    main()
