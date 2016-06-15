#ifndef ATL_zGetNB_geqrf

/*
 * NB selection for GEQRF: Side='RIGHT', Uplo='UPPER'
 * M : 25,160,400,800,1680
 * N : 25,160,400,800,1680
 * NB : 12,80,80,80,80
 */
#define ATL_zGetNB_geqrf(n_, nb_) \
{ \
   if ((n_) < 92) (nb_) = 12; \
   else (nb_) = 80; \
}


#endif    /* end ifndef ATL_zGetNB_geqrf */
