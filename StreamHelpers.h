#ifndef StreamHelpers_h
#define StreamHelpers_h

#include <string.h>
// base class for character-based streams (arduino core)
#include <Stream.h>

namespace StreamHelpers{
    // via sequence filtered input stream is written to output stream
    // returns true after successful filtering
    bool filterBySequence(Stream &input, Stream &output, const char *startSeq, const char *endSeq);
}

#endif
