#include <gtk/gtk.h>

typedef struct {
    GtkStack *stack;
    GtkWidget *export_radio;
} ConfigData;

void on_back_to_config(GtkButton* button, gpointer user_data) {
    GtkStack *stack = GTK_STACK(user_data);
    gtk_stack_set_visible_child_name(stack, "config");
}

void on_generate_clicked(GtkButton* button, gpointer user_data) {
    ConfigData *data = (ConfigData*)user_data;
    gboolean is_export = gtk_check_button_get_active(GTK_CHECK_BUTTON(data->export_radio));
    
    if(is_export) {
        gtk_stack_set_visible_child_name(data->stack, "export");
    } else {
        gtk_stack_set_visible_child_name(data->stack, "problems");
    }
}

GtkWidget* create_config_page(GtkStack *stack) {
    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_box_set_homogeneous(GTK_BOX(vbox), TRUE);

    // 创建单选按钮组
    GtkWidget *export_radio = gtk_check_button_new_with_label("导出到Word");
    GtkWidget *do_radio = gtk_check_button_new_with_label("直接做题");
    gtk_check_button_set_group(GTK_CHECK_BUTTON(do_radio), GTK_CHECK_BUTTON(export_radio));

    // 创建生成按钮
    GtkWidget *generate_btn = gtk_button_new_with_label("生成题目");
    
    // 准备回调数据
    ConfigData *data = g_new(ConfigData, 1);
    data->stack = stack;
    data->export_radio = export_radio;

    // 连接信号
    g_signal_connect_data(generate_btn, "clicked", 
                         G_CALLBACK(on_generate_clicked),
                         data,
                         (GClosureNotify)g_free, 0);

    // 组装界面
    gtk_box_append(GTK_BOX(vbox), export_radio);
    gtk_box_append(GTK_BOX(vbox), do_radio);
    gtk_box_append(GTK_BOX(vbox), generate_btn);

    return vbox;
}

GtkWidget* create_problems_page(GtkStack *stack) {
    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_box_set_homogeneous(GTK_BOX(vbox), TRUE);

    GtkWidget *label = gtk_label_new("题目显示区域（待实现）");
    GtkWidget *back_btn = gtk_button_new_with_label("返回配置");

    g_signal_connect(back_btn, "clicked", G_CALLBACK(on_back_to_config), stack);

    gtk_box_append(GTK_BOX(vbox), label);
    gtk_box_append(GTK_BOX(vbox), back_btn);

    return vbox;
}

GtkWidget* create_export_page(GtkStack *stack) {
    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_box_set_homogeneous(GTK_BOX(vbox), TRUE);

    GtkWidget *label = gtk_label_new("导出选项设置（待实现）");
    GtkWidget *back_btn = gtk_button_new_with_label("返回配置");

    g_signal_connect(back_btn, "clicked", G_CALLBACK(on_back_to_config), stack);

    gtk_box_append(GTK_BOX(vbox), label);
    gtk_box_append(GTK_BOX(vbox), back_btn);

    return vbox;
}

void activate(GtkApplication* app, gpointer user_data) {
    GtkWidget *window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "数学题生成器");
    gtk_window_set_default_size(GTK_WINDOW(window), 800, 600);

    // 创建页面容器
    GtkWidget *stack = gtk_stack_new();
    gtk_stack_set_transition_type(GTK_STACK(stack), GTK_STACK_TRANSITION_TYPE_SLIDE_LEFT);

    // 创建各页面
    GtkWidget *config_page = create_config_page(GTK_STACK(stack));
    GtkWidget *problems_page = create_problems_page(GTK_STACK(stack));
    GtkWidget *export_page = create_export_page(GTK_STACK(stack));

    // 添加页面到stack
    gtk_stack_add_named(GTK_STACK(stack), config_page, "config");
    gtk_stack_add_named(GTK_STACK(stack), problems_page, "problems");
    gtk_stack_add_named(GTK_STACK(stack), export_page, "export");

    // 设置默认显示页面
    gtk_stack_set_visible_child_name(GTK_STACK(stack), "config");

    gtk_window_set_child(GTK_WINDOW(window), stack);
    gtk_widget_show(window);
}

int main(int argc, char** argv) {
    GtkApplication *app = gtk_application_new("org.example.mathexam", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
    int status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);
    return status;
}