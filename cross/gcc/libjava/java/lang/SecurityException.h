
// DO NOT EDIT THIS FILE - it is machine generated -*- c++ -*-

#ifndef __java_lang_SecurityException__
#define __java_lang_SecurityException__

#pragma interface

#include <java/lang/RuntimeException.h>

class java::lang::SecurityException : public ::java::lang::RuntimeException
{

public:
  SecurityException();
  SecurityException(::java::lang::String *);
  SecurityException(::java::lang::String *, ::java::lang::Throwable *);
  SecurityException(::java::lang::Throwable *);
private:
  static const jlong serialVersionUID = 6878364983674394167LL;
public:
  static ::java::lang::Class class$;
};

#endif // __java_lang_SecurityException__