/* Do not edit this file. It was automatically generated. */

#ifndef HEADER_LinuxProcess
#define HEADER_LinuxProcess
/*
htop - LinuxProcess.h
(C) 2014 Hisham H. Muhammad
Released under the GNU GPL, see the COPYING file
in the source distribution for its full text.
*/


#include "PerfCounter.h"

#define PROCESS_FLAG_LINUX_IOPRIO   0x0100L
#define PROCESS_FLAG_LINUX_OPENVZ   0x0200L
#define PROCESS_FLAG_LINUX_VSERVER  0x0400L
#define PROCESS_FLAG_LINUX_CGROUP   0x0800L
#define PROCESS_FLAG_LINUX_OOM      0x1000L

#define PROCESS_FLAG_LINUX_HPC       0xff0000L
#define PROCESS_FLAG_LINUX_HPC_CYCLE 0x10000L
#define PROCESS_FLAG_LINUX_HPC_INSN  0x20000L
#define PROCESS_FLAG_LINUX_HPC_MISS  0x40000L
#define PROCESS_FLAG_LINUX_HPC_BMISS 0x80000L

#define PROCESS_FLAG_LINUX_HPC_L1DR   0x100000L
#define PROCESS_FLAG_LINUX_HPC_L1DW   0x200000L
#define PROCESS_FLAG_LINUX_HPC_L1DRM  0x400000L
#define PROCESS_FLAG_LINUX_HPC_L1DWM  0x800000L

typedef enum UnsupportedProcessFields {
   FLAGS = 9,
   ITREALVALUE = 20,
   VSIZE = 22,
   RSS = 23,
   RLIM = 24,
   STARTCODE = 25,
   ENDCODE = 26,
   STARTSTACK = 27,
   KSTKESP = 28,
   KSTKEIP = 29,
   SIGNAL = 30,
   BLOCKED = 31,
   SSIGIGNORE = 32,
   SIGCATCH = 33,
   WCHAN = 34,
   NSWAP = 35,
   CNSWAP = 36,
   EXIT_SIGNAL = 37,
} UnsupportedProcessField;

typedef enum LinuxProcessFields {
   CMINFLT = 11,
   CMAJFLT = 13,
   UTIME = 14,
   STIME = 15,
   CUTIME = 16,
   CSTIME = 17,
   M_SHARE = 41,
   M_TRS = 42,
   M_DRS = 43,
   M_LRS = 44,
   M_DT = 45,
   #ifdef HAVE_OPENVZ
   CTID = 100,
   VPID = 101,
   #endif
   #ifdef HAVE_VSERVER
   VXID = 102,
   #endif
   #ifdef HAVE_TASKSTATS
   RCHAR = 103,
   WCHAR = 104,
   SYSCR = 105,
   SYSCW = 106,
   RBYTES = 107,
   WBYTES = 108,
   CNCLWB = 109,
   IO_READ_RATE = 110,
   IO_WRITE_RATE = 111,
   IO_RATE = 112,
   #endif
   #ifdef HAVE_CGROUP
   CGROUP = 113,
   #endif
   OOM = 114,
   IO_PRIORITY = 115,
   #ifdef HAVE_DELAYACCT
   PERCENT_CPU_DELAY = 116,
   PERCENT_IO_DELAY = 117,
   PERCENT_SWAP_DELAY = 118,
   #endif
   #ifdef HAVE_PERFCOUNTERS
   IPC = 119,
   MCYCLE = 120,
   MINSTR = 121,
   PERCENT_MISS = 122,
   PERCENT_BMISS = 123,
   L1DREADS = 124,
   L1DRMISSES = 125,
   L1DWRITES = 126,
   L1DWMISSES = 127,
   #endif
   LAST_PROCESSFIELD = 128,
} LinuxProcessField;

#include "IOPriority.h"

typedef struct LinuxProcess_ {
   Process super;
   bool isKernelThread;
   IOPriority ioPriority;
   unsigned long int cminflt;
   unsigned long int cmajflt;
   unsigned long long int utime;
   unsigned long long int stime;
   unsigned long long int cutime;
   unsigned long long int cstime;
   long m_share;
   long m_trs;
   long m_drs;
   long m_lrs;
   long m_dt;
   #ifdef HAVE_TASKSTATS
   unsigned long long io_rchar;
   unsigned long long io_wchar;
   unsigned long long io_syscr;
   unsigned long long io_syscw;
   unsigned long long io_read_bytes;
   unsigned long long io_write_bytes;
   unsigned long long io_cancelled_write_bytes;
   unsigned long long io_rate_read_time;
   unsigned long long io_rate_write_time;   
   double io_rate_read_bps;
   double io_rate_write_bps;
   #endif
   #ifdef HAVE_OPENVZ
   unsigned int ctid;
   unsigned int vpid;
   #endif
   #ifdef HAVE_VSERVER
   unsigned int vxid;
   #endif
   #ifdef HAVE_CGROUP
   char* cgroup;
   #endif
   unsigned int oom;
   char* ttyDevice;
   #ifdef HAVE_DELAYACCT
   unsigned long long int delay_read_time;
   unsigned long long cpu_delay_total;
   unsigned long long blkio_delay_total;
   unsigned long long swapin_delay_total;
   float cpu_delay_percent;
   float blkio_delay_percent;
   float swapin_delay_percent;
   #endif
   #ifdef HAVE_PERFCOUNTERS
   PerfCounter* cycleCounter;
   PerfCounter* insnCounter;
   PerfCounter* missCounter;
   PerfCounter* brCounter;
   PerfCounter* l1drCounter;
   PerfCounter* l1drmCounter;
   PerfCounter* l1dwCounter;
   PerfCounter* l1dwmCounter;
   float ipc;
   float mcycle;
   float minstr;
   float pMiss;
   float pBMiss;
   float l1dr;
   float l1drm;
   float l1dw;
   float l1dwm;
   #endif
} LinuxProcess;

#ifndef Process_isKernelThread
#define Process_isKernelThread(_process) (((LinuxProcess*)(_process))->isKernelThread)
#endif

#ifndef Process_isUserlandThread
#define Process_isUserlandThread(_process) (_process->pid != _process->tgid)
#endif


extern ProcessFieldData Process_fields[];

extern ProcessPidColumn Process_pidColumns[];

extern ProcessClass LinuxProcess_class;

LinuxProcess* LinuxProcess_new(Settings* settings);

void Process_delete(Object* cast);

/*
[1] Note that before kernel 2.6.26 a process that has not asked for
an io priority formally uses "none" as scheduling class, but the
io scheduler will treat such processes as if it were in the best
effort class. The priority within the best effort class will  be
dynamically  derived  from  the  cpu  nice level of the process:
extern io_priority;
*/
#define LinuxProcess_effectiveIOPriority(p_) (IOPriority_class(p_->ioPriority) == IOPRIO_CLASS_NONE ? IOPriority_tuple(IOPRIO_CLASS_BE, (p_->super.nice + 20) / 5) : p_->ioPriority)

IOPriority LinuxProcess_updateIOPriority(LinuxProcess* this);

bool LinuxProcess_setIOPriority(LinuxProcess* this, IOPriority ioprio);

#if HAVE_DELAYACCT || HAVE_PERFCOUNTERS

#endif

void LinuxProcess_writeField(Process* this, RichString* str, ProcessField field);

#define COMPARE_FIELD(_f) return (p2->_f > p1->_f ? 1 : -1)

long LinuxProcess_compare(const void* v1, const void* v2);

bool Process_isThread(Process* this);

#endif
