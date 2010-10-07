#ifndef STRUCTCOMPACTOR_H
#define STRUCTCOMPACTOR_H

#include "TypeInformation.h"
#include "BasicVec.h"
#include "String.h"

BEG_METIL_NAMESPACE;

/**
*/
class StructCompactor {
public:
    CANNOT_BE_DERIVED;

    struct BasicProfile {
    };

    struct Item {
        NEW_AND_DEL_COMPATIBLE_PURE_VIRTUAL;

        void set_type( const char *t ) { type = t; }
        virtual void make_decl( String &os, const String &sp = "" ) = 0;
        virtual Item *base_str() { return this; }
        virtual void make_copy( String &os, const String &sp, const String &dst, const String &src, const String &num, int par_level ) = 0;
        virtual void copy_attr( String &os, const String &sp, const String &dst, const String &src, int par_level ) = 0;
        virtual void copy_data( String &os, const String &sp, const String &dst, const String &src, int par_level ) = 0;
        virtual String alig() const = 0;
        // bool is_POD() const;

        String type;
        String name;
    };

    struct ItemSca : public Item {
        NEW_AND_DEL_COMPATIBLE;

        ItemSca( const String &type, const String &name ) {
            this->type = type;
            this->name = name;
        }

        virtual void make_decl( String &os, const String &sp = "" );
        virtual void make_copy( String &os, const String &sp, const String &dst, const String &src, const String &num, int par_level );
        virtual void copy_attr( String &os, const String &sp, const String &dst, const String &src, int par_level );
        virtual void copy_data( String &os, const String &sp, const String &dst, const String &src, int par_level );
        virtual String alig() const { return "16 * 4"; }
    };

    struct ItemStr : public Item {
        NEW_AND_DEL_COMPATIBLE;

        template<class T>
        ItemStr( const T &inst, const String &name, int par_level ) : par_level( par_level ) {
            this->name = name;
            inst.apply_bs( *this, BasicProfile() );
        }

        template<class T>
        void apply( const String &name, const T &val ) { items << StructCompactor::new_Item( val, name, par_level ); }

        virtual void make_decl( String &os, const String &sp = "" );
        virtual void make_copy( String &os, const String &sp, const String &dst, const String &src, const String &num, int par_level );
        virtual void copy_attr( String &os, const String &sp, const String &dst, const String &src, int par_level );
        virtual void copy_data( String &os, const String &sp, const String &dst, const String &src, int par_level );
        virtual String alig() const { return "sizeof( ST )"; }

        BasicVec<Item *> items;
        int par_level;
    };

    struct ItemVec : public Item {
        NEW_AND_DEL_COMPATIBLE;

        template<class T>
        ItemVec( const T &inst, const String &name, int par_level ) {
            this->data_type = StructCompactor::new_Item( inst[ 0 ], name + '[' + char( 'i' + par_level ) + ']', par_level + 1 );
            this->type << "BasicVecRef<" << data_type->type << " >";
            this->name = name;
        }

        virtual void make_decl( String &os, const String &sp = "" );
        virtual void make_copy( String &os, const String &sp, const String &dst, const String &src, const String &num, int par_level );
        virtual void copy_attr( String &os, const String &sp, const String &dst, const String &src, int par_level );
        virtual void copy_data( String &os, const String &sp, const String &dst, const String &src, int par_level );
        virtual Item *base_str() { return data_type->base_str(); }
        virtual String alig() const { return "sizeof( ST )"; }

        Item *data_type;
    };


    // variants of new_Item
    template<class T>
    static Item *new_Item( const T &inst, const String &name, int par_level ) {
        return NEW( ItemStr, inst, name, par_level );
    }

    #define NEW_ITEM( T ) \
        static Item *new_Item( const T &, const String &name, int par_level ) { return NEW( ItemSca, TypeInformation<T>::type(), name ); }
    NEW_ITEM( SI32 );
    NEW_ITEM( SI64 );
    NEW_ITEM( FP32 );
    NEW_ITEM( FP64 );
    #undef NEW_ITEM

    template<class T>
    static Item *new_Item( const BasicVec<T> &inst, const String &name, int par_level ) {
        return NEW( ItemVec, inst, name, par_level + 1 );
    }

    // constructor
    template<class T>
    StructCompactor( const T &val ) {
        item = new_Item( val, "", 0 );
    }

    // methods
    void make_files();

private:
    // void make_copy( String &os, const String &sp, const String &dst, const String &src, int par_lev );
    // void make_push( String &os, const String &sp, const String &dst, int par_lev = 0, const String &suf = "", const String &n = "n" );

    Item *item;
};


END_METIL_NAMESPACE;

#endif // STRUCTCOMPACTOR_H
