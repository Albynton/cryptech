// Include libraries
#include <unistd.h>
#include <string.h>
#include <gtk/gtk.h>
#include <gtk/gtkx.h>
#include <gdk/gdk.h>
#include <math.h>
#include <ctype.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include "caesar.h"
#include "polyalph.h"
#include "vigenere.h"

// Declare key variables
int choix=1,size,type,ok=10;
char name[128],key[128],file[11];
FILE *f;
GdkColor color;

// Declare GUI elements
GtkWidget     *window; // Main window
GtkWidget     *dialog; // Display error message
GtkWidget     *fixed1; // Grid (positioning items)
GtkWidget     *button1; // "Chiffrer" button to select encrypting
GtkWidget     *button2; // "Déchiffrer button to select decrypting"
GtkWidget     *button3; // "Save" (proceed) button
GtkWidget     *dark; // "Dark theme" toggle
GtkWidget     *label1; // Text "Taille du fichier"
GtkWidget     *label2; // Text displaying file size
GtkWidget     *label3; // Unused
GtkWidget     *radio1; // "Niveau 1" radio button (Caesar's cypher)
GtkWidget     *radio2; // "Niveau 2" radio button (polyalphabetic cypher)
GtkWidget     *radio3; // "Niveau 3" radio button (Vigenere's cypher)
GtkBuilder    *builder; // Interface file storage
GtkWidget     *file1; // File chooser
GtkWidget     *entry1; // Encryption key box
GtkWidget     *entry2; // Target file box
GtkWidget     *prog1; // Progress bar

static gboolean progress_bar(float prog)
// Creates a progress bar
{ 
    //gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(prog1),(gdouble) 0);  
    //printf("prog=%f\n",prog);  
    gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(prog1),(gdouble) prog);
    //sleep(1000);
}

int on_radio1_toggled(GtkRadioButton *b)
// When radio button "Niveau 1" is selected
{
  gboolean T= gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(b));
  if (T)
  {
    choix=1;
  }
}

int on_radio2_toggled(GtkRadioButton *c)
// When radio button "Niveau 2" is selected
{
  gboolean T= gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(c));
  if (T)
  {
    choix=2;
  }
}

int on_radio3_toggled(GtkRadioButton *d)
// When radio button "Niveau 3" is selected
{
  gboolean T= gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(d));
  if (T)
  {
    choix=3;
  }
}

int main(int argc, char *argv[])
// Create the UI
{
  gtk_init(&argc, &argv);
  
  builder = gtk_builder_new_from_file ("interface.ui"); // Construct interface from file
  
  window = GTK_WIDGET(gtk_builder_get_object(builder, "window"));
  g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
  
  gtk_builder_connect_signals(builder, NULL);
  
  fixed1 = GTK_WIDGET(gtk_builder_get_object(builder, "fixed1"));
  button1 = GTK_WIDGET(gtk_builder_get_object(builder, "button1"));
  button2 = GTK_WIDGET(gtk_builder_get_object(builder, "button2"));
  button3 = GTK_WIDGET(gtk_builder_get_object(builder, "button3"));
  dark = GTK_WIDGET(gtk_builder_get_object(builder, "dark"));
  label1 = GTK_WIDGET(gtk_builder_get_object(builder, "label1"));
  label2 = GTK_WIDGET(gtk_builder_get_object(builder, "label2"));
  label3 = GTK_WIDGET(gtk_builder_get_object(builder, "label3"));
  file1 = GTK_WIDGET(gtk_builder_get_object(builder,"file1"));
  radio1 = GTK_WIDGET(gtk_builder_get_object(builder, "radio1"));
  radio2 = GTK_WIDGET(gtk_builder_get_object(builder, "radio2"));
  radio3 = GTK_WIDGET(gtk_builder_get_object(builder, "radio3"));
  entry1 = GTK_WIDGET(gtk_builder_get_object(builder, "entry1"));
  entry2 = GTK_WIDGET(gtk_builder_get_object(builder, "entry2"));
  prog1 = GTK_WIDGET(gtk_builder_get_object(builder, "prog1"));
  
  gtk_widget_show(window);
  gtk_widget_hide(entry1);
  gtk_widget_hide(entry2);
  gtk_widget_hide(button3);
  gtk_widget_hide(prog1);
  //gtk_widget_hide(dialog);

	
  gtk_main();

	return EXIT_SUCCESS;
}

