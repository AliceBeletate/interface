#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <locale.h>
#include <time.h>

#define MAX_PRODUTOS 100

struct Produto {
    int codigo;
    char nome[50];
    char descricao[100];
    int quantidade;
    float precoUnitario;
    char dataValidade[11];
};

int totalProdutos = 0;
struct Produto estoque[MAX_PRODUTOS];

GtkWidget *entry_codigo;
GtkWidget *entry_nome;
GtkWidget *entry_descricao;
GtkWidget *entry_quantidade;
GtkWidget *entry_preco;
GtkWidget *entry_data;

void salvar_produto(GtkWidget *widget, gpointer data) {
    if (totalProdutos >= MAX_PRODUTOS) {
        printf("Limite de produtos atingido!\n");
        return;
    }

    struct Produto novo_produto;
    novo_produto.codigo = atoi(gtk_entry_get_text(GTK_ENTRY(entry_codigo)));
    strcpy(novo_produto.nome, gtk_entry_get_text(GTK_ENTRY(entry_nome)));
    strcpy(novo_produto.descricao, gtk_entry_get_text(GTK_ENTRY(entry_descricao)));
    novo_produto.quantidade = atoi(gtk_entry_get_text(GTK_ENTRY(entry_quantidade)));
    novo_produto.precoUnitario = atof(gtk_entry_get_text(GTK_ENTRY(entry_preco)));
    strcpy(novo_produto.dataValidade, gtk_entry_get_text(GTK_ENTRY(entry_data)));

    estoque[totalProdutos++] = novo_produto;
    printf("Produto adicionado: %s\n", novo_produto.nome);
    gtk_widget_destroy(gtk_widget_get_toplevel(widget));
}

void mostrar_janela_entrada(GtkWidget *widget, gpointer data) {
    GtkWidget *window;
    GtkWidget *grid;
    GtkWidget *button_salvar;

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Entrada de Produto");
    gtk_window_set_default_size(GTK_WINDOW(window), 300, 200);

    grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(window), grid);

    entry_codigo = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), gtk_label_new("Código:"), 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), entry_codigo, 1, 0, 1, 1);

    entry_nome = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), gtk_label_new("Nome:"), 0, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), entry_nome, 1, 1, 1, 1);

    entry_descricao = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), gtk_label_new("Descrição:"), 0, 2, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), entry_descricao, 1, 2, 1, 1);

    entry_quantidade = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), gtk_label_new("Quantidade:"), 0, 3, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), entry_quantidade, 1, 3, 1, 1);

    entry_preco = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), gtk_label_new("Preço Unitário:"), 0, 4, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), entry_preco, 1, 4, 1, 1);

    entry_data = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), gtk_label_new("Data Validade:"), 0, 5, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), entry_data, 1, 5, 1, 1);

    button_salvar = gtk_button_new_with_label("Salvar");
    g_signal_connect(button_salvar, "clicked", G_CALLBACK(salvar_produto), NULL);
    gtk_grid_attach(GTK_GRID(grid), button_salvar, 0, 6, 2, 1);

    g_signal_connect(window, "destroy", G_CALLBACK(gtk_widget_destroy), NULL);
    gtk_widget_show_all(window);
}

int main(int argc, char *argv[]) {
    GtkWidget *window;
    GtkWidget *vbox;
    GtkWidget *button_entrada, *button_saida, *button_editar, *button_excluir, *button_listar;

    gtk_init(&argc, &argv);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Sistema de Estoque");
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 300);

    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    button_entrada = gtk_button_new_with_label("Dar Entrada em Produto");
    g_signal_connect(button_entrada, "clicked", G_CALLBACK(mostrar_janela_entrada), NULL);
    gtk_box_pack_start(GTK_BOX(vbox), button_entrada, TRUE, TRUE, 0);

    button_saida = gtk_button_new_with_label("Registrar Saída de Produto");
    gtk_box_pack_start(GTK_BOX(vbox), button_saida, TRUE, TRUE, 0);

    button_editar = gtk_button_new_with_label("Editar Produto");
    gtk_box_pack_start(GTK_BOX(vbox), button_editar, TRUE, TRUE, 0);

    button_excluir = gtk_button_new_with_label("Excluir Produto");
    gtk_box_pack_start(GTK_BOX(vbox), button_excluir, TRUE, TRUE, 0);

    button_listar = gtk_button_new_with_label("Listar Produtos");
    gtk_box_pack_start(GTK_BOX(vbox), button_listar, TRUE, TRUE, 0);

    gtk_widget_show_all(window);
    gtk_main();

    return 0;
}
