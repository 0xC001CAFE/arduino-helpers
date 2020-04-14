#include "StreamHelpers.h"

bool StreamHelpers::filterBySequence(Stream &input, Stream &output, const char *startSeq, const char *endSeq, bool invertedOutput){
    if(!startSeq || !endSeq) return false;
    
    size_t startSeqLen = strlen(startSeq);
    bool startSeqFound = false;
    
    size_t endSeqLen = strlen(endSeq);
    bool endSeqFound = false;
    
    // null character is not required
    char buffer[startSeqLen > endSeqLen ? startSeqLen : endSeqLen];
    size_t bufferIndex = 0;
    
    // current byte of the input stream
    char currentByte;
    // current sequence to be found
    const char *currentSeq = startSeq;
    size_t currentSeqLen = startSeqLen;
    
    while(input.available() > 0){
        currentByte = input.read();
        
        // check if the following evaluation can be skipped
        if(startSeqFound && endSeqFound){
            if(invertedOutput){
                // evaluation successfully completed
                return true;
            }else{
                // write to output stream
                output.write(currentByte);
                
                // read next byte
                continue;
            }
        }
        
        if(currentByte == currentSeq[bufferIndex]){
            // buffer current byte
            buffer[bufferIndex++] = currentByte;
            
            if(bufferIndex == currentSeqLen){
                // current sequence was found
                
                // write buffer to output stream
                if(invertedOutput) output.write(buffer, bufferIndex);
                
                // reset buffer index
                bufferIndex = 0;
                
                if(startSeqFound){
                    // end sequence
                    
                    endSeqFound = true;
                }else{
                    // start sequence
                    
                    startSeqFound = true;
                    
                    // try to find the end sequence now
                    currentSeq = endSeq;
                    currentSeqLen = endSeqLen;
                }
            }
            
            // next byte is necessary for evaluation
            continue;
        }
        
        // check if buffering has already started
        if(bufferIndex > 0){
            // buffered sequence does not correspond to the current sequence
            
            // write buffer to output stream
            if((invertedOutput && startSeqFound) || (!invertedOutput && !startSeqFound)) output.write(buffer, bufferIndex);
            
            // reset buffer index
            bufferIndex = 0;
            
            // check if current byte matches first byte of current sequence
            if(currentByte == currentSeq[bufferIndex]){
                // start buffering again
                buffer[bufferIndex++] = currentByte;
                
                // next byte is necessary for evaluation
                continue;
            }
        }
        
        // write to output stream
        if((invertedOutput && startSeqFound) || (!invertedOutput && !startSeqFound)) output.write(currentByte);
    }
    
    return startSeqFound && endSeqFound;
}
