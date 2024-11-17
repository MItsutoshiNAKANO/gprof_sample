/**
 * @file
 * @author Mitsutoshi Nakano <ItSANgo@gmail.com>
 * @brief Using gprof sample program.
 * @version 0.1.0
 * @date 2024-11-17
 * @copyright
 *      Copyright (c) 2024 Mitsutoshi Nakano
 *      SPDX-License-Identifier: GPL-3.0-or-later
 */

#include <sysexits.h>
#include <getopt.h>
#include <stdlib.h>
#include <stdio.h>

static FILE *
create_file(void)
{
    return tmpfile();
}

static void
write_to_file(FILE *fp, long long lines)
{
    for (long long i = 0; i < lines; ++i) {
        fprintf(fp, "%lld\n", lines);
    }
}

static int
close_file(FILE *fp)
{
    return fclose(fp);
}

static int
benchmark(long long lines)
{
    FILE *fp;
    if ((fp = create_file()) == NULL) {
        perror("create_file");
        return -1;
    }
    write_to_file(fp, lines);
    if (close_file(fp) == -1) {
        perror("close_file");
        return -2;
    }
    return 0;
}

static char *program_invocation_short_name;

static void
usage(FILE *fp, int status)
{
    fprintf(
        fp,
        "Usage: %s [OPTION]...\n"
        "Options:\n"
        "  -h, --help  Display this help message\n"
        "  -r, --repeat=COUNT  Repeat COUNT times\n"
        "  -l, --lines=COUNT  Write COUNT lines\n",
        program_invocation_short_name);
    exit(status);
}

int
main(int argc, char *argv[])
{
    program_invocation_short_name = argv[0];
    long long repeat = 1000;
    long long lines = 1000;
    static const struct option long_options[] = {
        {"help", no_argument, 0, 'h'},
        {"repeat", required_argument, 0, 'r'},
        {"lines", required_argument, 0, 'l'},
        {0, 0, 0, 0}
    };
    int option_index = 0;
    int c;
    while ((
        c = getopt_long(argc, argv, "r:l:h", long_options, &option_index)
    ) != -1) {
        switch (c) {
        case 'r':
            repeat = atoll(optarg);
            break;
        case 'l':
            lines = atoll(optarg);
            break;
        case 'h':
            usage(stdout, EX_OK);
            break;
        case '?':
            usage(stderr, EX_USAGE);
            break;
        default:
            fprintf(stderr, "getopt returned character code 0x%x?\n", c);
            exit(EX_SOFTWARE);
        }
    }

    for (long long i = 0; i < repeat; ++i) {
        benchmark(lines);
    }
    exit(EX_OK);
}
