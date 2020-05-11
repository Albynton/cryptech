void v_crypt(char key[],int fatkey[256][256], char *file,char name[])
    {
        int newKey[256],i,j;
        //boucle assurant que la taille de la cle est de 256
         for(i = 0, j = 0; i < 256; ++i, ++j){
            if(j == strlen(key)){
                j = 0;
            }
            newKey[i] = key[j];
            //prise de la valeur absolue de newKey
            if (newKey[i]<0)
            {
                newKey[i]=-newKey[i];
            }
        }
        //encryption
        for(i = 0,j = 0; i < strlen(file); i++,j++){
            //printf("\n[%d]=[%d][%d]\n",fatkey[newKey[j]][file[i]],newKey[j],file[i]);
            file[i] = file[i]-fatkey[newKey[j]][i];//association de la valeur cryptee en fonction de la cle et du tableau
            if(j == 256){j=0;}
            //printf("\nfile[%d]=[%c]::::newkey[%d]=[%c]::::file[%d]=[%c]",i,file[i],i,newKey[i],i,file[i+1]);
        }

        //creation du fichier crypte
        FILE* pgmimg;
        pgmimg = fopen(name, "a");
        //fprintf(pgmimg,"tag 3\n");//info pour reconnaitre les modifications apportees automatiquement
        for (i = 0; i < strlen(file); i++)
        {
            fprintf(pgmimg, "%c", file[i]);//ecriture du nouveau fichier
        }
        fclose(pgmimg);
    }

void v_decrypt(char key[],int fatkey[256][256], char *file,char name[])
    {
        int newKey[256],i,j;
        //boucle assurant que la taille de la cle est la meme que le texte par repetition
         for(i = 0, j = 0; i < 255; ++i, ++j){
            if(j == strlen(key))
                j = 0;

            newKey[i] = key[j];
            //prise de la valeur absolue de newKey
            if (newKey[i]<0)
            {
                newKey[i]=-newKey[i];
            }
        }
        //dechiffrage
        for(i = 0,j = 0; i < strlen(file); ++i,++j){
            //file[i] = fatkey[newKey[j]][file[j]];//association de la valeur cryptee en fonction de la cle et du tableau
            file[i] = file[i]+fatkey[newKey[j]][j];
            //printf("\n[%d]=[%d][%d][%d]\n",fatkey[newKey[j]][file[i]],newKey[j],file[i],h);
            if(j == 256){j=0;}// remise a 0 du compteur pour rester dans la valeur du tableau <256
            //printf("\nfile[%d]=[%c]::::newkey[%d]=[%c]::::file[%d]=[%c]",i,file[i],i,newKey[i],i,file[i+1]);
        }

        //creation du fichier crypte
        FILE* pgmimg;
        pgmimg = fopen(name, "a");
        for (i = 0; i < strlen(file); i++)
        {
            fprintf(pgmimg, "%c", file[i]);//ecriture du nouveau fichier
        }
        fclose(pgmimg);
    }
