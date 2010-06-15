/* ######################################################################
 * # This programm is a demo of a GtkNotebook. Each Tab is an example   #
 * # of different GtkContainer types                                    #
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
   GtkWidget *label;
   GtkWidget *expander;
   GtkWidget *exp_label;
   GtkWidget *table;
   GtkWidget *nlabel;
   GtkWidget *name;
   GtkWidget *handle;
   GtkWidget *hlabel;
   GtkWidget *hbox;
   GtkWidget *vbox;
   GtkWidget *hpaned;
   GtkWidget *button1;
   GtkWidget *button2;
   gchar *lname;

   gtk_init (&argc, &argv);

   window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
   gtk_window_set_title (GTK_WINDOW (window), "My notebook demo with Container examples");
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

   
   /* TAB 1: Expander. */
   expander = gtk_expander_new_with_mnemonic ("Click here and discover what an exapander can do...!");
   exp_label = gtk_label_new ("curious like a cat! (o;");
   gtk_container_add (GTK_CONTAINER (expander), exp_label);      

   label = gtk_label_new (lname = (g_strdup_printf ("Expander")));
   gtk_notebook_append_page (GTK_NOTEBOOK (notebook), expander, label);
   g_free(lname);

   /* TAB 2: Table. */
   table = gtk_table_new (2, 2, TRUE);
   nlabel = gtk_label_new ("How are you today?: ");
   name = gtk_entry_new ();
 
   gtk_table_attach (GTK_TABLE (table), nlabel, 0, 1, 1, 2,
                     GTK_EXPAND, GTK_SHRINK, 0, 0);
   gtk_table_attach (GTK_TABLE (table), name, 1, 2, 1, 2,
                     GTK_EXPAND, GTK_SHRINK, 0, 0);
 
   gtk_table_set_row_spacings (GTK_TABLE (table), 5);
   gtk_table_set_col_spacings (GTK_TABLE (table), 5);
  
   label = gtk_label_new (lname = (g_strdup_printf ("Table")));
   gtk_notebook_append_page (GTK_NOTEBOOK (notebook), table, label);
   g_free(lname);

   /* TAB 3: Handle Box. */
   handle = gtk_handle_box_new ();
   hlabel = gtk_label_new ("Free me from this small space!!");
   gtk_container_add (GTK_CONTAINER (handle), hlabel);

   gtk_handle_box_set_shadow_type (GTK_HANDLE_BOX (handle), GTK_SHADOW_ETCHED_IN);
   gtk_handle_box_set_handle_position (GTK_HANDLE_BOX (handle), GTK_POS_LEFT);
   gtk_handle_box_set_snap_edge (GTK_HANDLE_BOX (handle), GTK_POS_TOP);

   label = gtk_label_new (lname = (g_strdup_printf ("Handle Box")));
   gtk_notebook_append_page (GTK_NOTEBOOK (notebook), handle, label);
   g_free(lname);

   /* TAB 4: Paned. */
   hpaned = gtk_hpaned_new ();
   button1 = gtk_button_new_with_label ("Make me");
   button2 = gtk_button_new_with_label ("bigger or smaller!");
 
   g_signal_connect_swapped (G_OBJECT (button1), "clicked",
                             G_CALLBACK (gtk_widget_destroy),
                             (gpointer) notebook);
   g_signal_connect_swapped (G_OBJECT (button2), "clicked",
                             G_CALLBACK (gtk_widget_destroy),
                             (gpointer) notebook);
 
   gtk_paned_pack1 (GTK_PANED (hpaned), button1, FALSE, FALSE);
   gtk_paned_pack2 (GTK_PANED (hpaned), button2, FALSE, TRUE);

   label = gtk_label_new (lname = (g_strdup_printf ("Paned")));
   gtk_notebook_append_page (GTK_NOTEBOOK (notebook), hpaned, label);
   g_free(lname);

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
