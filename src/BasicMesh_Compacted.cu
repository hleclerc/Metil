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
        (char *&)elem_groups.data_[ i ].fields.data_ += off;
        for( ST j = 0; j < elem_groups.data_[ i ].fields.size_; ++j ) {
            (char *&)elem_groups.data_[ i ].fields.data_[ j ].name.data_ += off;
            (char *&)elem_groups.data_[ i ].fields.data_[ j ].data.data_ += off;
            for( ST k = 0; k < elem_groups.data_[ i ].fields.data_[ j ].data.size_; ++k ) {
                (char *&)elem_groups.data_[ i ].fields.data_[ j ].data.data_[ k ].data_ += off;
            }
        }
    }
    (char *&)node_to_elem.data_ += off;
    for( ST i = 0; i < node_to_elem.size_; ++i ) {
        (char *&)node_to_elem.data_[ i ].data_ += off;
        for( ST j = 0; j < node_to_elem.data_[ i ].size_; ++j ) {
        }
    }
    (char *&)nodal_fields.data_ += off;
    for( ST i = 0; i < nodal_fields.size_; ++i ) {
        (char *&)nodal_fields.data_[ i ].name.data_ += off;
        (char *&)nodal_fields.data_[ i ].data.data_ += off;
        for( ST j = 0; j < nodal_fields.data_[ i ].data.size_; ++j ) {
            (char *&)nodal_fields.data_[ i ].data.data_[ j ].data_ += off;
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
        (char *&)obj->elem_groups.data_[ i ].fields.data_ += off;
        for( ST j = 0; j < obj->elem_groups.data_[ i ].fields.size_; ++j ) {
            (char *&)obj->elem_groups.data_[ i ].fields.data_[ j ].name.data_ += off;
            (char *&)obj->elem_groups.data_[ i ].fields.data_[ j ].data.data_ += off;
            for( ST k = 0; k < obj->elem_groups.data_[ i ].fields.data_[ j ].data.size_; ++k ) {
                (char *&)obj->elem_groups.data_[ i ].fields.data_[ j ].data.data_[ k ].data_ += off;
            }
        }
    }
    (char *&)obj->node_to_elem.data_ += off;
    for( ST i = 0; i < obj->node_to_elem.size_; ++i ) {
        (char *&)obj->node_to_elem.data_[ i ].data_ += off;
        for( ST j = 0; j < obj->node_to_elem.data_[ i ].size_; ++j ) {
        }
    }
    (char *&)obj->nodal_fields.data_ += off;
    for( ST i = 0; i < obj->nodal_fields.size_; ++i ) {
        (char *&)obj->nodal_fields.data_[ i ].name.data_ += off;
        (char *&)obj->nodal_fields.data_[ i ].data.data_ += off;
        for( ST j = 0; j < obj->nodal_fields.data_[ i ].data.size_; ++j ) {
            (char *&)obj->nodal_fields.data_[ i ].data.data_[ j ].data_ += off;
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
        for( ST j = 0; j < elem_groups.data_[ i ].fields.size_; ++j ) {
            (char *&)elem_groups.data_[ i ].fields.data_[ j ].name.data_ += off;
            for( ST k = 0; k < elem_groups.data_[ i ].fields.data_[ j ].data.size_; ++k ) {
                (char *&)elem_groups.data_[ i ].fields.data_[ j ].data.data_[ k ].data_ += off;
            }
            (char *&)elem_groups.data_[ i ].fields.data_[ j ].data.data_ += off;
        }
        (char *&)elem_groups.data_[ i ].fields.data_ += off;
    }
    (char *&)elem_groups.data_ += off;
    for( ST i = 0; i < node_to_elem.size_; ++i ) {
        for( ST j = 0; j < node_to_elem.data_[ i ].size_; ++j ) {
        }
        (char *&)node_to_elem.data_[ i ].data_ += off;
    }
    (char *&)node_to_elem.data_ += off;
    for( ST i = 0; i < nodal_fields.size_; ++i ) {
        (char *&)nodal_fields.data_[ i ].name.data_ += off;
        for( ST j = 0; j < nodal_fields.data_[ i ].data.size_; ++j ) {
            (char *&)nodal_fields.data_[ i ].data.data_[ j ].data_ += off;
        }
        (char *&)nodal_fields.data_[ i ].data.data_ += off;
    }
    (char *&)nodal_fields.data_ += off;
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
        for( ST j = 0; j < obj->elem_groups.data_[ i ].fields.size_; ++j ) {
            (char *&)obj->elem_groups.data_[ i ].fields.data_[ j ].name.data_ += off;
            for( ST k = 0; k < obj->elem_groups.data_[ i ].fields.data_[ j ].data.size_; ++k ) {
                (char *&)obj->elem_groups.data_[ i ].fields.data_[ j ].data.data_[ k ].data_ += off;
            }
            (char *&)obj->elem_groups.data_[ i ].fields.data_[ j ].data.data_ += off;
        }
        (char *&)obj->elem_groups.data_[ i ].fields.data_ += off;
    }
    (char *&)obj->elem_groups.data_ += off;
    for( ST i = 0; i < obj->node_to_elem.size_; ++i ) {
        for( ST j = 0; j < obj->node_to_elem.data_[ i ].size_; ++j ) {
        }
        (char *&)obj->node_to_elem.data_[ i ].data_ += off;
    }
    (char *&)obj->node_to_elem.data_ += off;
    for( ST i = 0; i < obj->nodal_fields.size_; ++i ) {
        (char *&)obj->nodal_fields.data_[ i ].name.data_ += off;
        for( ST j = 0; j < obj->nodal_fields.data_[ i ].data.size_; ++j ) {
            (char *&)obj->nodal_fields.data_[ i ].data.data_[ j ].data_ += off;
        }
        (char *&)obj->nodal_fields.data_[ i ].data.data_ += off;
    }
    (char *&)obj->nodal_fields.data_ += off;
}

