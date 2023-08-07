c
Copy
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <elf.h>

void print_error(const char *message)
{
    fprintf(stderr, "%s\n", message);
    exit(98);
}

void print_elf_header(const Elf64_Ehdr *header)
{
    printf("ELF Header:\n");
    printf("  Magic:   ");
    for (int i = 0; i < EI_NIDENT; i++) {
        printf("%02x ", header->e_ident[i]);
    }
    printf("\n  Class:\t\t\t\t");
    switch (header->e_ident[EI_CLASS]) {
        case ELFCLASS32:
            printf("ELF32\n");
            break;
        case ELFCLASS64:
            printf("ELF64\n");
            break;
        default:
            printf("<unknown>\n");
            break;
    }
    printf("  Data:\t\t\t\t");
    switch (header->e_ident[EI_DATA]) {
        case ELFDATA2LSB:
            printf("2's complement, little endian\n");
            break;
        case ELFDATA2MSB:
            printf("2's complement, big endian\n");
            break;
        default:
            printf("<unknown>\n");
            break;
    }
    printf("  Version:\t\t\t%d (current)\n", (int) header->e_ident[EI_VERSION]);
    printf("  OS/ABI:\t\t\t");
    switch (header->e_ident[EI_OSABI]) {
        case ELFOSABI_SYSV:
            printf("UNIX - System V\n");
            break;
        case ELFOSABI_NETBSD:
            printf("UNIX - NetBSD\n");
            break;
        case ELFOSABI_SOLARIS:
            printf("UNIX - Solaris\n");
            break;
        default:
            printf("<unknown: %d>\n", header->e_ident[EI_OSABI]);
            break;
    }
    printf("  ABI Version:\t\t\t%d\n", (int) header->e_ident[EI_ABIVERSION]);
    printf("  Type:\t\t\t\t");
    switch (header->e_type) {
        case ET_NONE:
            printf("NONE (Unknown type)\n");
            break;
        case ET_REL:
            printf("REL (Relocatable file)\n");
            break;
        case ET_EXEC:
            printf("EXEC (Executable file)\n");
            break;
        case ET_DYN:
            printf("DYN (Shared object file)\n");
            break;
        case ET_CORE:
            printf("CORE (Core file)\n");
            break;
        default:
            printf("<unknown>\n");
            break;
    }
    printf("  Entry point address:\t\t0x%lx\n", (unsigned long) header->e_entry);
}

int main(int argc, char *argv[])
{
    if (argc != 2) {
        print_error("Usage: elf_header elf_filename");
    }

    const char *filename = argv[1];
    int fd = open(filename, O_RDONLY);
    if (fd == -1) {
        print_error("Error opening file");
    }

    Elf64_Ehdr header;
    ssize_t bytes_read = read(fd, &header, sizeof(header));
    if (bytes_read == -1) {
        print_error("Error reading file");
    } else if (bytes_read != sizeof(header)) {
        print_error("Invalid ELF file");
    }

    close(fd);

    print_elf_header(&header);

    return 0;
}
