def egyptian_fraction(numerator, denominator):
    """Calculate the Egyptian Fraction representation of a given fraction."""
    result = []
    print(f"Starting with: {numerator}/{denominator}")

    while numerator != 0:
        # Calculate the next unit fraction's denominator
        x = denominator // numerator + (denominator % numerator != 0)
        result.append(f"1/{x}")

        # Display current step
        print(f"Next unit fraction: 1/{x}")
        print(f"Update: {numerator}/{denominator} - 1/{x}")

        # Update the numerator and denominator
        numerator = numerator * x - denominator
        denominator = denominator * x

        # Display the new fraction after the update
        print(f"New Fraction: {numerator}/{denominator}")
        print("------------------------------------")
    
    return result

def display_egyptian_fraction(numerator, denominator):
    """Display the Egyptian Fraction representation of a given fraction."""
    print(f"\nEgyptian Fraction representation of {numerator}/{denominator} is: ", end="")
    fractions = egyptian_fraction(numerator, denominator)
    print(" + ".join(fractions))

def get_valid_input(prompt):
    """Get a valid integer input from the user."""
    while True:
        try:
            value = int(input(prompt))
            if value <= 0:
                raise ValueError("The value must be a positive integer.")
            return value
        except ValueError as e:
            print(e)

def main():
    print("=== Egyptian Fraction Calculator ===")
    while True:
        # Get numerator and denominator from the user
        numerator = get_valid_input("Enter the numerator: ")
        denominator = get_valid_input("Enter the denominator: ")

        display_egyptian_fraction(numerator, denominator)

        # Ask the user if they want to perform another calculation
        choice = input("\nWould you like to perform another calculation? (y/n): ").strip().lower()
        if choice != 'y':
            break
    
    print("Thank you for using the Egyptian Fraction Calculator!")

if __name__ == "__main__":
    main()