void BasicMesh_Compacted::update_ptr_gpu_save( ST off ) {
    BasicMesh_Compacted__update_ptr_gpu_save<<<1,1>>>( this, off );
}

void BasicMesh_Compacted::ElemGroup::update_ptr_cpu_load( ST off ) {
    (char *&)connec.data_ += off;
    for( ST i = 0; i < connec.size_; ++i ) {
        (char *&)connec.data_[ i ].data_ += off;
    }
    (char *&)fields.data_ += off;
    for( ST i = 0; i < fields.size_; ++i ) {
        (char *&)fields.data_[ i ].name.data_ += off;
        (char *&)fields.data_[ i ].data.data_ += off;
        for( ST j = 0; j < fields.data_[ i ].data.size_; ++j ) {
            (char *&)fields.data_[ i ].data.data_[ j ].data_ += off;
        }
    }
}

__global__
void BasicMesh_Compacted__ElemGroup__update_ptr_gpu_load( BasicMesh_Compacted::ElemGroup *obj, ST off ) {
    (char *&)obj->connec.data_ += off;
    for( ST i = 0; i < obj->connec.size_; ++i ) {
        (char *&)obj->connec.data_[ i ].data_ += off;
    }
    (char *&)obj->fields.data_ += off;
    for( ST i = 0; i < obj->fields.size_; ++i ) {
        (char *&)obj->fields.data_[ i ].name.data_ += off;
        (char *&)obj->fields.data_[ i ].data.data_ += off;
        for( ST j = 0; j < obj->fields.data_[ i ].data.size_; ++j ) {
            (char *&)obj->fields.data_[ i ].data.data_[ j ].data_ += off;
        }
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
    for( ST i = 0; i < fields.size_; ++i ) {
        (char *&)fields.data_[ i ].name.data_ += off;
        for( ST j = 0; j < fields.data_[ i ].data.size_; ++j ) {
            (char *&)fields.data_[ i ].data.data_[ j ].data_ += off;
        }
        (char *&)fields.data_[ i ].data.data_ += off;
    }
    (char *&)fields.data_ += off;
}

__global__
void BasicMesh_Compacted__ElemGroup__update_ptr_gpu_save( BasicMesh_Compacted::ElemGroup *obj, ST off ) {
    for( ST i = 0; i < obj->connec.size_; ++i ) {
        (char *&)obj->connec.data_[ i ].data_ += off;
    }
    (char *&)obj->connec.data_ += off;
    for( ST i = 0; i < obj->fields.size_; ++i ) {
        (char *&)obj->fields.data_[ i ].name.data_ += off;
        for( ST j = 0; j < obj->fields.data_[ i ].data.size_; ++j ) {
            (char *&)obj->fields.data_[ i ].data.data_[ j ].data_ += off;
        }
        (char *&)obj->fields.data_[ i ].data.data_ += off;
    }
    (char *&)obj->fields.data_ += off;
}

void BasicMesh_Compacted::ElemGroup::update_ptr_gpu_save( ST off ) {
    BasicMesh_Compacted__ElemGroup__update_ptr_gpu_save<<<1,1>>>( this, off );
}

void BasicMesh_Compacted::ElemGroup::Field::update_ptr_cpu_load( ST off ) {
    (char *&)name.data_ += off;
    (char *&)data.data_ += off;
    for( ST i = 0; i < data.size_; ++i ) {
        (char *&)data.data_[ i ].data_ += off;
    }
}

__global__
void BasicMesh_Compacted__ElemGroup__Field__update_ptr_gpu_load( BasicMesh_Compacted::ElemGroup::Field *obj, ST off ) {
    (char *&)obj->name.data_ += off;
    (char *&)obj->data.data_ += off;
    for( ST i = 0; i < obj->data.size_; ++i ) {
        (char *&)obj->data.data_[ i ].data_ += off;
    }
}

void BasicMesh_Compacted::ElemGroup::Field::update_ptr_gpu_load( ST off ) {
    BasicMesh_Compacted__ElemGroup__Field__update_ptr_gpu_load<<<1,1>>>( this, off );
}

void BasicMesh_Compacted::ElemGroup::Field::update_ptr_cpu_save( ST off ) {
    (char *&)name.data_ += off;
    for( ST i = 0; i < data.size_; ++i ) {
        (char *&)data.data_[ i ].data_ += off;
    }
    (char *&)data.data_ += off;
}

__global__
void BasicMesh_Compacted__ElemGroup__Field__update_ptr_gpu_save( BasicMesh_Compacted::ElemGroup::Field *obj, ST off ) {
    (char *&)obj->name.data_ += off;
    for( ST i = 0; i < obj->data.size_; ++i ) {
        (char *&)obj->data.data_[ i ].data_ += off;
    }
    (char *&)obj->data.data_ += off;
}

void BasicMesh_Compacted::ElemGroup::Field::update_ptr_gpu_save( ST off ) {
    BasicMesh_Compacted__ElemGroup__Field__update_ptr_gpu_save<<<1,1>>>( this, off );
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

void BasicMesh_Compacted::Field::update_ptr_cpu_load( ST off ) {
    (char *&)name.data_ += off;
    (char *&)data.data_ += off;
    for( ST i = 0; i < data.size_; ++i ) {
        (char *&)data.data_[ i ].data_ += off;
    }
}

__global__
void BasicMesh_Compacted__Field__update_ptr_gpu_load( BasicMesh_Compacted::Field *obj, ST off ) {
    (char *&)obj->name.data_ += off;
    (char *&)obj->data.data_ += off;
    for( ST i = 0; i < obj->data.size_; ++i ) {
        (char *&)obj->data.data_[ i ].data_ += off;
    }
}

void BasicMesh_Compacted::Field::update_ptr_gpu_load( ST off ) {
    BasicMesh_Compacted__Field__update_ptr_gpu_load<<<1,1>>>( this, off );
}

void BasicMesh_Compacted::Field::update_ptr_cpu_save( ST off ) {
    (char *&)name.data_ += off;
    for( ST i = 0; i < data.size_; ++i ) {
        (char *&)data.data_[ i ].data_ += off;
    }
    (char *&)data.data_ += off;
}

__global__
void BasicMesh_Compacted__Field__update_ptr_gpu_save( BasicMesh_Compacted::Field *obj, ST off ) {
    (char *&)obj->name.data_ += off;
    for( ST i = 0; i < obj->data.size_; ++i ) {
        (char *&)obj->data.data_[ i ].data_ += off;
    }
    (char *&)obj->data.data_ += off;
}

void BasicMesh_Compacted::Field::update_ptr_gpu_save( ST off ) {
    BasicMesh_Compacted__Field__update_ptr_gpu_save<<<1,1>>>( this, off );
}


END_METIL_NAMESPACE
