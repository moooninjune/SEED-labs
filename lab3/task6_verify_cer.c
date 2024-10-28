// I used the website www.seedsecuritylabs.org:443
// bc it's (https), we use the port number 443
// the default port number is 80 (for http)
// if you don't specify a port, it'll assume it's 80

#include <stdio.h>
#include <openssl/bn.h>

void printBN(char *msg, BIGNUM *a)
{
    char *number_str_a = BN_bn2hex(a);
    printf("%s %s\n", msg, number_str_a);
    OPENSSL_free(number_str_a);
}

int main()
{
    // init
    BN_CTX *ctx = BN_CTX_new();

    BIGNUM *n = BN_new();
    BIGNUM *e = BN_new();
    // BIGNUM *d = BN_new();
    // Private key isn't used for verifying
    BIGNUM *M = BN_new();
    BIGNUM *C = BN_new();
    BIGNUM *S = BN_new();

    // assign values
    // openssl x509 -in c1.pem -noout -modulus
    BN_hex2bn(&n, "CCF710624FA6BB636FED905256C56D277B7A12568AF1F4F9D6E7E18FBD95ABF260411570DB1200FA270AB557385B7DB2519371950E6A41945B351BFA7BFABBC5BE2430FE56EFC4F37D97E314F5144DCBA710F216EAAB22F031221161699026BA78D9971FE37D66AB75449573C8ACFFEF5D0A8A5943E1ACB23A0FF348FCD76B37C163DCDE46D6DB45FE7D23FD90E851071E51A35FED4946547F2C88C5F4139C97153C03E8A139DC690C32C1AF16574C9447427CA2C89C7DE6D44D54AF4299A8C104C2779CD648E4CE11E02A8099F04370CF3F766BD14C49AB245EC20D82FD46A8AB6C93CC6252427592F89AFA5E5EB2B061E51F1FB97F0998E83DFA837F4769A1");
    // openssl x509 -in c1.pem -text -noout
    BN_dec2bn(&e, "65537");

    // openssl x509 -in c0.pem -text -noout
    // cat signature | tr -d '[:space:]:'
    BN_hex2bn(&S, "72a5bf339b241c718322da50d08415fdfb98d16c52d5e6696be499c7c8b7d57e4d9ed09adbe3c796ec77996a01f969fdeaa4e3e258a6761c296ad97ccfef31dc4f4137a1fd54167b063f8589fa5ff575b3624832d8ea1245b86a8b557568c756fb31e2b023cf9bedb9bff055882dad4f23bac1f74d5a53f7fd00a0584a1399b6212ecc220ef0291f830f1a0d8f87c5165bb1b5e54d81bb70b8971bdb7364050a9f1d70af416ab15d9640e0dc25fd6a063e8186756e6a54e73706586d2135b9dc04b286f282ec702b863ecbc101fc0bf751827d5a8081cff6f549d4d6999cf5e12bdf13a21bfef8e3b413f17f6d518d5959cb050e2fe4f8d0cd14144c6bccda65");
    
    // openssl asn1parse -i -in c0.pem
    // openssl asn1parse -i -in c0.pem -strparse 4 -out c0_body.bin -noout
    // sha256sum c0_body.bin (calculate the hash)
    BN_hex2bn(&M, "45c12019e2ec23b51760f8b7cd466aea7b5cca737fa6c62e894c33b407387c6e"); //hash of the certificate body

    // decrypt S: C = S^e mod n
    // If S=M^d mod n, then C=M
    BN_mod_exp(C, S, e, n, ctx);

    printBN("Hash:", M);
    printBN("Signature:", C);

    // clear sensitive data
    BN_clear_free(n);
    BN_clear_free(e);
    BN_clear_free(M);
    BN_clear_free(C);
    BN_clear_free(S);

    return 0;
}

/* The output will be:
Hash: 45C12019E2EC23B51760F8B7CD466AEA7B5CCA737FA6C62E894C33B407387C6E
Signature: 01FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF003031300D06096086480165030402010500042045C12019E2EC23B51760F8B7CD466AEA7B5CCA737FA6C62E894C33B407387C6E
*/