struct lu_fid {
	/**
	 * FID sequence. Sequence is a unit of migration: all files (objects)
	 * with FIDs from a given sequence are stored on the same server.
	 * Lustre should support 2^64 objects, so even if each sequence
	 * has only a single object we can still enumerate 2^64 objects.
	 **/
        __u64 f_seq;
        /* FID number within sequence. */
        __u32 f_oid;
        /**
         * FID version, used to distinguish different versions (in the sense
         * of snapshots, etc.) of the same file system object. Not currently
         * used.
         **/
        __u32 f_ver;
} __attribute__((packed));

struct ost_id {
        union {
                struct {
                        __u64   oi_id;
                        __u64   oi_seq;
		} oi;
                struct lu_fid oi_fid;
        };
} __attribute__((packed));

struct lov_ost_data_v1 {          /* per-stripe data structure (little-endian)*/
        struct ost_id l_ost_oi;   /* OST object ID */
        __u32 l_ost_gen;          /* generation of this l_ost_idx */
        __u32 l_ost_idx;          /* OST index in LOV (lov_tgt_desc->tgts) */
};

/* this is like struct lov_ost_data_v1 */
struct lov_user_ost_data_v1 {     /* per-stripe data structure */
	struct ost_id l_ost_oi;   /* OST object ID */
	__u32 l_ost_gen;          /* generation of this OST index */
        __u32 l_ost_idx;          /* OST index in LOV */
} __attribute__((packed));

struct lov_mds_md_v1 {            /* LOV EA mds/wire data (little-endian) */
        __u32 lmm_magic;          /* magic number = LOV_MAGIC_V1 */
        __u32 lmm_pattern;        /* LOV_PATTERN_RAID0, LOV_PATTERN_RAID1 */
        struct ost_id   lmm_oi;   /* LOV object ID */
        __u32 lmm_stripe_size;    /* size of stripe in bytes */
        /* lmm_stripe_count used to be __u32 */
        __u16 lmm_stripe_count;   /* num stripes in use for this object */
        __u16 lmm_layout_gen;     /* layout generation number */
        struct lov_ost_data_v1 lmm_objects[0]; /* per-stripe data */
};

struct lov_user_md_v1 {           /* LOV EA user data (host-endian) */
	__u32 lmm_magic;          /* magic number = LOV_USER_MAGIC_V1 */
	__u32 lmm_pattern;        /* LOV_PATTERN_RAID0, LOV_PATTERN_RAID1 */
	struct ost_id lmm_oi;     /* MDT parent inode id/seq (id/0 for 1.x) */
	__u32 lmm_stripe_size;    /* size of stripe in bytes */
	__u16 lmm_stripe_count;   /* num stripes in use for this object */
	union {
		__u16 lmm_stripe_offset;  /* starting stripe offset in
					   * lmm_objects, use when writing */
		__u16 lmm_layout_gen;     /* layout generation number
					   * used when reading */
	};
	struct lov_user_ost_data_v1 lmm_objects[0]; /* per-stripe data */
} __attribute__((packed, __may_alias__));
