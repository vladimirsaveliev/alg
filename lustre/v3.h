#define LOV_MAXPOOLNAME 15

struct lov_mds_md_v3 {            /* LOV EA mds/wire data (little-endian) */
        __u32 lmm_magic;          /* magic number = LOV_MAGIC_V3 */
        __u32 lmm_pattern;        /* LOV_PATTERN_RAID0, LOV_PATTERN_RAID1 */
        struct ost_id   lmm_oi;   /* LOV object ID */
        __u32 lmm_stripe_size;    /* size of stripe in bytes */
        /* lmm_stripe_count used to be __u32 */
        __u16 lmm_stripe_count;   /* num stripes in use for this object */
        __u16 lmm_layout_gen;     /* layout generation number */
        char  lmm_pool_name[LOV_MAXPOOLNAME + 1]; /* must be 32bit aligned */
        struct lov_ost_data_v1 lmm_objects[0]; /* per-stripe data */
};

struct lov_user_md_v3 {           /* LOV EA user data (host-endian) */
        __u32 lmm_magic;          /* magic number = LOV_USER_MAGIC_V3 */
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
        char  lmm_pool_name[LOV_MAXPOOLNAME + 1]; /* pool name */
        struct lov_user_ost_data_v1 lmm_objects[0]; /* per-stripe data */
} __attribute__((packed, __may_alias__));
