#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <fcntl.h>
#include <assert.h>
#include <getopt.h>

static const int I_option = 0;
static const int F_option = 1;
static const int V_option = 2;

static const int Num_opt  = 3;

static const char* Long_opt_str[] = { "interactive",
                                      "force",
                                      "verbose"};

static const char Short_opt_str[] = {'i', 'f', 'v'};

//=========================================================

static int open_file(const char* filename, int flags);

static int close_file(int file_descr);

static int write_file(int fd_in, int fd_out);

static int get_options(const int argc, const char** argv, int options[]);

static int cp_single_file(int options[], const char* src, const char* dst);

static int cp_several_files(int options[], int optnum, const char* argv[]);

//=========================================================


    /*
    if (argc == 1)
    {
        err = write_file(0, 1);
        if (err)
            return err;
    }
    for (int iter = 1; iter < argc; iter++)
    {
        const char* filename = argv[iter];
        int input_fd = open_file(filename);
        if (input_fd < 0)
        {
            err = -input_fd;
            continue;
        }
        err = write_file(input_fd, 1);
        if (err)
            return err;
        err = close_file(input_fd);
        if (err)
            return err;
    }
    */

}

//---------------------------------------------------------

static int cp_single_file(int options[], const char* src, const char* dst)
{
    assert(options);
    assert(src);
    assert(dst);

    int src_fd = open_file(src, O_RDONLY);
    if (src_fd < 0)
        return -src_fd;

    int dst_fd = open_file(dst, O_WRONLY | O_CREAT);
    if (dst_fd < 0)
        return -dst_fd;

    int write_err = write_file(src_fd, dst_fd);
    if (write_err)
        return write_err;

    int close_err = close_file(src_fd);
    if (close_err)
        return close_err;

    close_err = close_file(dst_fd);
    if (close_err)
        return close_err;

    return 0;
}

//---------------------------------------------------------

int close_file(int file_descr)
{
    if (close(file_descr) < 0)
    {
        fprintf(stderr, "close() system call failed: %s \n", strerror(errno));
        return errno;
    }

    return 0;
}

//---------------------------------------------------------

ssize_t safe_write(int fd, const void* buf, size_t count)
{
    assert(buf);

    while (count)
    {
        ssize_t written;
        if ((written = write(fd, buf, (size_t) count)) < 0)
            return -1;

        count -= written;
    }

    return 0;
}

//---------------------------------------------------------

int write_file(int fd_in, int fd_out)
{
    char buff[Buffer_size];

    while (ssize_t read_ret = read(fd_in, buff, Buffer_size))
    {
        if (read_ret < 0)
        {
            fprintf(stderr, "read() system call failed: %s \n", strerror(errno));
            return errno;
        }

        if (!read_ret)
            break;

        if (safe_write(fd_out, buff, (size_t) read_ret) < 0)
        {
            fprintf(stderr, "write() system call failed: %s \n", strerror(errno));
            return errno;
        }
    }

    return 0;
}

