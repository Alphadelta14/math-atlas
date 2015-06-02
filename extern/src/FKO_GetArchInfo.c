#define DECL_ 1
#include "fko_parseinfo.h"
#include "fko_archinfo.h"

fko_archinfo_t *FKO_NewArchInfo(void)
{
   fko_archinfo_t *ap;
   ap = calloc(1, sizeof(fko_archinfo_t));
   return(ap);
}

fko_archinfo_t *FKO_GetArchInfoC(char *fnin)
{
   fko_archinfo_t *ap;
   FILE *fpin;
   fko_infoline_t il;

   if (!strcmp(fnin, "stdin"))
      fpin = stdin;
   else
   {
      fpin = fopen(fnin, "r");
      assert(fpin);
   }
   ap = FKO_NewArchInfo();

   while(FKO_ParseInfoLine(&il, fpin))
   {
      fko_word_t *wp;
      char *sp;
      int n, i;

      assert(il.nwords == 1);  /* all top-level arch are single words */
      wp = il.words;
      assert(wp->eqpos > 0);   /* all top-lvl arch end in =%d */
      switch(wp->eqpos)        /* avoid many strcmp */
      {
               /* 012345678901 */
      case 7:  /* FPUPIPE, NCACHES */
         if (!strncmp(wp->word, "FPUPIPE=", 7))
         {
            n = FKO_GetIntFromEqWord(wp);
            ap->nfpupipes = n;
            for (i=0; i < n; i++)      /* FxxxPIPELEN: */
            {                          /* 012345678901 */
               short *nr;
               FKO_FreeAllWords(wp);
               assert(FKO_ParseInfoLine(&il, fpin));
               wp = il.words;
               sp = wp->word;
               assert(wp->len == 12);
               assert(!strcmp(sp+4, "PIPELEN:"));
               assert(sp[0] == 'F');
               wp = wp->next;
               assert(wp);
               nr = FKO_GetShortArrayFromTypeList(wp);
               if (sp[1] == 'A')
               {
                  assert(sp[2] == 'D' && sp[3] == 'D');
                  ap->pipelen_add = nr;
               }
               else
               {
                  assert(sp[1] == 'M');
                  if (sp[2] == 'U')
                  {
                     assert(sp[3] == 'L');
                     ap->pipelen_mul = nr;
                  }
                  else
                  {
                     assert(sp[2] == 'A');
                     assert(sp[3] == 'C');
                     ap->pipelen_mac = nr;
                  }
               }
            }
         }
         else
         {
            assert(!strncmp(wp->word, "NCACHES=", 7));
            n = FKO_GetIntFromEqWord(wp);
            for (i=0; i < n; i++)
            {
               FKO_FreeAllWords(il.words);
               assert(FKO_ParseInfoLine(&il, fpin));
            }
         }
         break;
      case 8:  /* REGTYPES, VECTYPES */
         if (*sp == 'R') 
         {
            FKO_FreeAllWords(il.words);
            assert(FKO_ParseInfoLine(&il, fpin));
            wp = il.words;
            sp = wp->word;
            if (*sp == 'N') /* NUMREGS: */
               ap->numregs = FKO_GetShortArrayFromTypeList(wp->next);
            else            /* ALIASGROUPS= */
            {
               assert(!strncmp(sp, "ALIASGROUPS=", 12));
               n = FKO_GetIntFromEqWord(wp);
               for (i=0; i < n; i++)
               {
                  FKO_FreeAllWords(il.words);
                  assert(FKO_ParseInfoLine(&il, fpin));
               }
            }
         }
         else /* VECTYPES */
         {
            FKO_FreeAllWords(il.words);
            assert(FKO_ParseInfoLine(&il, fpin));
         }
         break;
      case 12: /* EXTENDEDINST */
         assert(!strncmp(wp->word, "EXTENDEDINST=", 12));
         n = FKO_GetIntFromEqWord(wp);
         for (i=0; i < n; i++)
         {
            FKO_FreeAllWords(il.words);
            assert(FKO_ParseInfoLine(&il, fpin));
         }
         break;
      default:
         fprintf(stderr, "No = found in top-level archinfo string: '%s'!\n",
                 wp->word ? wp->word:"NULL");
      }
      FKO_FreeAllWords(il.words);
   }

   if (fpin != stdin)
      fclose(fpin);
   return(ap);
}

void FKO_GetArchInfo(char *fname)
{
   FKO_ARCHINF = FKO_GetArchInfoC(fname);
}
