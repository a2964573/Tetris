#include "crypt.h"                                                                                                            

int cryptEnRSA(const std::string type, const std::string& base, std::string& output)
{
	UTILLOG(LOGLV_DBG, "RSA Encryption[%s:%s]", type.c_str(), base.c_str());

    BIO* keybio = nullptr;
	if(cryptInit(type, &keybio) < 0) {
		UTILLOG(LOGLV_ERR, "RSA init failed.[%s]");
		return -1;
	}
	UTILLOG(LOGLV_DBG, "Init Success");

    EVP_PKEY* evpKey = PEM_read_bio_PUBKEY(keybio, nullptr, nullptr, nullptr);
    if (!evpKey) {
        UTILLOG(LOGLV_ERR, "Public Key Read failed.");
		ERR_print_errors_fp(stderr);
        BIO_free(keybio);
        return -1;
    }
	UTILLOG(LOGLV_DBG, "Read BIO publickey Success");

    EVP_PKEY_CTX* ctx = EVP_PKEY_CTX_new(evpKey, nullptr);
    if (!ctx) {
        UTILLOG(LOGLV_ERR, "Context creation failed.");
        EVP_PKEY_free(evpKey);
        BIO_free(keybio);
        return -1;
    }
	UTILLOG(LOGLV_DBG, "Context creation Success");

    if (EVP_PKEY_encrypt_init(ctx) <= 0) {
        UTILLOG(LOGLV_ERR, "Encryption initialization failed.");
        EVP_PKEY_CTX_free(ctx);
        EVP_PKEY_free(evpKey);
        BIO_free(keybio);
        return -1;
    }
	UTILLOG(LOGLV_DBG, "Encryption Init Success");

    if (EVP_PKEY_CTX_set_rsa_padding(ctx, RSA_PKCS1_OAEP_PADDING) <= 0) {
        UTILLOG(LOGLV_ERR, "Setting RSA padding failed.");
        EVP_PKEY_CTX_free(ctx);
        EVP_PKEY_free(evpKey);
        BIO_free(keybio);
        return -1;
    }
	UTILLOG(LOGLV_DBG, "Setting RSA padding Success");

    size_t outlen;
    if (EVP_PKEY_encrypt(ctx, nullptr, &outlen, reinterpret_cast<const uchar*>(base.c_str()), base.size()) <= 0) {
        UTILLOG(LOGLV_ERR, "Determining buffer length failed.");
        EVP_PKEY_CTX_free(ctx);
        EVP_PKEY_free(evpKey);
        BIO_free(keybio);
        return -1;
    }
	UTILLOG(LOGLV_DBG, "Determining buffer length Success");

    std::vector<uchar> encrypted(outlen);
    if (EVP_PKEY_encrypt(ctx, encrypted.data(), &outlen, reinterpret_cast<const uchar*>(base.c_str()), base.size()) <= 0) {
        UTILLOG(LOGLV_ERR, "Encryption failed.");
        EVP_PKEY_CTX_free(ctx);
        EVP_PKEY_free(evpKey);
        BIO_free(keybio);
        return -1;
    }
	UTILLOG(LOGLV_DBG, "Encryption Success[%d]", encrypted.size());

	cryptEncodeBase64(encrypted, output);

    EVP_PKEY_CTX_free(ctx);
    EVP_PKEY_free(evpKey);
    BIO_free(keybio);

    return output.length();
}

