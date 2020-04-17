#ifndef FileHelpers_h
#define FileHelpers_h

// header file of the SdFat library
#include <ArduinoFiles.h>

namespace FileHelpers{
    // section between start and end sequence is removed from file
    // conditions of use:
    // - file must be open for reading and writing
    // - the current file position must be zero
    // - the volume working directory must contain the file
    // returns true after successful removal
    bool removeBySequence(File &file, const char *startSeq, const char *endSeq);
}

#endif
