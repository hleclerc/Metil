#ifndef BasicMesh_Compacted_H
#define BasicMesh_Compacted_H

#include <MemoryDriver.h>
#include <BasicVecRef.h>

BEG_METIL_NAMESPACE

struct BasicMesh_Compacted {
    typedef void HasOffPtr;
    struct ElemGroup {
        typedef void HasOffPtr;
        template<class T> static ElemGroup *copy( MemoryDriver &md, const T *src, ST num = 1 ) {
            ElemGroup *dst, *loc;
            ST rese = num * sizeof( ElemGroup );
            md.beg_local_data( &dst, &loc, rese, sizeof( ST ) );
            for( ST i = 0; i < num; ++i ) {
                loc[ i ].connec.size_ = src[ i ].connec.size();
                loc[ i ].connec.rese_ = src[ i ].connec.size();
                BasicVecRef<SI32 > *loc_0;
                ST rese_0 = src[ i ].connec.size() * sizeof( BasicVecRef<SI32 > );
                md.beg_local_data( &loc[ i ].connec.data_, &loc_0, rese_0, sizeof( ST ) );
                for( ST j = 0; j < src[ i ].connec.size(); ++j ) {
                    loc_0[ j ].size_ = src[ i ].connec[ j ].size();
                    loc_0[ j ].rese_ = src[ i ].connec[ j ].size();
                    md.copy( &loc_0[ j ].data_, src[ i ].connec[ j ].ptr(), src[ i ].connec[ j ].size() * sizeof( SI32 ), 16 * 4 );
                }
                md.end_local_data( loc[ i ].connec.data_, loc_0, rese_0 );
                loc[ i ].elem_id = src[ i ].elem_id;
            }
            md.end_local_data( dst, loc, rese );
            return dst;
        }
        void update_ptr_cpu_load( ST off );
        void update_ptr_cpu_save( ST off );
        void update_ptr_gpu_load( ST off );
        void update_ptr_gpu_save( ST off );

        BasicVecRef<BasicVecRef<SI32 > > connec;
        SI32 elem_id;
    };
    struct NodeToElemItem {
        typedef void HasOffPtr;
        template<class T> static NodeToElemItem *copy( MemoryDriver &md, const T *src, ST num = 1 ) {
            NodeToElemItem *dst, *loc;
            ST rese = num * sizeof( NodeToElemItem );
            md.beg_local_data( &dst, &loc, rese, sizeof( ST ) );
            for( ST i = 0; i < num; ++i ) {
                loc[ i ].num_group = src[ i ].num_group;
                loc[ i ].num_elem = src[ i ].num_elem;
            }
            md.end_local_data( dst, loc, rese );
            return dst;
        }
        void update_ptr_cpu_load( ST off );
        void update_ptr_cpu_save( ST off );
        void update_ptr_gpu_load( ST off );
        void update_ptr_gpu_save( ST off );

        SI32 num_group;
        SI32 num_elem;
    };
    template<class T> static BasicMesh_Compacted *copy( MemoryDriver &md, const T *src, ST num = 1 ) {
        BasicMesh_Compacted *dst, *loc;
        ST rese = num * sizeof( BasicMesh_Compacted );
        md.beg_local_data( &dst, &loc, rese, sizeof( ST ) );
        for( ST i = 0; i < num; ++i ) {
            loc[ i ].pos_nodes.size_ = src[ i ].pos_nodes.size();
            loc[ i ].pos_nodes.rese_ = src[ i ].pos_nodes.size();
            BasicVecRef<FP32 > *loc_0;
            ST rese_0 = src[ i ].pos_nodes.size() * sizeof( BasicVecRef<FP32 > );
            md.beg_local_data( &loc[ i ].pos_nodes.data_, &loc_0, rese_0, sizeof( ST ) );
            for( ST j = 0; j < src[ i ].pos_nodes.size(); ++j ) {
                loc_0[ j ].size_ = src[ i ].pos_nodes[ j ].size();
                loc_0[ j ].rese_ = src[ i ].pos_nodes[ j ].size();
                md.copy( &loc_0[ j ].data_, src[ i ].pos_nodes[ j ].ptr(), src[ i ].pos_nodes[ j ].size() * sizeof( FP32 ), 16 * 4 );
            }
            md.end_local_data( loc[ i ].pos_nodes.data_, loc_0, rese_0 );
            loc[ i ].elem_groups.size_ = src[ i ].elem_groups.size();
            loc[ i ].elem_groups.rese_ = src[ i ].elem_groups.size();
            loc[ i ].elem_groups.data_ = ElemGroup::copy( md, src[ i ].elem_groups.ptr(), src[ i ].elem_groups.size() );
            loc[ i ].node_to_elem.size_ = src[ i ].node_to_elem.size();
            loc[ i ].node_to_elem.rese_ = src[ i ].node_to_elem.size();
            BasicVecRef<NodeToElemItem > *loc_1;
            ST rese_1 = src[ i ].node_to_elem.size() * sizeof( BasicVecRef<NodeToElemItem > );
            md.beg_local_data( &loc[ i ].node_to_elem.data_, &loc_1, rese_1, sizeof( ST ) );
            for( ST j = 0; j < src[ i ].node_to_elem.size(); ++j ) {
                loc_1[ j ].size_ = src[ i ].node_to_elem[ j ].size();
                loc_1[ j ].rese_ = src[ i ].node_to_elem[ j ].size();
                loc_1[ j ].data_ = NodeToElemItem::copy( md, src[ i ].node_to_elem[ j ].ptr(), src[ i ].node_to_elem[ j ].size() );
            }
            md.end_local_data( loc[ i ].node_to_elem.data_, loc_1, rese_1 );
        }
        md.end_local_data( dst, loc, rese );
        return dst;
    }
    void update_ptr_cpu_load( ST off );
    void update_ptr_cpu_save( ST off );
    void update_ptr_gpu_load( ST off );
    void update_ptr_gpu_save( ST off );

    BasicVecRef<BasicVecRef<FP32 > > pos_nodes;
    BasicVecRef<ElemGroup > elem_groups;
    BasicVecRef<BasicVecRef<NodeToElemItem > > node_to_elem;
};

END_METIL_NAMESPACE

#endif // BasicMesh_Compacted_H
