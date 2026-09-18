#include "sha256_hash.h"
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <openssl/sha.h>

int hash_file(const char *filename, char *output){
  FILE *file = fopen(filename, "rb");
  if (file == NULL) {
    printf("ERROR: Could not able to open File : %s", filename);
    return 0;
  }

  SHA256_CTX sha_context;
  SHA256_Init(&sha_context);

  unsigned char buffer[32768];
  size_t bytes_read = 0;

  while ((bytes_read = fread(buffer, 1, sizeof(buffer), file))){
    SHA256_Update(&sha_context, buffer, bytes_read);
  }

  fclose(file);
  unsigned char raw_hash[SHA256_DIGEST_LENGTH];
  SHA256_Final(raw_hash, &sha_context);

  for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
    sprintf(output + (i * 2), "%02x", raw_hash[i]);
  }

  output[SHA256_DIGEST_LENGTH * 2] = '\0';

  return 1;
}

int main(){

  const char *file_path = "hello.txt";
  char result[SHA256_DIGEST_LENGTH * 2 + 1];

  if(hash_file(file_path, result)){
    printf("File name   : %s\n", file_path);
    printf("SHA256 sums : %s\n", result);
  }
  else {
    printf("Error: Could not open or read the file '%s'\nReason : %s", file_path, strerror(errno));
  }

  return 0;
}
