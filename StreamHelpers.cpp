#include "StreamHelpers.h"

bool StreamHelpers::filterBySequence(Stream &input, Stream &output, const char *startSeq, const char *endSeq){
    size_t startSeqLen = strlen(startSeq);
    size_t endSeqLen = strlen(endSeq);
    
    // null character is not required
    char buffer[startSeqLen > endSeqLen ? startSeqLen : endSeqLen];
    size_t index = 0;
    
    return false;
}
