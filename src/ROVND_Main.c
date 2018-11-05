#include "ROVND_Proto.h"

int main(int argc, char *argv[])
{
    int i;

    if (argc < 3) {
        exit(-1);
    }

    PInfInit(argv[argc-1]);
    ItemInit(argv[1]);

    return 0;
}
