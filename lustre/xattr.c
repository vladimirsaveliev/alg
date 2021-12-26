#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>
#include <linux/types.h>
#include <sys/xattr.h>

#include "v1.h"
#include "v3.h"
#include "composite.h"

#define LOV_PATTERN_RAID0               0x001
#define LOV_PATTERN_RAID1               0x002
#define LOV_PATTERN_MDT                 0x100


struct lustre_mdt_attrs {
        /**
         * Bitfield for supported data in this structure. From enum lma_compat.
         * lma_self_fid and lma_flags are always available.
         */
        __u32   lma_compat;
        /**
         * Per-file incompat feature list. Lustre version should support all
         * flags set in this field. The supported feature mask is available in
         * LMA_INCOMPAT_SUPP.
         */
        __u32   lma_incompat;
        /** FID of this inode */
        struct lu_fid  lma_self_fid;
};

static void print_lma(const char *str, void *p)
{
	struct lustre_mdt_attrs *lma = (struct lustre_mdt_attrs *)p;

	printf("%scompat: %x\n", str, lma->lma_compat);
	printf("%sincompat: %x\n", str, lma->lma_incompat);
	printf("%sself_fid[seq:oid:ver]: [%llx:%x:%x]\n", str, lma->lma_self_fid.f_seq,
	       lma->lma_self_fid.f_oid, lma->lma_self_fid.f_ver);
}

static const char *pattern_name(__u32 pattern)
{
	if (pattern == LOV_PATTERN_RAID0)
		return "raid0";
	if (pattern == LOV_PATTERN_RAID1)
		return "raid1";
	if (pattern == LOV_PATTERN_MDT)
		return "mdt";
	return "unknown";
}

static void print_lum_v1(const char *str, void *p)
{
	struct lov_user_md_v1 *lum = (struct lov_user_md_v1 *)p;

	printf("%smagic %x LOV V1\n", str, lum->lmm_magic);
	printf("%spattern %s\n", str, pattern_name(lum->lmm_pattern));
	printf("%sstripe_size %d\n", str, lum->lmm_stripe_size);
	printf("%sstripe_count %d\n", str, lum->lmm_stripe_count);
	printf("%sstripe_offset/layout_gen %d\n", str, lum->lmm_stripe_offset);
}

static void print_lum_v3(const char *str, void *p)
{
	struct lov_user_md_v3 *lum = (struct lov_user_md_v3 *)p;

	printf("%smagic %x LOV V3\n", str, lum->lmm_magic);
	printf("%spattern %s\n", str, pattern_name(lum->lmm_pattern));
	printf("%sstripe_size %d\n", str, lum->lmm_stripe_size);
	printf("%sstripe_count %d\n", str, lum->lmm_stripe_count);
	printf("%sstripe_offset/layout_gen %d\n", str, lum->lmm_stripe_offset);
	printf("%spool_name %s\n", str, lum->lmm_pool_name);
}

static void print_lum_comp(const char *str, void *p)
{
	struct lov_comp_md_v1 *lcm  = (struct lov_comp_md_v1 *)p;
	struct lov_comp_md_entry_v1 *lce;
	struct lov_user_md_v1 *lum;
	int i;

	printf("%smagic: %x LOV COMP\n", str, lcm->lcm_magic);
	printf("%ssize: %d\n", str, lcm->lcm_size);
	printf("%slayout gen: %d\n", str, lcm->lcm_layout_gen);
	printf("%sflags: %d\n", str, lcm->lcm_flags);
	printf("%sentry count: %d\n", str, lcm->lcm_entry_count);
	printf("%smirror count: %d\n", str, lcm->lcm_mirror_count);

	lce = &lcm->lcm_entries[0];
	for (i = 0; i < lcm->lcm_entry_count; i++, lce++) {
		printf("%s\tid: %d\n", str, lce->lcme_id);
		printf("%s\tflags: %x\n", str, lce->lcme_flags);
		printf("%s\textent: [%llu %llu]\n", str, lce->lcme_extent.e_start,
		       lce->lcme_extent.e_end);
		printf("%s\toffset %u\n", str, lce->lcme_offset);
		printf("%s\tsize %u\n", str, lce->lcme_size);

		lum = (struct lov_user_md_v1 *)((char *)p + lce->lcme_offset);
		switch (lum->lmm_magic) {
		case 0x0BD10BD0:
			print_lum_v1("\t\t\t", lum);
			break;
		case 0x0BD30BD0:
			print_lum_v3("\t\t\t", lum);
			break;
		default:
			printf("\t\t\tmagic  %x\n", lum->lmm_magic);
			break;
		}
	}
}


static void xattr_value(const char *name, const char *key)
{
	ssize_t vallen;
	char *val;

	vallen = getxattr(name, key, NULL, 0);
	if (vallen == -1) {
		perror("getxattr failed");
		exit(1);
	}
	val = malloc(vallen);
	if (val == NULL) {
		perror("malloc failed");
		exit(1);
	}
	vallen = getxattr(name, key, val, vallen);
	if (vallen == -1) {
		perror("getxattr failed");
		exit(1);
	}

	printf("%s: %ld\n", key, vallen);
	if (!strcmp(key, "trusted.lov")) {
		struct lov_mds_md_v3 *lmm;

		lmm = (struct lov_mds_md_v3 *)val;
		switch(lmm->lmm_magic) {
		case 0x0BD10BD0:
			print_lum_v1("\t", lmm);
			break;
		case 0x0BD30BD0:
			print_lum_v3("\t", lmm);
			break;
		case 0x0BD60BD0: {
			print_lum_comp("\t", lmm);
			break;
		}
		default:
			printf("\tlmm_magic %x\n", lmm->lmm_magic);
			break;
		}
	} else if (!strcmp(key, "lustre.lov")) {
		struct lov_mds_md_v3 *lmm;

		lmm = (struct lov_mds_md_v3 *)val;
		switch(lmm->lmm_magic) {
		case 0x0BD10BD0:
			print_lum_v1("\t", lmm);
			break;
		case 0x0BD30BD0:
			print_lum_v3("\t", lmm);
			break;
		case 0x0BD60BD0:
			print_lum_comp("\t", lmm);
			break;
		default:
			printf("\tlmm_magic %x\n", lmm->lmm_magic);
			break;
		}
	} else if (!strcmp(key, "trusted.lma")) {
		print_lma("\t", val);
	} else {
		printf("\tnot ready\n");
	}
	free(val);
}

int main(int argc, char **argv)
{
	ssize_t buflen;
	char *buf;
	char *key;

	printf("lov_user_md_v1 size %lu\n", sizeof(struct lov_user_md_v1));
	printf("lov_user_md_v3 size %lu\n", sizeof(struct lov_user_md_v3));
	printf("lov_comp_md_v1 size %lu\n", sizeof(struct lov_comp_md_v1));

	if (argc < 2) {
		printf("Usage: %s file\n", argv[0]);
		return 1;
	}

	buflen = listxattr(argv[1], NULL, 0);
	if (buflen < 1) {
		perror("listxattr NULL 0 failed");
		return 0;
	}
	buf = malloc(buflen);
	if (buf == NULL) {
		perror("malloc failed");
		return 1;
	}
	buflen = listxattr(argv[1], buf, buflen);
	if (buflen == -1) {
		perror("listxattr failed");
		return 0;
	}

	key = buf;
	printf("%s\n", argv[1]);
	while (buflen > 0) {
		xattr_value(argv[1], key);
		
		buflen -= strlen(key) + 1;
		key += strlen(key) + 1;		
	}

	return 0;
}
