from decimal import Decimal, getcontext
import math

getcontext().prec = 28  # precision

def binary_to_decimal(binary):
    dot_pos = binary.find('.')
    integer_part = binary[:dot_pos] if dot_pos != -1 else binary
    fractional_part = binary[dot_pos + 1:] if dot_pos != -1 else ''
    
    decimal = Decimal(0)
    
    # Converting Integer Part
    print("Converting Binary to Decimal (Integer Part):")
    for power, bit in enumerate(reversed(integer_part)):
        if bit == '1':
            print(f"Adding 2^{power} = {Decimal(2 ** power)}")
            decimal += Decimal(2 ** power)
    
    # Converting Fractional Part
    print("Converting Binary to Decimal (Fractional Part):")
    for power, bit in enumerate(fractional_part):
        if bit == '1':
            print(f"Adding 2^{-(power + 1)} = {Decimal(2 ** -(power + 1))}")
            decimal += Decimal(2 ** -(power + 1))
    
    print(f"Result: {decimal}")
    return decimal

def decimal_to_binary(decimal):
    integer_part = int(decimal)
    fractional_part = decimal - integer_part
    binary = ""
    
    print("Converting Decimal to Binary (Integer Part):")
    if integer_part == 0:
        binary = "0"
    while integer_part > 0:
        remainder = integer_part % 2
        print(f"{integer_part} / 2, Remainder = {remainder}, Quotient = {integer_part // 2}")
        binary = str(remainder) + binary
        integer_part //= 2
    
    # Converting Fractional Part
    print("Converting Decimal to Binary (Fractional Part):")
    fractional_binary = "."
    while fractional_part > 0:
        if len(fractional_binary) > 20:  #limit for precision
            break
        fractional_part *= 2
        bit = int(fractional_part)
        print(f"{fractional_part} -> Bit = {bit}")
        fractional_binary += '1' if bit == 1 else '0'
        fractional_part -= bit
    
    print(f"Binary result: {binary + fractional_binary}")
    return binary + fractional_binary

def decimal_to_octal(decimal):
    integer_part = int(decimal)
    fractional_part = decimal - integer_part
    octal = ""

    print("Converting Decimal to Octal (Integer Part):")
    if integer_part == 0:
        octal = "0"
    while integer_part > 0:
        remainder = integer_part % 8
        print(f"{integer_part} / 8, Remainder = {remainder}, Quotient = {integer_part // 8}")
        octal = str(remainder) + octal
        integer_part //= 8
    
    # Converting Fractional Part
    print("Converting Decimal to Octal (Fractional Part):")
    fractional_octal = "."
    while fractional_part > 0:
        if len(fractional_octal) > 20:  # Limit  length 
            break
        fractional_part *= 8
        digit = int(fractional_part)
        print(f"{fractional_part} -> Digit = {digit}")
        fractional_octal += str(digit)
        fractional_part -= digit
    
    print(f"Octal result: {octal + fractional_octal}")
    return octal + fractional_octal

def octal_to_decimal(octal):
    dot_pos = octal.find('.')
    integer_part = octal[:dot_pos] if dot_pos != -1 else octal
    fractional_part = octal[dot_pos + 1:] if dot_pos != -1 else ''
    
    decimal = Decimal(0)
    
    # Converting Integer Part
    print("Converting Octal to Decimal (Integer Part):")
    for power, digit in enumerate(reversed(integer_part)):
        digit = int(digit)
        print(f"Adding {digit} * 8^{power} = {Decimal(digit * (8 ** power))}")
        decimal += Decimal(digit * (8 ** power))
    
    # Converting Fractional Part
    print("Converting Octal to Decimal (Fractional Part):")
    for power, digit in enumerate(fractional_part):
        digit = int(digit)
        print(f"Adding {digit} * 8^{-(power + 1)} = {Decimal(digit * (8 ** -(power + 1)))}")
        decimal += Decimal(digit * (8 ** -(power + 1)))
    
    print(f"Result: {decimal}")
    return decimal

def decimal_to_hexadecimal(decimal):
    integer_part = int(decimal)
    fractional_part = decimal - integer_part
    hex_result = ""
    
    print("Converting Decimal to Hexadecimal (Integer Part):")
    if integer_part == 0:
        hex_result = "0"
    while integer_part > 0:
        remainder = integer_part % 16
        print(f"{integer_part} / 16, Remainder = {remainder}, Quotient = {integer_part // 16}")
        hex_result = (hex(remainder)[2:].upper() if remainder >= 10 else str(remainder)) + hex_result
        integer_part //= 16
    
    # Converting Fractional Part
    print("Converting Decimal to Hexadecimal (Fractional Part):")
    fractional_hex = "."
    while fractional_part > 0:
        if len(fractional_hex) > 20:  # Limit length
            break
        fractional_part *= 16
        digit = int(fractional_part)
        print(f"{fractional_part} -> Digit = {digit}")
        fractional_hex += (hex(digit)[2:].upper() if digit >= 10 else str(digit))
        fractional_part -= digit
    
    print(f"Hexadecimal result: {hex_result + fractional_hex}")
    return hex_result + fractional_hex

