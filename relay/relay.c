#include <wolfssl/wolfcrypt/settings.h>
#include <wolfssl/ssl.h>

int main() {
    int result = 0;
    char errMsg[80];
    WOLFSSL_CTX *ctx;
    SOCKET listenFd;

    result = wolfSSL_Init();
    if (result != WOLFSSL_SUCCESS) {
        // Get error string from error number
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
    // Third parameter is NULL because we don't want to load a directory full of CA certs
    result = wolfSSL_CTX_load_verify_locations(ctx, "./certs/ca-cert.pem", NULL);
    if (result != WOLFSSL_SUCCESS) {
        wolfSSL_ERR_error_string(result, errMsg);
        fprintf(stderr, "Failed to load CA certs: %s\n", errMsg);
        exit(result);
    }

    // Load relay certificate
    result = wolfSSL_CTX_use_certificate_file(ctx, "./certs/relay-cert.pem", SSL_FILETYPE_PEM);
    if (result != WOLFSSL_SUCCESS) {
        wolfSSL_ERR_error_string(result, errMsg);
        frptinf(stderr, "Failed to load relay certificate: %s\n", errMsg);
        exit(result);
    }

    // Load relay private key
    result = wolfSSL_CTX_use_PrivateKey_file(ctx, "./certs/relay-key.pem", SSL_FILETYPE_PEM);
    if (result != WOLFSSL_SUCCESS) {
        wolfSSL_ERR_error_string(result, errMsg);
        fprintf(stderr, "Failed to load relay private key: %s\n", errMsg);
        exit(result);
    }

    // Setup a TCP socket file descriptor
    // The third option can be set to "0" to let the protocol automatically be determined
    listenFd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    // Configure socket to allow address reuse
    int opt = 1;
    setsockopt(listenFd, SOL_SOCKET, SO_REUSEADDR, (const char *)&opt, sizeof(int));

    // Cleanup wolfSSL
    wolfSSL_CTX_free(ctx);
    wolfSSL_Cleanup();

    return 0;
}