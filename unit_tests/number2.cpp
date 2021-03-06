#include "UnitTest.h"
#include "String.h"
#include "Val.h"

using namespace Metil;

int main() {
//    UNIT_TEST_CMP_STRING(  minus_one , -1 );
//    UNIT_TEST_CMP_STRING(  ( ( Val( 2 )  +  Val( 27 ) ) -  ( Val( 31 )  -  Val( 2 ) )), 0 );
//    UNIT_TEST_CMP_STRING(  ( ( zero  *  one ) +  ( minus_one  /  one )), -1 );
//    UNIT_TEST_CMP_STRING(  ( ( minus_one  +  Val( 31 ) ) /  ( Val( 26 )  *  Val( 8 ) )), 15/104 );
//    UNIT_TEST_CMP_STRING(  ( Val( 7 )  -  ( Val( 7 )  /  Val( 21 ) )), 20/3 );
//    UNIT_TEST_CMP_STRING(  zero , 0 );
//    UNIT_TEST_CMP_STRING(  ( ( zero  -  minus_one ) *  ( minus_one  *  Val( 7 ) )), -7 );
//    UNIT_TEST_CMP_STRING(  ( ( minus_one  /  Val( 20 ) ) *  Val( 1 ) ), -1/20 );
//    UNIT_TEST_CMP_STRING(  ( ( minus_one  /  Val( 7 ) ) *  ( minus_one  +  zero )), 1/7 );
//    UNIT_TEST_CMP_STRING(  ( ( Val( 27 )  -  Val( 4 ) ) /  ( Val( 8 )  -  Val( 0 ) )), 23/8 );
//    UNIT_TEST_CMP_STRING(  ( one  +  ( Val( 12 )  -  zero )), 13 );
//    UNIT_TEST_CMP_STRING(  ( ( Val( 3 )  +  zero ) *  Val( 28 ) ), 84 );
//    UNIT_TEST_CMP_STRING(  Val( 7 ) , 7 );
//    UNIT_TEST_CMP_STRING(  one , 1 );
//    UNIT_TEST_CMP_STRING(  ( ( Val( 5 )  /  Val( 13 ) ) *  ( one  +  Val( 29 ) )), 150/13 );
//    UNIT_TEST_CMP_STRING(  ( ( Val( 24 )  -  one ) *  ( minus_one  /  Val( 24 ) )), -23/24 );
//    UNIT_TEST_CMP_STRING(  ( one  *  one ), 1 );
//    UNIT_TEST_CMP_STRING(  ( zero  *  ( Val( 9 )  /  Val( 12 ) )), 0 );
//    UNIT_TEST_CMP_STRING(  ( ( Val( 15 )  /  Val( 28 ) ) *  ( Val( 7 )  -  Val( 3 ) )), 15/7 );

//    UNIT_TEST_CMP_STRING(  ( ( Val( 30 )  *  ( Val( 6 )  -  Val( 14 ) )) /  ( ( Val( 4 )  *  Val( 29 ) ) *  ( Val( 17 )  /  one ))), -60/493 );
//    UNIT_TEST_CMP_STRING(  ( ( ( Val( 13 )  *  minus_one ) -  ( Val( 31 )  /  Val( 18 ) )) +  Val( 22 ) ), 131/18 );
//    UNIT_TEST_CMP_STRING(  ( ( ( Val( 29 )  -  minus_one ) /  Val( 7 ) ) +  Val( 4 ) ), 58/7 );
//    UNIT_TEST_CMP_STRING(  Val( 16 ) , 16 );
//    UNIT_TEST_CMP_STRING(  ( one  *  ( ( Val( 2 )  /  Val( 20 ) ) *  Val( 13 ) )), 13/10 );
//    UNIT_TEST_CMP_STRING(  ( ( ( Val( 0 )  -  Val( 22 ) ) +  ( Val( 11 )  +  Val( 16 ) )) *  Val( 31 ) ), 155 );
//    UNIT_TEST_CMP_STRING(  ( ( ( Val( 12 )  *  Val( 28 ) ) *  ( one  /  Val( 3 ) )) /  Val( 1 ) ), 112 );
//    UNIT_TEST_CMP_STRING(  ( ( zero  +  ( Val( 12 )  *  Val( 25 ) )) /  ( ( minus_one  +  one ) -  ( Val( 14 )  -  Val( 15 ) ))), 300 );
//    UNIT_TEST_CMP_STRING(  ( ( ( Val( 7 )  -  Val( 2 ) ) +  ( one  *  Val( 23 ) )) *  ( ( Val( 25 )  /  Val( 19 ) ) /  ( Val( 14 )  /  one ))), 50/19 );
//    UNIT_TEST_CMP_STRING(  ( Val( 1 )  *  ( ( Val( 1 )  /  Val( 18 ) ) /  ( one  /  Val( 2 ) ))), 1/9 );
//    UNIT_TEST_CMP_STRING(  Val( 23 ) , 23 );
//    UNIT_TEST_CMP_STRING(  ( ( ( Val( 13 )  +  minus_one ) -  Val( 17 ) ) -  ( Val( 4 )  *  ( Val( 13 )  +  minus_one ))), -53 );
//    UNIT_TEST_CMP_STRING(  ( ( ( Val( 0 )  +  minus_one ) +  zero ) -  ( ( Val( 26 )  -  Val( 21 ) ) /  Val( 18 ) )), -23/18 );
//    UNIT_TEST_CMP_STRING(  ( ( ( Val( 9 )  +  one ) -  ( Val( 21 )  -  Val( 19 ) )) +  ( ( Val( 2 )  /  zero ) /  Val( 25 ) )), nan );
//    UNIT_TEST_CMP_STRING(  ( ( ( Val( 22 )  +  one ) +  ( zero  +  Val( 15 ) )) -  Val( 1 ) ), 37 );
//    UNIT_TEST_CMP_STRING(  ( ( ( one  +  one ) -  ( Val( 9 )  /  Val( 19 ) )) +  ( ( Val( 20 )  +  zero ) +  Val( 2 ) )), 447/19 );
//    UNIT_TEST_CMP_STRING(  ( Val( 27 )  +  ( ( Val( 26 )  -  zero ) -  minus_one )), 54 );
    
//    UNIT_TEST_CMP_STRING(  ( ( Val( 11 )  +  ( one  *  Val( 5 ) )) *  ( ( Val( 20 )  *  Val( 19 ) ) /  ( one  *  Val( 31 ) ))), 6080/31 );
//    UNIT_TEST_CMP_STRING(  ( ( Val( 21 )  -  ( minus_one  +  zero )) +  ( ( minus_one  -  minus_one ) /  ( Val( 4 )  *  one ))), 22 );
//    UNIT_TEST_CMP_STRING(  ( Val( 14 )  *  ( ( Val( 28 )  +  minus_one ) /  ( Val( 18 )  /  minus_one ))), -21 );
//    UNIT_TEST_CMP_STRING(  ( one  -  minus_one ), 2 );
//    UNIT_TEST_CMP_STRING(  ( ( ( zero  +  zero ) +  ( Val( 30 )  /  Val( 17 ) )) +  ( ( Val( 7 )  *  Val( 0 ) ) /  ( Val( 22 )  *  Val( 25 ) ))), 30/17 );
//    UNIT_TEST_CMP_STRING(  ( Val( 8 )  +  ( ( Val( 10 )  -  Val( 4 ) ) /  ( Val( 17 )  +  minus_one ))), 67/8 );
//    UNIT_TEST_CMP_STRING(  ( ( ( one  /  Val( 25 ) ) /  ( Val( 11 )  /  one )) +  ( ( Val( 29 )  /  Val( 23 ) ) +  Val( 20 ) )), 134498/6325 );
//    UNIT_TEST_CMP_STRING(  ( ( Val( 22 )  -  ( Val( 12 )  *  minus_one )) /  ( Val( 7 )  /  ( Val( 2 )  +  Val( 4 ) ))), 204/7 );
//    UNIT_TEST_CMP_STRING(  ( ( ( Val( 27 )  +  Val( 21 ) ) -  ( Val( 15 )  +  minus_one )) *  ( ( minus_one  +  Val( 10 ) ) /  ( Val( 24 )  *  Val( 2 ) ))), 51/8 );
//    UNIT_TEST_CMP_STRING(  ( Val( 22 )  /  ( ( Val( 1 )  +  zero ) -  ( Val( 28 )  +  one ))), -11/14 );
//    UNIT_TEST_CMP_STRING(  ( ( ( Val( 10 )  -  Val( 7 ) ) /  Val( 16 ) ) *  ( ( Val( 0 )  -  Val( 9 ) ) /  ( Val( 30 )  /  Val( 31 ) ))), -279/160 );
//    UNIT_TEST_CMP_STRING(  ( ( ( one  +  Val( 27 ) ) +  ( Val( 11 )  +  Val( 12 ) )) /  ( ( Val( 26 )  +  minus_one ) +  ( Val( 12 )  *  Val( 31 ) ))), 51/397 );
//    UNIT_TEST_CMP_STRING(  ( ( ( Val( 2 )  -  Val( 23 ) ) *  ( Val( 8 )  /  Val( 4 ) )) /  ( Val( 19 )  -  ( Val( 5 )  +  zero ))), -3 );
//    UNIT_TEST_CMP_STRING(  ( ( ( one  +  Val( 4 ) ) /  ( Val( 17 )  *  zero )) +  ( ( Val( 23 )  -  Val( 25 ) ) *  ( minus_one  +  minus_one ))), nan );
//    UNIT_TEST_CMP_STRING(  ( zero  *  ( Val( 8 )  -  ( Val( 3 )  /  Val( 23 ) ))), 0 );
//    UNIT_TEST_CMP_STRING(  ( ( ( one  -  Val( 15 ) ) *  ( Val( 15 )  -  zero )) -  ( ( Val( 12 )  +  Val( 15 ) ) /  ( Val( 9 )  -  Val( 31 ) ))), -4593/22 );
//    UNIT_TEST_CMP_STRING(  ( Val( 31 )  *  ( ( Val( 6 )  -  Val( 25 ) ) *  ( Val( 12 )  *  Val( 3 ) ))), -21204 );
//    UNIT_TEST_CMP_STRING(  ( ( ( zero  /  one ) *  ( Val( 20 )  +  Val( 7 ) )) +  ( ( Val( 24 )  -  Val( 10 ) ) -  ( minus_one  -  minus_one ))), 14 );
    
//        UNIT_TEST_CMP_STRING(  ( ( ( ( Val( 3 )  +  Val( 8 ) ) -  ( Val( 22 )  +  Val( 3 ) )) *  minus_one ) *  ( ( ( Val( 3 )  -  Val( 10 ) ) *  ( Val( 8 )  -  minus_one )) +  ( ( Val( 24 )  *  one ) +  ( zero  /  Val( 0 ) )))), nan );
//    UNIT_TEST_CMP_STRING(  ( Val( 17 )  -  ( ( zero  *  Val( 14 ) ) *  ( zero  -  ( Val( 0 )  /  Val( 14 ) )))), 17 );
//    UNIT_TEST_CMP_STRING(  ( ( ( ( Val( 3 )  +  Val( 31 ) ) *  ( one  /  Val( 6 ) )) *  ( ( Val( 20 )  -  minus_one ) -  ( Val( 4 )  *  Val( 16 ) ))) -  ( Val( 18 )  -  Val( 0 ) )), -785/3 );
//    UNIT_TEST_CMP_STRING(  ( ( ( ( one  *  Val( 3 ) ) -  ( Val( 27 )  *  Val( 8 ) )) /  ( zero  +  ( Val( 27 )  +  Val( 19 ) ))) /  ( ( ( Val( 1 )  /  Val( 11 ) ) *  ( one  -  Val( 30 ) )) +  ( ( one  -  zero ) -  ( Val( 25 )  /  minus_one )))), -2343/11822 );
//    UNIT_TEST_CMP_STRING(  zero , 0 );
//    UNIT_TEST_CMP_STRING(  ( Val( 23 )  +  minus_one ), 22 );
//    UNIT_TEST_CMP_STRING(  ( ( ( ( one  /  Val( 4 ) ) -  Val( 15 ) ) /  ( ( Val( 27 )  *  Val( 20 ) ) -  ( Val( 15 )  *  Val( 7 ) ))) /  minus_one ), 59/1740 );
//    UNIT_TEST_CMP_STRING(  ( ( ( Val( 28 )  -  ( Val( 9 )  +  Val( 20 ) )) +  ( Val( 26 )  *  ( Val( 29 )  -  minus_one ))) +  ( Val( 26 )  *  Val( 16 ) )), 1195 );
//    UNIT_TEST_CMP_STRING(  ( ( ( ( zero  +  Val( 7 ) ) -  ( minus_one  /  Val( 24 ) )) *  ( ( Val( 23 )  *  Val( 31 ) ) +  ( Val( 10 )  -  zero ))) -  one ), 40721/8 );
//    UNIT_TEST_CMP_STRING(  ( ( ( ( minus_one  *  Val( 31 ) ) /  ( Val( 31 )  -  Val( 6 ) )) +  ( ( Val( 28 )  /  Val( 22 ) ) +  ( Val( 22 )  +  minus_one ))) +  ( one  -  ( Val( 16 )  +  ( Val( 25 )  *  Val( 11 ) )))), -73966/275 );
//    UNIT_TEST_CMP_STRING(  ( ( Val( 27 )  +  Val( 27 ) ) -  Val( 21 ) ), 33 );
//    UNIT_TEST_CMP_STRING(  ( ( ( ( Val( 9 )  -  Val( 15 ) ) /  ( minus_one  +  Val( 28 ) )) *  ( ( Val( 1 )  +  Val( 7 ) ) +  ( zero  /  one ))) -  ( ( Val( 5 )  /  ( Val( 28 )  /  Val( 6 ) )) *  ( ( minus_one  +  Val( 27 ) ) +  ( Val( 19 )  -  Val( 10 ) )))), -707/18 );
//    UNIT_TEST_CMP_STRING(  ( ( Val( 0 )  /  ( ( Val( 21 )  -  Val( 1 ) ) /  ( Val( 17 )  /  Val( 0 ) ))) +  ( ( ( Val( 14 )  /  zero ) +  ( Val( 20 )  +  Val( 20 ) )) -  ( ( Val( 3 )  *  Val( 4 ) ) /  ( minus_one  /  Val( 20 ) )))), nan );
//    UNIT_TEST_CMP_STRING(  ( ( ( ( Val( 25 )  -  Val( 1 ) ) -  Val( 4 ) ) +  ( ( Val( 18 )  /  Val( 24 ) ) *  ( zero  -  Val( 10 ) ))) /  ( ( ( zero  -  Val( 7 ) ) *  ( Val( 20 )  +  Val( 30 ) )) /  ( Val( 11 )  -  ( one  *  Val( 17 ) )))), 3/14 );
//    UNIT_TEST_CMP_STRING(  ( ( ( ( Val( 25 )  +  one ) +  ( minus_one  -  Val( 7 ) )) *  ( ( Val( 1 )  /  Val( 6 ) ) +  ( one  /  Val( 19 ) ))) /  Val( 6 ) ), 25/38 );
//    UNIT_TEST_CMP_STRING(  ( ( ( ( Val( 21 )  /  minus_one ) /  ( Val( 31 )  *  Val( 16 ) )) *  ( ( one  *  Val( 27 ) ) -  ( minus_one  /  one ))) *  ( ( ( Val( 0 )  /  Val( 13 ) ) -  ( zero  +  Val( 26 ) )) +  ( Val( 15 )  -  ( zero  +  minus_one )))), 735/62 );
//    UNIT_TEST_CMP_STRING(  ( ( ( zero  /  ( one  +  Val( 30 ) )) *  ( ( Val( 20 )  -  Val( 26 ) ) /  ( Val( 20 )  -  Val( 24 ) ))) *  ( ( ( Val( 22 )  /  Val( 21 ) ) *  ( one  -  Val( 16 ) )) -  ( ( Val( 23 )  -  Val( 22 ) ) -  ( zero  /  zero )))), nan );
//    UNIT_TEST_CMP_STRING(  ( ( Val( 11 )  *  ( ( Val( 27 )  +  Val( 12 ) ) *  Val( 20 ) )) +  ( ( ( one  *  Val( 11 ) ) *  ( Val( 30 )  /  Val( 11 ) )) *  ( ( minus_one  *  Val( 5 ) ) -  ( Val( 16 )  +  zero )))), 7950 );
//    UNIT_TEST_CMP_STRING(  ( ( ( ( Val( 3 )  /  Val( 14 ) ) /  ( one  +  one )) +  ( ( minus_one  -  minus_one ) /  one )) +  ( Val( 20 )  +  ( ( minus_one  *  minus_one ) +  ( minus_one  *  Val( 5 ) )))), 451/28 );
    
//    UNIT_TEST_CMP_STRING(  ( ( ( ( Val( 13 )  *  minus_one ) *  Val( 13 ) ) /  ( ( Val( 7 )  /  Val( 1 ) ) *  ( Val( 6 )  *  Val( 6 ) ))) *  ( ( minus_one  -  ( Val( 12 )  /  Val( 19 ) )) -  ( ( zero  +  Val( 9 ) ) *  ( Val( 27 )  *  minus_one )))), -387517/2394 );
//    UNIT_TEST_CMP_STRING(  ( ( ( ( Val( 30 )  /  Val( 20 ) ) /  Val( 19 ) ) *  ( ( Val( 12 )  *  Val( 28 ) ) +  zero )) -  ( Val( 15 )  -  ( ( Val( 25 )  /  Val( 20 ) ) /  ( one  /  Val( 30 ) )))), 1863/38 );
//    UNIT_TEST_CMP_STRING(  ( ( ( ( Val( 19 )  +  Val( 12 ) ) *  ( Val( 6 )  +  Val( 6 ) )) /  Val( 19 ) ) +  Val( 25 ) ), 847/19 );
//    UNIT_TEST_CMP_STRING(  ( Val( 24 )  +  ( Val( 18 )  *  ( ( Val( 8 )  *  Val( 28 ) ) /  ( one  -  zero )))), 4056 );
//    UNIT_TEST_CMP_STRING(  ( ( ( ( minus_one  +  minus_one ) -  ( Val( 30 )  +  Val( 14 ) )) -  ( one  *  ( one  +  Val( 18 ) ))) -  ( ( ( Val( 8 )  +  Val( 6 ) ) *  ( Val( 0 )  +  Val( 23 ) )) *  ( ( Val( 8 )  *  Val( 31 ) ) -  Val( 27 ) ))), -71227 );
//    UNIT_TEST_CMP_STRING(  ( ( ( ( Val( 6 )  /  Val( 24 ) ) /  Val( 2 ) ) -  ( ( Val( 23 )  /  Val( 1 ) ) /  ( Val( 4 )  +  Val( 14 ) ))) *  ( ( ( zero  /  Val( 21 ) ) +  ( Val( 21 )  /  Val( 16 ) )) *  ( ( Val( 27 )  -  zero ) /  ( Val( 17 )  +  Val( 26 ) )))), -5229/5504 );
//    UNIT_TEST_CMP_STRING(  ( ( ( ( Val( 3 )  +  one ) +  ( Val( 2 )  -  Val( 29 ) )) *  ( ( Val( 2 )  -  Val( 1 ) ) +  ( Val( 4 )  +  Val( 19 ) ))) -  zero ), -552 );
//    UNIT_TEST_CMP_STRING(  ( ( ( ( minus_one  +  Val( 5 ) ) -  Val( 23 ) ) -  ( ( Val( 16 )  +  Val( 7 ) ) *  ( Val( 22 )  /  Val( 5 ) ))) /  ( ( ( minus_one  +  Val( 2 ) ) /  ( Val( 6 )  +  Val( 18 ) )) +  ( minus_one  -  Val( 30 ) ))), 14424/3715 );
//    UNIT_TEST_CMP_STRING(  ( ( ( Val( 27 )  /  ( Val( 9 )  -  Val( 29 ) )) -  ( ( Val( 15 )  +  Val( 4 ) ) /  Val( 16 ) )) +  ( ( ( Val( 5 )  +  Val( 13 ) ) *  ( minus_one  -  Val( 18 ) )) +  ( ( Val( 19 )  -  Val( 30 ) ) +  ( one  +  Val( 19 ) )))), -26843/80 );
//    UNIT_TEST_CMP_STRING(  minus_one , -1 );
//    UNIT_TEST_CMP_STRING(  ( ( Val( 22 )  +  ( ( Val( 8 )  -  minus_one ) *  ( Val( 19 )  +  minus_one ))) +  ( ( ( Val( 16 )  +  Val( 1 ) ) +  ( minus_one  /  Val( 30 ) )) *  ( ( Val( 29 )  /  Val( 15 ) ) +  ( Val( 24 )  /  Val( 28 ) )))), 728737/3150 );
//    UNIT_TEST_CMP_STRING(  ( Val( 1 )  -  ( ( ( one  *  Val( 14 ) ) +  ( Val( 27 )  -  Val( 0 ) )) -  ( ( Val( 4 )  -  Val( 27 ) ) -  ( Val( 29 )  /  one )))), -92 );
//    UNIT_TEST_CMP_STRING(  ( minus_one  /  ( ( ( one  +  Val( 27 ) ) /  ( Val( 28 )  /  Val( 11 ) )) +  ( ( Val( 8 )  +  zero ) +  ( one  -  Val( 17 ) )))), -1/3 );
//    UNIT_TEST_CMP_STRING(  ( ( ( ( zero  +  Val( 16 ) ) /  ( Val( 30 )  -  Val( 21 ) )) *  one ) /  Val( 25 ) ), 16/225 );
//    UNIT_TEST_CMP_STRING(  ( ( ( ( Val( 25 )  *  Val( 20 ) ) /  ( Val( 29 )  -  Val( 23 ) )) *  ( Val( 12 )  -  ( Val( 4 )  *  minus_one ))) *  ( Val( 14 )  +  ( ( Val( 30 )  *  one ) +  Val( 14 ) ))), 232000/3 );

//    UNIT_TEST_CMP_STRING(  ( ( minus_one  +  minus_one ) +  ( Val( 1344002910 )  *  Val( 636469945 ) )), 855417458207539948 );
//    UNIT_TEST_CMP_STRING(  ( ( one  *  Val( 741081342 ) ) +  ( Val( 488693011 )  -  Val( 1871056279 ) )), -641281926 );
//    UNIT_TEST_CMP_STRING(  ( minus_one  +  Val( 2 ) ), 1 );
//    UNIT_TEST_CMP_STRING(  ( ( Val( 2041835745 )  -  zero ) -  ( zero  *  Val( 1106593969 ) )), 2041835745 );
//    UNIT_TEST_CMP_STRING(  ( ( Val( 84409727 )  *  Val( 910726790 ) ) -  ( zero  *  zero )), 76874199715486330 );
//    UNIT_TEST_CMP_STRING(  ( ( one  /  one ) +  ( one  +  Val( 1687113726 ) )), 1687113728 );
//    UNIT_TEST_CMP_STRING(  ( one  *  ( Val( 536011372 )  +  Val( 1283848285 ) )), 1819859657 );
//    UNIT_TEST_CMP_STRING(  ( ( Val( 731071774 )  -  Val( 2106376503 ) ) *  ( Val( 1172061765 )  *  Val( 795257014 ) )), -1281908251711073386537258590 );
//    UNIT_TEST_CMP_STRING(  ( one  +  ( Val( 1530764827 )  +  Val( 321377996 ) )), 1852142824 );
//    UNIT_TEST_CMP_STRING(  ( Val( 12 )  +  ( Val( 1508508720 )  *  minus_one )), -1508508708 );
//    UNIT_TEST_CMP_STRING(  ( ( minus_one  /  Val( 1644605293 ) ) -  ( one  *  one )), -1644605294/1644605293 );
//    UNIT_TEST_CMP_STRING(  ( ( Val( 68902265 )  /  Val( 2118132822 ) ) *  ( Val( 1671189371 )  +  Val( 482056523 ) )), 74181759599274955/1059066411 );
//    UNIT_TEST_CMP_STRING(  ( Val( 11 )  /  ( one  +  Val( 1858991216 ) )), 11/1858991217 );
    
//    UNIT_TEST_CMP_STRING(  ( minus_one  +  minus_one ), -2 );
//    UNIT_TEST_CMP_STRING(  ( ( ( Val( 2006481689 )  +  Val( 2121905653 ) ) +  ( Val( 97654242 )  -  minus_one )) /  Val( 15 ) ), 845208317/3 );
//    UNIT_TEST_CMP_STRING(  ( ( ( Val( 1546296782 )  +  Val( 1433874934 ) ) +  ( zero  -  Val( 487811209 ) )) -  ( ( Val( 287619404 )  -  minus_one ) +  ( one  *  Val( 206824387 ) ))), 1997916715 );
//    UNIT_TEST_CMP_STRING(  ( ( ( Val( 694360630 )  -  minus_one ) /  Val( 23 ) ) *  one ), 694360631/23 );
//    UNIT_TEST_CMP_STRING(  ( zero  /  ( ( Val( 1463556103 )  -  zero ) +  ( Val( 588495928 )  +  Val( 990959124 ) ))), 0 );
//    UNIT_TEST_CMP_STRING(  ( ( ( minus_one  /  one ) -  ( Val( 718549667 )  -  Val( 699656709 ) )) -  ( ( Val( 1577266788 )  /  Val( 2017168181 ) ) +  ( Val( 1777979718 )  +  Val( 1839295580 ) ))), -7334762910359897305/2017168181 );
//    UNIT_TEST_CMP_STRING(  ( ( ( minus_one  *  Val( 555465768 ) ) -  ( Val( 412809784 )  /  Val( 1457783864 ) )) -  ( ( minus_one  +  Val( 1852286114 ) ) *  ( Val( 425451366 )  /  Val( 1400015351 ) ))), -285309851792794026988228531/255114973505012033 );
//    UNIT_TEST_CMP_STRING(  ( ( ( Val( 187619016 )  *  Val( 1065704836 ) ) +  minus_one ) /  ( Val( 25 )  /  ( one  *  Val( 890432477 ) ))), 7121554029665239659167035 );
//    UNIT_TEST_CMP_STRING(  ( ( ( Val( 1091346046 )  +  minus_one ) -  ( Val( 1130055366 )  /  Val( 1999050831 ) )) /  ( ( one  *  Val( 85535036 ) ) /  Val( 0 ) )), nan );
//    UNIT_TEST_CMP_STRING(  ( ( ( Val( 1454952418 )  /  Val( 1588034973 ) ) *  ( Val( 960239470 )  +  Val( 382077927 ) )) -  ( ( Val( 617874221 )  +  Val( 296439320 ) ) -  Val( 21 ) )), 501046096441880986/1588034973 );
//    UNIT_TEST_CMP_STRING(  ( ( ( minus_one  -  Val( 1522701112 ) ) -  Val( 22 ) ) /  minus_one ), 1522701135 );
//    UNIT_TEST_CMP_STRING(  ( ( ( Val( 149947379 )  /  Val( 1093358763 ) ) *  ( minus_one  -  Val( 1374092920 ) )) /  ( ( Val( 1789382638 )  +  Val( 1277863224 ) ) +  Val( 11 ) )), -206041632006404059/3353600153520135099 );
//    UNIT_TEST_CMP_STRING(  ( ( ( zero  +  Val( 71775961 ) ) /  ( Val( 1049017417 )  -  Val( 124086555 ) )) +  ( Val( 5 )  *  ( Val( 1517149581 )  +  Val( 2111110731 ) ))), 16779449689764520681/924930862 );
//    UNIT_TEST_CMP_STRING(  ( ( minus_one  /  ( one  +  Val( 1817025143 ) )) /  Val( 13 ) ), -1/23621326872 );
//    UNIT_TEST_CMP_STRING(  ( ( ( Val( 1346444806 )  /  zero ) +  ( Val( 1637470697 )  *  Val( 374673892 ) )) /  ( ( Val( 604683071 )  /  Val( 1275740731 ) ) -  ( zero  -  Val( 1444699704 ) ))), nan );
//    UNIT_TEST_CMP_STRING(  ( ( ( Val( 1230033046 )  /  Val( 229413461 ) ) -  ( Val( 1076323487 )  +  Val( 97687259 ) )) +  ( Val( 2 )  +  ( Val( 1361971699 )  -  Val( 1562639466 ) ))), -315369753740803525/229413461 );
//    UNIT_TEST_CMP_STRING(  ( ( ( Val( 498169376 )  *  Val( 863486723 ) ) /  ( Val( 1678705406 )  +  Val( 1395866406 ) )) +  ( ( minus_one  /  minus_one ) +  ( minus_one  +  Val( 684823117 ) ))), 633925123428843213/768642953 );
    
//    UNIT_TEST_CMP_STRING(  ( ( Val( 13 )  /  ( ( Val( 241275743 )  -  Val( 1596578328 ) ) *  Val( 19 ) )) -  ( Val( 29 )  -  Val( 26 ) )), -5942480566/1980826855 );
//    UNIT_TEST_CMP_STRING(  ( Val( 0 )  +  ( ( ( Val( 1574106547 )  *  Val( 522235951 ) ) *  minus_one ) *  ( ( Val( 1417069992 )  +  Val( 695583912 ) ) *  ( zero  /  zero )))), nan );
//    UNIT_TEST_CMP_STRING(  ( ( Val( 28 )  *  ( ( Val( 317068514 )  /  Val( 613264820 ) ) -  ( one  *  one ))) +  one ), -274293991/21902315 );
//    UNIT_TEST_CMP_STRING(  ( ( ( ( zero  +  Val( 696610474 ) ) -  ( Val( 1825873831 )  /  Val( 201419489 ) )) +  Val( 19 ) ) +  minus_one ), 140310927504804757/201419489 );
//    UNIT_TEST_CMP_STRING(  ( ( ( Val( 22 )  +  ( minus_one  -  Val( 1405424057 ) )) /  ( Val( 30 )  +  ( Val( 2881040 )  -  Val( 1344566684 ) ))) /  ( minus_one  /  ( ( one  /  Val( 798594912 ) ) *  ( Val( 121523282 )  +  Val( 473208703 ) )))), -69654218891415955/89288608736999664 );
//    UNIT_TEST_CMP_STRING(  ( ( ( minus_one  +  ( zero  +  Val( 167024776 ) )) +  ( ( zero  -  Val( 855977883 ) ) *  ( minus_one  +  Val( 1249450441 ) ))) +  ( ( ( minus_one  *  Val( 1493157725 ) ) -  ( Val( 1017180343 )  *  Val( 159824988 ) )) *  ( one  /  ( Val( 1958065189 )  -  Val( 2128348922 ) )))), -182118783036236720849081476/170283733 );
//    UNIT_TEST_CMP_STRING(  ( ( ( ( Val( 521772761 )  -  one ) *  ( zero  /  Val( 1171179128 ) )) *  ( ( zero  -  Val( 954579923 ) ) -  ( minus_one  -  Val( 1060860392 ) ))) *  ( ( ( minus_one  *  Val( 1559868287 ) ) +  Val( 6 ) ) +  ( ( Val( 100266441 )  +  Val( 1499921641 ) ) -  Val( 1 ) ))), 0 );
//    UNIT_TEST_CMP_STRING(  ( Val( 19 )  /  ( ( ( zero  +  zero ) +  ( Val( 1166069256 )  *  Val( 1874149427 ) )) -  ( Val( 6 )  -  ( one  /  one )))), 19/2185388027974716307 );
//    UNIT_TEST_CMP_STRING(  ( ( ( ( Val( 411433269 )  -  one ) *  ( Val( 1869209698 )  +  Val( 656214150 ) )) +  ( Val( 15 )  *  ( Val( 1661612028 )  -  zero ))) *  ( ( ( Val( 1893208689 )  +  minus_one ) -  ( Val( 1817350778 )  +  one )) /  minus_one )), -78819660578763701208904756 );
//    UNIT_TEST_CMP_STRING(  ( ( ( one  *  Val( 16 ) ) *  ( Val( 10 )  +  ( zero  *  Val( 1975797282 ) ))) /  Val( 17 ) ), 160/17 );
//    UNIT_TEST_CMP_STRING(  ( ( ( ( one  /  zero ) +  ( zero  +  minus_one )) +  Val( 8 ) ) +  Val( 5 ) ), nan );
//    UNIT_TEST_CMP_STRING(  ( Val( 14 )  *  ( ( ( zero  *  zero ) -  ( Val( 1470756322 )  +  minus_one )) *  ( ( Val( 2014981673 )  *  Val( 958500273 ) ) *  ( zero  *  Val( 675322107 ) )))), 0 );
//    UNIT_TEST_CMP_STRING(  ( ( ( ( Val( 732563838 )  +  Val( 269719106 ) ) -  ( one  /  Val( 1096158558 ) )) *  ( ( Val( 1646272235 )  /  Val( 431294272 ) ) +  ( Val( 1574914307 )  +  Val( 876267502 ) ))) /  ( one  -  ( ( Val( 1232605769 )  -  Val( 1530048384 ) ) -  ( Val( 511342733 )  *  Val( 1570434466 ) )))), 1161483206248148974065182489464904533/379646128747476188382000383062604544 );
//    UNIT_TEST_CMP_STRING(  ( ( zero  *  ( Val( 13 )  /  one )) /  ( zero  -  ( ( zero  /  minus_one ) -  ( zero  +  one )))), 0 );
//    UNIT_TEST_CMP_STRING(  ( ( zero  *  ( ( Val( 2024524473 )  *  Val( 1987930029 ) ) -  ( Val( 300883351 )  /  one ))) +  ( Val( 20 )  *  ( ( zero  /  Val( 2028388989 ) ) *  ( zero  +  Val( 812165246 ) )))), 0 );
//    UNIT_TEST_CMP_STRING(  ( ( ( ( Val( 467476632 )  +  one ) -  ( one  *  Val( 289971972 ) )) *  ( ( Val( 1549033190 )  /  Val( 399161003 ) ) +  ( one  -  Val( 1779378558 ) ))) /  ( ( ( one  /  one ) +  Val( 19 ) ) *  ( ( Val( 1861896140 )  *  Val( 1138739499 ) ) -  ( Val( 1018183850 )  -  Val( 1654520142 ) )))), -126074199231409771629660941/16926140351230936214247649120 );
//    UNIT_TEST_CMP_STRING(  ( ( ( ( Val( 1078542917 )  -  Val( 1546850685 ) ) +  Val( 6 ) ) +  ( ( Val( 1346402237 )  -  Val( 1018740177 ) ) *  Val( 25 ) )) /  ( ( zero  *  Val( 28 ) ) *  ( ( Val( 226359453 )  /  Val( 1809290132 ) ) /  ( Val( 1780426298 )  -  Val( 1421932252 ) )))), nan );
    
//    UNIT_TEST_CMP_STRING(  ( ( ( ( Val( 437052922 )  /  Val( 1135374603 ) ) *  ( zero  *  Val( 1477390624 ) )) -  ( Val( 29 )  *  Val( 12 ) )) +  ( ( ( one  +  Val( 591585900 ) ) -  ( Val( 1435420009 )  +  zero )) -  ( ( zero  -  Val( 422747421 ) ) +  ( Val( 1658272331 )  /  Val( 1121048253 ) )))), -472058886605972186/1121048253 );
//    UNIT_TEST_CMP_STRING(  ( ( ( ( Val( 251914938 )  -  Val( 1610299922 ) ) *  ( Val( 48419468 )  -  zero )) /  ( ( one  *  Val( 592733609 ) ) -  ( Val( 1623570574 )  /  Val( 388290028 ) ))) /  ( ( ( Val( 717570 )  /  one ) -  ( Val( 1862013076 )  +  Val( 1184567875 ) )) /  ( ( Val( 547204428 )  *  Val( 430645517 ) ) +  ( Val( 304648589 )  *  Val( 1889214964 ) )))), 941679703073617678676884449715176709492736/31864237183287151903394369 );
//    UNIT_TEST_CMP_STRING(  ( ( ( ( Val( 1967914853 )  *  zero ) /  ( Val( 1876829805 )  *  minus_one )) +  Val( 29 ) ) /  ( Val( 24 )  *  ( ( Val( 2092557281 )  -  Val( 289631807 ) ) /  ( Val( 1724791094 )  /  Val( 51132191 ) )))), 862395547/38146564011862152 );
//    UNIT_TEST_CMP_STRING(  Val( 29 ) , 29 );
//    UNIT_TEST_CMP_STRING(  ( ( ( ( Val( 2069501915 )  /  Val( 90201391 ) ) /  ( Val( 344572504 )  +  Val( 202283538 ) )) /  Val( 7 ) ) /  ( ( ( Val( 1932394609 )  +  one ) *  ( Val( 2144500907 )  *  Val( 176546118 ) )) +  ( ( minus_one  /  Val( 982702824 ) ) *  ( one  -  Val( 1827117850 ) )))), 338950896023984660/41374758094064228866695624513541636352643643410595751 );
//    UNIT_TEST_CMP_STRING(  ( ( ( ( zero  +  zero ) +  ( Val( 1214816417 )  /  Val( 1733228434 ) )) *  ( ( minus_one  *  minus_one ) -  ( Val( 1407073915 )  *  Val( 375640965 ) ))) -  ( ( ( Val( 912516366 )  -  Val( 1061545961 ) ) *  ( Val( 1500943087 )  +  Val( 2100564343 ) )) *  minus_one )), -786187287811259379061589029/866614217 );
//    UNIT_TEST_CMP_STRING(  ( ( ( zero  /  ( Val( 357183000 )  /  Val( 1906353754 ) )) *  ( ( Val( 1864878735 )  -  Val( 876665527 ) ) *  ( zero  *  Val( 1541906124 ) ))) +  ( ( ( Val( 1174857422 )  *  zero ) /  ( Val( 1067930984 )  *  Val( 1278543101 ) )) /  ( ( one  +  one ) *  ( zero  +  Val( 2044902375 ) )))), 0 );
//    UNIT_TEST_CMP_STRING(  ( Val( 6 )  /  ( ( ( Val( 18328027 )  *  Val( 1635074593 ) ) +  ( zero  *  Val( 289440075 ) )) /  ( ( Val( 1035719900 )  -  Val( 1328099841 ) ) /  ( Val( 1569574766 )  /  Val( 350852923 ) )))), -307747070779252629/23518266020083160418055213 );
//    UNIT_TEST_CMP_STRING(  ( ( ( ( zero  /  minus_one ) *  ( zero  /  Val( 14535464 ) )) /  ( ( Val( 384293949 )  *  Val( 1665494482 ) ) -  ( minus_one  *  Val( 653676611 ) ))) -  ( Val( 21 )  -  ( ( Val( 186396437 )  /  minus_one ) /  ( Val( 1353504825 )  -  Val( 860263876 ) )))), -10544456366/493240949 );
//    UNIT_TEST_CMP_STRING(  ( ( ( ( Val( 728064456 )  -  one ) -  Val( 21 ) ) -  Val( 18 ) ) *  ( ( ( Val( 1507761833 )  -  one ) *  Val( 24 ) ) -  ( ( one  *  one ) *  Val( 26 ) ))), 26345945685442407872 );
//    UNIT_TEST_CMP_STRING(  ( ( minus_one  -  ( ( Val( 1887086475 )  /  one ) +  Val( 14 ) )) *  ( ( ( Val( 2115209156 )  /  zero ) -  ( Val( 9557388 )  -  minus_one )) -  Val( 3 ) )), nan );
//    UNIT_TEST_CMP_STRING(  ( ( ( ( Val( 1614900255 )  *  Val( 1451532512 ) ) /  Val( 30 ) ) -  ( Val( 2 )  -  ( zero  +  Val( 405672608 ) ))) -  ( Val( 20 )  +  ( Val( 21 )  +  ( Val( 37879467 )  *  minus_one )))), 78136007902538384 );
//    UNIT_TEST_CMP_STRING(  ( Val( 23 )  -  ( ( zero  /  ( Val( 1230676585 )  /  Val( 1983145498 ) )) +  ( ( minus_one  /  Val( 870681083 ) ) *  ( Val( 1561160155 )  +  Val( 908493205 ) )))), 22495318269/870681083 );
//    UNIT_TEST_CMP_STRING(  ( Val( 12 )  -  ( ( ( Val( 130910556 )  *  one ) /  ( zero  /  one )) *  ( ( zero  *  zero ) /  ( Val( 1447459976 )  -  minus_one )))), nan );
//    UNIT_TEST_CMP_STRING(  ( Val( 22 )  /  ( one  -  ( Val( 9 )  *  ( Val( 828520468 )  -  Val( 1341850938 ) )))), 22/4619974231 );
//    UNIT_TEST_CMP_STRING(  minus_one , -1 );
//    UNIT_TEST_CMP_STRING(  ( ( ( ( minus_one  /  Val( 166016242 ) ) *  ( one  /  minus_one )) /  ( ( Val( 798004387 )  +  Val( 884806390 ) ) *  ( Val( 1045570444 )  -  one ))) *  ( zero  /  ( ( Val( 1921908623 )  +  Val( 2138443935 ) ) -  ( Val( 533210270 )  *  one )))), 0 );
//    UNIT_TEST_CMP_STRING(  ( ( ( ( Val( 864895607 )  *  one ) /  ( Val( 1948031541 )  *  Val( 1955201912 ) )) -  Val( 23 ) ) /  ( ( ( minus_one  /  Val( 1589877565 ) ) +  ( zero  *  one )) -  ( ( zero  +  one ) +  ( zero  *  zero )))), 139276907328812919455806239085/6055517713816968801314401872 );
//    UNIT_TEST_CMP_STRING(  ( ( Val( 3 )  +  ( ( Val( 1576919847 )  *  Val( 356427529 ) ) -  ( Val( 911934304 )  *  minus_one ))) +  ( ( ( Val( 2000535204 )  +  Val( 1597884352 ) ) -  ( Val( 67107221 )  *  Val( 434968380 ) )) +  Val( 5 ) )), 532868129802949951 );
    
//    UNIT_TEST_CMP_STRING(  ( ( ( ( Val( 16 )  -  minus_one ) *  ( ( Val( 2113318672 )  +  minus_one ) -  ( Val( 340456902 )  -  zero ))) /  ( ( Val( 8 )  /  ( one  +  one )) +  ( ( minus_one  +  Val( 2102594609 ) ) /  ( zero  -  Val( 1489914952 ) )))) -  ( ( ( ( Val( 459698588 )  +  Val( 1774512971 ) ) *  ( Val( 1751311697 )  -  Val( 701954671 ) )) +  ( ( Val( 423741439 )  *  Val( 1324655992 ) ) -  ( zero  /  Val( 676657140 ) ))) *  ( ( ( Val( 731149085 )  /  Val( 1334021010 ) ) +  ( Val( 1576519338 )  +  Val( 859534061 ) )) /  ( minus_one  /  ( minus_one  /  Val( 1997073602 ) ))))), -1806679973255414933523586108080397636305013/509710045714876375227525 );
//    UNIT_TEST_CMP_STRING(  ( ( ( ( ( Val( 1716272458 )  -  Val( 1707535198 ) ) /  ( minus_one  -  minus_one )) *  ( one  +  ( zero  -  minus_one ))) -  ( ( ( minus_one  +  Val( 104688153 ) ) *  Val( 23 ) ) -  ( minus_one  +  zero ))) *  ( ( ( ( Val( 820060909 )  *  Val( 1714774134 ) ) /  ( Val( 1142418647 )  /  zero )) /  ( Val( 6 )  +  ( Val( 557123044 )  -  zero ))) *  ( ( Val( 3 )  +  ( Val( 960326867 )  /  Val( 1143808476 ) )) /  ( ( Val( 1638709212 )  /  Val( 779866600 ) ) -  Val( 8 ) )))), nan );
//    UNIT_TEST_CMP_STRING(  ( ( ( ( ( Val( 1032877773 )  /  one ) *  zero ) +  ( Val( 29 )  -  Val( 8 ) )) /  Val( 9 ) ) /  ( ( ( ( minus_one  /  zero ) -  one ) -  ( ( Val( 662812167 )  *  Val( 1721686391 ) ) /  Val( 27 ) )) -  ( ( ( Val( 23741743 )  +  Val( 317951341 ) ) +  zero ) -  ( Val( 30 )  /  Val( 23 ) )))), nan );
//    UNIT_TEST_CMP_STRING(  ( ( ( ( ( one  *  Val( 1381433827 ) ) /  ( Val( 1420300879 )  /  Val( 112362854 ) )) /  ( minus_one  /  ( Val( 1968069822 )  +  one ))) -  ( ( ( Val( 21819437 )  *  Val( 1875460905 ) ) +  Val( 17 ) ) -  ( ( Val( 817983526 )  -  Val( 456035247 ) ) *  ( Val( 592787108 )  *  minus_one )))) /  ( Val( 14 )  -  ( ( minus_one  -  ( Val( 1087305979 )  +  one )) -  ( Val( 1 )  +  ( Val( 311700540 )  *  Val( 892135692 ) ))))), -55695465185017367450663385/32913008416459977360661267 );
//    UNIT_TEST_CMP_STRING(  ( ( ( ( ( one  *  Val( 902355611 ) ) +  ( Val( 1103208269 )  /  one )) /  ( ( Val( 979601647 )  *  Val( 2013039005 ) ) *  ( Val( 969034190 )  /  Val( 824333670 ) ))) +  ( ( ( Val( 1836811550 )  +  Val( 1122657280 ) ) *  Val( 17 ) ) *  Val( 25 ) )) *  ( Val( 31 )  *  ( ( ( zero  *  Val( 1123320123 ) ) -  ( Val( 343387251 )  *  Val( 1969980064 ) )) *  ( ( minus_one  *  Val( 1647207694 ) ) /  Val( 0 ) )))), nan );
//    UNIT_TEST_CMP_STRING(  ( ( ( ( Val( 12 )  +  ( one  +  Val( 1086205035 ) )) *  ( ( Val( 545297683 )  -  Val( 912245090 ) ) +  Val( 10 ) )) *  ( ( ( Val( 1801002485 )  *  Val( 1895015528 ) ) *  ( Val( 1833879056 )  +  Val( 75965797 ) )) *  ( ( zero  -  zero ) *  ( zero  -  Val( 1651151948 ) )))) +  ( ( ( ( Val( 2040054733 )  *  Val( 199926829 ) ) *  ( Val( 719996147 )  *  one )) *  Val( 23 ) ) +  ( ( Val( 0 )  -  Val( 21 ) ) +  Val( 17 ) ))), 6754153173091313733907688313 );
//    UNIT_TEST_CMP_STRING(  ( ( ( ( Val( 8 )  /  ( Val( 2121307964 )  +  Val( 1167324289 ) )) *  one ) +  ( Val( 3 )  /  Val( 8 ) )) +  Val( 4 ) ), 115102128919/26309058024 );
//    UNIT_TEST_CMP_STRING(  ( ( ( ( ( Val( 1529355988 )  +  Val( 27488842 ) ) *  ( one  *  Val( 825743930 ) )) +  one ) /  ( ( ( one  +  Val( 120997698 ) ) +  ( Val( 1198546209 )  +  Val( 417119211 ) )) -  ( ( Val( 2077279915 )  /  one ) *  ( Val( 868604601 )  +  Val( 1265887675 ) )))) /  ( ( ( Val( 21 )  +  minus_one ) -  ( ( Val( 1454098896 )  *  Val( 1946404406 ) ) -  Val( 21 ) )) *  ( ( Val( 6 )  *  ( Val( 863182106 )  *  zero )) -  ( ( zero  /  Val( 2100823452 ) ) *  one )))), nan );
//    UNIT_TEST_CMP_STRING(  ( ( ( ( ( Val( 1735745029 )  +  Val( 792633818 ) ) *  ( minus_one  /  Val( 1509420124 ) )) /  ( ( one  /  zero ) /  ( Val( 1250189684 )  +  Val( 1709358056 ) ))) *  ( ( ( Val( 408749567 )  +  zero ) *  ( one  *  Val( 741354147 ) )) /  ( ( Val( 290498941 )  -  Val( 1495857522 ) ) /  ( Val( 1665143976 )  -  minus_one )))) +  ( Val( 28 )  *  ( Val( 14 )  *  ( Val( 25 )  +  Val( 0 ) )))), nan );
//    UNIT_TEST_CMP_STRING(  ( ( ( ( ( Val( 2071157095 )  +  Val( 852076418 ) ) +  ( Val( 669108996 )  /  Val( 1024062944 ) )) -  ( ( Val( 1745329282 )  /  Val( 1650008967 ) ) /  ( Val( 508628749 )  *  Val( 706389701 ) ))) +  ( ( ( Val( 1200295460 )  *  Val( 1393158909 ) ) /  Val( 15 ) ) +  ( Val( 17 )  *  ( Val( 267854793 )  +  Val( 1411839850 ) )))) -  ( ( ( ( Val( 387660866 )  +  Val( 103364896 ) ) /  Val( 19 ) ) +  Val( 9 ) ) -  ( ( ( Val( 314034778 )  *  minus_one ) /  ( Val( 1816245648 )  -  Val( 1384584956 ) )) +  ( ( Val( 149213854 )  *  Val( 970572224 ) ) +  ( one  -  Val( 1011979184 ) ))))), 79760531709469787837941906531366107406581356758212390616065757/311196238795807607257982673314437360211324856 );
//    UNIT_TEST_CMP_STRING(  ( minus_one  *  ( ( ( ( minus_one  +  minus_one ) +  ( Val( 2093017894 )  /  one )) -  ( Val( 22 )  +  Val( 12 ) )) /  Val( 26 ) )), -1046508929/13 );
//    UNIT_TEST_CMP_STRING(  ( ( Val( 21 )  -  ( ( Val( 4 )  /  Val( 30 ) ) *  ( ( Val( 564015939 )  *  Val( 1752937002 ) ) *  Val( 6 ) ))) /  Val( 1 ) ), -3954737636763499407/5 );
//    UNIT_TEST_CMP_STRING(  ( Val( 27 )  *  ( ( Val( 15 )  *  ( ( zero  +  Val( 1006599636 ) ) *  ( minus_one  +  Val( 25380982 ) ))) -  ( ( ( Val( 748303975 )  -  minus_one ) -  ( Val( 1489530964 )  -  Val( 1528977773 ) )) -  ( Val( 9 )  +  ( Val( 667060081 )  /  one ))))), 10347136922290132215 );
//    UNIT_TEST_CMP_STRING(  ( ( ( ( ( Val( 314420206 )  *  Val( 764989975 ) ) /  ( Val( 2092954902 )  *  Val( 1977935239 ) )) *  ( ( Val( 937268907 )  -  zero ) /  ( one  -  Val( 919315243 ) ))) /  minus_one ) *  ( ( ( ( Val( 241771172 )  /  Val( 1844961667 ) ) +  ( zero  +  Val( 1881869077 ) )) +  ( ( Val( 962842967 )  -  Val( 1532206963 ) ) /  Val( 10 ) )) *  zero )), 0 );
//    UNIT_TEST_CMP_STRING(  ( ( ( ( ( zero  *  Val( 193614883 ) ) +  one ) /  ( ( Val( 1890590444 )  /  Val( 1742503943 ) ) /  ( Val( 2105991955 )  *  minus_one ))) /  ( ( ( Val( 1620303263 )  *  Val( 37607672 ) ) +  ( Val( 441002978 )  /  Val( 916533418 ) )) -  ( ( Val( 343824320 )  /  Val( 1900645138 ) ) +  ( Val( 1159931189 )  -  minus_one )))) /  ( ( ( zero  *  Val( 1 ) ) -  ( ( minus_one  *  Val( 1078789171 ) ) *  Val( 4 ) )) *  ( ( ( one  -  one ) -  ( Val( 258089298 )  -  Val( 1927449153 ) )) *  ( ( Val( 1123436021 )  -  Val( 855103313 ) ) /  ( minus_one  *  minus_one ))))), -32545737266612851776301831892513/1974940393465272656906716100126363133133986011454687626311500814656 );
//    UNIT_TEST_CMP_STRING(  ( ( ( ( ( Val( 954737417 )  *  Val( 843011525 ) ) +  ( Val( 972602212 )  /  minus_one )) -  ( ( Val( 1234475307 )  -  one ) *  ( Val( 1390903827 )  *  Val( 593108892 ) ))) /  ( ( Val( 31 )  /  ( Val( 408647249 )  +  Val( 1563898912 ) )) -  ( ( Val( 2033975627 )  +  Val( 2134804789 ) ) *  ( Val( 1245226306 )  -  Val( 1505843277 ) )))) +  ( ( ( ( minus_one  /  minus_one ) +  ( Val( 637856776 )  +  Val( 1759265244 ) )) -  minus_one ) /  ( ( ( Val( 293826446 )  -  Val( 2037863740 ) ) /  ( Val( 1889207371 )  +  Val( 1616656093 ) )) *  ( ( Val( 584607361 )  -  Val( 377867147 ) ) *  ( Val( 1846553453 )  *  minus_one ))))), -162393033275776310634817545909207561649971171127512340981737/173246776644362958408170765653697592310241508197861 );
//    UNIT_TEST_CMP_STRING(  ( ( one  -  ( ( zero  *  ( Val( 1165866056 )  -  zero )) -  ( Val( 8 )  *  ( one  /  Val( 2022851404 ) )))) /  minus_one ), -505712853/505712851 );
    return 0;
}
