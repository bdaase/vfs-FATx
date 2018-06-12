#pragma once

#include <linux/fs.h>

struct fatx_super_info {
    char manufacturer_description[9];
};

int fatx_fill_super(struct super_block *sb, void *data, int silent);
