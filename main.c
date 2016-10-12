#include <gtk/gtk.h>
#include <webkit2/webkit2.h>

GtkWidget *window;
GtkWidget *home_button;
GtkWidget *refresh_button;
GtkWidget *back_button;
GtkWidget *headerBar;
GtkWidget *box;

GtkWidget *exit_window;
GtkWidget *box2;
GtkWidget *box3;
GtkWidget *pass_entry;
GtkWidget *pass_button;
GtkWidget *cancel_button;

WebKitWebView *webView;



gint delete_event( GtkWidget *widget,
                   GdkEvent  *event,
                   gpointer   data )
{
        g_print ("delete event occurred\n");
        gtk_widget_show_all (exit_window);
        return TRUE;
}

void destroy( GtkWidget *widget, gpointer   data )
{
        gtk_main_quit ();
}
//static void go_home (GtkWidget *widget, gpointer   data)
//{
//  webkit_web_view_load_uri (webView, "http://www.google.com/");
//}

void on_pass_button_clicked (GtkWidget *widget, gpointer data)
{
    gchar pass[] = "123";
    const gchar *entry_text;
    entry_text = gtk_entry_get_text (GTK_ENTRY(data));
    g_print("%s\n",entry_text);
    g_print("%s\n",pass);

    if (!strcmp(entry_text, pass))
    {
    printf("Cumple\n");
    gtk_main_quit ();
    }
}

static void hide_window ()
{
    gtk_widget_hide(exit_window);
}

static void go_home ()
{
  webkit_web_view_load_uri (webView, "http://munisatipo.gob.pe/index.php/23-ordenanza-municipal");
  //system("thunar");
}

static void refresh ()
{
    webkit_web_view_reload (webView);
}

static void go_back ()
{
    webkit_web_view_go_back (webView);
}

int main (int argc, char *argv[])
{
    gtk_init (&argc, &argv);

    webView = WEBKIT_WEB_VIEW(webkit_web_view_new());
    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    //exit_window = gtk_window_new (GTK_WINDOW_POPUP);
    headerBar = gtk_header_bar_new ();
    box = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
    home_button = gtk_button_new_with_label ("Principal");
    refresh_button = gtk_button_new_with_label ("Recargar");
    back_button = gtk_button_new_with_label ("Atras");

    g_signal_connect (G_OBJECT (window), "delete_event", G_CALLBACK (delete_event), NULL);
    //g_signal_connect (window, "destroy", G_CALLBACK (destroy), NULL);
    g_signal_connect (exit_window, "delete_event", G_CALLBACK (gtk_widget_hide), NULL);
    g_signal_connect (home_button, "clicked", G_CALLBACK (go_home), NULL);
    g_signal_connect (refresh_button, "clicked", G_CALLBACK (refresh), NULL);
    g_signal_connect (back_button, "clicked", G_CALLBACK (go_back), NULL);


    gtk_header_bar_set_title (GTK_HEADER_BAR (headerBar), "MuniSatipo");
    gtk_header_bar_pack_start (GTK_HEADER_BAR (headerBar), home_button);
    gtk_header_bar_pack_start (GTK_HEADER_BAR (headerBar), refresh_button);
    gtk_header_bar_pack_start (GTK_HEADER_BAR (headerBar), back_button);

    gtk_window_set_decorated (GTK_WINDOW (window), FALSE);
    gtk_header_bar_set_show_close_button (GTK_HEADER_BAR(headerBar), TRUE);

    gtk_box_pack_start (GTK_BOX(box),headerBar,FALSE,FALSE,0);
    gtk_box_pack_start (GTK_BOX(box),GTK_WIDGET (webView), TRUE, TRUE, 0);
    gtk_container_add (GTK_CONTAINER (window), GTK_WIDGET (box));

    exit_window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    box2 = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
    box3 = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0);
    pass_button = gtk_button_new_with_label ("Aceptar");
    cancel_button = gtk_button_new_with_label ("Cancelar");
    pass_entry = gtk_entry_new ();

    g_signal_connect (cancel_button, "clicked", G_CALLBACK (hide_window), NULL);
    g_signal_connect (pass_button, "clicked", G_CALLBACK (on_pass_button_clicked), pass_entry);

    gtk_box_pack_start (GTK_BOX(box2),pass_entry,FALSE,FALSE,0);
    gtk_box_pack_start (GTK_BOX(box2),box3,FALSE,FALSE,0);
    gtk_box_pack_start (GTK_BOX(box3),pass_button,FALSE,FALSE,0);
    gtk_box_pack_start (GTK_BOX(box3),cancel_button,FALSE,FALSE,0);
    gtk_container_add (GTK_CONTAINER (exit_window), GTK_WIDGET (box2));
    //gtk_window_set_position (GTK_WINDOW(exit_window),GTK_WIN_POS_CENTER_ALWAYS);
    gtk_window_set_transient_for(GTK_WINDOW(exit_window),GTK_WINDOW(window));

    go_home();
    //gtk_window_maximize (GTK_WINDOW(window));
    //gtk_window_fullscreen (GTK_WINDOW(window));
    gtk_window_set_default_size (GTK_WINDOW(window),800,800);
    gtk_widget_show_all (window);
//

    gtk_main ();

    return 0;
}
