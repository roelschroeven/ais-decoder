
#include "../../ais_decoder/ais_quick.h"
#include "../example_utils.h"

#include <cstring>



/*
 
 
 
 
 
 
 This example demonstrates how to use the 'AIS Quick' interface.  This interface was created as a simple
 interface for the SWIG/Python bindings.
 
 The interface accepts new data through:
 - 'pushAisSentence(...)' which consumes one sentence/line per call
 
 - 'pushAisChunk(...)' which consumes a whole block of data, consuming all strings in the data. Any remaining
   data (partial sentence) is buffered until the next call.
 
 - 'popAisMessage(...)' returns the next decoded message as a set of key/value pairs (a dictionary in Python case).
 
 The AIS Decoder is created by inheriting from the AIS::AisDecoder base class with most of the pure virtual
 methods implemented as empty stubs.  This allows us to focus specifically on the raw decoding performance.
 
 The 'AIS::processAisFile(...)' function is a utility function (see 'ais_decoder/ais_file.h') that reads
 and decodes a file in blocks of the specified size.
 
 
 
 
 
 
 */




void pushSentence(const char *_pszSentence)
{
    pushAisSentence(_pszSentence, strlen(_pszSentence));
}

#include <iostream>

int main()
{
    pushSentence("!AIVDM,1,1,,A,13HOI:0P0000VOHLCnHQKwvL05Ip,0*23\n");
    pushSentence("!AIVDM,1,1,,A,133sVfPP00PD>hRMDH@jNOvN20S8,0*7F\n");
    pushSentence("!AIVDM,1,1,,B,100h00PP0@PHFV`Mg5gTH?vNPUIp,0*3B\n");
    pushSentence("!AIVDM,1,1,,B,13eaJF0P00Qd388Eew6aagvH85Ip,0*45\n");
    pushSentence("!AIVDM,1,1,,A,14eGrSPP00ncMJTO5C6aBwvP2D0?,0*7A,1452026224\n");
    pushSentence("\\c:1452026224\\!AIVDM,1,1,,A,15MrVH0000KH<:V:NtBLoqFP2H9:,0*2F\n");
    pushSentence("!AIVDM,1,1,,A,83`fLjPj2d<dtN>LtAK@a?a@6Tt0,0*16\n"); // inland static & voyage related data
    
    // NOTE: popping many more messages than sentences pushed
    for (int i = 0; i < 100; ++i)
      {
        auto msg = popAisMessage();
        if (msg.empty())
          continue;
        for (std::map<std::string, std::string>::const_iterator it = msg.begin(); it != msg.end(); ++it)
          std::cout << it->first << "   " << it->second << "\n";
        std::cout << "\n";
      }

    return 0;
}






