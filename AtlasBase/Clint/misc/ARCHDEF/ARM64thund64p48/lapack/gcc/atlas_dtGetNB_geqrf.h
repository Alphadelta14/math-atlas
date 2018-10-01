#ifndef ATL_dtGetNB_geqrf

/*
 * NB selection for GEQRF: Side='RIGHT', Uplo='UPPER'
 * M : 25,75,125,175,225,325,425,475,525,575,625,725,826,1026,1227,1427,1628,1828,1878,1928,1978,2029,2229,2430,2831,3232,4836,6440
 * N : 25,75,125,175,225,325,425,475,525,575,625,725,826,1026,1227,1427,1628,1828,1878,1928,1978,2029,2229,2430,2831,3232,4836,6440
 * NB : 1,2,7,7,9,9,11,11,12,12,14,14,15,12,31,32,35,32,40,48,48,59,59,83,80,100,116,231
 */
#define ATL_dtGetNB_geqrf(n_, nb_) \
{ \
   if ((n_) < 50) (nb_) = 1; \
   else if ((n_) < 100) (nb_) = 2; \
   else if ((n_) < 200) (nb_) = 7; \
   else if ((n_) < 375) (nb_) = 9; \
   else if ((n_) < 500) (nb_) = 11; \
   else if ((n_) < 600) (nb_) = 12; \
   else if ((n_) < 775) (nb_) = 14; \
   else if ((n_) < 926) (nb_) = 15; \
   else if ((n_) < 1126) (nb_) = 12; \
   else if ((n_) < 1327) (nb_) = 31; \
   else if ((n_) < 1527) (nb_) = 32; \
   else if ((n_) < 1728) (nb_) = 35; \
   else if ((n_) < 1853) (nb_) = 32; \
   else if ((n_) < 1903) (nb_) = 40; \
   else if ((n_) < 2003) (nb_) = 48; \
   else if ((n_) < 2329) (nb_) = 59; \
   else if ((n_) < 2630) (nb_) = 83; \
   else if ((n_) < 3031) (nb_) = 80; \
   else if ((n_) < 4034) (nb_) = 100; \
   else if ((n_) < 5638) (nb_) = 116; \
   else (nb_) = 231; \
}


#endif    /* end ifndef ATL_dtGetNB_geqrf */
