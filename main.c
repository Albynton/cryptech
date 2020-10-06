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
#include <unistd.h>
#include "crypt1.h"
#include "crypt2.h"
#include "crypt3.h"


int choix=1,size,type,ok=10;
char name[128],key[128],file[11];
FILE *f;
GdkColor color;


GtkWidget     *window;
GtkWidget     *dialog;
GtkWidget     *fixed1;
GtkWidget     *button1;
GtkWidget     *button2;
GtkWidget     *button3;
GtkWidget     *dark;
GtkWidget     *label1;
GtkWidget     *label2;
GtkWidget     *label3;
GtkWidget     *radio1;
GtkWidget     *radio2;
GtkWidget     *radio3;
GtkBuilder    *builder;
GtkWidget     *file1;
GtkWidget     *entry1;
GtkWidget     *prog1;

static gboolean progress_bar(float prog)
{ 
    //gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(prog1),(gdouble) 0);  
    //printf("prog=%f\n",prog);  
    gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(prog1),(gdouble) prog);
    //sleep(1000);
}

int on_radio1_toggled(GtkRadioButton *b)
{
  gboolean T= gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(b));
  if (T)
  {
    choix=1;
  }
}

int on_radio2_toggled(GtkRadioButton *c)
{
  gboolean T= gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(c));
  if (T)
  {
    choix=2;
  }
}

int on_radio3_toggled(GtkRadioButton *d)
{
  gboolean T= gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(d));
  if (T)
  {
    choix=3;
  }
}

int main(int argc, char *argv[])
{
	gtk_init(&argc, &argv);

	builder = gtk_builder_new_from_file ("interface.ui");

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
  prog1 = GTK_WIDGET(gtk_builder_get_object(builder, "prog1"));

	gtk_widget_show(window);
  gtk_widget_hide(entry1);
  gtk_widget_hide(button3);
  gtk_widget_hide(prog1);
  //gtk_widget_hide(dialog);

	
  gtk_main();

	return EXIT_SUCCESS;
}

void on_button1_clicked(GtkButton *b)
{
  type=0;
  gtk_widget_show(button3);
  gtk_widget_show(prog1);
  if (choix==1)
  {
    gtk_widget_hide(entry1);
    //printf("choix = %d\n",choix);
  }
  if (choix==2)
  {
    //printf("choix = %d\n",choix);
    gtk_widget_show(entry1);
    
  }
  if (choix==3)
  {
    //printf("choix = %d\n",choix);
    gtk_widget_show(entry1);
    if(fopen("key.txt","r")==NULL)
    { 
      quick_message(window,"Vous n'avez pas accès à ce produit");
      gtk_widget_hide(entry1);
      gtk_widget_hide(button3);
      gtk_widget_hide(prog1);
    }
    
  } 
  gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(prog1),(gdouble) 0);
}

void on_button2_clicked(GtkButton *b)
{
  type=1;
  gtk_widget_show(button3);
  gtk_widget_show(prog1);
  if (choix==1)
  {
    gtk_widget_hide(entry1);
    //printf("choix = %d\n",choix);
  }
  if (choix==2)
  {
    //printf("choix = %d\n",choix);
    gtk_widget_show(entry1);
  }
  if (choix==3)
  {
    //printf("choix = %d\n",choix);
    gtk_widget_show(entry1);
    if(fopen("key.txt","r")==NULL)
    { 
      quick_message(window,"Vous n'avez pas accès à ce produit");
      gtk_widget_hide(entry1);
      gtk_widget_hide(button3);
      gtk_widget_hide(prog1);

    }
    
  } 
  gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(prog1),(gdouble) 0);
}

void on_button3_clicked(GtkButton *b)
  {
    FILE *fileopen;
    char *filename;
    
    GtkWidget *dialog;
     
     dialog = gtk_file_chooser_dialog_new ("Save File",
     				      window,
     				      GTK_FILE_CHOOSER_ACTION_SAVE,
     				      GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
     				      GTK_STOCK_SAVE, GTK_RESPONSE_ACCEPT,
     				      NULL);
     gtk_file_chooser_set_do_overwrite_confirmation (GTK_FILE_CHOOSER (dialog), TRUE);
     
     /*if (user_edited_a_new_document)
       {
         gtk_file_chooser_set_current_folder (GTK_FILE_CHOOSER (dialog), default_folder_for_saving);
         gtk_file_chooser_set_current_name (GTK_FILE_CHOOSER (dialog), "Untitled document");
       }
     else
       gtk_file_chooser_set_filename (GTK_FILE_CHOOSER (dialog), filename_for_existing_document);
     */
     
     if (gtk_dialog_run (GTK_DIALOG (dialog)) == GTK_RESPONSE_ACCEPT)
       {
         
     
         filename = gtk_file_chooser_get_filename (GTK_FILE_CHOOSER (dialog));
        //name=filename;
        fileopen=fopen(filename,"w");
       }else
       {
          type=2;
          gtk_widget_hide(entry1);
          gtk_widget_hide(button3);
          gtk_widget_hide(prog1);
       }

     gtk_widget_destroy (dialog);
     gtk_widget_destroy (dialog);              
  float total=size;
  //printf("total = %d\n",total);
  //printf("filename : %s\n",filename);
  if(type!=2)
  {
    ok=10;
    while(size>0)
    {
      
      size = size -10;
      if(size<0)
      {
        ok = size+10;
      }
      float state=1-size/total;
      //printf("div=%f\n",state);
      progress_bar(state);
      //printf("ok=%d\n",ok);
      for(int y=0;y<ok;y++)
      {
          file[y]=fgetc(f);
      }
      if (type==0)
      {
        if (choix==1){cesar_crypt(2,file,filename);}
        if (choix==2){poly_crypt(key,file,filename);}
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
          v_normal(key,fatkey,file,filename);  
        }
      }
      if (type==1)
      {
        if (choix==1){cesar_normal(-2,file,filename);}
        if (choix==2){poly_normal(key,file,filename);}
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
            v_normal(key,fatkey,file,filename);
        }
      }
      memset(file,0,sizeof file);
    } 
    gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(prog1),(gdouble) 1.00);
  }
}

void on_file1_file_set (GtkFileChooserButton *file)
{
  gtk_widget_hide(entry1);
  gtk_widget_hide(button3);
  gtk_widget_hide(prog1);
  //printf("I got here");
  char *filename;
  filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(file));
  f=fopen(filename,"rb");
  struct stat st;
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
{
  sprintf(key,"%s",gtk_entry_get_text(e));
  //printf("entry : %s",name);
}

void on_dark_toggled(GtkCheckButton *b)
{
  gboolean T= gtk_check_menu_item_get_active(GTK_CHECK_MENU_ITEM(b));

    if (T)
    {
      gdk_color_parse ("white", &color);
      gtk_widget_modify_fg (window, GTK_STATE_NORMAL, &color);
      gdk_color_parse ("black", &color);
      gtk_widget_modify_bg (window, GTK_STATE_NORMAL, &color);
    }
    else
    {
      gdk_color_parse ("black", &color);
      gtk_widget_modify_fg (window, GTK_STATE_NORMAL, &color);
      gdk_color_parse ("white", &color);
      gtk_widget_modify_bg (window, GTK_STATE_NORMAL, &color);
    }
}

int findSize(const char *file_name)
{
    struct stat st; /*declare stat variable*/
     
    /*get the size using stat()*/
    if(stat(file_name,&st)==0)
        return (st.st_size);
    else
        return -1;
}

void quick_message (GtkWindow *parent, gchar *message)
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
