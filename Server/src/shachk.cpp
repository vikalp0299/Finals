#include<string>
#include <boost/uuid/detail/sha1.hpp>
#include <boost/predef/other/endian.h>
#include <boost/endian/conversion.hpp>
#include <boost/algorithm/hex.hpp>
#include <boost/range/iterator_range_core.hpp>
#include <iostream>
#include <vector>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

using namespace std;

string getMySHA(const char* filename){

  int fd = open(filename, O_RDONLY);
  if (fd == -1) { cerr << "open: " << strerror(errno) << ")\n"; return "Error"; }
  vector<char> v(128*1024);
  boost::uuids::detail::sha1 sha1;
  for (;;) {
    ssize_t n = read(fd, v.data(), v.size());
    if (n == -1) {
      if (errno == EINTR) continue;
      cerr << "read error: " << strerror(errno) << '\n';
      return "Error"; 
    }
    if (!n) break;
    sha1.process_bytes(v.data(), n);
  } 
  boost::uuids::detail::sha1::digest_type hash;
  sha1.get_digest(hash);
#ifdef  BOOST_ENDIAN_BIG_BYTE
  for (unsigned i = 0; i < sizeof hash / sizeof hash[0]; ++i)
    boost::endian::endian_reverse_inplace(hash[i]);
#endif
    cout<<1<<endl;
    stringstream buffer;
  boost::algorithm::hex(boost::make_iterator_range(
        reinterpret_cast<const char*>(hash),
        reinterpret_cast<const char*>(hash) + sizeof hash),
        std::ostream_iterator<char>(buffer)); 

  int r = close(fd);
  if (r == -1) { cerr << "close error: " << strerror(errno) << '\n';
                 return "Error"; }
  return buffer.str();
}
