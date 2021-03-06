/*
 * Copyright (C) 2009-2012 the libgit2 contributors
 *
 * This file is part of libgit2, distributed under the GNU GPL v2 with
 * a Linking Exception. For full terms see the included COPYING file.
 */
#ifndef INCLUDE_sha1_lookup_h__
#define INCLUDE_sha1_lookup_h__

#include <stdlib.h>

int sha1_entry_pos(const void *table,
			size_t elem_size,
			size_t key_offset,
			unsigned lo, unsigned hi, unsigned nr,
			const unsigned char *key);

#endif
