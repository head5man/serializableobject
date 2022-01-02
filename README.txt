# serializableobject

serializableobject's main goal is to define independent 
tag/token based serializable classes. Using the serializable 
member definitions the serialization is done by implementing 
specialized Serializers and DeSerializers. 

Implementation of these Serialzers depend on the platform 
and possible libraries used for example json-c, nlohmann json.

##  Class specification

serializable::Serializable
- define members of basic types int, bool, double, string
- define members of derived Serializable types
- define members which are vectors of the types above
- can copy/clone itself using member definitions

serializable::Serializer (TBD)
- can serialize serializable::Serializable to string using member definitions

serializable::DeSerializer (TBD)
- can deserialize to serializable::Serializable from string using member definitions

## Install

There is currently nothing to be installed.

## Usage

Solution and project files were created with
Microsoft Visual Studio Community 2022 - Version 17.0.4

Project is build and run as VisualStudio::CppUnitTestFramework Tests

For any other use include Serializable, Serializer and DeSerializer sources
from the source folder in your build and implement application specific Serializer and DeSerializer.

## Contributing

Let's see after implementing the interfaces for Serialzer and DeSerializer

## License
Copyright © 2022 Tuomas Lahtinen
This work is free. You can redistribute it and/or modify it under the
terms of the Do What The Fuck You Want To Public License, Version 2,
as published by Sam Hocevar. See http://www.wtfpl.net/ for more details.
