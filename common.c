#include "common.h"

// ---------------------------------------------
// Safe implementation of writeP()
// ---------------------------------------------
void writeP(void)
{
    // Ensure last byte is FLUSH if caller forgot
    if (bufferU[DIMBUF - 1] != FLUSH)
        bufferU[DIMBUF - 1] = FLUSH;

    // Send packet with minimal safe timeout
    PacketIO(2);   // 2 ms is enough for write-only operations
}

// ---------------------------------------------
// Safe implementation of readP()
// ---------------------------------------------
void readP(void)
{
    // Read packet with safe timeout
    PacketIO(5);   // 5 ms is typical for read operations

    // Optional: basic sanity check
    if (bufferI[0] == 0 && bufferI[1] == 0)
    {
        // Probably no response — log but do not abort
        if (saveLog && logfile)
            fprintf(logfile, "Warning: empty response in readP()\n");
    }
}
