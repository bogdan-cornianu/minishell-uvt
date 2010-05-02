#include <config.h>
#include <algorithm>
#include <errno.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string.h>
#include <bstream.hh>
#include <gunzip.hh>
#include <log.hh>


int returnCode = 0;

namespace 
	
{
  const int FILEBUFSIZE = 4096;
  const int BUFSIZE = 4096;

  struct ToStdout : Gunzip::IO {
    byte buf[BUFSIZE];
    virtual ~ToStdout() { }
    virtual void gunzip_deleted() { }
    virtual void gunzip_data(Gunzip*, byte* decompressed,
                             unsigned size) {
      cout.write(reinterpret_cast<char*>(decompressed), size);
    }
    virtual void gunzip_needOut(Gunzip* self) {
      self->setOut(buf, BUFSIZE);
    }
    virtual void gunzip_succeeded() { }
    virtual void gunzip_failed(string* message) {
      cerr << *message << endl;
    }
  };

  const char* const hexDigits = "0123456789abcdef";
  void escapedChar(string* o, byte c) {
    switch (c) {
    case 0: *o += "\\0"; break;
    case '\n': *o += "\\n"; break;
    case '\t': *o += "\\t"; break;
    case '"': case '\\': *o += '\\'; *o += c; break;
    default:
      if (c >= ' ' && c <= '~') {
        *o += c;
      } else {
        *o += "\\x";
        *o += hexDigits[unsigned(c) >> 4];
        *o += hexDigits[unsigned(c) & 0xfU];
      }
    }
  }

  inline string escapedString(const string& s) {
    string result;
    for (unsigned i = 0; i < s.length(); ++i)
      escapedChar(&result, s[i]);
    return result;
  }

  inline string escapedString(const byte* s, unsigned ssize) {
    string result;
    for (unsigned i = 0; i < ssize; ++i)
      escapedChar(&result, s[i]);
    return result;
  }

  struct ToString : Gunzip::IO {
    unsigned bufsize;
    byte* buf;
    ToString(unsigned bufs) : bufsize(bufs) {
      buf = new byte[bufs + 1];
      buf[bufs] = 0x7fU;
    }
    virtual ~ToString() { delete[] buf; }
    virtual void gunzip_deleted() { }
    virtual void gunzip_data(Gunzip*, byte* decompressed,
                             unsigned size) {
      if (buf[bufsize] != 0x7fU) o += "[BUFFER OVERFLOW]";
      o.append(reinterpret_cast<const char*>(decompressed), size);
    }
    virtual void gunzip_needOut(Gunzip* self) {
      self->setOut(buf, bufsize);
    }
    virtual void gunzip_succeeded() { }
    virtual void gunzip_failed(string* message) {
      o += '[';
      o += *message;
      o += ']';
    }
    string o;
  };

  void decompressFile(const char* name) {
    bifstream f(name);
    byte buf[FILEBUFSIZE];
    ToStdout out;
    Gunzip decompressor(&out);

    while (f) {
      readBytes(f, buf, FILEBUFSIZE);
      unsigned n = f.gcount();
      decompressor.inject(buf, n);
    }
    if (!f.eof()) {
      cerr << strerror(errno) << endl;
    }
  }

}
 // namespace

int main(int argc, char* argv[]) 
	
{

  if (argc == 3 && strcmp("decompress", argv[1]) == 0) {
    decompressFile(argv[2]);
    exit(0);
  }

  /* Special case, nothing to do with testing gunzip: Convert stdin to
     C-style string. */
  if (argc == 2 && strcmp("tohex", argv[1]) == 0) {
    string o;
    int len = 0;
    while (cin) {
      byte c;
      cin.read(reinterpret_cast<char*>(&c), 1);
      if (cin.gcount() == 0) continue;
      escapedChar(&o, c);
      ++len;
    }
    cout << len << ", \"" << o << '"' << endl;
    return 0;
  } else if (argc == 2) {
    Logger::scanOptions(argv[1], argv[0]);
  }

  msg("Usage: `gunzip decompress FILENAME.gz' to decompress to stdout\n");
  
}

