#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

ssize_t read_textfile(const char *filename, size_t letters)
{
    int fd;
    ssize_t bytes_read;
    char buffer[1024];

    if (filename == NULL)
        return 0;

    fd = open(filename, O_RDONLY);
    if (fd == -1)
        return 0;

    bytes_read = read(fd, buffer, letters);
    if (bytes_read == -1)
    {
        close(fd);
        return 0;
    }

    if (write(STDOUT_FILENO, buffer, bytes_read) != bytes_read)
    {
        close(fd);
        return 0;
    }

    close(fd);
    return bytes_read;
}
