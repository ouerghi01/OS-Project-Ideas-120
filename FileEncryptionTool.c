#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

char *content_file( char *argv);
bool is_prime(int e);
long long mod_exponentiation(long long base, long long exp, long long mod);
int gcd(int a, int b);

bool is_prime(int e) {
    if (e < 2) return false;
    for (int i = 2; i * i <= e; i++) {
        if (e % i == 0) {
            return false;
        }
    }
    return true;
}

long long mod_exponentiation(long long base, long long exp, long long mod) {
    long long result = 1;
    base = base % mod;  // Reduce base if it's more than mod
    while (exp > 0) {
        if (exp % 2 == 1) {  // If exp is odd, multiply base with result
            result = (result * base) % mod;
        }
        exp = exp >> 1;  // Divide exp by 2
        base = (base * base) % mod;
    }
    return result;
}

int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int encrypt(int argc,char *argv []) {
    int p = 7919;
    int q = 1009;
    if (!is_prime(p) || !is_prime(q)) {
        printf("Error: Numbers must be prime\n");
        return 1;
    }

    long long n = (long long)p * q;
    long long phi = (long long)(p - 1) * (q - 1);
    
    long long e;
    for (e = 2; e < phi; e++) {
        if (gcd(e, phi) == 1) {
            break;
        }
    }

    long long d = 1;
    while ((d * e) % phi != 1) {
        d++;
    }

    char *text_file = content_file( argv[1]);
    if (!text_file) {
        printf("Failed to read file.\n");
        return 1;
    }

    int length_text = strlen(text_file);
    FILE *file_ptr = fopen("output.txt", "w");
    FILE *file_d=fopen("d.txt","w") ;
    FILE *file_n=fopen("n.txt","w") ;

    fprintf(file_d, "%lld", d);
    fprintf(file_n, "%lld", n);

     
    if (!file_ptr) {
        printf("Error opening output file.\n");
        free(text_file);
        return 1;
    }

    for (int k = 0; k < length_text; k++) {
        int M = (int)text_file[k];  
        long long C = mod_exponentiation(M, e, n); // Encrypt
        fprintf(file_ptr, "%lld\n", C); 
    }

    fclose(file_ptr);
    fclose(file_d);
    free(text_file);
    fclose(file_n);
    
    // Public Key: (n, e), Private Key: (n, d)
    printf("Encryption complete! Public Key: (%lld, %lld)\n", n, e);
    return 0;
}

char *content_file( char *argv) {
    

    FILE *fptr = fopen(argv, "r");
    if (!fptr) {
        printf("Error opening file: %s\n", argv[1]);
        return NULL;
    }

    fseek(fptr, 0, SEEK_END);
    size_t length = ftell(fptr);
    fseek(fptr, 0, SEEK_SET);

    char *buffer = (char *)malloc(length + 1);
    if (!buffer) {
        fclose(fptr);
        return NULL;
    }

    size_t read_length = fread(buffer, 1, length, fptr);
    buffer[read_length] = '\0'; // Ensure null termination

    fclose(fptr);
    return buffer;
}
int decrypt(int argc,char *argv []) {
    char * file_encrypted= content_file(argv[1]);
    int    d= atoi(content_file(argv[2]));
    int    n= atoi(content_file(argv[3]));
    FILE * fptr = fopen("decrypted.txt","w");
    if (!fptr) {
        printf("Error opening output file.\n");
        free(file_encrypted);
        return 1;
    }    
    int i = 0 ;
    char *token = strtok(file_encrypted, "\n");  // Tokenize encrypted numbers
    while (token != NULL) {
        int C = atoi(token);  // Convert encrypted text to integer
        long long M = mod_exponentiation(C, d, n);  // Decrypt using modular exponentiation
        fprintf(fptr, "%c", (char)M);  // Write decrypted character to file
        token = strtok(NULL, "\n");  // Get next token
    }      
    fclose(fptr);

    return 0;
}
int main(int argc,char *argv []) {
    if (argc <3 ) {
        // encrypt file 
        return encrypt(argc,argv);

    }else{
        return decrypt(argc,argv);
    }
}
