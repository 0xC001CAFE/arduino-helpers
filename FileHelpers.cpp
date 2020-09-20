#include "FileHelpers.h"

bool FileHelpers::removeBySequence(File &file, const char *startSeq, const char *endSeq){
    // create temporary file
    File tempFile("temp", O_WRONLY | O_CREAT | O_TRUNC);
    
    // check if temporary file is open
    if(!tempFile) return false;
    
    char filename[FILENAME_MAX_LENGTH];
    // return value of the function
    bool result = true;
    
    // try to get the filename
    if(!file.getName(filename, FILENAME_MAX_LENGTH)) result = false;
    
    // try to write the filtered file into the temporary file
    if(result && !StreamHelpers::filterBySequence(file, tempFile, startSeq, endSeq, false)) result = false;
    
    // remove the obsolete file
    // the temporary file contains the latest content
    if(result && !file.remove()) result = false;
    
    // rename the temporary file to the filename of the removed file
    if(result && !tempFile.rename(filename)) result = false;
    
    tempFile.close();
    
    return result;
}
