#include "filter.h"
	git_diff_data_fn line_cb;
	git_diff_range range;
		memcpy(&info->range, &range, sizeof(git_diff_range));

			info->cb_data, info->delta, &info->range, origin, bufs[1].ptr, bufs[1].size) < 0)
				info->cb_data, info->delta, &info->range, origin, bufs[2].ptr, bufs[2].size);
	if (git_attr_get(repo, 0, file->path, "diff", &value) < 0)
	if ((delta->old_file.flags & GIT_DIFF_FILE_BINARY) != 0 ||
		(delta->new_file.flags & GIT_DIFF_FILE_BINARY) != 0)
	else if ((delta->old_file.flags & GIT_DIFF_FILE_NOT_BINARY) != 0 ||
			 (delta->new_file.flags & GIT_DIFF_FILE_NOT_BINARY) != 0)
	if ((git_off_t)((size_t)delta->old_file.size) != delta->old_file.size ||
		(git_off_t)((size_t)delta->new_file.size) != delta->new_file.size)
		delta->old_file.flags |= GIT_DIFF_FILE_BINARY;
		delta->new_file.flags |= GIT_DIFF_FILE_BINARY;
		delta->old_file.flags |= GIT_DIFF_FILE_NOT_BINARY;
		delta->new_file.flags |= GIT_DIFF_FILE_NOT_BINARY;
	if (update_file_is_binary_by_attr(diff->repo, &delta->old_file) < 0)
	mirror_new = (delta->new_file.path == delta->old_file.path ||
				  strcmp(delta->new_file.path, delta->old_file.path) == 0);
		delta->new_file.flags &= (delta->old_file.flags & BINARY_DIFF_FLAGS);
		error = update_file_is_binary_by_attr(diff->repo, &delta->new_file);
	git_buf search;
	git_text_stats stats;

	if ((delta->old_file.flags & BINARY_DIFF_FLAGS) == 0) {
		search.ptr  = old_data->data;
		search.size = min(old_data->len, 4000);

		git_text_gather_stats(&stats, &search);
		if (git_text_is_binary(&stats))
			delta->old_file.flags |= GIT_DIFF_FILE_BINARY;
			delta->old_file.flags |= GIT_DIFF_FILE_NOT_BINARY;
	if ((delta->new_file.flags & BINARY_DIFF_FLAGS) == 0) {
		search.ptr  = new_data->data;
		search.size = min(new_data->len, 4000);

		git_text_gather_stats(&stats, &search);

		if (git_text_is_binary(&stats))
			delta->new_file.flags |= GIT_DIFF_FILE_BINARY;
			delta->new_file.flags |= GIT_DIFF_FILE_NOT_BINARY;
static void fill_map_from_mmfile(git_map *dst, mmfile_t *src) {
	assert(dst && src);

	dst->data = src->ptr;
	dst->len = src->size;
#ifdef GIT_WIN32
	dst->fmh = NULL;
#endif
}

	git_diff_data_fn line_cb)
		mmfile_t old_xdiff_data, new_xdiff_data;
				error = get_workdir_content(diff->repo, &delta->old_file, &old_data);
					diff->repo, &delta->old_file.oid, &old_data, &old_blob);

			(hunk_cb || line_cb || git_oid_iszero(&delta->new_file.oid)) &&
				error = get_workdir_content(diff->repo, &delta->new_file, &new_data);
					diff->repo, &delta->new_file.oid, &new_data, &new_blob);

			if ((delta->new_file.flags | GIT_DIFF_FILE_VALID_OID) == 0) {
					&delta->new_file.oid, new_data.data, new_data.len, GIT_OBJ_BLOB);

				if (git_oid_cmp(&delta->old_file.oid, &delta->new_file.oid) == 0) {
				delta, &old_data, &new_data);
		old_xdiff_data.ptr = old_data.data;
		old_xdiff_data.size = old_data.len;
		new_xdiff_data.ptr = new_data.data;
		new_xdiff_data.size = new_data.len;
		xdl_diff(&old_xdiff_data, &new_xdiff_data,
		release_content(&delta->old_file, &old_data, old_blob);
		release_content(&delta->new_file, &new_data, new_blob);
	git_diff_data_fn print_cb;
	old_suffix = pick_suffix(delta->old_file.mode);
	new_suffix = pick_suffix(delta->new_file.mode);
	if (delta->old_file.path != delta->new_file.path &&
		strcmp(delta->old_file.path,delta->new_file.path) != 0)
			delta->old_file.path, old_suffix, delta->new_file.path, new_suffix);
	else if (delta->old_file.mode != delta->new_file.mode &&
		delta->old_file.mode != 0 && delta->new_file.mode != 0)
			delta->old_file.path, new_suffix, delta->old_file.mode, delta->new_file.mode);
		git_buf_printf(pi->buf, "%c\t%s%c\n", code, delta->old_file.path, old_suffix);
		git_buf_printf(pi->buf, "%c\t%s\n", code, delta->old_file.path);
	return pi->print_cb(pi->cb_data, delta, NULL, GIT_DIFF_LINE_FILE_HDR, git_buf_cstr(pi->buf), git_buf_len(pi->buf));
	git_diff_data_fn print_cb)
	git_oid_tostr(start_oid, sizeof(start_oid), &delta->old_file.oid);
	git_oid_tostr(end_oid, sizeof(end_oid), &delta->new_file.oid);
	if (delta->old_file.mode == delta->new_file.mode) {
			start_oid, end_oid, delta->old_file.mode);
		if (delta->old_file.mode == 0) {
			git_buf_printf(pi->buf, "new file mode %o\n", delta->new_file.mode);
		} else if (delta->new_file.mode == 0) {
			git_buf_printf(pi->buf, "deleted file mode %o\n", delta->old_file.mode);
			git_buf_printf(pi->buf, "old mode %o\n", delta->old_file.mode);
			git_buf_printf(pi->buf, "new mode %o\n", delta->new_file.mode);
	const char *oldpfx = pi->diff->opts.old_prefix;
	const char *oldpath = delta->old_file.path;
	const char *newpfx = pi->diff->opts.new_prefix;
	const char *newpath = delta->new_file.path;
		oldpfx = DIFF_OLD_PREFIX_DEFAULT;
		newpfx = DIFF_NEW_PREFIX_DEFAULT;
	git_buf_printf(pi->buf, "diff --git %s%s %s%s\n", oldpfx, delta->old_file.path, newpfx, delta->new_file.path);
	if (git_oid_iszero(&delta->old_file.oid)) {
	if (git_oid_iszero(&delta->new_file.oid)) {
    result = pi->print_cb(pi->cb_data, delta, NULL, GIT_DIFF_LINE_FILE_HDR, git_buf_cstr(pi->buf), git_buf_len(pi->buf));
	return pi->print_cb(pi->cb_data, delta, NULL, GIT_DIFF_LINE_BINARY, git_buf_cstr(pi->buf), git_buf_len(pi->buf));
	return pi->print_cb(pi->cb_data, d, r, GIT_DIFF_LINE_HUNK_HDR, git_buf_cstr(pi->buf), git_buf_len(pi->buf));
	git_diff_range *range,
	return pi->print_cb(pi->cb_data, delta, range, line_origin, git_buf_cstr(pi->buf), git_buf_len(pi->buf));
	git_diff_data_fn print_cb)
	git_diff_file_fn file_cb,
	git_diff_data_fn line_cb)
	mmfile_t old_data, new_data;
	git_map old_map, new_map;
	git_blob *new, *old;
	memset(&delta, 0, sizeof(delta));

	new = new_blob;
	old = old_blob;
		git_blob *swap = old;
		old = new;
		new = swap;
	if (old) {
		old_data.ptr  = (char *)git_blob_rawcontent(old);
		old_data.size = git_blob_rawsize(old);
		git_oid_cpy(&delta.old_file.oid, git_object_id((const git_object *)old));
		old_data.ptr  = "";
		old_data.size = 0;
	if (new) {
		new_data.ptr  = (char *)git_blob_rawcontent(new);
		new_data.size = git_blob_rawsize(new);
		git_oid_cpy(&delta.new_file.oid, git_object_id((const git_object *)new));
		new_data.ptr  = "";
		new_data.size = 0;
	delta.status = new ?
		(old ? GIT_DELTA_MODIFIED : GIT_DELTA_ADDED) :
		(old ? GIT_DELTA_DELETED : GIT_DELTA_UNTRACKED);

	if (git_oid_cmp(&delta.new_file.oid, &delta.old_file.oid) == 0)
		delta.status = GIT_DELTA_UNMODIFIED;

	delta.old_file.size = old_data.size;
	delta.new_file.size = new_data.size;

	fill_map_from_mmfile(&old_map, &old_data);
	fill_map_from_mmfile(&new_map, &new_data);

	if (file_is_binary_by_content(&delta, &old_map, &new_map) < 0)
		return -1;

	if (file_cb != NULL) {
		int error = file_cb(cb_data, &delta, 1);
		if (error < 0)
			return error;
	}

	/* don't do hunk and line diffs if the two blobs are identical */
	if (delta.status == GIT_DELTA_UNMODIFIED)
		return 0;

	/* don't do hunk and line diffs if file is binary */
	if (delta.binary == 1)
		return 0;
	xdl_diff(&old_data, &new_data, &xdiff_params, &xdiff_config, &xdiff_callback);