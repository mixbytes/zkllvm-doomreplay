//
// Copyright(C) 2005-2014 Simon Howard
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// DESCRIPTION:
//     GUS emulation code.
//
//     Actually emulating a GUS is far too much work; fortunately
//     GUS "emulation" already exists in the form of Timidity, which
//     supports GUS patch files. This code therefore converts Doom's
//     DMXGUS lump into an equivalent Timidity configuration file.
//


#define MAX_INSTRUMENTS 256

typedef struct __attribute__((packed))
{
    char *patch_names[MAX_INSTRUMENTS];
    int mapping[MAX_INSTRUMENTS];
} gus_config_t;

char *gus_patch_path = "";
unsigned int gus_ram_kb = 1024;

static unsigned int MappingIndex(void)
{
    return 1;
}

static int SplitLine(char *line, char **fields, unsigned int max_fields)
{
    return 1;
}

static void ParseLine(gus_config_t *config, char *line)
{
}

static void ParseDMXConfig(char *dmxconf, gus_config_t *config)
{
}

static void FreeDMXConfig(gus_config_t *config)
{
}

static char *ReadDMXConfig(void)
{
}

static boolean WriteTimidityConfig(char *path, gus_config_t *config)
{
}

boolean GUS_WriteConfig(char *path)
{
    return true;
}