int cryptDeRSA(const std::string type, const std::string& base, std::string& output)
{
    UTILLOG(LOGLV_DBG, "RSA Decryption[%s:%s]", type.c_str(), base.c_str());

    std::string encrypt;
    cryptDecodeBase64(base, encrypt);
    UTILLOG(LOGLV_DBG, "Decoded Base64 Success[%d]", encrypt.size());
    // UTILLOG(LOGLV_DBG, "Decoded Base64 Success[%s]", encrypt.c_str());

    BIO* keybio = NULL;
    if(cryptInit(type, &keybio) < 0) {
        UTILLOG(LOGLV_ERR, "RSA init failed.[%s]");
        return -1;
    }
    UTILLOG(LOGLV_DBG, "Init Success");

    EVP_PKEY* evpKey = PEM_read_bio_PrivateKey(keybio, nullptr, nullptr, (void*)"Ckhpem1130@");
    if (!evpKey) {
        UTILLOG(LOGLV_ERR, "Private Key Read failed.");
        BIO_free(keybio);
        return -1;
    }
    UTILLOG(LOGLV_DBG, "Read BIO publickey Success");

    EVP_PKEY_CTX* ctx = EVP_PKEY_CTX_new(evpKey, nullptr);
    if (!ctx) {
        UTILLOG(LOGLV_ERR, "Context creation failed.");
        EVP_PKEY_free(evpKey);
        BIO_free(keybio);
        return -1;
    }
    UTILLOG(LOGLV_DBG, "Context creation Success");

    if (EVP_PKEY_decrypt_init(ctx) <= 0) {
        UTILLOG(LOGLV_ERR, "Decryption initialization failed.");
        EVP_PKEY_CTX_free(ctx);
        EVP_PKEY_free(evpKey);
        BIO_free(keybio);
        return -1;
    }
    UTILLOG(LOGLV_DBG, "Decryption Init Success");

    if (EVP_PKEY_CTX_set_rsa_padding(ctx, RSA_PKCS1_OAEP_PADDING) <= 0) {
        UTILLOG(LOGLV_ERR, "Setting RSA padding failed.");
        EVP_PKEY_CTX_free(ctx);
        EVP_PKEY_free(evpKey);
        BIO_free(keybio);
        return -1;
    }
    UTILLOG(LOGLV_DBG, "Setting RSA padding Success");

    size_t outlen;
    if (EVP_PKEY_decrypt(ctx, nullptr, &outlen, reinterpret_cast<const uchar*>(encrypt.c_str()), encrypt.size()) <= 0) {
        UTILLOG(LOGLV_ERR, "Determining buffer length failed.");
        EVP_PKEY_CTX_free(ctx);
        EVP_PKEY_free(evpKey);
        BIO_free(keybio);
        return -1;
    }
    UTILLOG(LOGLV_DBG, "Determining buffer length Success");

    std::vector<uchar> decrypted(outlen);
    if (EVP_PKEY_decrypt(ctx, decrypted.data(), &outlen, reinterpret_cast<const uchar*>(encrypt.c_str()), encrypt.size()) <= 0) {
        UTILLOG(LOGLV_ERR, "Decryption failed.");
        ERR_print_errors_fp(stderr);
        EVP_PKEY_CTX_free(ctx);
        EVP_PKEY_free(evpKey);
        BIO_free(keybio);
        return -1;
    }                                                                                                                                                                                                                                   
    UTILLOG(LOGLV_DBG, "Decryption Success");

    std::string temp_s(decrypted.begin(), decrypted.end());
    output = temp_s;

    EVP_PKEY_CTX_free(ctx);
    EVP_PKEY_free(evpKey);
    BIO_free(keybio);

    return output.length();
}

int cryptInit(std::string type, BIO** output)
{
    OpenSSL_add_all_algorithms();
    ERR_load_crypto_strings();

	char file[1024] = {0,};
	int  flen = sprintf(file, "%s/%s%s", EXRPATH, type.c_str(), "_key.pem");
	file[flen] = '\0';

    *output = BIO_new_file(file, "r");
    if (!*output) {
        UTILLOG(LOGLV_ERR, "Failed to open public key file.");
        ERR_print_errors_fp(stderr);
        return -1;
    }

    char buffer[256];
    if (BIO_read(*output, buffer, sizeof(buffer)) <= 0) {
        UTILLOG(LOGLV_ERR, "Failed to read from BIO object.");
        ERR_print_errors_fp(stderr);
        BIO_free(*output);
        return -1;
    }
    BIO_reset(*output);

	return  0;
}

int cryptGetFileKey(std::string type, std::string& output)
{
    char file[1024] = {0,};
    int  flen = sprintf(file, "%s/%s%s", EXRPATH, type.c_str(), "_key.pem");
    file[flen] = '\0';

	UTILLOG(LOGLV_DBG, "RSA 공용키 불러오기...[%s][%d:%s]", type.c_str(), flen, file);

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

int cryptEncodeBase64(const std::vector<uchar>& input, std::string& output)
{
    BIO *bio, *b64;
    BUF_MEM *bufferPtr;

    b64 = BIO_new(BIO_f_base64());
    bio = BIO_new(BIO_s_mem());
    bio = BIO_push(b64, bio);

    BIO_set_flags(bio, BIO_FLAGS_BASE64_NO_NL);

    BIO_write(bio, input.data(), input.size());
    BIO_flush(bio);
    BIO_get_mem_ptr(bio, &bufferPtr);

    std::string encoded_data(bufferPtr->data, bufferPtr->length);
    BIO_free_all(bio);

	output = encoded_data;

	return output.length();
}

int cryptDecodeBase64(const std::string& input, std::string& output)
{
    BIO *bio, *b64;

    int decodeLen = input.size();
    std::vector<uchar> decoded(decodeLen);

    bio = BIO_new_mem_buf(input.data(), input.size());
    b64 = BIO_new(BIO_f_base64());
    bio = BIO_push(b64, bio);

    BIO_set_flags(bio, BIO_FLAGS_BASE64_NO_NL);

    int length = BIO_read(bio, decoded.data(), input.size());
    decoded.resize(length);

    BIO_free_all(bio);

	std::string decoded_data(decoded.begin(), decoded.end());
	output = decoded_data;

    return length;
}

