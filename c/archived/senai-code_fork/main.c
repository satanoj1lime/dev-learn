#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_CLIENTES 100
#define MAX_TIPOS_ACAI 10
#define MAX_TIPOS_COMPLEMENTOS 20
#define PRECO_FRETE 10.0 // Preço fixo do frete
#define USUARIO_FUNCIONARIO "funcionario"
#define SENHA_FUNCIONARIO "senha123"
#define MAX_ESTOQUE 20

typedef struct {
    char nome[50];
    char complemento[MAX_TIPOS_COMPLEMENTOS][50];
    float peso;
    int numComplementos;
    char tipoAcai[50];
    char dataPedido[11]; // Formato DD/MM/AAAA
    char endereco[100];
    int entrega; // 1 se entrega, 0 se não
    int formaPagamento; // 1- Cartão de Crédito, 2- Cartão de Débito, 3- Dinheiro, 4- Pix, 5- Cheque
    float precoTotal;
} Cliente;

typedef struct {
    char tipo[50];
    float precoPorKilo;
} Acai;

typedef struct {
    char nome[50];
    float preco;
} Complemento;

typedef struct {
    char nome[50];
    float quantidade; // Alterado para quilos
} ItemEstoque;

Acai tiposAcai[MAX_TIPOS_ACAI] = {
    {"Açaí Tradicional", 25.0},
    {"Açaí com Banana", 30.0},
    {"Açaí com Nutella", 35.0},
    {"Açaí com Frutas Tropicais", 32.0},
    {"Açaí com Granola e Mel", 28.0},
    {"Açaí com Leite Ninho", 33.0},
    {"Açaí com Morango", 31.0},
    {"Açaí com Frutas Secas", 29.0},
    {"Açaí com Paçoca", 34.0},
    {"Açaí Energético", 36.0}
};

Complemento complementos[MAX_TIPOS_COMPLEMENTOS] = {
    {"Granola", 2.0},
    {"Leite Condensado", 3.0},
    {"Frutas Vermelhas", 4.0},
    {"Chocolate", 5.0},
    {"Coco Ralado", 2.5},
    {"Mel", 2.0},
    {"Amendoim", 2.5},
    {"Açaí em Pó", 3.5},
    {"Semente de Chia", 4.0},
    {"Nutella", 5.0},
    {"Doce de Leite", 3.0},
    {"M&M's", 4.0},
    {"Pé de Moleque", 5.0},
    {"Castanha de Caju", 4.5},
    {"Pistache", 6.0},
    {"Biscoito de Chocolate", 3.5},
    {"Groselha", 2.0},
    {"Açúcar Mascavo", 1.5},
    {"Cinnamon", 2.0},
    {"Iogurte Grego", 4.0},
};

Cliente clientes[MAX_CLIENTES];
ItemEstoque estoque[MAX_ESTOQUE] = {
    {"Açaí Tradicional", 100},
    {"Açaí com Banana", 80},
    {"Açaí com Nutella", 50},
    {"Açaí com Frutas Tropicais", 60},
    {"Açaí com Granola e Mel", 70},
    {"Açaí com Leite Ninho", 40},
    {"Açaí com Morango", 90},
    {"Açaí com Frutas Secas", 30},
    {"Açaí com Paçoca", 45},
    {"Açaí Energético", 25},
    {"Granola", 200},
    {"Leite Condensado", 150}
};

int numClientes = 0;
float lucroTotal = 0.0; 
int funcionarioAutenticado = 0; 

// Função para calcular o preço total do pedido
float calcularPreco(float peso, const char* tipo, int numComplementos, int entrega) {
    float preco = 0.0;
    for (int i = 0; i < MAX_TIPOS_ACAI; i++) {
        if (strcmp(tipo, tiposAcai[i].tipo) == 0) {
            preco += peso * tiposAcai[i].precoPorKilo;
        }
    }

    preco += numComplementos * 2.0; // Cada complemento adicional custa R$ 2.0

    if (entrega) {
        preco += PRECO_FRETE; // Adiciona o custo do frete
    }

    return preco;
}

// Função para mostrar o cardápio
void mostrarCardapio() {
    printf("\n--- Cardápio de Açaí ---\n");
    for (int i = 0; i < MAX_TIPOS_ACAI; i++) {
        printf("%d. %s - R$ %.2f por kg\n", i + 1, tiposAcai[i].tipo, tiposAcai[i].precoPorKilo);
    }
}

// Função para mostrar complementos
void mostrarComplementos() {
    printf("\n--- Complementos Disponíveis ---\n");
    for (int i = 0; i < MAX_TIPOS_COMPLEMENTOS; i++) {
        printf("%d. %s - R$ %.2f\n", i + 1, complementos[i].nome, complementos[i].preco);
    }
}

