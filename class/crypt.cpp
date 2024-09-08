#include "crypt.h"                                                                                                            

int cryptEnRSA(const std::string& publicKey, const std::string& base, std::string& output)
{
    BIO* keybio = BIO_new_mem_buf(publicKey.c_str(), -1);
    EVP_PKEY* evpKey = PEM_read_bio_PUBKEY(keybio, nullptr, nullptr, nullptr);
    if (!evpKey) {
        UTILLOG(LOGLV_ERR, "Public Key Read failed.");
        BIO_free(keybio);
        return -1;
    }

    EVP_PKEY_CTX* ctx = EVP_PKEY_CTX_new(evpKey, nullptr);
    if (!ctx) {
        UTILLOG(LOGLV_ERR, "Context creation failed.");
        EVP_PKEY_free(evpKey);
        BIO_free(keybio);
        return -1;
    }

    if (EVP_PKEY_encrypt_init(ctx) <= 0) {
        UTILLOG(LOGLV_ERR, "Encryption initialization failed.");
        EVP_PKEY_CTX_free(ctx);
        EVP_PKEY_free(evpKey);
        BIO_free(keybio);
        return -1;
    }

    if (EVP_PKEY_CTX_set_rsa_padding(ctx, RSA_PKCS1_OAEP_PADDING) <= 0) {
        UTILLOG(LOGLV_ERR, "Setting RSA padding failed.");
        EVP_PKEY_CTX_free(ctx);
        EVP_PKEY_free(evpKey);
        BIO_free(keybio);
        return -1;
    }

    size_t outlen;
    if (EVP_PKEY_encrypt(ctx, nullptr, &outlen, reinterpret_cast<const unsigned char*>(base.c_str()), base.size()) <= 0) {
        UTILLOG(LOGLV_ERR, "Determining buffer length failed.");
        EVP_PKEY_CTX_free(ctx);
        EVP_PKEY_free(evpKey);
        BIO_free(keybio);
        return -1;
    }

    std::vector<unsigned char> encrypted(outlen);
    if (EVP_PKEY_encrypt(ctx, encrypted.data(), &outlen, reinterpret_cast<const uchar*>(base.c_str()), base.size()) <= 0) {
        UTILLOG(LOGLV_ERR, "Encryption failed.");
        EVP_PKEY_CTX_free(ctx);
        EVP_PKEY_free(evpKey);
        BIO_free(keybio);
        return -1;
    }

    output.assign(reinterpret_cast<char*>(encrypted.data()), outlen);

    EVP_PKEY_CTX_free(ctx);
    EVP_PKEY_free(evpKey);
    BIO_free(keybio);

    return output.length();
}

int cryptDeRSA(const std::string& privateKey, const std::string& encrypt, std::string& output)
{
    BIO* keybio = BIO_new_mem_buf(privateKey.c_str(), -1);
    EVP_PKEY* evpKey = PEM_read_bio_PrivateKey(keybio, nullptr, nullptr, nullptr);
    if (!evpKey) {
        UTILLOG(LOGLV_ERR, "Private Key Read failed.");
        BIO_free(keybio);
        return -1;
    }

    EVP_PKEY_CTX* ctx = EVP_PKEY_CTX_new(evpKey, nullptr);
    if (!ctx) {
        UTILLOG(LOGLV_ERR, "Context creation failed.");
        EVP_PKEY_free(evpKey);
        BIO_free(keybio);
        return -1;
    }
                                                                                                                              
    if (EVP_PKEY_decrypt_init(ctx) <= 0) {
        UTILLOG(LOGLV_ERR, "Decryption initialization failed.");
        EVP_PKEY_CTX_free(ctx);
        EVP_PKEY_free(evpKey);
        BIO_free(keybio);
        return -1;
    }

    if (EVP_PKEY_CTX_set_rsa_padding(ctx, RSA_PKCS1_OAEP_PADDING) <= 0) {
        UTILLOG(LOGLV_ERR, "Setting RSA padding failed.");
        EVP_PKEY_CTX_free(ctx);
        EVP_PKEY_free(evpKey);
        BIO_free(keybio);
        return -1;
    }

    size_t outlen;
    if (EVP_PKEY_decrypt(ctx, nullptr, &outlen, reinterpret_cast<const uchar*>(encrypt.c_str()), encrypt.size()) <= 0) {
        UTILLOG(LOGLV_ERR, "Determining buffer length failed.");
        EVP_PKEY_CTX_free(ctx);
        EVP_PKEY_free(evpKey);
        BIO_free(keybio);
        return -1;
    }

    std::vector<uchar> decrypted(outlen);
    if (EVP_PKEY_decrypt(ctx, decrypted.data(), &outlen, reinterpret_cast<const uchar*>(encrypt.c_str()), encrypt.size()) <= 0) {
        UTILLOG(LOGLV_ERR, "Decryption failed.");
        EVP_PKEY_CTX_free(ctx);
        EVP_PKEY_free(evpKey);
        BIO_free(keybio);
        return -1;
    }

    output.assign(reinterpret_cast<char*>(decrypted.data()), outlen);

    EVP_PKEY_CTX_free(ctx);
    EVP_PKEY_free(evpKey);
    BIO_free(keybio);

    return output.length();
}

int cryprtGetFileKey(std::string type, std::string& output)
{
    char file[1024] = {0,};
    int  flen = sprintf(file, "%s/%s%s", EXRPATH, type.c_str(), "_key.pem");
    file[flen] = '\0';

    std::ifstream pfile(file);
    if(!pfile.is_open()) {
        UTILLOG(LOGLV_ERR, "[%s] 파일 불러오기 실패.", type);
        return -1;
    }

    std::string line;
    while(std::getline(pfile, line)) {
        if(line.empty() || line[0] == '-') {
            continue;
        }

        output += line;
    }

    return output.length();
}

