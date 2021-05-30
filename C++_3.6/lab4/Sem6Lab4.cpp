#include <iostream>
#include <cstring>
#include <string>
#include <random>
#include <chrono>
#include <fstream>

using namespace std;
 
class SHA2{

    protected:
        #define SHA2_SHIFT_R(x, n)    (x >> n)
        #define SHA2_ROTATE_R(x, n)   ((x >> n) | (x << ((sizeof(x) << 3) - n)))
        #define SHA2_ROTATE_L(x, n)   ((x << n) | (x >> ((sizeof(x) << 3) - n)))
        #define SHA2_CH(x, y, z)  ((x & y) ^ (~x & z))
        #define SHA2_MAJ(x, y, z) ((x & y) ^ (x & z) ^ (y & z))
        #define SHA2_SIGMA_0(x) (SHA2_ROTATE_R(x,  2) ^ SHA2_ROTATE_R(x, 13) ^ SHA2_ROTATE_R(x, 22))
        #define SHA2_SIGMA_1(x) (SHA2_ROTATE_R(x,  6) ^ SHA2_ROTATE_R(x, 11) ^ SHA2_ROTATE_R(x, 25))
        #define SHA2_DELTA_0(x) (SHA2_ROTATE_R(x,  7) ^ SHA2_ROTATE_R(x, 18) ^ SHA2_SHIFT_R(x,  3))
        #define SHA2_DELTA_1(x) (SHA2_ROTATE_R(x, 17) ^ SHA2_ROTATE_R(x, 19) ^ SHA2_SHIFT_R(x, 10))

