Open Arinc

Arinc is an organization which publishes standards for use in the Aviation industry.  openarinc is a library which provides open-source software implementations of various Arinc standards. openarinc does not replace the Arinc documents, and those documents cannot be reverse engineered from this library. For a full understanding of the standards implemented here, it is suggested to obtain a copy of the standards.

a429 is the first library available in openarinc and provides utilities for packing and unpacking words following the Arinc 429 specification.  

Filestructure: 

root - This folder, contains license, makefile, and this readme.
  \- bin - Contains binary outputs (executables, dynamic, and static libraries)
  |   \- *.exe  *.so *.dll *.a
  \- ext - Contains 3rd party libraries
  |   \- lib - Contains 3rd party binary libraries (.so .a .dll)
  |   \- inc - Contains 3rd party header files to accompany libraries
  \- inc - Contains an export of headers to be used with this library.
  |   \- <module>
  |        \- *.hpp
  \- int - Contains intermediate binaries (.o, .d)
  |   \- *.o
  |   \- *.d
  \- test - Contains sources for unit-testing the library
  |   \- *.hpp
  |   \- *.cpp
  \- src - Contains all sources and headers in this library
      \- <module> - sources are split logically by smaller modules
          \- *.hpp
          \- *.cpp
		  
		  
		  
Todo:  Items outstanding
 - Find proper way to link boost headers
 - Implement socket buffers
 - Implement templated sizes for buffers
 - Fix std::function callback_type for basebuf_rx;


