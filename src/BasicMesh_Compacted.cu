#include "BasicMesh_Compacted.h"

BEG_METIL_NAMESPACE

void BasicMesh_Compacted::update_ptr_cpu_load( ST off ) {
    (char *&)pos_nodes.data_ += off;
    for( ST i = 0; i < pos_nodes.size_; ++i ) {
        (char *&)pos_nodes.data_[ i ].data_ += off;
    }
    (char *&)elem_groups.data_ += off;
    for( ST i = 0; i < elem_groups.size_; ++i ) {
        (char *&)elem_groups.data_[ i ].connec.data_ += off;
        for( ST j = 0; j < elem_groups.data_[ i ].connec.size_; ++j ) {
            (char *&)elem_groups.data_[ i ].connec.data_[ j ].data_ += off;
        }
    }
    (char *&)node_to_elem.data_ += off;
    for( ST i = 0; i < node_to_elem.size_; ++i ) {
        (char *&)node_to_elem.data_[ i ].data_ += off;
        for( ST j = 0; j < node_to_elem.data_[ i ].size_; ++j ) {
        }
    }
}

__global__
void BasicMesh_Compacted__update_ptr_gpu_load( BasicMesh_Compacted *obj, ST off ) {
    (char *&)obj->pos_nodes.data_ += off;
    for( ST i = 0; i < obj->pos_nodes.size_; ++i ) {
        (char *&)obj->pos_nodes.data_[ i ].data_ += off;
    }
    (char *&)obj->elem_groups.data_ += off;
    for( ST i = 0; i < obj->elem_groups.size_; ++i ) {
        (char *&)obj->elem_groups.data_[ i ].connec.data_ += off;
        for( ST j = 0; j < obj->elem_groups.data_[ i ].connec.size_; ++j ) {
            (char *&)obj->elem_groups.data_[ i ].connec.data_[ j ].data_ += off;
        }
    }
    (char *&)obj->node_to_elem.data_ += off;
    for( ST i = 0; i < obj->node_to_elem.size_; ++i ) {
        (char *&)obj->node_to_elem.data_[ i ].data_ += off;
        for( ST j = 0; j < obj->node_to_elem.data_[ i ].size_; ++j ) {
        }
    }
}

void BasicMesh_Compacted::update_ptr_gpu_load( ST off ) {
    BasicMesh_Compacted__update_ptr_gpu_load<<<1,1>>>( this, off );
}

void BasicMesh_Compacted::update_ptr_cpu_save( ST off ) {
    for( ST i = 0; i < pos_nodes.size_; ++i ) {
        (char *&)pos_nodes.data_[ i ].data_ += off;
    }
    (char *&)pos_nodes.data_ += off;
    for( ST i = 0; i < elem_groups.size_; ++i ) {
        for( ST j = 0; j < elem_groups.data_[ i ].connec.size_; ++j ) {
            (char *&)elem_groups.data_[ i ].connec.data_[ j ].data_ += off;
        }
        (char *&)elem_groups.data_[ i ].connec.data_ += off;
    }
    (char *&)elem_groups.data_ += off;
    for( ST i = 0; i < node_to_elem.size_; ++i ) {
        for( ST j = 0; j < node_to_elem.data_[ i ].size_; ++j ) {
        }
        (char *&)node_to_elem.data_[ i ].data_ += off;
    }
    (char *&)node_to_elem.data_ += off;
}

__global__
void BasicMesh_Compacted__update_ptr_gpu_save( BasicMesh_Compacted *obj, ST off ) {
    for( ST i = 0; i < obj->pos_nodes.size_; ++i ) {
        (char *&)obj->pos_nodes.data_[ i ].data_ += off;
    }
    (char *&)obj->pos_nodes.data_ += off;
    for( ST i = 0; i < obj->elem_groups.size_; ++i ) {
        for( ST j = 0; j < obj->elem_groups.data_[ i ].connec.size_; ++j ) {
            (char *&)obj->elem_groups.data_[ i ].connec.data_[ j ].data_ += off;
        }
        (char *&)obj->elem_groups.data_[ i ].connec.data_ += off;
    }
    (char *&)obj->elem_groups.data_ += off;
    for( ST i = 0; i < obj->node_to_elem.size_; ++i ) {
        for( ST j = 0; j < obj->node_to_elem.data_[ i ].size_; ++j ) {
        }
        (char *&)obj->node_to_elem.data_[ i ].data_ += off;
    }
    (char *&)obj->node_to_elem.data_ += off;
}

void BasicMesh_Compacted::update_ptr_gpu_save( ST off ) {
    BasicMesh_Compacted__update_ptr_gpu_save<<<1,1>>>( this, off );
}

void BasicMesh_Compacted::ElemGroup::update_ptr_cpu_load( ST off ) {
    (char *&)connec.data_ += off;
    for( ST i = 0; i < connec.size_; ++i ) {
        (char *&)connec.data_[ i ].data_ += off;
    }
}

__global__
void BasicMesh_Compacted__ElemGroup__update_ptr_gpu_load( BasicMesh_Compacted::ElemGroup *obj, ST off ) {
    (char *&)obj->connec.data_ += off;
    for( ST i = 0; i < obj->connec.size_; ++i ) {
        (char *&)obj->connec.data_[ i ].data_ += off;
    }
}

void BasicMesh_Compacted::ElemGroup::update_ptr_gpu_load( ST off ) {
    BasicMesh_Compacted__ElemGroup__update_ptr_gpu_load<<<1,1>>>( this, off );
}

void BasicMesh_Compacted::ElemGroup::update_ptr_cpu_save( ST off ) {
    for( ST i = 0; i < connec.size_; ++i ) {
        (char *&)connec.data_[ i ].data_ += off;
    }
    (char *&)connec.data_ += off;
}

__global__
void BasicMesh_Compacted__ElemGroup__update_ptr_gpu_save( BasicMesh_Compacted::ElemGroup *obj, ST off ) {
    for( ST i = 0; i < obj->connec.size_; ++i ) {
        (char *&)obj->connec.data_[ i ].data_ += off;
    }
    (char *&)obj->connec.data_ += off;
}

void BasicMesh_Compacted::ElemGroup::update_ptr_gpu_save( ST off ) {
    BasicMesh_Compacted__ElemGroup__update_ptr_gpu_save<<<1,1>>>( this, off );
}

void BasicMesh_Compacted::NodeToElemItem::update_ptr_cpu_load( ST off ) {
}

__global__
void BasicMesh_Compacted__NodeToElemItem__update_ptr_gpu_load( BasicMesh_Compacted::NodeToElemItem *obj, ST off ) {
}

void BasicMesh_Compacted::NodeToElemItem::update_ptr_gpu_load( ST off ) {
    BasicMesh_Compacted__NodeToElemItem__update_ptr_gpu_load<<<1,1>>>( this, off );
}

void BasicMesh_Compacted::NodeToElemItem::update_ptr_cpu_save( ST off ) {
}

__global__
void BasicMesh_Compacted__NodeToElemItem__update_ptr_gpu_save( BasicMesh_Compacted::NodeToElemItem *obj, ST off ) {
}

void BasicMesh_Compacted::NodeToElemItem::update_ptr_gpu_save( ST off ) {
    BasicMesh_Compacted__NodeToElemItem__update_ptr_gpu_save<<<1,1>>>( this, off );
}


END_METIL_NAMESPACE
