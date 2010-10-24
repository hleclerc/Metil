#ifndef LSTREAMITEM_H
#define LSTREAMITEM_H

#include "LazyObject.h"
#include "String.h"

#ifdef METIL_COMP_DIRECTIVE
#pragma src_file LStreamItem.cpp
#endif

namespace Metil {

/**
*/
class LStreamItem : public LazyObject {
public:
    LStreamItem( const LStreamItem *old_stream_item, Stream *os );
    virtual ~LStreamItem();

    virtual bool done() const;

    const LStreamItem *old_stream_item;
    Stream *os;
    mutable bool _done;
};

///
class LStreamItemFromLazyObject : public LStreamItem {
public:
    LStreamItemFromLazyObject( const LStreamItem *old_stream_item, Stream *os, const LazyObject *obj );
    virtual ~LStreamItemFromLazyObject();

    virtual void exec_node() const;

    const LazyObject *obj;
};

///
class LStreamItemString : public LStreamItem {
public:
    LStreamItemString( const LStreamItem *old_stream_item, Stream *os, const String &str );

    virtual void exec_node() const;

    String str;
};

const LStreamItem *new_LStreamItemString( const LStreamItem *old_item, Stream *os, const String &str );


}

#endif // LSTREAMITEM_H
