#include <stdio.h>
#include <bfd.h>

void print_architecture(bfd *file) {
    puts("architecture:");

    printf("%s\n", bfd_get_arch_info(file)->printable_name);
}

void print_section(bfd *file) {
    puts("section:");

    asection *p;
    for (p = file->sections; p != NULL; p = p->next) {
        printf("%s\n", p->name);
    }
}

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

    print_architecture(file);
    puts("");
    print_section(file);

    return 0;
}
