/**
 * \file args.c
 * \brief Args.
 * \author RAZANAJATO RANAIVOARIVONY Harenome
 * \date 2014
 * \copyright WTFPL version 2
 */
/* This program is free software. It comes without any warranty, to
 * the extent permitted by applicable law. You can redistribute it
 * and/or modify it under the terms of the Do What The Fuck You Want
 * To Public License, Version 2, as published by Sam Hocevar. See
 * http://www.wtfpl.net/ for more details.
 */
#include "args.h"

const char * _version_strings[] = { "-v", "--version", NULL };
const char * _help_strings[] = { "-h", "--help", NULL };

static bool _string_equals (const char * const arg, const char * const word)
{
    return strcmp (arg, word) == 0;
}

static bool _string_equals_any (const char * const arg, const char ** words)
{
    bool found = false;

    for (int i = 0; ! found && words[i] != NULL; ++i)
        found = _string_equals (arg, words[i]);

    return found;
}

static int _print_help (const char * const arg)
{
    printf
    (
        "Keyboard and mouse commands in Perlimpinpin:\n"
        "============================================\n"
        "\nRotations:\n"
        "----------\n"
        "Rotations are possible once the polygon has been extruded.\n"
        "\t6:\n"
        "\t\tRotate to the right.\n"
        "\t4:\n"
        "\t\tRotate to the left.\n"
        "\t8:\n"
        "\t\tRotate upwards.\n"
        "\t2:\n"
        "\t\tRotate downwards.\n"
        "\nMoves:\n"
        "------\n"
        "Moving is possible once the polygon has been extruded.\n"
        "\tUP:\n"
        "\t\tTranslate upwards.\n"
        "\tDOWN:\n"
        "\t\tTranslate downwards.\n"
        "\tLEFT:\n"
        "\t\tTranslate to the left.\n"
        "\tRIGHT:\n"
        "\t\tTranslate to the right.\n"
        "\nZooming:\n"
        "------\n"
        "Zooming is possible once the polygon has been extruded.\n"
        "\tPage UP:\n"
        "\t\tZoom in.\n"
        "\tPage DOWN:\n"
        "\t\tZoom out.\n"
        "\nMisceallenous:\n"
        "--------------\n"
        "\tr:\n"
        "\t\tReset everyting.\n"
        "\tp:\n"
        "\t\tExtrude the polygon (if not already done).\n"
        "\tspace:\n"
        "\t\tSwitch lighting modes.\n"
        "\techap:\n"
        "\t\tQuit.\n"

    );
    return 0;
}

static int _print_version (const char * const arg)
{
    printf
    (
        "Perlimpinpin, version %d.%d.%d\n"
        "Copyright © 2014 Harenome RAZANAJATO RANAIVOARIVONY.\n"
        "Licensed under the WTFPLv2.\n",
        VERSION_MAJOR,
        VERSION_MINOR,
        VERSION_PATCH
    );
    return 0;
}

static int _wrong_argument (const char * const arg)
{
    fprintf (stderr, "Error: wrong argument (%s)\n", arg);
    return EX_USAGE;
}

static int _action (const char * const arg)
{
    int (* action) (const char * const arg) = _wrong_argument;

    if (_string_equals_any (arg, _version_strings))
        action = _print_version;
    else if (_string_equals_any (arg, _help_strings))
        action = _print_help;

    return action (arg);
}

static int _too_many_arguments (void)
{
    fprintf (stderr, "Error: too many arguments.\n");
    return EX_USAGE;
}

int stupid_parse (int argc, char ** argv)
{
    int return_code = -1;

    if (argc > 2)
        return_code = _too_many_arguments ();

    for (int i = 1; return_code == -1 && i < argc; ++i)
        return_code = _action (argv[i]);

    return return_code;
}
