#ifndef BITSWAP_H
#define BITSWAP_H

#include "Number.h"

BEG_METIL_NAMESPACE;

template<int n,class S=int>
struct BitSwap {
    template<int src_bit, int dst_bit>
    __inline__ void swap_bit_pair( int &val, N<src_bit>, N<dst_bit> ) const {
        S m_src = 1 << src_bit;
        S m_dst = 1 << dst_bit;
        bool v_src = val & m_src;
        bool v_dst = val & m_dst;
        val &= ~m_src;
        val &= ~m_dst;
        val |= m_src * v_dst;
        val |= m_dst * v_src;
    }

    template<int src_bit>
    __inline__ void swap_bit_pair( S &val, N<src_bit>, N<src_bit> ) const {
    }

    template<int i,int c>
    __inline__ void swap_bits( S &val, N<i>, N<c> ) const {
        swap_bit_pair( val, N<i>(), N<n-i-1>() );
        swap_bits( val, N<i+1>(), N<c>() );
    }

    template<int c>
    __inline__ void swap_bits( S &val, N<c>, N<c> ) const {
    }

    __inline__ int operator()( S val ) const {
        S res = val;
        swap_bits( res, N<0>(), N<n/2>() );
        return res;
    }
};

END_METIL_NAMESPACE;

#endif // BITSWAP_H
