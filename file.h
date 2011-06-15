struct file {
  enum { FD_NONE, FD_PIPE, FD_INODE } type;
  int ref; // reference count
  char readable;
  char writable;
  struct pipe *pipe;
  struct inode *ip;
  uint off;
};


// in-core file system types

struct inode {
  uint dev;           // Device number
  uint inum;          // Inode number
  uint gen;           // Generation number
  int ref;            // Reference count
  int flags;          // I_BUSY, I_VALID
  int readbusy;
  struct condvar cv;
  struct spinlock lock;
  char lockname[16];

  short type;         // copy of disk inode
  short major;
  short minor;
  short nlink;
  uint size;
  uint addrs[NDIRECT+1];
};

#define I_BUSYR 0x1
#define I_BUSYW 0x2
#define I_VALID 0x4
#define I_FREE 0x8


// device implementations

struct devsw {
  int (*read)(struct inode*, char*, int);
  int (*write)(struct inode*, char*, int);
};

extern struct devsw devsw[];

#define CONSOLE 1
