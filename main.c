#include <gtk/gtk.h>
#include <webkit2/webkit2.h>
#include <string.h>

WebKitWebView *webView;
//-----------------------------main window
GtkWidget *main_window;
GtkWidget *home_button;
GtkWidget *refresh_button;
GtkWidget *back_button;
GtkWidget *headerBar;
GtkWidget *box1;
//-----------------------------window exit
GtkWidget *exit_window;
GtkWidget *box2;
GtkWidget *box3;
GtkWidget *pass_entry;
GtkWidget *pass_button;
GtkWidget *cancel_button;

static gboolean
decide_policy_cb (WebKitWebView *webView,
                  WebKitPolicyDecision *decision,
                  WebKitPolicyDecisionType type)
{
    switch (type) {
    case WEBKIT_POLICY_DECISION_TYPE_NAVIGATION_ACTION:
        //WebKitNavigationPolicyDecision *navigation_decision = WEBKIT_NAVIGATION_POLICY_DECISION (decision);
        /* Make a policy decision here. */
        g_print("Abriendo link\n");
        break;
    case WEBKIT_POLICY_DECISION_TYPE_NEW_WINDOW_ACTION:
        //WebKitNavigationPolicyDecision *navigation_decision = WEBKIT_NAVIGATION_POLICY_DECISION (decision);
        /* Make a policy decision here. */
        g_print("Abriendo ventana\n");
        const gchar *aki = webkit_web_view_get_uri (webView);
        //const gchar *aki2 = webkit_web_view_load_html(webView, gchar *conte, NULL);
        g_print("%s\n", aki);

        break;
    case WEBKIT_POLICY_DECISION_TYPE_RESPONSE:
        //WebKitResponsePolicyDecision *response = WEBKIT_RESPONSE_POLICY_DECISION (decision);
        /* Make a policy decision here. */
        g_print("No estamos seguros\n");
        break;
    default:
        /* Making no decision results in webkit_policy_decision_use(). */
        return FALSE;
    }
    return TRUE;
}

gint
delete_event( GtkWidget *widget,
                   GdkEvent  *event,
                   gpointer   data )
{
        g_print ("delete event occurred\n");
        gtk_widget_show_all (exit_window);
        return TRUE;
}

void
destroy( GtkWidget *widget,
            gpointer   data )
{
        gtk_main_quit ();
}

void
on_pass_button_clicked (GtkWidget *widget,
                            gpointer data)
{
    gchar pass[] = "123";
    const gchar *entry_text;
    entry_text = gtk_entry_get_text (GTK_ENTRY(data));

    int check = !strcmp(entry_text, pass);

    if (check == 1)
    {
        gtk_main_quit ();
    }
}

void
hide_window ()
{
    gtk_widget_hide(exit_window);
}

void
go_home ()
{
    webkit_web_view_load_uri (webView, "http://google.com/");
  //system("thunar");
}

void
refresh ()
{
    webkit_web_view_reload (webView);
}

void
go_back ()
{
    webkit_web_view_go_back (webView);
}

int
main (int argc, char *argv[])
{
    gtk_init (&argc, &argv);

    webView = WEBKIT_WEB_VIEW(webkit_web_view_new());
    main_window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    headerBar = gtk_header_bar_new ();
    box1 = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
    home_button = gtk_button_new_with_label ("Principal");
    refresh_button = gtk_button_new_with_label ("Recargar");
    back_button = gtk_button_new_with_label ("Atras");

    g_signal_connect (G_OBJECT (main_window), "delete_event", G_CALLBACK (delete_event), NULL);
    //g_signal_connect (main_window, "destroy", G_CALLBACK (destroy), NULL);
    g_signal_connect (exit_window, "delete_event", G_CALLBACK (gtk_widget_hide), NULL);
    g_signal_connect (home_button, "clicked", G_CALLBACK (go_home), NULL);
    g_signal_connect (refresh_button, "clicked", G_CALLBACK (refresh), NULL);
    g_signal_connect (back_button, "clicked", G_CALLBACK (go_back), NULL);


    gtk_header_bar_set_title (GTK_HEADER_BAR (headerBar), "MuniSatipo");
    gtk_header_bar_pack_start (GTK_HEADER_BAR (headerBar), home_button);
    gtk_header_bar_pack_start (GTK_HEADER_BAR (headerBar), refresh_button);
    gtk_header_bar_pack_start (GTK_HEADER_BAR (headerBar), back_button);

    gtk_window_set_decorated (GTK_WINDOW (main_window), FALSE);
    gtk_header_bar_set_show_close_button (GTK_HEADER_BAR(headerBar), TRUE);

    gtk_box_pack_start (GTK_BOX(box1),headerBar,FALSE,FALSE,0);
    gtk_box_pack_start (GTK_BOX(box1),GTK_WIDGET (webView), TRUE, TRUE, 0);
    gtk_container_add (GTK_CONTAINER (main_window), GTK_WIDGET (box1));

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
    gtk_window_set_transient_for(GTK_WINDOW(exit_window),GTK_WINDOW(main_window));
    g_signal_connect (webView, "decide-policy", G_CALLBACK (decide_policy_cb), NULL);

    webkit_web_view_load_uri (webView, "http://munisatipo.gob.pe/index.php/23-ordenanza-municipal");
    //gtk_window_maximize (GTK_WINDOW(main_window));
    //gtk_window_fullscreen (GTK_WINDOW(main_window));
    gtk_window_set_default_size (GTK_WINDOW(main_window),800,800);
    gtk_widget_show_all (main_window);

    gtk_main ();

    return 0;
}
