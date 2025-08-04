def modular_exponentiation(base, exp, mod):
    result = 1
    base = base % mod
    while exp > 0:
        if exp % 2 == 1:
            result = (result * base) % mod
        exp //= 2
        base = (base * base) % mod
    return result

def diffie_hellman(p, g, private_key):
    return modular_exponentiation(g, private_key, p)

def get_valid_prime():
    while True:
        try:
            p = int(input("Enter a large prime number (p): "))
            if p <= 1:
                raise ValueError("The number must be greater than 1.")
            if not is_prime(p):
                raise ValueError(f"{p} is not a prime number. Please enter a valid prime.")
            return p
        except ValueError as ve:
            print(ve)

def get_valid_primitive_root(p):
    while True:
        try:
            g = int(input(f"Enter a primitive root modulo {p} (g): "))
            if g <= 1 or g >= p:
                raise ValueError("The primitive root must be greater than 1 and less than p.")
            return g
        except ValueError as ve:
            print(ve)

def get_valid_private_key(name):
    while True:
        try:
            private_key = int(input(f"{name}, enter your private key (a): "))
            if private_key <= 0:
                raise ValueError("Private key must be a positive integer.")
            return private_key
        except ValueError as ve:
            print(ve)

def is_prime(num):
    if num < 2:
        return False
    for i in range(2, int(num**0.5) + 1):
        if num % i == 0:
            return False
    return True

def main():
    print("=== Diffie-Hellman Key Exchange ===")
    
    p = get_valid_prime()
    g = get_valid_primitive_root(p)
    
    private_key_a = get_valid_private_key("Alice")
    private_key_b = get_valid_private_key("Bob")
    
    public_key_a = diffie_hellman(p, g, private_key_a)
    public_key_b = diffie_hellman(p, g, private_key_b)
    
    print(f"\nAlice's public key (A): {public_key_a}")
    print(f"Bob's public key (B): {public_key_b}")

    shared_secret_a = diffie_hellman(p, public_key_b, private_key_a)
    shared_secret_b = diffie_hellman(p, public_key_a, private_key_b)

    print(f"\nAlice's shared secret: {shared_secret_a}")
    print(f"Bob's shared secret: {shared_secret_b}")

    if shared_secret_a == shared_secret_b:
        print("The shared secrets match!")
    else:
        print("The shared secrets do not match!")

if __name__ == "__main__":
    main()
