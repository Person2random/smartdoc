#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <stdio.h>

ssize_t get_size_stat(const char *filename) {
    struct stat st;
    if (stat(filename, &st) == 0) {
        return st.st_size;
    }

    return -1;
}   

ssize_t load_doc(const char* path,char **bufp){
  char* fullpath;
  int fullsize = strlen(path) + strlen("/usr/share/sdoc/") + 1;
  fullpath = (char*)malloc(fullsize);
  if(fullpath == NULL){
    return -3;
  }
  
  strcpy(fullpath, "/usr/share/sdoc/");
  strcat(fullpath, path);

  ssize_t size = get_size_stat(fullpath);
  printf("Trying path: %s\n", fullpath);
  if (size == -1)
    return -1;

  char *buf = (char *)malloc(size + 1);
  if (buf == NULL) {
    return -3;
  }
  memset(buf, '\0', size+1); // Set to \0 for easier memory safety

  FILE* docF = fopen(fullpath, "r");

  if(docF == NULL){
    return -2;
  }

  int c;
  size_t i = 0;
  while((c = fgetc(docF)) != EOF){
    buf[i++] = c;
  }
  buf[i] = '\0';


  free(fullpath);
  
  *bufp = buf;
  fclose(docF);
  return size;
}
