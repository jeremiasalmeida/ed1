print_format.h - Header do arquivo que contém todas as funções relativas a enviar dados para o stdout com formatos. Estes formatos são suportados apenas pelo Bash.
/*
 * Printa texto em bold
 */
void print_bold(char t[]);
/*
 * Printa texto em vermelho
 */
void print_red(char t[]);
/*
 * Printa texto em verde
 */
void print_green(char t[]);
/*
 * Printa texto em amarelo
 */
void print_yellow(char t[]);
/*
 * Printa texto em formato de alerta
 */
void print_alert(char t[]);

movi_functions.h - Header do arquivo que contém todoas as funções relativas a movimentações financeiras.

/*
 * Esta estrutura não pode ser em forma de arvore, pois irá dificultar a saida de dados e calculo
 * do saldo das contas, uma vez que esta estrutura não vai ter muita buscas não vale a pena ser em formato de
 * arvore binária de busca
 */
struct movi
{
    int id; //controle interno
    char tipo[1]; // Tipo da movimentação (Deposito,Saque, Transferencia)
    float valor; //Valor da movimentação
    struct movi* proximo; //Proximo item da lista
};


/*
 * insere uma nova movimentação a uma lista dada
 */
struct movi* newMovi(char tipo[], float valor);

/*
 * insere uma nova movimentação a uma lista dada
 */
extern void insertMovi(struct movi** root,struct movi* novo);

/*
 * Printa a movimentação de uma lista dada.
 */
extern void print_movi(struct movi* root);

/*
 * Faz a coleta das informacoes necessarias para uma nova movimentacao
 */
extern struct movi* getData_movi();
/*
 * Cria uma nova struct movi* com tipo de deposito
 */
extern struct movi* newDeposito(float valor);
/*
 * Retornar a data atual
 */
extern struct tm* getDateAtual();
/*
 * Limpa uma lista
 */
extern void clearMovi(struct movi* root);
/*
 * Cria uma movimentação de saque
 */
extern struct movi* newSaque(float valor);
/*
 * Retornar struct movi* com tipo de transferencia
 */
extern struct movi* transferencia();
/*
 * Retornar a última struct movi* de uma lista
 */
extern struct movi* getLastMovi(struct movi* root);

input_functions.h - Header para o arquivo que contém as funções relativas a pegar dados do stdin. Todas feitas de forma a criar um buffer para que seja colocado todo o dados digitado e depois convertido para o tipo esperado, desta forma retornando quantos matchs foram possíveis e alterando o valor da variável de destino.
/*
 * Captura strings do stdin
 */
int getInutChar(char *target);

/*
 * Captura inteiros do stdin
 */
int getInutInt(int *target);
/*
 * Captura floats do stdin
 */
int getInutFloat(float *target);
/*
 * Captura Strings do stdin
 */
int getInutString(char target[]);

cc_function.h Header para o arquivo que contém todas as funções para implementação das contas dos usuários.

struct cc
{
    int id, altura; // campos de controle
    float saldo_atual, ultima_valor; // campos float para valores
    char nome[40], senha[6], cpf[12], rg[10], tipo_conta[1], ultima_tipo[1], status[1]; // campos chars
    struct tm *nascimento, *abertura, *ultima_data; //campos de datas
    struct cc* esquerda, *direita; // ligações da arvore de contas
    struct movi* raiz; //lista encadeada simplesmente ligada de todas as movimentações da conta.
};

/*
 * Helper para trazer o maior valor entre dois inteiros
 */
extern int max(int a, int b);

/*
 * Retorna a altura de uma arvore.
 */
extern int height(struct cc* N);

/*
 * Função para printar na tela em pre-orderm a arvore de contas correntes.
 */
extern void preOrder(struct cc* root);

/*
 * Faz toda a rotina de inserção de um novo item na arvore de contas correntes.
 * Também cuida para que a após a inserção a arvore permaneça balanceada.
 */
extern struct cc* insert(struct cc* node, struct cc* new, int id);

/*
 * Esta função tem a finalidade de funcionar como um 'model' dos dados de uma conta corrente. Ela terá que saber:
 * Quais dados uma conta corrente precisa possuir;
 * Validar os dados de entrada do usuário;
 * Fazer as devidas chamadas para funções que saibam criar pontos e que fazer a inserção na arvore;
 */
extern struct cc* getData();

/*
 * Retornar o valor de balanceamento de um ponto.
 */
extern int getBalance(struct cc* N);

/*
 * Faz a rotação a esquerda de uma arvore.
 */
extern struct cc* leftRotate(struct cc* x);

/*
 * Faz a rotação a direita de uma arvore
 */
extern struct cc* rightRotate(struct cc* y);

/*
  * Cria uma nova cc para ser adicionada a arvore.
 * Com esta centralização da criação de itens cc é possivel controlar prever o comportamento de todos os itens
 * da struct cc
 */
extern struct cc* findById(struct cc* node, int id);
//Cria um novo node do tipo struct cc*
extern struct cc* newNode();
//Procura o maior id da arvore de contas
extern int getMaiorId(struct cc* root);
//Procura ids que possam ser reutilizados, ao encontrar o primeiro irá retornar o mesmo.
extern int getReUsebleId(struct cc* root);
//procura o proximo id para cadastro de conta, utilizando as as funções getReUsebleId e getMaiorId para definir qual vai ser o id retornado.
extern int findNextId(struct cc* root);
//Manda para o stdout informações relativas a conta selecionada
extern void printCcdata(struct cc* root,int id);
//Abre a possibilidade de edição de uma conta
extern void alterCCdata(struct cc* node);




