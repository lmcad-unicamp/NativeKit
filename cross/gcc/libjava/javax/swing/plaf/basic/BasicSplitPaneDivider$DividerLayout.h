
// DO NOT EDIT THIS FILE - it is machine generated -*- c++ -*-

#ifndef __javax_swing_plaf_basic_BasicSplitPaneDivider$DividerLayout__
#define __javax_swing_plaf_basic_BasicSplitPaneDivider$DividerLayout__

#pragma interface

#include <java/lang/Object.h>
extern "Java"
{
  namespace java
  {
    namespace awt
    {
        class Component;
        class Container;
        class Dimension;
    }
  }
  namespace javax
  {
    namespace swing
    {
      namespace plaf
      {
        namespace basic
        {
            class BasicSplitPaneDivider;
            class BasicSplitPaneDivider$DividerLayout;
        }
      }
    }
  }
}

class javax::swing::plaf::basic::BasicSplitPaneDivider$DividerLayout : public ::java::lang::Object
{

public: // actually protected
  BasicSplitPaneDivider$DividerLayout(::javax::swing::plaf::basic::BasicSplitPaneDivider *);
public:
  virtual void addLayoutComponent(::java::lang::String *, ::java::awt::Component *);
  virtual void layoutContainer(::java::awt::Container *);
  virtual ::java::awt::Dimension * minimumLayoutSize(::java::awt::Container *);
  virtual ::java::awt::Dimension * preferredLayoutSize(::java::awt::Container *);
  virtual void removeLayoutComponent(::java::awt::Component *);
public: // actually package-private
  ::javax::swing::plaf::basic::BasicSplitPaneDivider * __attribute__((aligned(__alignof__( ::java::lang::Object)))) this$0;
public:
  static ::java::lang::Class class$;
};

#endif // __javax_swing_plaf_basic_BasicSplitPaneDivider$DividerLayout__