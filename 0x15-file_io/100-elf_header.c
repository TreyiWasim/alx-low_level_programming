#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <elf.h>

#define BUF_SIZE 128

int main(int argc, char **argv) {
    int fd;
    char buf[BUF_SIZE];
    Elf64_Ehdr ehdr;
    ssize_t n;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s elf_filename\n", argv[0]);
        exit(98);
    }

    fd = open(argv[1], O_RDONLY);
    if (fd == -1) {
        fprintf(stderr, "Failed to open %s\n", argv[1]);
        exit(98);
    }

    n = read(fd, buf, sizeof(Elf64_Ehdr));
    if (n != sizeof(Elf64_Ehdr)) {
        fprintf(stderr, "Failed to read ELF header from %s\n", argv[1]);
        exit(98);
    }

    memcpy(&ehdr, buf, sizeof(Elf64_Ehdr));
    if (memcmp(ehdr.e_ident, ELFMAG, SELFMAG) != 0) {
        fprintf(stderr, "%s is not an ELF file\n", argv[1]);
        exit(98);
    }

    printf("Magic:   ");
    for (int i = 0; i < SELFMAG; i++) {
        printf("%02x ", ehdr.e_ident[i]);
    }
    printf("\n");

    printf("Class:   ");
    switch (ehdr.e_ident[EI_CLASS]) {
        case ELFCLASSNONE:
            printf("none\n");
            break;
        case ELFCLASS32:
            printf("ELF32\n");
            break;
        case ELFCLASS64:
            printf("ELF64\n");
            break;
        default:
            printf("invalid\n");
            break;
    }

    printf("Data:    ");
    switch (ehdr.e_ident[EI_DATA]) {
        case ELFDATANONE:
            printf("none\n");
            break;
        case ELFDATA2LSB:
            printf("2's complement, little endian\n");
            break;
        case ELFDATA2MSB:
            printf("2's complement, big endian\n");
            break;
        default:
            printf("invalid\n");
            break;
    }

    printf("Version: %d\n", ehdr.e_ident[EI_VERSION]);

    printf("OS/ABI:  ");
    switch (ehdr.e_ident[EI_OSABI]) {
        case ELFOSABI_SYSV:
            printf("UNIX System V ABI\n");
            break;
        case ELFOSABI_HPUX:
            printf("HP-UX ABI\n");
            break;
        case ELFOSABI_NETBSD:
            printf("NetBSD ABI\n");
            break;
        case ELFOSABI_LINUX:
            printf("Linux ABI\n");
            break;
        case ELFOSABI_SOLARIS:
            printf("Solaris ABI\n");
            break;
        case ELFOSABI_AIX:
            printf("AIX ABI\n");
            break;
        case ELFOSABI_IRIX:
            printf("IRIX ABI\n");
            break;
        case ELFOSABI_FREEBSD:
            printf("FreeBSD ABI\n");
            break;
        case ELFOSABI_TRU64:
            printf("Tru64 UNIX ABI\n");
            break;
        case ELFOSABI_ARM:
            printf("ARM architecture ABI\n");
            break;
        case ELFOSABI_ST