        #define SHA2_UNPACK32(x, str){              \
            *((str) + 3) = (uint8) ((x)      );       \
            *((str) + 2) = (uint8) ((x) >>  8);       \
            *((str) + 1) = (uint8) ((x) >> 16);       \
            *((str) + 0) = (uint8) ((x) >> 24);       \
        }

        #define SHA2_PACK32(str, x){                \
            *(x) =   ((uint32) *((str) + 3)   )       \
                | ((uint32) *((str) + 2) <<  8)       \
                | ((uint32) *((str) + 1) << 16)       \
                | ((uint32) *((str) + 0) << 24);      \
        }

        SHA2(){
            initHashesAndLen();
        }

        typedef unsigned char uint8;
        typedef unsigned int uint32;
        static const unsigned int SHA2_BLOCK_SIZE = (512 / 8);
        static const unsigned int HASH_SIZE = (256 / 8);
        unsigned int crypted_message_len;
        unsigned int not_crypted_message_len;
        unsigned char m_block[2 * SHA2_BLOCK_SIZE] = {0};
        uint32 hash_val[8];

        const unsigned int SHA2_KEYS[64] = {
            0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5,
            0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
            0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3,
            0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
            0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc,
            0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
            0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7,
            0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
            0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13,
            0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
            0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3,
            0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
            0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5,
            0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
            0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
            0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
        };

        
        void initHashesAndLen(){
            
            hash_val[0] = 0x6a09e667;
            hash_val[1] = 0xbb67ae85;
            hash_val[2] = 0x3c6ef372;
            hash_val[3] = 0xa54ff53a;
            hash_val[4] = 0x510e527f;
            hash_val[5] = 0x9b05688c;
            hash_val[6] = 0x1f83d9ab;
            hash_val[7] = 0x5be0cd19;

            not_crypted_message_len = 0;
            crypted_message_len = 0;
        }


        void separateMessage(const unsigned char* message, unsigned int len){
            unsigned int block_amount;
            unsigned int rest_message_len, not_in_blocks_len;
            const unsigned char* leftover_message;
            not_in_blocks_len = len < SHA2_BLOCK_SIZE ? len : SHA2_BLOCK_SIZE;

            memcpy(&m_block[not_crypted_message_len], message, not_in_blocks_len);

            if (not_crypted_message_len + len < SHA2_BLOCK_SIZE) {
                not_crypted_message_len += len;
                return;
            }

            rest_message_len = len - not_in_blocks_len;
            block_amount = rest_message_len / SHA2_BLOCK_SIZE;
            leftover_message = message + not_in_blocks_len;

            computeHash(m_block, 1);
            computeHash(leftover_message, block_amount);
            not_in_blocks_len = rest_message_len % SHA2_BLOCK_SIZE;
            memcpy(m_block, &leftover_message[block_amount << 6], not_in_blocks_len);
            not_crypted_message_len = not_in_blocks_len;
            crypted_message_len += (block_amount + 1) << 6;
        }

        
        void finalHash(unsigned char* hash){
            unsigned int block_amount;
            unsigned int rest_block_bytes;
            unsigned int message_len_bits;

            block_amount = (1 + ((SHA2_BLOCK_SIZE - 9) < (not_crypted_message_len % SHA2_BLOCK_SIZE)));
            message_len_bits = (crypted_message_len + not_crypted_message_len) << 3;
            rest_block_bytes = block_amount << 6;
            memset(m_block + not_crypted_message_len, 0, rest_block_bytes - not_crypted_message_len);
            m_block[not_crypted_message_len] = 0x80;

            SHA2_UNPACK32(message_len_bits, m_block + rest_block_bytes - 4);
            computeHash(m_block, block_amount);

            for (int i = 0 ; i < 8; i++) {
                SHA2_UNPACK32(hash_val[i], &hash[i << 2]);
            }
        }
        
        
        void computeHash(const unsigned char* message, unsigned int block_amount){
            
            uint32 w[64];
            uint32 hash_val_copy[8];
            uint32 temp1, temp2;

            const unsigned char* sub_block;

            for (int i = 0; i < block_amount; i++) {
                sub_block = message + (i << 6);
                for (int j = 0; j < 16; j++) {
                    SHA2_PACK32(&sub_block[j << 2], &w[j]);
                }

                for (int j = 16; j < 64; j++) {
                    w[j] =  SHA2_DELTA_1(w[j - 2]) + w[j -  7] + SHA2_DELTA_0(w[j - 15]) + w[j - 16];
                }

                for (int j = 0; j < 8; j++) {
                    hash_val_copy[j] = hash_val[j];
                }

                for (int j = 0; j < 64; j++) {
                    temp1 = hash_val_copy[7] + SHA2_SIGMA_1(hash_val_copy[4]) + SHA2_CH(hash_val_copy[4], hash_val_copy[5], hash_val_copy[6])
                        + SHA2_KEYS[j] + w[j];
                    temp2 = SHA2_SIGMA_0(hash_val_copy[0]) + SHA2_MAJ(hash_val_copy[0], hash_val_copy[1], hash_val_copy[2]);
                    hash_val_copy[7] = hash_val_copy[6];
                    hash_val_copy[6] = hash_val_copy[5];
                    hash_val_copy[5] = hash_val_copy[4];
                    hash_val_copy[4] = hash_val_copy[3] + temp1;
                    hash_val_copy[3] = hash_val_copy[2];
                    hash_val_copy[2] = hash_val_copy[1];
                    hash_val_copy[1] = hash_val_copy[0];
                    hash_val_copy[0] = temp1 + temp2;
                }

                for (int j = 0; j < 8; j++) {
                    hash_val[j] += hash_val_copy[j];
                }
            }
        }

        friend string sha256(string);
};


string sha256(string input){
    unsigned char hash[SHA2::HASH_SIZE] = {0};
    SHA2 sha_obj;

    sha_obj.separateMessage( (unsigned char*)input.c_str(), input.length());
    sha_obj.finalHash(hash);
    
    char final_hash[2 * SHA2::HASH_SIZE + 1] = {0};
    final_hash[2 * SHA2::HASH_SIZE] = 0;

    for (int i = 0; i < SHA2::HASH_SIZE; i++)
        sprintf(final_hash + i * 2, "%02x", hash[i]);

    return string(final_hash);
}


int main(){
    mt19937 engine(time(0));

    ofstream res_file;
    res_file.open("res.txt", ios::out);

    string test_str = "Hello world Hello world Hello wo";

    chrono::high_resolution_clock::time_point start;
    chrono::high_resolution_clock::time_point end;
    chrono::duration<double, milli> milli_diff;
    for(int i = 0; i < 5; i++){
        
        start = chrono::high_resolution_clock::now();
        
        string ready_hash = sha256(test_str);

        end = chrono::high_resolution_clock::now();
        milli_diff = end - start;

        res_file << test_str.size() << " - " << milli_diff.count() << " - " << test_str << " - " << ready_hash << endl;

        test_str += test_str;
    }
    
    res_file.close();
}