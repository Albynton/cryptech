void poly_crypt(char key[], char *file, char name[])
    {
        char newKey[strlen(file)];
        int i,j;
        //boucle assurant que la taille de la cle est la meme que le texte par repetition
         for(i = 0,j = 0; i < strlen(file); ++i, ++j){
            
            if(j == strlen(key))
                j = 0;

            newKey[i] = key[j];
            
        }

        //chiffrage
        for(i = 0; i < strlen(file); ++i){
            if((file[i] + newKey[i] + 'a')>255);
            {
                
            }
            file[i] = ((file[i] + newKey[i])) + 'a';
        }

        //creation du fichier crypteo
        FILE* pgmimg;
        pgmimg = fopen(name, "a"); // ouverture du fichier
        //fprintf(pgmimg,"tag 2\n");//info pour reconnaitre les modifications apportees automatiquement
        for (i = 0; i < strlen(file); i++)
        {
            fprintf(pgmimg, "%c", file[i]);//ecriture du nouveau fichier
        }
        fclose(pgmimg);//fermeture du fichier
    }

void poly_decrypt(char key[], char *file, char name[])
    {
        char newKey[strlen(file)];
        int i,j;
        //boucle assurant que la taille de la cle est la meme que le texte par repetition
            for(i = 0,j = 0; i < strlen(file); ++i, ++j){
            if(j == strlen(key))
                j = 0;

            newKey[i] = key[j];
        }

        //dechiffrage
        for(i = 0; i < strlen(file); ++i){
            file[i] = ((file[i] - newKey[i])) - 'a'; //affectation de la nouvelle valeur
        }

        //creation du fichier crypte
        FILE* pgmimg;
        pgmimg = fopen(name, "a"); //ouverture du nouveau fichier
        for (i = 0; i < strlen(file); i++)
        {
            fprintf(pgmimg, "%c", file[i]);//ecriture du nouveau fichier
        }
        fclose(pgmimg); //fermeture du fichier
    }
