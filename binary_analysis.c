#include <stdio.h>
#include <bfd.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("%s [binary]\n", argv[0]);
        return 0;
    }

    bfd_init();

    bfd *file = bfd_openr(argv[1], NULL);

    if (!file) {
        puts("Failed to read the binary");
        return 1;
    }

    if (!bfd_check_format(file, bfd_object)) {
        puts("Not an executable file");
        return 1;
    }

    if (bfd_get_flavour(file) == bfd_target_unknown_flavour) {
        puts("Unknown format");
        return 1;
    }

    printf("arch: %s\n", bfd_get_arch_info(file)->printable_name);

    puts("section: ");
    asection *p;
    for (p = file->sections; p != NULL; p = p->next) {
        printf("%s\n", p->name);
    }

    return 0;
}
