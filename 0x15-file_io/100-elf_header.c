#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <elf.h>

#define BUFFER_SIZE 128

void print_error(char *message) {
  fprintf(stderr, "Error: %s\n", message);
}

void print_elf_header(Elf64_Ehdr *header) {
  printf("ELF Header:\n");
  printf("  Magic:   ");
  for (int i = 0; i < EI_NIDENT; i++) {
    printf("%02x ", header->e_ident[i]);
  }
  printf("\n");
  printf("  Class:                             ");
  switch (header->e_ident[EI_CLASS]) {
    case ELFCLASSNONE:
      printf("Invalid class\n");
      break;
    case ELFCLASS32:
      printf("ELF32\n");
      break;
    case ELFCLASS64:
      printf("ELF64\n");
      break;
    default:
      printf("Unknown class\n");
  }
  printf("  Data:                              ");
  switch (header->e_ident[EI_DATA]) {
    case ELFDATANONE:
      printf("Invalid data encoding\n");
      break;
    case ELFDATA2LSB:
      printf("2's complement, little endian\n");
      break;
    case ELFDATA2MSB:
      printf("2's complement, big endian\n");
      break;
    default:
      printf("Unknown data encoding\n");
  }
  printf("  Version:                           %d (current)\n", header->e_ident[EI_VERSION]);
  printf("  OS/ABI:                            ");
  switch (header->e_ident[EI_OSABI]) {
    case ELFOSABI_SYSV:
      printf("UNIX - System V\n");
      break;
    case ELFOSABI_NETBSD:
      printf("NetBSD\n");
      break;
    case ELFOSABI_LINUX:
      printf("Linux\n");
      break;
    default:
      printf("Unknown OS/ABI\n");
  }
  printf("  ABI Version:                       %d\n", header->e_ident[EI_ABIVERSION]);
  printf("  Type:                              ");
  switch (header->e_type) {
    case ET_NONE:
      printf("No file type\n");
      break;
    case ET_REL:
      printf("Relocatable file\n");
      break;
    case ET_EXEC:
      printf("Executable file\n");
      break;
    case ET_DYN:
      printf("Shared object file\n");
      break;
    case ET_CORE:
      printf("Core file\n");
      break;
    default:
      printf("Unknown file type\n");
  }
  printf("  Entry point address:               0x%lx\n", header->e_entry);
}

int main(int argc, char **argv) {
  int fd;
  Elf64_Ehdr header;
  ssize_t n;

  if (argc != 2) {
    print_error("Usage: elf_header elf_filename");
    return 98;
  }

  fd = open(argv[1], O_RDONLY);
  if (fd == -1) {
    print_error(strerror(errno));
    return 98;
  }

  n = read(fd, &header, sizeof(header));
  if (n == -1) {
    print_error(strerror(errno));
    close(fd);
    return 98;
  }

  if (n != sizeof(header)i
