struct lu_extent {
        __u64   e_start;
	__u64   e_end;
} __attribute__((packed));

struct lov_comp_md_entry_v1 {
        __u32                   lcme_id;        /* unique id of component */
	__u32                   lcme_flags;     /* LCME_FL_XXX */
        struct lu_extent        lcme_extent;    /* file extent for component */
        __u32                   lcme_offset;    /* offset of component blob,
                                                   start from lov_comp_md_v1 */
        __u32                   lcme_size;      /* size of component blob */
	__u32                   lcme_layout_gen;
        __u64                   lcme_timestamp; /* snapshot time if applicable*/
        __u32                   lcme_padding_1;
} __attribute__((packed));

struct lov_comp_md_v1 {
        __u32   lcm_magic;      /* LOV_USER_MAGIC_COMP_V1 */
        __u32   lcm_size;       /* overall size including this struct */
        __u32   lcm_layout_gen;
        __u16   lcm_flags;
        __u16   lcm_entry_count;
        /* lcm_mirror_count stores the number of actual mirrors minus 1,
         * so that non-flr files will have value 0 meaning 1 mirror. */
        __u16   lcm_mirror_count;
        __u16   lcm_padding1[3];
        __u64   lcm_padding2;
        struct lov_comp_md_entry_v1 lcm_entries[0];
} __attribute__((packed));