void on_button1_clicked(GtkButton *b)
// When button "Chiffrer" is clicked
{
  type=0; // encrypting
  // Display useful information
  gtk_widget_show(entry2); // Target file
  gtk_widget_show(button3); // Execute action button
  gtk_widget_show(prog1); // Progress bar
  if (choix==1) // "Niveau 1" selected
  {
    gtk_widget_hide(entry1); // Hide encryptin key box (key is hardcoded for this method)
    //printf("choix = %d\n",choix);
  }
  if (choix==2) // "Niveau 2" selected
  {
    //printf("choix = %d\n",choix);
    gtk_widget_show(entry1); // Display key-selection box
    
  }
  if (choix==3) // "Niveau 3" selected
  {
    //printf("choix = %d\n",choix);
    gtk_widget_show(entry1); // Display key-selection box
    if(fopen("key.txt","r")==NULL) // Check key file can be opened
    { 
      quick_message(window,"Vous n'avez pas accès à ce fichier"); // Display error message if file cannot be opened
      // Hide dialogs is failure to open key file
      gtk_widget_hide(entry1);
      gtk_widget_hide(entry2);
      gtk_widget_hide(button3);
      gtk_widget_hide(prog1);
    }
    
  } 
  gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(prog1),(gdouble) 0); // Set progress bar to empty
}

void on_button2_clicked(GtkButton *b)
// When button "Déchiffrer" is clicked, same behaviour as for button1
{
  type=1; // decrypting
  gtk_widget_show(entry2);
  gtk_widget_show(button3);
  gtk_widget_show(prog1);
  if (choix==1) // "Niveau 1" is selected
  {
    gtk_widget_hide(entry1);
    //printf("choix = %d\n",choix);
  }
  if (choix==2) // "Niveau 2" is selected
  {
    //printf("choix = %d\n",choix);
    gtk_widget_show(entry1);
  }
  if (choix==3) // "Niveau 3" is selected
  {
    //printf("choix = %d\n",choix);
    gtk_widget_show(entry1);
    if(fopen("key.txt","r")==NULL)
    { 
      quick_message(window,"Vous n'avez pas accès à ce fichier");
      gtk_widget_hide(entry1);
      gtk_widget_hide(entry2);
      gtk_widget_hide(button3);
      gtk_widget_hide(prog1);

    }
    
  } 
  gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(prog1),(gdouble) 0);
}

void on_button3_clicked(GtkButton *b)
// When 'proceed' button is selected
{
  //fopen(name, "w");
  float total=size;
  //printf("total = %d\n",total);
  ok=10;
  while(size>0)
  {
    
    size = size -10;
    if(size<0)
    {
      ok = size+10;
    }
    float state=1-size/total; // Progress bar state
    //printf("div=%f\n",state);
    progress_bar(state); // Display progress bar with state
    //printf("ok=%d\n",ok);
    for(int y=0;y<ok;y++)
    {
        file[y]=fgetc(f);
    }
    if (type==0) // If encrypting
    {
      if (choix==1){cesar_crypt(2,file,name);} // Encrypt with Caesar's cypher
      if (choix==2){poly_crypt(key,file,name);} // Encrypt with polyalphabetic cypher
      if (choix==3)
      {
        int fatkey[256][256];
        FILE *k;
        k= fopen("key.txt","r");
        for (int i = 0; i < 256; i++)
        {
            for (int j = 0; j < 256; j++)
            {
                fatkey[i][j]=fgetc(k);
                //printf("\n[%d][%d]==[%d]\n",i,j,fatkey[i][j]);
                //Sleep(200);
            }
        }
        fclose(k);
        v_decrypt(key,fatkey,file,name); // Encrypt with Vigenere's cypher
      }
    }
    if (type==1) // If decrypting
    {
      if (choix==1){cesar_decrypt(-2,file,name);} // Decrypt with Caesar's cypher
      if (choix==2){poly_decrypt(key,file,name);} // Decrypt with polyalphabetic cypher
      if (choix==3)
      {
          int fatkey[256][256];
          FILE *k;
            k= fopen("key.txt","rb");
            if(k==NULL)
            { 
              gtk_widget_show(dialog);
            }
            for (int i = 0; i < 256; i++)
            {
                for (int j = 0; j < 256; j++)
                {
                    fatkey[i][j]=fgetc(k);
                    //printf("\n[%d][%d]==[%d]\n",i,j,fatkey[i][j]);
                    //Sleep(200);
                }
            }
          fclose(k);
          v_decrypt(key,fatkey,file,name); // Decrypt with Viegenere's cypher
      }
    }
    memset(file,0,sizeof file);
  } 
  gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(prog1),(gdouble) 1.00); // Set progress bar to full
}

