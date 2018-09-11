## Simple AIS NMEA Message Decoder

This project was created to learn more about AIS and see how easy it would be to create a decoder for the NMEA strings. The NMEA string decoding is implemented according to: 'http://catb.org/gpsd/AIVDM.html'.  The key component to implement was the 6bit nibble packing and unpacking of arbitrarily sized signed and unsigned integers as well as strings (see PayloadBuffer in ais_decoder.h).

The decoder consists of a base class that does the decoding, with pure virtual methods for each AIS messages type.  A user of the decoder has to inherit from the decoder class and implement/override 'onTypeXX(...)' style methods as well as error handling methods (see the examples, for how this is done).  Basic error checking, including CRC checks, are done and also reported.

The current 'onTypeXX(...)' message callback are unique for each message type (types 1,2,3,4,5,18,19 & 24 currently supported).  No assumtions are made on default or blank values -- all values are returned as integers and the user has to scale and convert the values like position and speed to floats and the desired units.

Some time was also spent on improving the speed of the NMEA string processing to see how quickly NMEA logs could be processed.  Currently the multi-threaded file reading examples (running a thread per file) achieve more than 500k NMEA messages per second, per thread.  When running on multiple logs concurrently (8 threads is a good number on modern hardware) 4M+ NMEA messages per second is possible.  During testing it was also found that most of the time was spent on the 6bit nibble packing and unpacking, not the file IO.


## Checklist
- [x] Basic payload 6bit nibble stuffing and unpacking
- [x] ASCII de-armouring
- [x] CRC checking
- [x] Multi-Sentence message handling
- [x] Decoder base class
- [x] Support types 1, 2, 3, 4, 5, 18, 19, 24 -- position reports and static info
- [x] Test with large data-sets (files)
- [x] Validate payload sizes (reject messages, where type and size does not match)
- [x] Build-up message stats (bytes processed, messages processed, etc.)
- [x] Profile and improve speed 
- [x] Validate fragment count and fragment number values

- [ ] Validate talker IDs
- [ ] Investigate faster ascii de-armouring and bit packing techniques
- [ ] Look at multiple threads/decoders working on the same file, for very large files
- [ ] Support NMEA files/data with non-standard meta data, timestamp data, etc.
- [ ] Add minimal networking to work with RTL-AIS and also to forward raw data

## Build
This project uses CMAKE to build.  To build through command line on linux, do the following:

- git clone https://github.com/aduvenhage/ais-decoder.git
- mkdir ais-decoder-build
- cd ais-decoder-build
- cmake ../ais-decoder -DCMAKE_BUILD_TYPE=RELEASE
- make
- sudo make install

** Currently the 'develop' branch is the branch to use -- the 'master' branch is empty/outdated.

## Examples
The project includes some examples of how to use the AIS decoder lib.
