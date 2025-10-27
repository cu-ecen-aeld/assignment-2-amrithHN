#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <syslog.h>

int main(int argc, char* argv[]) {
  openlog("WRITER_C_APP", LOG_PID | LOG_CONS | LOG_PERROR, LOG_USER);

  // Check for exactly 2 arguments (argc == 3)
  if (argc != 3) {
    syslog(LOG_ERR, "2 arguments must be provided (filename and data)");
    closelog();
    return 1;
  }

  // Validate input arguments
  if (argv[1][0] == '\0' || argv[2][0] == '\0') {
    syslog(LOG_ERR, "Filename or data string cannot be empty");
    closelog();
    return 1;
  }

  // Open file for writing
  FILE* file = fopen(argv[1], "w");
  syslog(LOG_DEBUG, "Writing %s to %s", argv[2], argv[1]);
  if (file != NULL) {
    // Write argv[2] to the file
    size_t len = strlen(argv[2]);
    if (fwrite(argv[2], sizeof(char), len, file) != len || ferror(file)) {
      syslog(LOG_ERR, "Error writing to file: %s", strerror(errno));
      fclose(file);
      closelog();
      return 1;
    }
    // Optionally append newline
    if (fwrite("\n", sizeof(char), 1, file) != 1 || ferror(file)) {
      syslog(LOG_ERR, "Error writing newline to file: %s", strerror(errno));
      fclose(file);
      closelog();
      return -1;
    }
    fclose(file);
  } else {
    syslog(LOG_ERR, "Error opening file: %s", strerror(errno));
    closelog();
    return 1;
  }

  closelog();
  return 0;
}