// Função para obter a data do pedido
void obterDataPedido(char *data) {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(data, "%02d/%02d/%04d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
}

// Função para cadastrar cliente
void cadastrarCliente() {
    if (numClientes >= MAX_CLIENTES) {
        printf("Limite de clientes atingido.\n");
        return;
    }

    Cliente novoCliente;
    printf("Nome do cliente: ");
    scanf(" %[^\n]", novoCliente.nome);
    
    mostrarCardapio();
    printf("Escolha o tipo de açaí (1-%d): ", MAX_TIPOS_ACAI);
    int escolha;
    scanf("%d", &escolha);
    
    if (escolha < 1 || escolha > MAX_TIPOS_ACAI) {
        printf("Escolha inválida! Cliente não cadastrado.\n");
        return;
    }
    strcpy(novoCliente.tipoAcai, tiposAcai[escolha - 1].tipo);
    
    printf("Peso do açaí em kg: ");
    scanf("%f", &novoCliente.peso);
    
    // Verifica se há estoque suficiente
    if (estoque[escolha - 1].quantidade < novoCliente.peso) {
        printf("Estoque insuficiente para o açaí escolhido.\n");
        return;
    }

    novoCliente.numComplementos = 0;
    char continuar;
    
    do {
        mostrarComplementos();
        printf("Deseja adicionar um complemento? (s para sim, n para não): ");
        scanf(" %c", &continuar);
        
        if (continuar == 's' || continuar == 'S') {
            printf("Escolha o complemento (1-%d): ", MAX_TIPOS_COMPLEMENTOS);
            int complementoEscolhido;
            scanf("%d", &complementoEscolhido);
            
            if (complementoEscolhido >= 1 && complementoEscolhido <= MAX_TIPOS_COMPLEMENTOS) {
                strcpy(novoCliente.complemento[novoCliente.numComplementos], complementos[complementoEscolhido - 1].nome);
                novoCliente.numComplementos++;
            } else {
                printf("Escolha inválida! Complemento não adicionado.\n");
            }
        }
        
    } while (continuar == 's' || continuar == 'S');
    
    // Obter data do pedido
    obterDataPedido(novoCliente.dataPedido);

    // Informar o valor da entrega
    printf("Taxa de entrega: R$ %.2f\n", PRECO_FRETE);
    
    // Perguntar se deseja entrega
    printf("Deseja entrega na sua casa? (1 para sim, 0 para não): ");
    scanf("%d", &novoCliente.entrega);

    if (novoCliente.entrega) {
        printf("Endereço de entrega: ");
        scanf(" %[^\n]", novoCliente.endereco);
    } else {
        strcpy(novoCliente.endereco, "Retirar no local");
    }

    // Escolher forma de pagamento
    printf("Escolha a forma de pagamento:\n");
    printf("1. Cartão de Crédito\n");
    printf("2. Cartão de Débito\n");
    printf("3. Dinheiro\n");
    printf("4. Pix\n");
    printf("5. Cheque\n");
    printf("Opção: ");
    scanf("%d", &novoCliente.formaPagamento);
    
    // Calcular o preço total
    novoCliente.precoTotal = calcularPreco(novoCliente.peso, novoCliente.tipoAcai, novoCliente.numComplementos, novoCliente.entrega);
    
    // Confirmar pagamento
    char confirmarPagamento;
    printf("Deseja confirmar o pagamento? (s para sim, n para não): ");
    scanf(" %c", &confirmarPagamento);
    
    if (confirmarPagamento == 's' || confirmarPagamento == 'S') {
        printf("Pagamento efetuado!\n");
        lucroTotal += novoCliente.precoTotal; // Atualiza o lucro total
        estoque[escolha - 1].quantidade -= novoCliente.peso; // Subtrai do estoque
        
        // Adiciona o cliente ao sistema
        clientes[numClientes++] = novoCliente;
        printf("Cliente cadastrado com sucesso!\n");
    } else {
        printf("Pagamento não confirmado. Cliente não cadastrado.\n");
    }
}

// Função para mostrar clientes
void mostrarClientes() {
    printf("\n--- Clientes Cadastrados ---\n");
    for (int i = 0; i < numClientes; i++) {
        printf("Cliente %d: %s\n", i + 1, clientes[i].nome);
        printf("Tipo de Açaí: %s, Peso: %.2f kg\n", clientes[i].tipoAcai, clientes[i].peso);
        printf("Complementos: ");
        for (int j = 0; j < clientes[i].numComplementos; j++) {
            printf("%s", clientes[i].complemento[j]);
            if (j < clientes[i].numComplementos - 1) {
                printf(", ");
            }
        }
        printf("\nData do Pedido: %s\n", clientes[i].dataPedido);
        printf("Endereço: %s\n", clientes[i].endereco);
        printf("Forma de Pagamento: %d\n", clientes[i].formaPagamento);
        printf("Preço Total: R$ %.2f\n", clientes[i].precoTotal);
        if (clientes[i].entrega) {
            printf("Taxa de Entrega: R$ %.2f\n", PRECO_FRETE);
        } else {
            printf("Taxa de Entrega: Não se aplica\n");
        }
        printf("\n"); // Adiciona espaçamento entre os clientes
    }
}

// Função para remover um cliente
void removerCliente() {
    if (numClientes == 0) {
        printf("Nenhum cliente cadastrado.\n");
        return;
    }
    
    mostrarClientes();
    printf("Digite o número do cliente a ser removido (1-%d): ", numClientes);
    int index;
    scanf("%d", &index);
    
    if (index < 1 || index > numClientes) {
        printf("Número inválido! Nenhum cliente removido.\n");
        return;
    }

    // Move todos os clientes uma posição para cima
    for (int i = index - 1; i < numClientes - 1; i++) {
        clientes[i] = clientes[i + 1];
    }
    numClientes--;
    printf("Cliente removido com sucesso!\n");
}

// Função para login do funcionário
void loginFuncionario() {
    char usuario[50];
    char senha[50];

    printf("Usuário: ");
    scanf(" %[^\n]", usuario);
    printf("Senha: ");
    scanf(" %[^\n]", senha);

    if (strcmp(usuario, USUARIO_FUNCIONARIO) == 0 && strcmp(senha, SENHA_FUNCIONARIO) == 0) {
        funcionarioAutenticado = 1;
        printf("Login efetuado com sucesso!\n");
    } else {
        printf("Usuário ou senha inválidos!\n");
    }
}

// Função para mostrar lucro total
void mostrarLucroTotal() {
    printf("Lucro total acumulado: R$ %.2f\n", lucroTotal);
}

// Função para mostrar estoque
void mostrarEstoque() {
    printf("\n--- Estoque ---\n");
    for (int i = 0; i < MAX_ESTOQUE; i++) {
        if (estoque[i].quantidade > 0) {
            printf("%s: %.2f kg\n", estoque[i].nome, estoque[i].quantidade);
        }
    }
}

// Função para modificar estoque
void modificarEstoque() {
    printf("\nModificar Estoque:\n");
    for (int i = 0; i < MAX_ESTOQUE; i++) {
        printf("%d. %s: %.2f kg\n", i + 1, estoque[i].nome, estoque[i].quantidade);
    }
    
    printf("Escolha o item para modificar (1-%d): ", MAX_ESTOQUE);
    int escolha;
    scanf("%d", &escolha);
    
    if (escolha < 1 || escolha > MAX_ESTOQUE) {
        printf("Escolha inválida!\n");
        return;
    }

    printf("Quantidade atual: %.2f kg\n", estoque[escolha - 1].quantidade);
    printf("Nova quantidade em kg: ");
    float novaQuantidade;
    scanf("%f", &novaQuantidade);
    estoque[escolha - 1].quantidade = novaQuantidade;
    printf("Estoque atualizado com sucesso!\n");
}

// Função principal
int main() {
    int opcao;
    
    do {
        printf("\n--- Sistema de Açaí ---\n");
        printf("1. Cadastrar Cliente\n");
        printf("2. Mostrar Clientes\n");
        printf("3. Mostrar Cardápio\n");
        printf("4. Remover Cliente\n");
        printf("5. Login Funcionário\n");
        printf("6. Mostrar Lucro Total\n");
        printf("7. Mostrar Estoque\n");
        printf("8. Modificar Estoque\n");
        printf("9. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                cadastrarCliente();
                break;
            case 2:
                mostrarClientes();
                break;
            case 3:
                mostrarCardapio();
                break;
            case 4:
                removerCliente();
                break;
            case 5:
                loginFuncionario();
                break;
            case 6:
                if (funcionarioAutenticado) {
                    mostrarLucroTotal();
                } else {
                    printf("Acesso restrito! Faça login como funcionário primeiro.\n");
                }
                break;
            case 7:
                if (funcionarioAutenticado) {
                    mostrarEstoque();
                } else {
                    printf("Acesso restrito! Faça login como funcionário primeiro.\n");
                }
                break;
            case 8:
                if (funcionarioAutenticado) {
                    modificarEstoque();
                } else {
                    printf("Acesso restrito! Faça login como funcionário primeiro.\n");
                }
                break;
            case 9:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while (opcao != 9);
    
    return 0;
}
