#ifndef ATL_sGetNB_geqrf

/*
 * NB selection for GEQRF: Side='RIGHT', Uplo='UPPER'
 * M : 25,160,240,320,400,880,1840,3760
 * N : 25,160,240,320,400,880,1840,3760
 * NB : 5,8,20,20,80,80,80,80
 */
#define ATL_sGetNB_geqrf(n_, nb_) \
{ \
   if ((n_) < 92) (nb_) = 5; \
   else if ((n_) < 200) (nb_) = 8; \
   else if ((n_) < 360) (nb_) = 20; \
   else (nb_) = 80; \
}


#endif    /* end ifndef ATL_sGetNB_geqrf */
