#ifndef LIBBCU_SILENT_H
#define LIBBCU_SILENT_H

#ifdef LIBBCU_NO_PRINT
#define printf(...) ((int)0)
#define fprintf(...) ((int)0)
#endif

#endif
