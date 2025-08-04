def gcd(a, b):
    while b != 0:
        a, b = b, a % b
    return a

def mod_inverse(e, phi):
    
    t, new_t = 0, 1
    r, new_r = phi, e
    while new_r != 0:
        quotient = r // new_r
        t, new_t = new_t, t - quotient * new_t
        r, new_r = new_r, r - quotient * new_r

    if r > 1:
        print("No modular inverse exists for the given values.")
        return -1
    if t < 0:
        t += phi
    return t

def mod_exp(base, exp, mod):
    result = 1
    base = base % mod
    while exp > 0:
        if exp % 2 == 1:
            result = (result * base) % mod
        exp = exp >> 1
        base = (base * base) % mod
    return result

def main():
    print("=== RSA Encryption Program ===")
    
    while True:
        try:
            p = int(input("Enter the first prime number (p): "))
            q = int(input("Enter the second prime number (q): "))
            if p == q:
                print("Error: p and q must be distinct prime numbers. Please try again.")
                continue
            break
        except ValueError:
            print("Invalid input. Please enter valid integers.")

    n = p * q
    phi = (p - 1) * (q - 1)
    print(f"\nStep 2: Compute n = p * q => n = {n}")
    print(f"Step 3: Compute phi(n) = (p - 1) * (q - 1) => phi(n) = {phi}")

    while True:
        try:
            e = int(input(f"\nEnter a public exponent e such that gcd(e, {phi}) = 1 and 1 < e < {phi}:\n"))
            if not (1 < e < phi):
                print("Error: e must be in the range 1 < e < phi(n). Please try again.")
                continue
            if gcd(e, phi) != 1:
                print("The chosen e is not coprime to phi(n). Please choose another e.")
                continue
            break
        except ValueError:
            print("Invalid input. Please enter a valid integer.")

    d = mod_inverse(e, phi)
    if d == -1:
        print("Error in computing modular inverse. Exiting program.")
        return

    print(f"Step 5: Compute d, the modular inverse of e mod phi(n) => d = {d}")
    print(f"\nPublic Key: ({e}, {n})")
    print(f"Private Key: ({d}, {n})\n")

    # Option to encrypt and decrypt message
    while True:
        try:
            message = int(input("Enter a message (integer) to encrypt: "))
            if message >= n:
                print("The message must be less than n. Please re-enter.")
                continue

            encrypted_message = mod_exp(message, e, n)
            print(f"Encrypted message: {encrypted_message}")

            decrypted_message = mod_exp(encrypted_message, d, n)
            print(f"Decrypted message: {decrypted_message}")

            choice = input("Would you like to encrypt and decrypt another message? (y/n): ").strip().lower()
            if choice != 'y':
                break
        except ValueError:
            print("Invalid input. Please enter a valid integer.")

    print("Thank you for using the RSA encryption program. Goodbye!")

if __name__ == "__main__":
    main()
