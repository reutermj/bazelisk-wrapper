#include <cosmo.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#define SLASH '\\'
#define BAZEL "\\tools\\bazel.bat"
#else
#define SLASH '/'
#define BAZEL "/tools/bazel"
#endif

int main(int argc, char *argv[]) {
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--version") == 0 || strcmp(argv[i], "--help") == 0 ||
            strcmp(argv[i], "-h") == 0) {
            printf("Hi! I'm a wrapper script around bazelisk to make a more platform independent method of running bazel.\n");
            printf("See more about me at https://github.com/reutermj/bazelisk-wrapper\n\n");
            break;
        }
    }

    char *path = GetProgramExecutableName();
    char *last_slash = strrchr(path, SLASH);
    *last_slash = '\0';  // Remove the last part of the path

    char bazel[5000];
    memset(bazel, 0, sizeof(bazel));
    int offset = snprintf(bazel, sizeof(bazel), "%s%s", path, BAZEL);

    for (int i = 1; i < argc; i++) {
        bazel[offset++] = ' ';
        offset += snprintf(&bazel[offset], sizeof(bazel) - offset, "%s", argv[i]);
    }

    system(bazel);

    return 0;
}
