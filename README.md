

!!!!!THIS REPO DOES NOT WORK ON WINDOWS OR MAC!!!!!!!

The repo is a basic implementation of ecc and bst of bst in data auditing

Three main libraries are at work in this
1. Crypto++ 
2. Boost for c++
3. cpp-httplib

MISC INFO:
=================
Download all the libraries is /usr/local/ directory as the headers to **.h** files are hardcoded.


Following are the download links and instructions to configure:
BOOST for C++
=========================
Download link: https://www.boost.org/users/download/

How to Install link: https://stackoverflow.com/a/24086375 (Follow this  and we are good)

Except for the **wget Part** do everything.

**NOTE :-** Depending on the boost lib current version we might have to change the name on headers.

CRYPTO++
===========================
Download link: https://github.com/weidai11/cryptopp (install the latest one)

Make a Directory by the name **crypto** in **/usr/local**

extract the files in the above mentioned directory

We need to "make" in the dir so that we can get libcryptopp.a

DO THE FOLLOWING INSIDE THE DIR



``sudo make
``

That should do for the Crypto++

CPP-HTTPLIB
================================
Download Link: https://github.com/yhirose/cpp-httplib

Extract this in **/usr/local**

**NOTE :-** Depending on the cpp-httplib current version we might have to change the name on headers.

That's it.


MYSQL CONFIGURATIONS
====================================

**To Be Continued**


