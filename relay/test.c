#include <wolfssl/wolfcrypt/settings.h>
#include <wolfssl/ssl.h>

int main() {
    int result = 0;
    char errMsg[80];
    WOLFSSL_CTX *ctx;

    result = wolfSSL_Init();
    if (result != WOLFSSL_SUCCESS) {
        wolfSSL_ERR_error_string(result, errMsg);
        fprintf(stderr, "Failed to intialize wolfSSL: %s\n", errMsg);
        exit(result);
    }

    // Configure wolfSSL as a server that only communicates over TLS 1.3
    if ((ctx = wolfSSL_CTX_new(wolfTLSv1_3_server_method())) == NULL) {
        fprintf(stderr, "Unable to create WolfSSL ctx\n");
        exit(EXIT_FAILURE);
    }

    // Load CA certificates
    result = wolfSSL_CTX_load_verify_locations(ctx, "./certs/ca-cert.pem", NULL);
    if (result != WOLFSSL_SUCCESS) {
        wolfSSL_ERR_error_string(result, errMsg);
        fprintf(stderr, "Failed to load CA certs: %s\n", errMsg);
        exit(result);
    }

    return 0;
}