def hexadecimal_to_decimal(hex_str):
    dot_pos = hex_str.find('.')
    integer_part = hex_str[:dot_pos] if dot_pos != -1 else hex_str
    fractional_part = hex_str[dot_pos + 1:] if dot_pos != -1 else ''
    
    decimal = Decimal(0)
    
    # Converting Integer Part
    print("Converting Hexadecimal to Decimal (Integer Part):")
    for power, digit in enumerate(reversed(integer_part)):
        if '0' <= digit <= '9':
            digit = int(digit)
        else:
            digit = ord(digit.upper()) - ord('A') + 10
        print(f"Adding {digit} * 16^{power} = {Decimal(digit * (16 ** power))}")
        decimal += Decimal(digit * (16 ** power))
    
    # Converting Fractional Part
    print("Converting Hexadecimal to Decimal (Fractional Part):")
    for power, digit in enumerate(fractional_part):
        if '0' <= digit <= '9':
            digit = int(digit)
        else:
            digit = ord(digit.upper()) - ord('A') + 10
        print(f"Adding {digit} * 16^{-(power + 1)} = {Decimal(digit * (16 ** -(power + 1)))}")
        decimal += Decimal(digit * (16 ** -(power + 1)))
    
    print(f"Result: {decimal}")
    return decimal

def binary_to_octal(binary):
    decimal = binary_to_decimal(binary)
    return decimal_to_octal(decimal)

def octal_to_binary(octal):
    decimal = octal_to_decimal(octal)
    return decimal_to_binary(decimal)

def binary_to_hexadecimal(binary):
    decimal = binary_to_decimal(binary)
    return decimal_to_hexadecimal(decimal)

def hexadecimal_to_binary(hex_str):
    decimal = hexadecimal_to_decimal(hex_str)
    return decimal_to_binary(decimal)

def octal_to_hexadecimal(octal):
    decimal = octal_to_decimal(octal)
    return decimal_to_hexadecimal(decimal)

def hexadecimal_to_octal(hex_str):
    decimal = hexadecimal_to_decimal(hex_str)
    return decimal_to_octal(decimal)

def main():
    cont = 'y'
    
    while cont.lower() == 'y':
        choice = int(input("Select the conversion you want to perform:\n"
                           "1. Binary to Decimal\n"
                           "2. Decimal to Binary\n"
                           "3. Decimal to Octal\n"
                           "4. Octal to Decimal\n"
                           "5. Decimal to Hexadecimal\n"
                           "6. Hexadecimal to Decimal\n"
                           "7. Binary to Octal\n"
                           "8. Octal to Binary\n"
                           "9. Binary to Hexadecimal\n"
                           "10. Hexadecimal to Binary\n"
                           "11. Octal to Hexadecimal\n"
                           "12. Hexadecimal to Octal\n"
                           "Enter your choice: "))

        if choice == 1:
            binary = input("Enter a binary number: ")
            binary_to_decimal(binary)
        elif choice == 2:
            decimal = Decimal(input("Enter a decimal number: "))
            decimal_to_binary(decimal)
        elif choice == 3:
            decimal = Decimal(input("Enter a decimal number: "))
            decimal_to_octal(decimal)
        elif choice == 4:
            octal = input("Enter an octal number: ")
            octal_to_decimal(octal)
        elif choice == 5:
            decimal = Decimal(input("Enter a decimal number: "))
            decimal_to_hexadecimal(decimal)
        elif choice == 6:
            hex_str = input("Enter a hexadecimal number: ")
            hexadecimal_to_decimal(hex_str)
        elif choice == 7:
            binary = input("Enter a binary number: ")
            binary_to_octal(binary)
        elif choice == 8:
            octal = input("Enter an octal number: ")
            octal_to_binary(octal)
        elif choice == 9:
            binary = input("Enter a binary number: ")
            binary_to_hexadecimal(binary)
        elif choice == 10:
            hex_str = input("Enter a hexadecimal number: ")
            hexadecimal_to_binary(hex_str)
        elif choice == 11:
            octal = input("Enter an octal number: ")
            octal_to_hexadecimal(octal)
        elif choice == 12:
            hex_str = input("Enter a hexadecimal number: ")
            hexadecimal_to_octal(hex_str)
        
        cont = input("Do you want to perform another conversion? (y/n): ")

if __name__ == "__main__":
    main()
