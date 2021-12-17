#! /bin/bash

create_pool()
{
	echo
	echo create pool..
	echo

	lctl pool_new lustre.mypool
	lctl pool_add lustre.mypool OST0000
	lfs pool_list lustre
}

destroy_pool()
{
	echo
	echo destroy pool..
	echo

	lctl pool_remove lustre.mypool OST0000
	lctl pool_destroy lustre.mypool
	lfs pool_list lustre
}

rm -rf /mnt/lustre/*

lctl set_param debug=-1 debug_mb=256
create_pool

echo create dir with pool
mkdir /mnt/lustre/dir1

lfs setstripe -p mypool /mnt/lustre/dir1

#echo getstripe /mnt/lustre/dir1 after -p pool
#lfs getstripe /mnt/lustre/dir1 -d

lfs setstripe -E 1M -L mdt -E -1 -c 1 /mnt/lustre/dir1

#lfs setstripe -E 1M -L mdt -E -1 -c 1 -p mypool /mnt/lustre/dir1 - OK
echo getstripe /mnt/lustre/dir1 after pfl
lfs getstripe /mnt/lustre/dir1 -d

echo create dir in dir
lctl dk > /dev/null
mkdir /mnt/lustre/dir1/dir2
lctl dk > mkdir.dir2.xx
lfs getstripe /mnt/lustre/dir1/dir2

destroy_pool

exit

lfs setstripe -E 1M -L mdt -E -1 -c 1 /mnt/lustre/dir1
lfs getstripe -d /mnt/lustre/dir1

lfs setdirstripe -i 0 -c 2 /mnt/lustre/dir1/dir2
lfs getstripe -d /mnt/lustre/dir1/dir2


destroy_pool