void on_file1_file_set (GtkFileChooserButton *file)
// Choose entry file
{
  gtk_widget_hide(entry1);
  gtk_widget_hide(entry2);
  gtk_widget_hide(button3);
  gtk_widget_hide(prog1);
  //printf("I got here");
  char *filename;
  filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(file));
  f=fopen(filename,"rb");
  // Display info about file size
  struct stat st; // same as findSize function
  if(stat(filename,&st)==0){size=st.st_size;}
  //printf("size = %d\n",size);
  char dispsize[100];
  sprintf(dispsize,"%d",size);
  strcat(dispsize," octets");
  gtk_label_set_text (GTK_LABEL(label1),(const char *) "Taille du fichier :");
  gtk_label_set_text (GTK_LABEL(label2),dispsize);
  //printf("I got here\n");
}

void on_entry1_changed(GtkEntry *e)
// When key is entered
{
  sprintf(key,"%s",gtk_entry_get_text(e));
  //printf("entry : %s",name);
}

void on_entry2_changed(GtkEntry *e)
// When target file is entrered
{
  sprintf(name,"%s",gtk_entry_get_text(e));
  //printf("entry : %s",name);
}

void on_dark_toggled(GtkCheckButton *b)
// When dark theme is toggled on/off
{
  gboolean T= gtk_check_menu_item_get_active(GTK_CHECK_MENU_ITEM(b));

    if (T)
    {
      // "dark" (black) theme
      gdk_color_parse ("white", &color);
      gtk_widget_modify_fg (window, GTK_STATE_NORMAL, &color);
      gdk_color_parse ("black", &color);
      gtk_widget_modify_bg (window, GTK_STATE_NORMAL, &color);
    }
    else
    {
      // white theme
      gdk_color_parse ("black", &color);
      gtk_widget_modify_fg (window, GTK_STATE_NORMAL, &color);
      gdk_color_parse ("white", &color);
      gtk_widget_modify_bg (window, GTK_STATE_NORMAL, &color);
    }
}

int findSize(const char *file_name) // unused, directly implemented in code
{
    struct stat st; /*declare stat variable*/
     
    /*get the size using stat()*/
    if(stat(file_name,&st)==0)
        return (st.st_size);
    else
        return -1;
}

void
quick_message (GtkWindow *parent, gchar *message)
// Display message
{
 GtkWidget *dialog, *label5, *content_area;
 GtkDialogFlags flags;

 // Create the widgets
 flags = GTK_DIALOG_DESTROY_WITH_PARENT;
 dialog = gtk_dialog_new_with_buttons ("Attention !",
                                       parent,
                                       flags,
                                       ("_OK"),
                                       GTK_RESPONSE_NONE,
                                       NULL);
 content_area = gtk_dialog_get_content_area (GTK_DIALOG (dialog));
 label5 = gtk_label_new (message);

 // Ensure that the dialog box is destroyed when the user responds

 g_signal_connect_swapped (dialog,
                           "response",
                           G_CALLBACK (gtk_widget_destroy),
                           dialog);

 // Add the label, and show everything we’ve added

 gtk_container_add (GTK_CONTAINER (content_area), label5);
 gtk_widget_show_all (dialog);
}
