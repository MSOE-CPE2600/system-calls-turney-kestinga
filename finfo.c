/* Abe Kesting
 * Lab week 10
 * 11/7/24
 * Section 111
 */
// finfo.c
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>

int main(int argc, char* argv[]) {
    if (argc <= 1) {
        printf("Specify file. Exiting...\n");
        exit(1);
    }
    char* filename = argv[1];
    int filenum = open(filename, O_CREAT);

    struct stat info;
    fstat(filenum, &info);
    close(filenum);
    if (errno) { //quit if errors
        perror("error getting file info");
        exit(1);
    }
    char* type;
    switch (info.st_mode & S_IFMT) { //different types found on man page inode.7
        case S_IFSOCK :
            type = "socket";
            break;
        case S_IFLNK :
            type = "symbolic link";
            break;
        case S_IFREG :
            type = "regular file";
            break;
        case S_IFBLK :
            type = "block device";
            break;
        case S_IFDIR :
            type = "directory";
            break;
        case S_IFCHR :
            type = "character device";
            break;
        case S_IFIFO :
            type = "FIFO";
            break;
        default :
            type = "unknown";
    }
    printf("File type: %s\n", type);
    printf("File permissions (octal): %o\n", info.st_mode & 0777); //mask for permission flags
    printf("User ID: %d\n", info.st_uid);
    printf("File size (bytes): %ld\n", info.st_size);

    struct tm access;
    localtime_r(&info.st_atim.tv_sec, &access);//convert to readable time
    printf("Last accessed %d/%d/%d %d:%02d\n", access.tm_mon+1, access.tm_mday, 1900+access.tm_year, access.tm_hour, access.tm_min);

    return 0;
}

//  struct stat {
//                dev_t     st_dev;          ID of device containing file */
//                ino_t     st_ino;          Inode number */
//                mode_t    st_mode;         File type and mode */
//                nlink_t   st_nlink;        Number of hard links */
//                uid_t     st_uid;          User ID of owner */
//                gid_t     st_gid;          Group ID of owner */
//                dev_t     st_rdev;         Device ID (if special file) */
//                off_t     st_size;         Total size, in bytes */
//                blksize_t st_blksize;      Block size for filesystem I/O */
//                blkcnt_t  st_blocks;       Number of 512B blocks allocated */

//                 Since Linux 2.6, the kernel supports nanosecond
//                 precision for the following timestamp fields.
//                 For the details before Linux 2.6, see NOTES. */

//                struct timespec st_atim;   Time of last access */
//                struct timespec st_mtim;   Time of last modification */
//                struct timespec st_ctim;   Time of last status change */

//            #define st_atime st_atim.tv_sec       Backward compatibility */
//            #define st_mtime st_mtim.tv_sec
//            #define st_ctime st_ctim.tv_sec
//            };

//         */