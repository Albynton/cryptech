void cesar_crypt (int decallage, char *file,char name[])
    {
        //printf("strlen=%ld\n",strlen(file));
        // boucle de cryptage
        for(int i=0 ; i<strlen(file) ; i++){  
            // condition pour rester dans la table ascii (<256)
            if  (file[i]+decallage>=255)
            {
                file[i]=decallage - (255-file[i]);
            } // retour au debut de la table ascii
            file[i] = file[i] + decallage; // affectation de la nouvelle valeur
        }

        FILE* pgmimg; //nouvelle variable de type fichier
        pgmimg = fopen(name, "a"); // ouverture du nouveau fichier
        //fprintf(pgmimg,"tag 1\n"); // ajout d'un label pour detection automatique des modifications
        for (int i = 0; i < strlen(file); i++)
        {
            fprintf(pgmimg, "%c", file[i]);//ecriture du nouveau fichier
        }
        fclose(pgmimg); //fermeture du fichier
    }

void cesar_decrypt (int decallage, char *file,char name[])
    {
        //boucle de decryptage
        for(int i=0 ; i<strlen(file) ; i++){
            // condition pour rester dans la table ascii (<256)
            if  (file[i]+decallage>=255)
            {
                file[i]=decallage - (255-file[i]);
            } // retour au debut de la table ascii
            if (decallage > file[i])
            {
                file[i]=255-(decallage-file[i]);
            }
            file[i] = file[i] + decallage; // affectation de la valeur originale
        }

        FILE* pgmimg; // nouvelle variable de type fichier
        pgmimg = fopen(name, "a"); // ouverture du nouveau fichier
        for (int i = 0; i < strlen(file); i++)
        {

            fprintf(pgmimg, "%c", file[i]);//ecriture du nouveau fichier
        }
        fclose(pgmimg); // fermeture du fichier
    }
