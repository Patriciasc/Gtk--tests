/* ######################################################################
 * # This programm is a demo of a GtkNotebook. Each tab will have       # 
 * # a number and the user has the option of navigating forwards or     #
 * # backwards through them.                                            #
 * #                                                                    #
 * # Datum: 14.06.10                                                    #
 * # Created by: Patricia Santana Cruz                                  #
 * ######################################################################*/

#include <gtk/gtk.h>
#include <stdio.h>

#define MAX_PAGE 9
#define MIN_PAGE 0

static void previous_tab (GtkButton *button, GtkNotebook *notebook);
static void next_tab (GtkButton *button, GtkNotebook *notebook);

int main (int argc,
          char *argv[])
{
   GtkWidget *window;
   GtkWidget *notebook;
   GtkWidget *prev_button;
   GtkWidget *next_button;
   GtkWidget *close_button;
   GtkWidget *hbox;
   GtkWidget *vbox;
   guint i;

   gtk_init (&argc, &argv);

   window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
   gtk_window_set_title (GTK_WINDOW (window), "My notebook demo");
   gtk_container_set_border_width (GTK_CONTAINER (window), 10);
   gtk_widget_set_size_request (window, 400, 300);
   g_signal_connect (G_OBJECT (window), "destroy",
                     G_CALLBACK (gtk_main_quit), NULL);

   notebook = gtk_notebook_new ();

   next_button = gtk_button_new_with_mnemonic ("_Next");
   g_signal_connect (G_OBJECT (next_button), "clicked",
                     G_CALLBACK (next_tab), 
                     (gpointer) notebook);

   prev_button = gtk_button_new_with_mnemonic ("_Previous");
   g_signal_connect (G_OBJECT (prev_button), "clicked",
                     G_CALLBACK (previous_tab), 
                     (gpointer) notebook);

   close_button = gtk_button_new_with_mnemonic ("_Exit");
   g_signal_connect_swapped (G_OBJECT (close_button), "clicked",
                     G_CALLBACK (gtk_widget_destroy), 
                     (gpointer) window);

   for (i=MIN_PAGE; i<=MAX_PAGE; i++)
   {
      GtkWidget *label;
      GtkWidget *expander;
      GtkWidget *exp_label;
      gchar *lname;
   
      expander = gtk_expander_new_with_mnemonic ("Click here and discover more...!");
      exp_label = gtk_label_new ("curious like a cat! (o;");
      gtk_container_add (GTK_CONTAINER (expander), exp_label);      

      label = gtk_label_new (lname = (g_strdup_printf ("Tab%i", i+1)));
      gtk_notebook_append_page (GTK_NOTEBOOK (notebook), expander, label);
      g_free(lname);
   }

   gtk_notebook_set_scrollable (GTK_NOTEBOOK (notebook), TRUE);

   hbox = gtk_hbox_new (FALSE, 5);
   gtk_box_pack_end (GTK_BOX (hbox), close_button, FALSE, FALSE, 10);
   gtk_box_pack_end (GTK_BOX (hbox), next_button, FALSE, FALSE, 10);
   gtk_box_pack_end (GTK_BOX (hbox), prev_button, FALSE, FALSE, 10);

   vbox = gtk_vbox_new (FALSE, 5);
   gtk_box_pack_start (GTK_BOX (vbox), notebook, TRUE, TRUE, 10);
   gtk_box_pack_start (GTK_BOX (vbox), hbox, TRUE, FALSE, 10);

   gtk_container_add (GTK_CONTAINER (window), vbox);
   gtk_widget_show_all (window);

   gtk_main ();
   return 0;
}

/* Move to the previous tab in the notebook. */
static void
previous_tab (GtkButton *button,
              GtkNotebook *notebook)
{
   if (gtk_notebook_get_current_page (notebook) == MIN_PAGE)
      gtk_notebook_set_current_page (notebook, MAX_PAGE);
   else
      gtk_notebook_prev_page (notebook);
} 

/* Move to the next tab in the notebook. */
static void
next_tab (GtkButton *button,
          GtkNotebook *notebook)
{
   if (gtk_notebook_get_current_page (notebook) == MAX_PAGE)
      gtk_notebook_set_current_page (notebook, MIN_PAGE);
   else
      gtk_notebook_next_page (notebook);
}
